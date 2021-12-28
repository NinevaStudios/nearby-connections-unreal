// Copyright (c) 2022 Nineva Studios

#pragma once

#include "UObject/Object.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "NCConnectionInfo.generated.h"

UCLASS(BlueprintType)
class UNCConnectionInfo : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UNCConnectionInfo();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	FString GetEndpointName();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	FString GetAuthenticationDigits();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	TArray<uint8> GetRawAuthenticationToken();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	bool IsIncomingConnection();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	TArray<uint8> GetEndpointInfo();

	/**
	 * Convenience function to check whether the native object is valid.
	 */
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	bool IsNativeObjectValid();

#if PLATFORM_ANDROID
	void Init(jobject javaObject);
	jobject JavaObject;
#endif

};