// Copyright (c) 2022 Nineva Studios

#include "NearbyConnectionsBPLibrary.h"

#include "NearbyConnectionsLog.h"

#if PLATFORM_ANDROID
#include "Android/NCConversionUtils.h"
#include "Android/NCMethodCallUtils.h"
#endif

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnStartAdvertisingSuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnStartAdvertisingError;

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnStartDiscoverySuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnStartDiscoveryError;

FNCConnectionInitiatedDelegate UNearbyConnectionsBPLibrary::OnConnectionInitiated;
FNCConnectionResultDelegate UNearbyConnectionsBPLibrary::OnConnectionResult;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnDisconnected;

FNCEndpointFoundDelegate UNearbyConnectionsBPLibrary::OnEndpointFound;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnEndpointLost;

FNCPayloadReceivedDelegate UNearbyConnectionsBPLibrary::OnPayloadReceived;
FNCPayloadTransferUpdateDelegate UNearbyConnectionsBPLibrary::OnPayloadTransferUpdate;

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnAcceptConnectionSuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnAcceptConnectionError;

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnDisconnectFromEndpointSuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnDisconnectFromEndpointError;

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnRejectConnectionSuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnRejectConnectionError;

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnRequestConnectionSuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnRequestConnectionError;

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnSendPayloadSuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnSendPayloadError;

void UNearbyConnectionsBPLibrary::StartAdvertising(const FNCConnectionOptions& Options, const FString& UserName, const FString& ServiceId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StartAdvertising"));

	OnStartAdvertisingSuccess = OnSuccess;
	OnStartAdvertisingError = OnError;

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::StopAdvertising()
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StopAdvertising"));

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::StartDiscovery(const FNCConnectionOptions& Options, const FString& ServiceId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StartDiscovery"));

	OnStartDiscoverySuccess = OnSuccess;
	OnStartDiscoveryError = OnError;

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::StopDiscovery()
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StopDiscovery"));

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::StopAllEndpoints()
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StopAllEndpoints"));

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::AcceptConnection(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::AcceptConnection"));

	OnAcceptConnectionSuccess = OnSuccess;
	OnAcceptConnectionError = OnError;

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::CancelPayload(int64 PayloadId)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::CancelPayload"));

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::DisconnectFromEndpoint(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::DisconnectFromEndpoint"));

	OnDisconnectFromEndpointSuccess = OnSuccess;
	OnDisconnectFromEndpointError = OnError;

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::RejectConnection(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::RejectConnection"));

	OnRejectConnectionSuccess = OnSuccess;
	OnRejectConnectionError = OnError;

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::RequestConnectionByName(const FString& Name, const FString& EndpointId, const FNCConnectionOptions& Options, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::RequestConnectionByName"));

	OnRequestConnectionSuccess = OnSuccess;
	OnRequestConnectionError = OnError;

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::RequestConnection(const TArray<uint8>& EndpointInfo, const FString& EndpointId, const FNCConnectionOptions& Options, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::RequestConnection"));

	OnRequestConnectionSuccess = OnSuccess;
	OnRequestConnectionError = OnError;

#if PLATFORM_ANDROID

#endif
}

void UNearbyConnectionsBPLibrary::SendPayload(UNCPayload* Payload, const TArray<FString>& Endpoints, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::SendPayload"));

	OnSendPayloadSuccess = OnSuccess;
	OnSendPayloadError = OnError;

#if PLATFORM_ANDROID

#endif
}
