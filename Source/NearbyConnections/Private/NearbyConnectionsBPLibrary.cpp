// Copyright (c) 2022 Nineva Studios

#include "NearbyConnectionsBPLibrary.h"

FNearbyConnectionsVoidDelegate UNearbyConnectionsBPLibrary::OnStartAdvertisingSuccess;
FNearbyConnectionsStringDelegate UNearbyConnectionsBPLibrary::OnStartAdvertisingError;

FNearbyConnectionsVoidDelegate UNearbyConnectionsBPLibrary::OnStartDiscoverySuccess;
FNearbyConnectionsStringDelegate UNearbyConnectionsBPLibrary::OnStartDiscoveryError;

void UNearbyConnectionsBPLibrary::StartAdvertising(const FNearbyConnectionOptions Options, const FString& UserName, const FString& ServiceId,
	const FNearbyConnectionsVoidDelegate& OnSuccess, const FNearbyConnectionsStringDelegate& OnError)
{
	OnStartAdvertisingSuccess = OnSuccess;
	OnStartAdvertisingError = OnError;
}

void UNearbyConnectionsBPLibrary::StartDiscovery(const FNearbyConnectionOptions Options, const FString& ServiceId,
	const FNearbyConnectionsVoidDelegate& OnSuccess, const FNearbyConnectionsStringDelegate& OnError)
{
	OnStartDiscoverySuccess = OnSuccess;
	OnStartDiscoveryError = OnError;
}

