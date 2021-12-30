// Copyright (c) 2022 Nineva Studios

#pragma once

#include "UObject/Object.h"

#if PLATFORM_ANDROID
#include "Android/AndroidJNI.h"
#endif

#include "NCConnectionInfo.generated.h"

/**
* Information about a connection that is being initiated.
*/
UCLASS(BlueprintType)
class UNCConnectionInfo : public UObject
{
	GENERATED_BODY()

public:

	virtual ~UNCConnectionInfo();

	/**
	* The name of the remote device we're connecting to.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	FString GetEndpointName();

	/**
	* A 4 digit authentication token that has been given to both devices.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	FString GetAuthenticationDigits();

	/**
	* The raw (significantly longer) version of the authentication token from getAuthenticationToken() -- 
	* this is intended for headless authentication, typically on devices with no output capabilities, 
	* where the authentication is purely programmatic and does not have the luxury of human intervention.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	TArray<uint8> GetRawAuthenticationToken();

	/**
	* True if the connection request was initiated from a remote device.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	bool IsIncomingConnection();

	/**
	* Information that represents the remote device which is defined by the client or application.
	*/
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