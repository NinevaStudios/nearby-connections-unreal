// Copyright (c) 2022 Nineva Studios

#pragma once

#include "UObject/Object.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "NCPayload.generated.h"

UENUM()
enum class ENCPayloadType : uint8
{
	None = 0,
	Bytes = 1,
	File = 2,
	Stream = 3
};

UCLASS(BlueprintType)
class UNCPayload : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UNCPayload();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static UNCPayload* PayloadFromBytes(const TArray<uint8>& Bytes);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static UNCPayload* PayloadFromFile(const FString& Path);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	int64 GetId();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	ENCPayloadType GetType();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	TArray<uint8> GetBytes();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	FString GetFilePath();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	void Close();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	void SetOffset(int64 Offset);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	int64 GetOffset();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	void SetSensitive(bool IsSensitive);

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