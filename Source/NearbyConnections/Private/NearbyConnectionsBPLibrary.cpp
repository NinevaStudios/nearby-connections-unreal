// Copyright (c) 2022 Nineva Studios

#include "NearbyConnectionsBPLibrary.h"

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnStartAdvertisingSuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnStartAdvertisingError;

FNCVoidDelegate UNearbyConnectionsBPLibrary::OnStartDiscoverySuccess;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnStartDiscoveryError;

FNCConnectionInitiatedDelegate UNearbyConnectionsBPLibrary::OnConnectionInitiated;
FNCConnectionResultDelegate UNearbyConnectionsBPLibrary::OnConnectionResult;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnDisconnected;

FNCEndpointFoundDelegate UNearbyConnectionsBPLibrary::OnEndpointFound;
FNCStringDelegate UNearbyConnectionsBPLibrary::OnEndpointLost;

void UNearbyConnectionsBPLibrary::StartAdvertising(const FNCConnectionOptions Options, const FString& UserName, const FString& ServiceId,
	const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	OnStartAdvertisingSuccess = OnSuccess;
	OnStartAdvertisingError = OnError;
}

void UNearbyConnectionsBPLibrary::StartDiscovery(const FNCConnectionOptions Options, const FString& ServiceId,
	const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	OnStartDiscoverySuccess = OnSuccess;
	OnStartDiscoveryError = OnError;
}