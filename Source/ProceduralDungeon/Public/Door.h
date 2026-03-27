// Copyright Benoit Pelletier 2019 - 2026 All Rights Reserved.
//
// This software is available under different licenses depending on the source from which it was obtained:
// - The Fab EULA (https://fab.com/eula) applies when obtained from the Fab marketplace.
// - The CeCILL-C license (https://cecill.info/licences/Licence_CeCILL-C_V1-en.html) applies when obtained from any other source.
// Please refer to the accompanying LICENSE file for further details.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UDoorType;
class UDoorComponent;

// Base class for all door actors in the dungeon.
// Use this class even if you want to create a wall to place instead of a door (when the door is not connected to another room for example).
UCLASS(Blueprintable, ClassGroup = "Procedural Dungeon")
class PROCEDURALDUNGEON_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	ADoor();

	//~ Begin AActor interface
	virtual void PostInitializeComponents() override;
	//~ End AActor interface

public:
	UDoorComponent* GetDoorComponent() const { return DoorComponent; }

	UFUNCTION(BlueprintPure, Category = "Door", meta = (CompactNodeTitle = "Is Locked", DeprecatedFunction, DeprecationMessage = "Use DoorComponent->IsLocked instead."))
	bool IsLocked() const;

	UFUNCTION(BlueprintPure, Category = "Door", meta = (CompactNodeTitle = "Is Open", DeprecatedFunction, DeprecationMessage = "Use DoorComponent->IsOpen instead."))
	bool IsOpen() const;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Door", meta = (DeprecatedFunction, DeprecationMessage = "Use DoorComponent->Open instead."))
	void Open(bool open);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Door", meta = (DeprecatedFunction, DeprecationMessage = "Use DoorComponent->Lock instead."))
	void Lock(bool lock);

	bool ShouldBeOpened() const;
	bool ShouldBeLocked() const;

	const UDoorType* GetDoorType() const;

	UFUNCTION(BlueprintGetter)
	URoom* GetRoomA() const;

	UFUNCTION(BlueprintGetter)
	URoom* GetRoomB() const;

protected:
	UFUNCTION()
	virtual void OnDoorLock() {}
	UFUNCTION(BlueprintImplementableEvent, Category = "Door", meta = (DisplayName = "On Locked", DeprecatedFunction, DeprecationMessage = "Bind to DoorComponent->OnDoorLocked(true) instead."))
	void OnDoorLock_BP();

	UFUNCTION()
	virtual void OnDoorUnlock() {}
	UFUNCTION(BlueprintImplementableEvent, Category = "Door", meta = (DisplayName = "On Unlocked", DeprecatedFunction, DeprecationMessage = "Bind to DoorComponent->OnDoorLocked(false) instead."))
	void OnDoorUnlock_BP();

	UFUNCTION()
	virtual void OnDoorOpen() {}
	UFUNCTION(BlueprintImplementableEvent, Category = "Door", meta = (DisplayName = "On Open", DeprecatedFunction, DeprecationMessage = "Bind to DoorComponent->OnDoorOpened(true) instead."))
	void OnDoorOpen_BP();

	UFUNCTION()
	virtual void OnDoorClose() {}
	UFUNCTION(BlueprintImplementableEvent, Category = "Door", meta = (DisplayName = "On Close", DeprecatedFunction, DeprecationMessage = "Bind to DoorComponent->OnDoorOpened(false) instead."))
	void OnDoorClose_BP();

	UFUNCTION()
	void DispatchDoorLock(UDoorComponent* Component, bool IsLocked);

	UFUNCTION()
	void DispatchDoorOpen(UDoorComponent* Component, bool IsOpened);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Door", meta = (DisplayName = "Always Visible"))
	bool bAlwaysVisible {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, Category = "Door", meta = (DisplayName = "Always Unlocked"))
	bool bAlwaysUnlocked {false};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Door", meta = (DisplayName = "Door Type"))
	UDoorType* Type {nullptr};

	UPROPERTY(EditAnywhere, Category = "Door")
	USceneComponent* DefaultSceneComponent {nullptr};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door")
	UDoorComponent* DoorComponent {nullptr};

private:
	// Ghost properties for retro-compatibility. Redirect to the DoorComponent->RoomA/B internally.
	UPROPERTY(BlueprintGetter = GetRoomA, Category = "Door", meta = (AllowPrivateAccess = true, DeprecatedProperty, DeprecationMessage = "Use DoorComponent->RoomA instead."))
	URoom* RoomA {nullptr};
	UPROPERTY(BlueprintGetter = GetRoomB, Category = "Door", meta = (AllowPrivateAccess = true, DeprecatedProperty, DeprecationMessage = "Use DoorComponent->RoomB instead."))
	URoom* RoomB {nullptr};
};
