// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

// 惰性创建 OverlayWidgetController（单例模式）
// 首次调用时 NewObject 并绑定回调，后续直接返回已有实例
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		// 绑定属性变化回调 → Widget 自动刷新
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return OverlayWidgetController;
}


UAttributeMenuWidgetController* AAuraHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

// 由 AuraCharacter::InitAbilityActorInfo 调用，完成 HUD 完整装配流程：
// 1. 创建 Widget
// 2. 创建/获取 WidgetController
// 3. Widget ↔ WidgetController 绑定
// 4. 广播初始值（Health/Mana 等）
// 5. Widget 添加到视口
void AAuraHUD::InitOverlap(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized,please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized,please fill out BP_AuraHUD"));


	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	// 建立 Widget 和 Controller 的双向绑定
	OverlayWidget->SetWidgetController(WidgetController);
	// 立即推送当前属性值到 UI
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();

}