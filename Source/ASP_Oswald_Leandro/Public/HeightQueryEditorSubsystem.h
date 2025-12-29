// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorSubsystem.h"
#include "HeightQueryEditorSubsystem.generated.h"


class AVoxelGridBaker;
class UVoxelHeightCache;

/**
 * 
 */
UCLASS()
class ASP_OSWALD_LEANDRO_API UHeightQueryEditorSubsystem : public UEditorSubsystem
{
	GENERATED_BODY()
	
public:
	// Aktivieren/Deaktivieren vom Klick-Modus
	UFUNCTION(BlueprintCallable, Category="HeightQuery")
	void SetClickQueryEnabled(bool bEnabled);

	UFUNCTION(BlueprintCallable, Category="HeightQuery")
	bool IsClickQueryEnabled() const { return bClickEnabled; }

	// Set references
	UFUNCTION(BlueprintCallable, Category="HeightQuery")
	void SetSources(AVoxelGridBaker* InGridBaker, UVoxelHeightCache* InCache);

private:
	bool bClickEnabled = false;

	TWeakObjectPtr<AVoxelGridBaker> GridBaker;
	TWeakObjectPtr<UVoxelHeightCache> Cache;

	// Hook
	void OnClick(const FVector& WorldPos);

	bool WorldXYToCell(const FVector& WorldPos, int32& OutX, int32& OutY) const;
};
