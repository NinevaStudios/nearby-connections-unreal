// Copyright (c) 2022 Nineva Studios

#include "NearbyConnectionsBPLibrary.h"

#include "NearbyConnectionsLog.h"

#include "Async/Async.h"

#include "NCPayload.h"
#include "NCConnectionInfo.h"

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

const ANSICHAR* UNearbyConnectionsBPLibrary::NearbyConnectionsClassName = "com/ninevastudios/nearbyconnections/NearbyConnections";

void UNearbyConnectionsBPLibrary::StartAdvertising(const FNCConnectionOptions& Options, const FString& UserName, const FString& ServiceId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StartAdvertising"));

	OnStartAdvertisingSuccess = OnSuccess;
	OnStartAdvertisingError = OnError;

#if PLATFORM_ANDROID
	jobject JavaOptions = NCConversionUtils::ToJavaOptions(Options);
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "startAdvertising", "(Landroid/app/Activity;Lcom/ninevastudios/nearbyconnections/Options;Ljava/lang/String;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, JavaOptions, NCConversionUtils::GetJavaString(UserName), NCConversionUtils::GetJavaString(ServiceId));
#endif
}

void UNearbyConnectionsBPLibrary::StopAdvertising()
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StopAdvertising"));

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "stopAdvertising", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UNearbyConnectionsBPLibrary::StartDiscovery(const FNCConnectionOptions& Options, const FString& ServiceId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StartDiscovery"));

	OnStartDiscoverySuccess = OnSuccess;
	OnStartDiscoveryError = OnError;

#if PLATFORM_ANDROID
	jobject JavaOptions = NCConversionUtils::ToJavaOptions(Options);
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "startDiscovery", "(Landroid/app/Activity;Lcom/ninevastudios/nearbyconnections/Options;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, JavaOptions, NCConversionUtils::GetJavaString(ServiceId));
#endif
}

void UNearbyConnectionsBPLibrary::StopDiscovery()
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StopDiscovery"));

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "stopDiscovery", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UNearbyConnectionsBPLibrary::StopAllEndpoints()
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::StopAllEndpoints"));

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "stopAllEndpoints", "(Landroid/app/Activity;)V", FJavaWrapper::GameActivityThis);
#endif
}

void UNearbyConnectionsBPLibrary::AcceptConnection(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::AcceptConnection"));

	OnAcceptConnectionSuccess = OnSuccess;
	OnAcceptConnectionError = OnError;

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "acceptConnection", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, NCConversionUtils::GetJavaString(EndpointId));
#endif
}

void UNearbyConnectionsBPLibrary::CancelPayload(int64 PayloadId)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::CancelPayload"));

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "cancelPayload", "(Landroid/app/Activity;J)V",
		FJavaWrapper::GameActivityThis, PayloadId);
#endif
}

void UNearbyConnectionsBPLibrary::DisconnectFromEndpoint(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::DisconnectFromEndpoint"));

	OnDisconnectFromEndpointSuccess = OnSuccess;
	OnDisconnectFromEndpointError = OnError;

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "disconnectFromEndpoint", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, NCConversionUtils::GetJavaString(EndpointId));
#endif
}

void UNearbyConnectionsBPLibrary::RejectConnection(const FString& EndpointId, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::RejectConnection"));

	OnRejectConnectionSuccess = OnSuccess;
	OnRejectConnectionError = OnError;

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "rejectConnection", "(Landroid/app/Activity;Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, NCConversionUtils::GetJavaString(EndpointId));
#endif
}

void UNearbyConnectionsBPLibrary::RequestConnectionByName(const FString& Name, const FString& EndpointId, const FNCConnectionOptions& Options, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::RequestConnectionByName"));

	OnRequestConnectionSuccess = OnSuccess;
	OnRequestConnectionError = OnError;

#if PLATFORM_ANDROID
	jobject JavaOptions = NCConversionUtils::ToJavaOptions(Options);
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "requestConnection", "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;Lcom/ninevastudios/nearbyconnections/Options;)V",
		FJavaWrapper::GameActivityThis, NCConversionUtils::GetJavaString(Name), NCConversionUtils::GetJavaString(EndpointId), JavaOptions);
#endif
}

void UNearbyConnectionsBPLibrary::RequestConnection(const TArray<uint8>& EndpointInfo, const FString& EndpointId, const FNCConnectionOptions& Options, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::RequestConnection"));

	OnRequestConnectionSuccess = OnSuccess;
	OnRequestConnectionError = OnError;

#if PLATFORM_ANDROID
	jobject JavaOptions = NCConversionUtils::ToJavaOptions(Options);
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "requestConnection", "(Landroid/app/Activity;[BLjava/lang/String;Lcom/ninevastudios/nearbyconnections/Options;)V",
		FJavaWrapper::GameActivityThis, NCConversionUtils::ConvertToJByteArray(EndpointInfo), NCConversionUtils::GetJavaString(EndpointId), JavaOptions);
#endif
}

void UNearbyConnectionsBPLibrary::SendPayload(UNCPayload* Payload, const TArray<FString>& Endpoints, const FNCVoidDelegate& OnSuccess, const FNCStringDelegate& OnError)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("UNearbyConnectionsBPLibrary::SendPayload"));

	OnSendPayloadSuccess = OnSuccess;
	OnSendPayloadError = OnError;

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallStaticVoidMethod(NearbyConnectionsClassName, "sendPayload", "(Landroid/app/Activity;Lcom/google/android/gms/nearby/connection/Payload;[Ljava/lang/String;)V",
		FJavaWrapper::GameActivityThis, Payload->JavaObject, NCConversionUtils::ToJavaStringArray(Endpoints));
#endif
}

#if PLATFORM_ANDROID
JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onStartAdvertisingSuccess(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnStartAdvertisingSuccess.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onStartAdvertisingError(JNIEnv* env, jclass clazz, jstring error)
{
	FString Error = NCConversionUtils::FromJavaString(error);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnStartAdvertisingError.ExecuteIfBound(Error);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onConnectionInitiated(JNIEnv* env, jclass clazz, jstring endpointId, jobject connectionInfo)
{
	FString EndpointId = NCConversionUtils::FromJavaString(endpointId);

	UNCConnectionInfo* ConnectionInfo = NewObject<UNCConnectionInfo>();
	ConnectionInfo->Init(connectionInfo);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnConnectionInitiated.ExecuteIfBound(EndpointId, ConnectionInfo);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onConnectionResult(JNIEnv* env, jclass clazz, jstring endpointId, int statusCode, jstring message)
{
	FString EndpointId = NCConversionUtils::FromJavaString(endpointId);
	FString Message = NCConversionUtils::FromJavaString(message);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnConnectionResult.ExecuteIfBound(EndpointId, statusCode, Message);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onDisconnected(JNIEnv* env, jclass clazz, jstring endpointId)
{
	FString EndpointId = NCConversionUtils::FromJavaString(endpointId);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnDisconnected.ExecuteIfBound(EndpointId);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onStartDiscoverySuccess(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnStartDiscoverySuccess.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onStartDiscoveryError(JNIEnv* env, jclass clazz, jstring error)
{
	FString Error = NCConversionUtils::FromJavaString(error);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnStartDiscoveryError.ExecuteIfBound(Error);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onEndpointFound(JNIEnv* env, jclass clazz, jstring endpointId, jstring serviceId, jstring endpointName, jbyteArray endpointInfo)
{
	FString EndpointId = NCConversionUtils::FromJavaString(endpointId);
	FString ServiceId = NCConversionUtils::FromJavaString(serviceId);
	FString EndpointName = NCConversionUtils::FromJavaString(endpointName);

	TArray<uint8> EndpointInfo = NCConversionUtils::ConvertToByteArray(endpointInfo);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnEndpointFound.ExecuteIfBound(EndpointId, ServiceId, EndpointName, EndpointInfo);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onEndpointLost(JNIEnv* env, jclass clazz, jstring endpointId)
{
	FString EndpointId = NCConversionUtils::FromJavaString(endpointId);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnEndpointLost.ExecuteIfBound(EndpointId);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onAcceptConnectionSuccess(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnAcceptConnectionSuccess.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onAcceptConnectionError(JNIEnv* env, jclass clazz, jstring error)
{
	FString Error = NCConversionUtils::FromJavaString(error);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnAcceptConnectionError.ExecuteIfBound(Error);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onPayloadReceived(JNIEnv* env, jclass clazz, jstring endpointId, jobject payload)
{
	FString EndpointId = NCConversionUtils::FromJavaString(endpointId);

	UNCPayload* Payload = NewObject<UNCPayload>();
	Payload->Init(payload);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnPayloadReceived.ExecuteIfBound(EndpointId, Payload);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onPayloadTransferUpdate(JNIEnv* env, jclass clazz, jstring endpointId, jobject payloadTransferUpdate)
{
	FString EndpointId = NCConversionUtils::FromJavaString(endpointId);

	FNCPayloadTransferUpdate PayloadTransferUpdate;
	PayloadTransferUpdate.PayloadId = NCMethodCallUtils::CallLongMethod(payloadTransferUpdate, "getPayloadId", "()J");
	PayloadTransferUpdate.Status = NCMethodCallUtils::CallIntMethod(payloadTransferUpdate, "getStatus", "()I");
	PayloadTransferUpdate.TotalBytes = NCMethodCallUtils::CallLongMethod(payloadTransferUpdate, "getTotalBytes", "()J");
	PayloadTransferUpdate.TransferredBytes = NCMethodCallUtils::CallLongMethod(payloadTransferUpdate, "getBytesTransferred", "()J");

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnPayloadTransferUpdate.ExecuteIfBound(EndpointId, PayloadTransferUpdate);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onRequestConnectionSuccess(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnRequestConnectionSuccess.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onRequestConnectionError(JNIEnv* env, jclass clazz, jstring error)
{
	FString Error = NCConversionUtils::FromJavaString(error);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnRequestConnectionError.ExecuteIfBound(Error);
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onSendPayloadSuccess(JNIEnv* env, jclass clazz)
{
	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnSendPayloadSuccess.ExecuteIfBound();
	});
}

JNI_METHOD void Java_com_ninevastudios_nearbyconnections_NearbyConnections_onSendPayloadError(JNIEnv* env, jclass clazz, jstring error)
{
	FString Error = NCConversionUtils::FromJavaString(error);

	AsyncTask(ENamedThreads::GameThread, [=]() {
		UNearbyConnectionsBPLibrary::OnSendPayloadError.ExecuteIfBound(Error);
	});
}
#endif