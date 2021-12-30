// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "NearbyConnectionsBPLibrary.generated.h"

/**
* The Strategy to be used when discovering or advertising to Nearby devices. The Strategy defines:
* - the connectivity requirements for the device;
* - the topology constraints of the connection.
*/
UENUM()
enum class ENCStrategy : uint8
{
	/**
	* Peer-to-peer strategy that supports an M-to-N, or cluster-shaped, connection topology.
	*/
	Cluster = 0,
	/**
	* Peer-to-peer strategy that supports a 1-to-1 connection topology.
	*/
	PointToPoint = 1,
	/**
	* Peer-to-peer strategy that supports a 1-to-N, or star-shaped, connection topology.
	*/
	Star = 2
};

/**
* Configuration parameters for the Connections API.
*/
USTRUCT(BlueprintType)
struct FNCConnectionOptions
{
	GENERATED_BODY()

	/**
	* The advertising strategy, the strategy used for advertising.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Nearby Connections")
	ENCStrategy Strategy;

	/**
	* Whether low power should be used, if true only low poer mediums (like BLE) will be used for advertising.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Nearby Connections")
	bool IsLowPower = false;

	/**
	* The disruptive upgrade flag.
	*/
	UPROPERTY(BlueprintReadWrite, Category = "Nearby Connections")
	bool IsDisruptiveUpgrade = false;
};

/**
* Describes the status for an active Payload transfer, either incoming or outgoing. Delivered to OnPayloadTransferUpdate delegate.
*/
USTRUCT(BlueprintType)
struct FNCPayloadTransferUpdate
{
	GENERATED_BODY()

	/**
	* The payload identifier.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	int64 PayloadId;

	/**
	* The status of the payload.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	int Status;

	/**
	* The total number of bytes in the payload.
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Nearby Connections")
	int64 TotalBytes;

	/**
	* The number of bytes transferred so far.
	*/
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

/**
* Entry point for advertising and discovering nearby apps and services, and communicating with them over established connections.
*/
UCLASS()
class UNearbyConnectionsBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	* Starts advertising an endpoint for a local app. Need to call BindConnectionDelegates before doing this.
	* 
	* @param Options - The options for advertising.
	* @param UserName - A human readable name for this endpoint, to appear on the remote device. Defined by client/application.
	* @param ServiceId - An identifier to advertise your app to other endpoints. This can be an arbitrary string, so long as it uniquely identifies your service. A good default is to use your app's package name.
	* @param OnSuccess - Action to be performed if the call was successful.
	* @param OnError - Action to be performed if the call was unsuccessful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void StartAdvertising(const FNCConnectionOptions& Options, const FString& UserName, const FString& ServiceId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	/**
	* Stops advertising a local endpoint. Should be called after calling StartAdvertising(), 
	* as soon as the application no longer needs to advertise itself or goes inactive. Payloads can still be sent to connected endpoints after advertising ends.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void StopAdvertising();

	/**
	* Starts discovery for remote endpoints with the specified service ID.
	* Has to be called after BindEndpointDelegates;
	*
	* @param Options - The options for discovery.
	* @param ServiceId - An identifier to advertise your app to other endpoints. This can be an arbitrary string, so long as it uniquely identifies your service. A good default is to use your app's package name.
	* @param OnSuccess - Action to be performed if the call was successful.
	* @param OnError - Action to be performed if the call was unsuccessful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void StartDiscovery(const FNCConnectionOptions& Options, const FString& ServiceId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	/**
	* Stops discovery for remote endpoints, after a previous call to StartDiscovery(), 
	* when the client no longer needs to discover endpoints or goes inactive. Payloads can still be sent to connected endpoints after discovery ends.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void StopDiscovery();

	/**
	* Disconnects from, and removes all traces of, all connected and/or discovered endpoints. This call is expected to be preceded by a call to StopAdvertising()
	* or StartDiscovery() as needed. After calling StopAllEndpoints(), no further operations with remote endpoints will be possible until a new call to one of 
	* StartAdvertising() or StartDiscovery().
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void StopAllEndpoints();

	/**
	* Accepts a connection to a remote endpoint. This method must be called before Payloads can be exchanged with the remote endpoint.
	* Has to be called after BindPayloadDelegates;
	*
	* @param EndpointId - The identifier for the remote endpoint to connect to.
	* @param OnSuccess - Action to be performed if the call was successful.
	* @param OnError - Action to be performed if the call was unsuccessful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void AcceptConnection(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	/**
	* Cancels a Payload currently in-flight to or from remote endpoint(s).
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void CancelPayload(int64 PayloadId);

	/**
	* Disconnects from a remote endpoint. Payloads can no longer be sent to or received from the endpoint after this method is called.
	*
	* @param EndpointId - The identifier for the remote endpoint to disconnect from.
	* @param OnSuccess - Action to be performed if the call was successful.
	* @param OnError - Action to be performed if the call was unsuccessful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void DisconnectFromEndpoint(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	/**
	* Rejects a connection to a remote endpoint.
	*
	* @param EndpointId - The identifier for the remote endpoint to reject connection to.
	* @param OnSuccess - Action to be performed if the call was successful.
	* @param OnError - Action to be performed if the call was unsuccessful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void RejectConnection(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	/**
	* Sends a request to connect to a remote endpoint.
	*
	* @param Name - A human readable name for the local endpoint, to appear on the remote device. Defined by client/application.
	* @param EndpointId - The identifier for the remote endpoint to request connection to.
	* @param Options - The options to set up a connection.
	* @param OnSuccess - Action to be performed if the call was successful.
	* @param OnError - Action to be performed if the call was unsuccessful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void RequestConnectionByName(const FString& Name, const FString& EndpointId, const FNCConnectionOptions& Options, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	/**
	* Sends a request to connect to a remote endpoint.
	*
	* @param EndpointInfo - Identifing information about this endpoint (eg. name, device type), to appear on the remote device. Defined by client/application.
	* @param EndpointId - The identifier for the remote endpoint to request connection to.
	* @param Options - The options to set up a connection.
	* @param OnSuccess - Action to be performed if the call was successful.
	* @param OnError - Action to be performed if the call was unsuccessful.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void RequestConnection(const TArray<uint8>& EndpointInfo, const FString& EndpointId, const FNCConnectionOptions& Options, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	/**
	* Sends a Payload to a remote endpoint. Payloads can only be sent to remote endpoints once a notice of connection acceptance 
	* has been delivered via OnConnectionResult()
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections", meta = (AutoCreateRefTerm = "OnSuccess,OnError"))
	static void SendPayload(UNCPayload* Payload, const TArray<FString>& Endpoints, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError);

	/**
	* Callbacks notified when remote endpoints request a connection to this endpoint.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void BindConnectionDelegates(const FNCConnectionInitiatedDelegate& OnConnectionInitiatedCallback, const FNCConnectionResultDelegate& OnConnectionResultCallback,
		const FNCStringDelegate& OnDisconnectedCallback)
	{
		OnConnectionInitiated = OnConnectionInitiatedCallback;
		OnConnectionResult = OnConnectionResultCallback;
		OnDisconnected = OnDisconnectedCallback;
	}

	/**
	* Callbacks notified when a remote endpoint is discovered.
	*/
	UFUNCTION(BlueprintCallable, Category = "Nearby Connections")
	static void BindEndpointDelegates(const FNCEndpointFoundDelegate& OnEndpointFoundCallback, const FNCStringDelegate& OnEndpointLostCallback)
	{
		OnEndpointFound = OnEndpointFoundCallback;
		OnEndpointLost = OnEndpointLostCallback;
	}

	/**
	* Callbacks notified when a payload is transferred to the device.
	*/
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
