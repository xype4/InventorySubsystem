// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "CPP_StatsComponent.generated.h"

/**
 * @Типы эффектов, применимых к персонажу
 */

UENUM(BlueprintType)
enum class EEffectType : uint8
{
	//Отрицательные эффекты
	// 
	// Режущий урон (Здоровье 100%)
	CuttingDamage       UMETA(DisplayName = "CuttingDamage"),
	// Рубящий урон (Здоровье 100%)
	SlashingDamage      UMETA(DisplayName = "SlashingDamage"),
	// Дробящий урон (Здоровье 100%)
	CrushingDamage      UMETA(DisplayName = "CrushingDamage"),
	// Колющий урон (Здоровье 100%)
	PiercingDamage      UMETA(DisplayName = "PiercingDamage"),

	// Огненный урон (Здоровье 100%, Выносливость 50%)
	FireDamage          UMETA(DisplayName = "FireDamage"),
	// Ледяной урон (Здоровье 90%, Выносливость 80%)
	IceDamage           UMETA(DisplayName = "IceDamage"),
	// Электрический урон (Здоровье 100%, Мана 50%)
	LightningDamage     UMETA(DisplayName = "LightningDamage"),
	// Урон светлой магией (Здоровье 50%, Выносливость 55%, Мана 55%, Ярость 55%)
	RadiantDamage       UMETA(DisplayName = "RadiantDamage"),
	// Некротический урон (Здоровье 70%, Выносливость 35%, Мана 35%, Ярость 35%) 
	NecroticDamage      UMETA(DisplayName = "NecroticDamage"),

	// Ядовитый урон (Здоровье 100%, Ярость 50%)
	PoisonDamage        UMETA(DisplayName = "PoisonDamage"),
	// Кровотечение (Здоровье 100%)
	BleedingDamage      UMETA(DisplayName = "BleedingDamage"),

	//Положительные эффекты
	// 
	// Восстановление маны
	ManaRecovery        UMETA(DisplayName = "ManaRecovery"),
	// Восстановление ярости
	FuryRecovery        UMETA(DisplayName = "FuryRecovery"),
	// Восстановление стамины
	StaminaRecovery     UMETA(DisplayName = "StaminaRecovery"),
	// Восстановление хп
	HealthRecovery      UMETA(DisplayName = "HealthRecovery"),

	// Повышение маны
	ManaIncrease        UMETA(DisplayName = "ManaIncrease"),
	// Повышение стамины
	StaminaIncrease     UMETA(DisplayName = "StaminaIncrease"),
	// Повышение здоровья
	HealthIncrease      UMETA(DisplayName = "HealthIncrease"),
	// Повышение ярости
	FuryIncrease        UMETA(DisplayName = "FuryIncrease"),

	//Защитные эффекты
	
	// Весь физический урон (защита)
	PhysicalResist      UMETA(DisplayName = "PhysicalResist"),
	// Режущий урон (защита)
	CuttingResist       UMETA(DisplayName = "CuttingResist"),
	// Рубящий урон (защита)
	SlashingResist      UMETA(DisplayName = "SlashingResist"),
	// Дробящий урон (защита)
	CrushingResist      UMETA(DisplayName = "CrushingResist"),
	// Колющий урон (защита)
	PiercingResist      UMETA(DisplayName = "PiercingResist"),

	// Весь магический урон (защита)
	MagicalResist       UMETA(DisplayName = "MagicalResist"),
	// Огненный урон (защита)
	FireResist          UMETA(DisplayName = "FireResist"),
	// Ледяной урон (защита)
	IceResist           UMETA(DisplayName = "IceResist"),
	// Электрический урон (защита)
	LightningResist     UMETA(DisplayName = "LightningResist"),
	// Урон светлой магией (защита)
	RadiantResist       UMETA(DisplayName = "RadiantResist"),
	// Некротический урон (защита)
	NecroticResist      UMETA(DisplayName = "NecroticResist"),
	// Ядовитый урон (защита)
	PoisonResist        UMETA(DisplayName = "PoisonResist"),
	// Кровотечение (защита)
	BleedingResist      UMETA(DisplayName = "BleedingResist"),
};

/**
 * @Структура, описывающая действие эффекта
 */

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FEffectAbstract
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Тип эффекта"))
	EEffectType EffectType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Группы для эффектов. При добавлении нового эффекта удаляются все старые эффекты с аналогичной группой (без пробелов и больших букв плз)"))
	FString EffectGroup;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Воздействие эффекта в секунду или в общем, если эффект бесконечный"))
	float EffectPerSecond = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Время эффекта (InFinityEffect = false)"))
	int EffectTime = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ClampMin = 0, UIMin = 0, ClampMax = 1, UIMax = 1, ToolTip = "Эффект игнорирует резисты 0 - режется резистами сильно 1 - не режется резистами вообще"))
	float IgnoreResists = false;

	bool operator==(const FEffectAbstract& Other) const
	{
		bool isTypeEqual = EffectType == Other.EffectType;
		bool isEffectPerSecondEqual = FMath::IsNearlyEqual(EffectPerSecond, Other.EffectPerSecond, 0.0001f);
		bool isEffectTimeEqual = EffectTime == Other.EffectTime;
		bool isIgnoreResistsEqual = FMath::IsNearlyEqual(IgnoreResists, Other.IgnoreResists, 0.0001f);

		return isTypeEqual && isEffectPerSecondEqual && isEffectTimeEqual && isIgnoreResistsEqual;
	}

	bool operator!=(const FEffectAbstract& Other) const
	{
		return !(*this == Other);
	}
};

/**
 * @Структура, описывающая конкретный работающий эффект и его оставшееся время действия
 */

USTRUCT(BlueprintType)
struct INVENTORYSYSTEM_API FEffectInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Эффект"))
	FEffectAbstract Effect;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Config", meta = (ToolTip = "Оставшееся время эффекта"))
	int RemainingTime;

	FEffectInstance(const FEffectAbstract& InEffect, int InRemainingTime)
		: Effect(InEffect), RemainingTime(InRemainingTime)
	{
	}

	FEffectInstance()
		: RemainingTime(0)
	{
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORYSYSTEM_API UCPP_StatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCPP_StatsComponent();

public:
	

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Config", meta = (ToolTip = "Базовые эффекты (реген характеристих и тд)"))
	TArray<FEffectAbstract> BaseEffects;


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "StatsComponent|Get", meta = (ToolTip = "Получение списка активных эффектов по типу"))
	TArray<FEffectInstance> GetAllEffectsByType(EEffectType Type);

	UFUNCTION(BlueprintCallable, Category = "StatsComponent|Add", meta = (ToolTip = "Добавить новый эффект. isInfinity - добавится в массив постоянных эффектов и будет активен пока не произойдёт удаление в ручную"))
	void AddEffect(FEffectAbstract Effect, bool isInfinity);

	UFUNCTION(BlueprintCallable, Category = "StatsComponent|Add", meta = (ToolTip = "Обновление максимальных значений параметров и резистов"))
	void UpdateAllParams();

	UFUNCTION(BlueprintCallable, Category = "StatsComponent", meta = (ToolTip = "Удалить эффект по группе"))
	void RemoveEffectByGroup(FString Group);

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Config", meta = (ToolTip = "Базовые эффекты (реген характеристих и тд)"))
	int CurrentHealthCount = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Config", meta = (ToolTip = "Базовые эффекты (реген характеристих и тд)"))
	int CurrentStaminaCount = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Config", meta = (ToolTip = "Базовые эффекты (реген характеристих и тд)"))
	int CurrentManaCount = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Config", meta = (ToolTip = "Базовые эффекты (реген характеристих и тд)"))
	int CurrentFuryCount = 1;

protected:

	

	int MaxHealthCount = 1;
	int MaxStaminaCount = 1;
	int MaxManaCount = 1;
	int MaxFuryCount = 1;
	//Расчёт текущего максимального значения параметров, записывается в Max...Count и возвращается. Соотношение Параметр/Максимальное значение сохраняется
	int CalculateHealthMaxCount();
	int CalculateStaminaMaxCount();
	int CalculateManaMaxCount();
	int CalculateFuryMaxCount();


	//Списое резистов, для пересчёта используется CalsulateResists()
	TMap<EEffectType, float> Resists;
	//Расчёт резистов, результат записывается в Resists и возвращается
	TMap<EEffectType, float> CalculateResists();



	//Список инстансов постоянных(без фиксированного времени дейсвтия) эффектов Базовых, Экипировки и Навыков (не отображаься на панеле эффектов)
	TArray<FEffectInstance> PermanentEffectsInstance;

	//Список инстансов временных(с фиксированным временем дейсвтия) эффектов от событий
	TArray<FEffectInstance> TepmoraryEffectsInstance;

	//Попытка нанести урон эффектом на тике. Возвращет флаг изменил ли параметы персонажа эффект
	bool EffectTick(FEffectAbstract currentEffectAbstract);

	//Вычислить резист с учётом игнора
	float CalculateResist(EEffectType resist, float ignoreresist);

protected:
	virtual void BeginPlay() override;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
