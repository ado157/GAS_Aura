// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include <InterAction/EnemyInterface.h>
AAuraPlayerController::AAuraPlayerController()
{
	// 多人游戏下 PlayerController 仅在 owning client 存在，需标记复制
	bReplicates = true;
}

// 每帧执行光标射线检测，驱动鼠标悬停高亮逻辑
void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	// Enhanced Input 映射上下文注册
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	// 显示鼠标光标，设置为游戏+UI混合输入模式
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeDate;
	InputModeDate.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeDate.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeDate);
}

// 绑定 WASD 移动输入到 Move 回调
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

// WASD → 基于摄像机方向的平面移动
void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotator(0.f, Rotation.Yaw, 0.f);

	const FVector ForWardDirection = FRotationMatrix(YawRotator).GetUnitAxis(EAxis::X);
	const FVector RightDirection= FRotationMatrix(YawRotator).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn=GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForWardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection , InputAxisVector.X);
	}
}

// 鼠标悬停高亮状态机
// 每帧从光标位置射出一条 Visibility 通道射线，命中实现了 IEnemyInterface 的 Actor 则高亮
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit)return;

	LastActor = ThisActor;
	// 尝试将命中 Actor 转为高亮接口指针（未实现则得到 nullptr）
	ThisActor=Cast<IEnemyInterface>(CursorHit.GetActor());

	// 四种状态转移
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// 鼠标移入可高亮对象
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			// 鼠标移出可高亮对象
			LastActor->UnHighlightActor();
		}
		else
		{
			if (LastActor != ThisActor)
			{
				// 鼠标从 A 移到 B
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			// else: 鼠标仍在同一对象上，不做任何操作
		}
	}


}