// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiShootGameBulletShell.h"
#include "MultiShootGameMagazineClip.h"
#include "GameFramework/Pawn.h"
#include "MultiShootGame/Enum/EWeaponMode.h"
#include "MultiShootGame/Struct/WeaponInfo.h"
#include "MultiShootGameWeapon.generated.h"

class AMultiShootGameCharacter;

UCLASS()
class MULTISHOOTGAME_API AMultiShootGameWeapon : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMultiShootGameWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool BulletCheck(AMultiShootGameCharacter* MyOwner);

	virtual void BulletFire(AMultiShootGameCharacter* MyOwner);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	USkeletalMeshComponent* WeaponMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName MuzzleSocketName = "Muzzle";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName TracerTargetName = "Target";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName BulletShellName = "BulletShell";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FName ClipBoneName = "b_gun_mag";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	EWeaponMode CurrentWeaponMode;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AMultiShootGameBulletShell> BulletShellClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	TSubclassOf<AMultiShootGameMagazineClip> MagazineClipClass;

	FTimerHandle TimerHandle;

	float LastFireTime;

	float TimeBetweenShots;

	bool Loop = false;

	void ShakeCamera();

	UFUNCTION(BlueprintImplementableEvent)
	void StartFireCurve();

	UFUNCTION(BlueprintImplementableEvent)
	void StopFireCurve();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Fire();

	void StartFire();

	void StopFire();

	void FireOfDelay();

	void EnablePhysicsSimulate();

	virtual void ReloadShowMagazineClip(bool Enabled);

	void BulletReload();

	void FillUpBullet();

	bool bInitializeReady = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	FWeaponInfo WeaponInfo;

	UFUNCTION(BlueprintPure, Category = Weapon)
	FORCEINLINE USkeletalMeshComponent* GetWeaponMeshComponent() const { return WeaponMeshComponent; }
};
