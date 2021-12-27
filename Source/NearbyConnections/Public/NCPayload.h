// Copyright (c) 2022 Nineva Studios

#pragma once

#include "UObject/Object.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "NCPayload.generated.h"

UCLASS(BlueprintType)
class UNCPayload : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UNCPayload();

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