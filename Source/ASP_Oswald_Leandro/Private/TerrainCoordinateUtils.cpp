// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainCoordinateUtils.h"
#include "LandscapeProxy.h"

// Was dieses Script macht:
// - cm ↔ m
// World <-> Landscape Local
// (später) World ↔ Grid Index

bool UTerrainCoordinateUtils::WorldToLandscapeLocal(const ALandscapeProxy* Landscape, const FVector& WorldPos, FVector& OutLocalPos)
{
	if (!Landscape) return false;

	const FTransform T = Landscape->GetActorTransform();
	OutLocalPos = T.InverseTransformPosition(WorldPos);
	return true;
}

bool UTerrainCoordinateUtils::LandscapeLocalToWorld(const ALandscapeProxy* Landscape, const FVector& LocalPos, FVector& OutWorldPos)
{
	if (!Landscape) return false;

	const FTransform T = Landscape->GetActorTransform();
	OutWorldPos = T.TransformPosition(LocalPos);
	return true;
}