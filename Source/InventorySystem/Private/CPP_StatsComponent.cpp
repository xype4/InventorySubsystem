// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_StatsComponent.h"

UCPP_StatsComponent::UCPP_StatsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 1.0f;
}

float UCPP_StatsComponent::CalculateResist(EEffectType resist, float ignoreresist)
{
	if (Resists.Contains(resist))
		return (1 - (Resists[resist] * (1 - ignoreresist)));
	else
		return 1.0;
}

bool UCPP_StatsComponent::EffectTick(FEffectAbstract currentEffectAbstract)
{
	switch (currentEffectAbstract.EffectType)
	{
	case EEffectType::CuttingDamage:
		// Режущий урон (Здоровье 100%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * CalculateResist(EEffectType::CuttingResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::PhysicalResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::SlashingDamage:
		// Рубящий урон (Здоровье 100%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * CalculateResist(EEffectType::SlashingResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::PhysicalResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::CrushingDamage:
		// Дробящий урон (Здоровье 100%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * CalculateResist(EEffectType::CrushingResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::PhysicalResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::PiercingDamage:
		// Колющий урон (Здоровье 100%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * CalculateResist(EEffectType::PiercingResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::PhysicalResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::FireDamage:
		// Огненный урон (Здоровье 100%, Выносливость 50%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * CalculateResist(EEffectType::FireResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentStaminaCount -= currentEffectAbstract.EffectPerSecond * 0.5 * CalculateResist(EEffectType::FireResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::IceDamage:
		// Ледяной урон (Здоровье 90%, Выносливость 80%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * 0.9 * CalculateResist(EEffectType::IceResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentStaminaCount -= currentEffectAbstract.EffectPerSecond * 0.8 * CalculateResist(EEffectType::IceResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::LightningDamage:
		// Электрический урон (Здоровье 100%, Мана 50%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * CalculateResist(EEffectType::LightningResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentManaCount -= currentEffectAbstract.EffectPerSecond * 0.5 * CalculateResist(EEffectType::LightningResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::PoisonDamage:
		// обработка ядовитого урона (Здоровье 100%, Ярость 50%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * CalculateResist(EEffectType::PoisonResist, currentEffectAbstract.IgnoreResists);
		CurrentFuryCount -= currentEffectAbstract.EffectPerSecond * 0.5 * CalculateResist(EEffectType::PoisonResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::BleedingDamage:
		// обработка кровотечения (Здоровье 100%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * 1 * CalculateResist(EEffectType::BleedingResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::RadiantDamage:
		// обработка урона светлой магией (Здоровье 50%, Выносливость 55%, Мана 55%, Ярость 55%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * 0.5 * CalculateResist(EEffectType::RadiantResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentStaminaCount -= currentEffectAbstract.EffectPerSecond * 0.55 * CalculateResist(EEffectType::RadiantResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentManaCount -= currentEffectAbstract.EffectPerSecond * 0.55 * CalculateResist(EEffectType::RadiantResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentFuryCount -= currentEffectAbstract.EffectPerSecond * 0.55 * CalculateResist(EEffectType::RadiantResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);

		break;

	case EEffectType::NecroticDamage:
		// обработка некротического урона (Здоровье 70%, Выносливость 35%, Мана 35%, Ярость 35%)
		CurrentHealthCount -= currentEffectAbstract.EffectPerSecond * 0.7 * CalculateResist(EEffectType::RadiantResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentStaminaCount -= currentEffectAbstract.EffectPerSecond * 0.35 * CalculateResist(EEffectType::RadiantResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentManaCount -= currentEffectAbstract.EffectPerSecond * 0.35 * CalculateResist(EEffectType::RadiantResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		CurrentFuryCount -= currentEffectAbstract.EffectPerSecond * 0.35 * CalculateResist(EEffectType::RadiantResist, currentEffectAbstract.IgnoreResists) * CalculateResist(EEffectType::MagicalResist, currentEffectAbstract.IgnoreResists);
		break;

	case EEffectType::ManaRecovery:
		CurrentManaCount += currentEffectAbstract.EffectPerSecond;
		break;

	case EEffectType::FuryRecovery:
		CurrentFuryCount += currentEffectAbstract.EffectPerSecond;
		break;

	case EEffectType::StaminaRecovery:
		CurrentStaminaCount += currentEffectAbstract.EffectPerSecond;
		break;

	case EEffectType::HealthRecovery:
		CurrentHealthCount += currentEffectAbstract.EffectPerSecond;
		break;

	default:
		return false;
	}
	return true;
}

void UCPP_StatsComponent::BeginPlay()
{
	Super::BeginPlay();

	for (auto const &CurrentBaseEffect : BaseEffects)
	{
		PermanentEffectsInstance.Add(FEffectInstance(CurrentBaseEffect, -1.0));
	}

	UpdateAllParams();
}

void UCPP_StatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for(auto& CurrentEffect: PermanentEffectsInstance)
	{
		EffectTick(CurrentEffect.Effect);
	}

	for (auto& CurrentEffect : TepmoraryEffectsInstance)
	{
		EffectTick(CurrentEffect.Effect);
		CurrentEffect.RemainingTime -= 1;
	}

	TepmoraryEffectsInstance.RemoveAll([&](const FEffectInstance& Effect) {
		return Effect.RemainingTime <= 0;
		});

	CurrentHealthCount = FMath::Clamp(CurrentHealthCount, 0, MaxHealthCount);
	CurrentStaminaCount = FMath::Clamp(CurrentStaminaCount, 0, MaxStaminaCount);
	CurrentManaCount = FMath::Clamp(CurrentManaCount, 0, MaxManaCount);
	CurrentFuryCount = FMath::Clamp(CurrentFuryCount, 0, MaxFuryCount);
}


TArray<FEffectInstance> UCPP_StatsComponent::GetAllEffectsByType(EEffectType Type)
{
	TArray<FEffectInstance> AllEffects;

	for(FEffectInstance const& CurrentEffect: PermanentEffectsInstance)
	{
		if (CurrentEffect.Effect.EffectType == Type)
			AllEffects.Add(CurrentEffect);
	}

	for (FEffectInstance const& CurrentEffect : TepmoraryEffectsInstance)
	{
		if (CurrentEffect.Effect.EffectType == Type)
			AllEffects.Add(CurrentEffect);
	}

	return AllEffects;
}

void UCPP_StatsComponent::AddEffect(FEffectAbstract Effect, bool isInfinity)
{
	RemoveEffectByGroup(Effect.EffectGroup);

	if(isInfinity)
	{
		PermanentEffectsInstance.Add(FEffectInstance(Effect, Effect.EffectTime));
	}
	else
	{
		TepmoraryEffectsInstance.Add(FEffectInstance(Effect, Effect.EffectTime));
	}


}

void UCPP_StatsComponent::UpdateAllParams()
{
	CalculateFuryMaxCount();
	CalculateHealthMaxCount();
	CalculateManaMaxCount();
	CalculateStaminaMaxCount();

	CalculateResists();
}

void UCPP_StatsComponent::RemoveEffectByGroup(FString Group)
{
	if(Group!="")
	{
		TepmoraryEffectsInstance.RemoveAll([Group](const FEffectInstance& effect) -> bool
			{
				return effect.Effect.EffectGroup == Group;
			});

		PermanentEffectsInstance.RemoveAll([Group](const FEffectInstance& effect) -> bool
			{
				return effect.Effect.EffectGroup == Group;
			});
	}
}


int UCPP_StatsComponent::CalculateHealthMaxCount()
{
	float currentRatio = (float)CurrentHealthCount / (float)MaxHealthCount;

	int health = 0;
	for(auto const& CurrentEffect: GetAllEffectsByType(EEffectType::HealthIncrease))
	{
		health += round(CurrentEffect.Effect.EffectPerSecond);
	}

	MaxHealthCount = health;
	CurrentHealthCount = MaxHealthCount * currentRatio;

	return health;
}

int UCPP_StatsComponent::CalculateStaminaMaxCount()
{
	float currentRatio = (float)CurrentStaminaCount / (float)MaxStaminaCount;

	int stamina = 0;
	for (auto const& CurrentEffect : GetAllEffectsByType(EEffectType::StaminaIncrease))
	{
		stamina += round(CurrentEffect.Effect.EffectPerSecond);
	}

	MaxStaminaCount = stamina;
	CurrentStaminaCount = MaxStaminaCount * currentRatio;

	return stamina;
}

int UCPP_StatsComponent::CalculateManaMaxCount()
{
	float currentRatio = (float)CurrentManaCount / (float)MaxManaCount;

	int mana = 0;
	for (auto const& CurrentEffect : GetAllEffectsByType(EEffectType::ManaIncrease))
	{
		mana += round(CurrentEffect.Effect.EffectPerSecond);
	}

	MaxManaCount = mana;
	CurrentManaCount = MaxManaCount * currentRatio;

	return mana;
}

int UCPP_StatsComponent::CalculateFuryMaxCount()
{
	float currentRatio = (float)CurrentFuryCount / (float)MaxFuryCount;

	int fury = 0;
	for (auto const& CurrentEffect : GetAllEffectsByType(EEffectType::FuryIncrease))
	{
		fury += round(CurrentEffect.Effect.EffectPerSecond);
	}

	MaxFuryCount = fury;
	CurrentFuryCount = MaxFuryCount * currentRatio;

	return fury;
}

TMap<EEffectType, float> UCPP_StatsComponent::CalculateResists()
{
	TMap<EEffectType, float> ResistsMap;
	ResistsMap.Add(EEffectType::PhysicalResist, 0.f);
	ResistsMap.Add(EEffectType::CuttingResist, 0.f);
	ResistsMap.Add(EEffectType::SlashingResist, 0.f);
	ResistsMap.Add(EEffectType::CrushingResist, 0.f);
	ResistsMap.Add(EEffectType::PiercingResist, 0.f);
	ResistsMap.Add(EEffectType::MagicalResist, 0.f);
	ResistsMap.Add(EEffectType::FireResist, 0.f);
	ResistsMap.Add(EEffectType::IceResist, 0.f);
	ResistsMap.Add(EEffectType::LightningResist, 0.f);
	ResistsMap.Add(EEffectType::RadiantResist, 0.f);
	ResistsMap.Add(EEffectType::NecroticResist, 0.f);
	ResistsMap.Add(EEffectType::PoisonResist, 0.f);
	ResistsMap.Add(EEffectType::BleedingResist, 0.f);

	TArray<FEffectInstance> AllEffects;
	AllEffects.Append(PermanentEffectsInstance);
	AllEffects.Append(TepmoraryEffectsInstance);

	for (FEffectInstance const& CurrentEffect : AllEffects)
	{
		FEffectAbstract currentEffect = CurrentEffect.Effect;
		switch (currentEffect.EffectType)
		{
		case EEffectType::PhysicalResist:
			ResistsMap[EEffectType::PhysicalResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::CuttingResist:
			ResistsMap[EEffectType::CuttingResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::SlashingResist:
			ResistsMap[EEffectType::SlashingResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::CrushingResist:
			ResistsMap[EEffectType::CrushingResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::PiercingResist:
			ResistsMap[EEffectType::PiercingResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::MagicalResist:
			ResistsMap[EEffectType::MagicalResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::FireResist:
			ResistsMap[EEffectType::FireResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::IceResist:
			ResistsMap[EEffectType::IceResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::LightningResist:
			ResistsMap[EEffectType::LightningResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::RadiantResist:
			ResistsMap[EEffectType::RadiantResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::NecroticResist:
			ResistsMap[EEffectType::NecroticResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::PoisonResist:
			ResistsMap[EEffectType::PoisonResist] += currentEffect.EffectPerSecond;
			break;

		case EEffectType::BleedingResist:
			ResistsMap[EEffectType::BleedingResist] += currentEffect.EffectPerSecond;
			break;

		default:
			break;
		}
	}
	for (TTuple<EEffectType, float>& Pair : ResistsMap)
	{
		float& ResistValue = Pair.Value;

		ResistValue = FMath::Clamp(ResistValue, 0.0f, 0.8f);
	}

	Resists = ResistsMap;
	return ResistsMap;
}

