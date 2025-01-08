// Fill out your copyright notice in the Description page of Project Settings.


#include "PMGameStateBase.h"
#include "HackingGameStateComponent.h"

APMGameStateBase::APMGameStateBase()
{
	HackingGameStateComponent = CreateDefaultSubobject<UHackingGameStateComponent>("HackingGameStateComponent");
}

UHackingGameStateComponent* APMGameStateBase::GetHackingGameStateComponent()
{
	return HackingGameStateComponent;
}
