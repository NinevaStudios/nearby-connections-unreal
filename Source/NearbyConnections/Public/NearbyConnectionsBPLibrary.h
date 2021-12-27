// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NearbyConnectionsBPLibrary.generated.h"

UENUM()
enum class ENCStrategy : uint8
{
	Cluster = 0,
	PointToPoint = 1,
	Star = 2
};

USTRUCT(BlueprintType)
struct FNCConnectionOptions
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	ENCStrategy Strategy;

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	bool IsLowPower = false;

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	bool IsDisruptiveUpgrade = false;
};

class UNCConnectionInfo;

DECLARE_DYNAMIC_DELEGATE(FNCVoidDelegate);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNCStringDelegate, FString, String);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNCConnectionInitiatedDelegate, FString, EndpointId, UNCConnectionInfo*, ConnectionInfo);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FNCConnectionResultDelegate, FString, EndpointId, int, StatusCode, FString, Message);

DECLARE_DYNAMIC_DELEGATE_FourParams(FNCEndpointFoundDelegate, FString, EndpointId, FString, ServiceId, FString, EndpointName, const TArray<uint8>&, EndpointInfo);

UCLASS()
class UNearbyConnectionsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void StartAdvertising(const FNCConnectionOptions Options, const FString& UserName, const FString& ServiceId,
		const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void StartDiscovery(const FNCConnectionOptions Options, const FString& ServiceId,
		const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void BindConnectionDelegates(const FNCConnectionInitiatedDelegate& OnConnectionInitiatedCallback, const FNCConnectionResultDelegate& OnConnectionResultCallback,
		const FNCStringDelegate& OnDisconnectedCallback)
	{
		OnConnectionInitiated = OnConnectionInitiatedCallback;
		OnConnectionResult = OnConnectionResultCallback;
		OnDisconnected = OnDisconnectedCallback;
	}

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void BindEndpointDelegates(const FNCEndpointFoundDelegate& OnEndpointFoundCallback, const FNCStringDelegate& OnEndpointLostCallback)
	{
		OnEndpointFound = OnEndpointFoundCallback;
		OnEndpointLost = OnEndpointLostCallback;
	}

	static FNCVoidDelegate OnStartAdvertisingSuccess;
	static FNCStringDelegate OnStartAdvertisingError;
	
	static FNCVoidDelegate OnStartDiscoverySuccess;
	static FNCStringDelegate OnStartDiscoveryError;

	static FNCConnectionInitiatedDelegate OnConnectionInitiated;
	static FNCConnectionResultDelegate OnConnectionResult;
	static FNCStringDelegate OnDisconnected;

	static FNCEndpointFoundDelegate OnEndpointFound;
	static FNCStringDelegate OnEndpointLost;
};
