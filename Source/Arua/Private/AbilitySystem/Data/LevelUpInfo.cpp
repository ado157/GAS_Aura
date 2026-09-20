// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP)const
{
    int Level = 1;
    bool bSearching = true;

    while (bSearching)
    {
        //LevelUpInformation[0]仅占位
        if (LevelUpInformation.Num()-1 < Level)return Level;

        if (XP >= LevelUpInformation[Level].LevelUpRequirment)
        {
            ++Level;
        }
        else {
            bSearching = false;
        }
    }
    return Level;
}
