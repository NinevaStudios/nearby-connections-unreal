// Copyright (c) 2022 Nineva Studios

#include "NCConnectionInfo.h"

#include "NearbyConnectionsLog.h"

#if PLATFORM_ANDROID
#include "Android/NCConversionUtils.h"
#include "Android/NCMethodCallUtils.h"
#endif

UNCConnectionInfo::~UNCConnectionInfo()
{
	if (!IsNativeObjectValid())
	{
		return;
	}

#if PLATFORM_ANDROID
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	Env->DeleteGlobalRef(JavaObject);
	JavaObject = nullptr;
#endif
}

FString UNCConnectionInfo::GetEndpointName()
{
	FString Result;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	Result = NCMethodCallUtils::CallStringMethod(JavaObject, "getEndpointName", "()Ljava/lang/String;");
#endif

	return Result;
}

FString UNCConnectionInfo::GetAuthenticationDigits()
{
	FString Result;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	Result = NCMethodCallUtils::CallStringMethod(JavaObject, "getAuthenticationDigits", "()Ljava/lang/String;");
#endif

	return Result;
}

TArray<uint8> UNCConnectionInfo::GetRawAuthenticationToken()
{
	TArray<uint8> Result;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	jbyteArray javaBytes = static_cast<jbyteArray>(NCMethodCallUtils::CallObjectMethod(JavaObject, "getRawAuthenticationToken", "()[B"));

	if (javaBytes == nullptr)
		return Result;

	Result = NCConversionUtils::ConvertToByteArray(javaBytes);
#endif

	return Result;
}

bool UNCConnectionInfo::IsIncomingConnection()
{
	bool Result = false;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	Result = NCMethodCallUtils::CallBoolMethod(JavaObject, "isIncomingConnection", "()Z");
#endif

	return Result;
}

TArray<uint8> UNCConnectionInfo::GetEndpointInfo()
{
	TArray<uint8> Result;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	jbyteArray javaBytes = static_cast<jbyteArray>(NCMethodCallUtils::CallObjectMethod(JavaObject, "getEndpointInfo", "()[B"));

	if (javaBytes == nullptr)
		return Result;

	Result = NCConversionUtils::ConvertToByteArray(javaBytes);
#endif

	return Result;
}

bool UNCConnectionInfo::IsNativeObjectValid()
{
	bool Result = false;

#if PLATFORM_ANDROID
	Result = JavaObject != nullptr;
#endif
#if !WITH_EDITOR
	if (!Result)
	{
		UE_LOG(LogNearbyConnections, Error, TEXT("Android native object is not valid."));
	}
#endif
	return Result;
}

#if PLATFORM_ANDROID
void UNCConnectionInfo::Init(jobject javaObject)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	JavaObject = Env->NewGlobalRef(javaObject);
}
#endif