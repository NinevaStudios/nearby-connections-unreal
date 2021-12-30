// Copyright (c) 2022 Nineva Studios

#pragma once

#include "UObject/Object.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "NCPayload.generated.h"

/**
* The type of this payload.
*/
UENUM()
enum class ENCPayloadType : uint8
{
	// Payload is not initialized properly and is most likely corrupted.
	None = 0,
	// A Payload consisting of a single byte array.
	Bytes = 1,
	// A Payload representing a file on the device.
	File = 2,
	// A Payload representing a real-time stream of data.
	Stream = 3
};

/**
* A Payload sent between devices. Payloads sent as a particular type will be received as that same type on the other device.
*/
UCLASS(BlueprintType)
class UNCPayload : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UNCPayload();

	/**
	* Creates a Payload of type ENCPayloadType::Bytes for sending to another device.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static UNCPayload* PayloadFromBytes(const TArray<uint8>& Bytes);

	/**
	* Creates a Payload of type ENCPayloadType::File for sending to another device.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static UNCPayload* PayloadFromFile(const FString& Path);

	/**
	* A unique identifier for this payload.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	int64 GetId();

	/**
	* The type of this payload, one of ENCPayloadType.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	ENCPayloadType GetType();

	/**
	* Non-empty for payloads of type ENCPayloadType::Bytes.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	TArray<uint8> GetBytes();

	/**
	* Non-empty for payloads of type ENCPayloadType::File.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	FString GetFilePath();

	/**
	* Closes to release any resources for ENCPayloadType::File or ENCPayloadType::Stream when the transferring stopped.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	void Close();

	/**
	* Sets the offset from GetOffset() when resuming a transfer.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	void SetOffset(int64 Offset);

	/**
	* Returns the offset of this payload for resume sending or receiving.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	int64 GetOffset();

	/**
	* Sets whether or not the payload is sensitive.
	*/
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