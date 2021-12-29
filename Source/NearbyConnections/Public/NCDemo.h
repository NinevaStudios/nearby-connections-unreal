// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NCDemo.generated.h"

UCLASS()
class UNCDemo : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections|Demo")
	static FString StringFromBytes(const TArray<uint8>& Bytes);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections|Demo")
	static TArray<uint8> BytesFromString(const FString& String);
};