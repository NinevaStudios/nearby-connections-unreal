// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NCDemo.generated.h"

UCLASS()
class UNCDemo : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	* Helper function to parse the message for Demo.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections|Demo")
	static FString StringFromBytes(const TArray<uint8>& Bytes);

	/**
	* Helper function to convert the message to bytes before sending for Demo.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections|Demo")
	static TArray<uint8> BytesFromString(const FString& String);
};