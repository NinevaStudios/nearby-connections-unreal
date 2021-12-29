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

	UPROPERTY(BlueprintReadWrite, Category = "Nearby Connections")
	ENCStrategy Strategy;

	UPROPERTY(BlueprintReadWrite, Category = "Nearby Connections")
	bool IsLowPower = false;

	UPROPERTY(BlueprintReadWrite, Category = "Nearby Connections")
	bool IsDisruptiveUpgrade = false;
};

USTRUCT(BlueprintType)
struct FNCPayloadTransferUpdate
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	int64 PayloadId;

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	int Status;

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	int64 TotalBytes;

	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	int64 TransferredBytes;
};

class UNCConnectionInfo;
class UNCPayload;

DECLARE_DYNAMIC_DELEGATE(FNCVoidDelegate);
DECLARE_DYNAMIC_DELEGATE_OneParam(FNCStringDelegate, FString, String);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNCConnectionInitiatedDelegate, FString, EndpointId, UNCConnectionInfo*, ConnectionInfo);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FNCConnectionResultDelegate, FString, EndpointId, int, StatusCode, FString, Message);

DECLARE_DYNAMIC_DELEGATE_FourParams(FNCEndpointFoundDelegate, FString, EndpointId, FString, ServiceId, FString, EndpointName, const TArray<uint8>&, EndpointInfo);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FNCPayloadReceivedDelegate, FString, EndpointId, UNCPayload*, Payload);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FNCPayloadTransferUpdateDelegate, FString, EndpointId, const FNCPayloadTransferUpdate&, PayloadTransferUpdate);

UCLASS()
class UNearbyConnectionsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void StartAdvertising(const FNCConnectionOptions& Options, const FString& UserName, const FString& ServiceId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void StopAdvertising();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void StartDiscovery(const FNCConnectionOptions& Options, const FString& ServiceId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void StopDiscovery();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void StopAllEndpoints();

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void AcceptConnection(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void CancelPayload(int64 PayloadId);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void DisconnectFromEndpoint(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void RejectConnection(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void RequestConnectionByName(const FString& Name, const FString& EndpointId, const FNCConnectionOptions& Options, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void RequestConnection(const TArray<uint8>& EndpointInfo, const FString& EndpointId, const FNCConnectionOptions& Options, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void SendPayload(UNCPayload* Payload, const TArray<FString>& Endpoints, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

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

	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void BindPayloadDelegates(const FNCPayloadReceivedDelegate& OnPayloadReceivedCallback, const FNCPayloadTransferUpdateDelegate& OnPayloadTransferUpdateCallback)
	{
		OnPayloadReceived = OnPayloadReceivedCallback;
		OnPayloadTransferUpdate = OnPayloadTransferUpdateCallback;
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

	static FNCPayloadReceivedDelegate OnPayloadReceived;
	static FNCPayloadTransferUpdateDelegate OnPayloadTransferUpdate;

	static FNCVoidDelegate OnAcceptConnectionSuccess;
	static FNCStringDelegate OnAcceptConnectionError;
	
	static FNCVoidDelegate OnDisconnectFromEndpointSuccess;
	static FNCStringDelegate OnDisconnectFromEndpointError;
	
	static FNCVoidDelegate OnRejectConnectionSuccess;
	static FNCStringDelegate OnRejectConnectionError;
	
	static FNCVoidDelegate OnRequestConnectionSuccess;
	static FNCStringDelegate OnRequestConnectionError;
	
	static FNCVoidDelegate OnSendPayloadSuccess;
	static FNCStringDelegate OnSendPayloadError;

	static const ANSICHAR* NearbyConnectionsClassName;
};
