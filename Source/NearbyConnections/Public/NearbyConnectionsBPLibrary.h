// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NearbyConnectionsBPLibrary.generated.h"

UENUM()
enum class ENearbyConnectionsStrategy : uint8
{
	Cluster = 0,
	PointToPoint = 1,
	Star = 2
};

USTRUCT(BlueprintType)
struct FNearbyConnectionOptions
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	ENearbyConnectionsStrategy Strategy;

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	bool IsLowPower;

	/// <summary>
	/// Used only for StartAdvertising, ignored in StartDiscovery.
	/// </summary>
	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	bool IsDisruptiveUpgrade;
};

DECLARE_DYNAMIC_DELEGATE(FNearbyConnectionsVoidDelegate);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNearbyConnectionsStringDelegate, FString, String);

UCLASS()
class UNearbyConnectionsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void StartAdvertising(const FNearbyConnectionOptions Options, const FString& UserName, const FString& ServiceId,
		const FNearbyConnectionsVoidDelegate& OnSuccess, const FNearbyConnectionsStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void StartDiscovery(const FNearbyConnectionOptions Options, const FString& ServiceId,
		const FNearbyConnectionsVoidDelegate& OnSuccess, const FNearbyConnectionsStringDelegate& OnError);

	static FNearbyConnectionsVoidDelegate OnStartAdvertisingSuccess;
	static FNearbyConnectionsStringDelegate OnStartAdvertisingError;
	
	static FNearbyConnectionsVoidDelegate OnStartDiscoverySuccess;
	static FNearbyConnectionsStringDelegate OnStartDiscoveryError;
};
