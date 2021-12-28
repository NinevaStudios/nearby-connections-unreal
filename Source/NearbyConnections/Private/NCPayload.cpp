// Copyright (c) 2022 Nineva Studios

#include "NCPayload.h"

#include "NearbyConnectionsLog.h"

#include "NearbyConnectionsBPLibrary.h"

#if PLATFORM_ANDROID
#include "Android/Utils/NCConversionUtils.h"
#include "Android/Utils/NCMethodCallUtils.h"
#endif

UNCPayload::~UNCPayload()
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

UNCPayload* UNCPayload::PayloadFromBytes(const TArray<uint8>& Bytes)
{
	UNCPayload* Payload = NewObject<UNCPayload>();

#if PLATFORM_ANDROID
	jobject javaPayload = NCMethodCallUtils::CallStaticObjectMethod(UNearbyConnectionsBPLibrary::NearbyConnectionsClassName, "payloadFromBytes",
		"([B)Lcom/google/android/gms/nearby/connection/Payload;", NCConversionUtils::ConvertToJByteArray(Bytes));

	Payload->Init(javaPayload);
#endif

	return Payload;
}

UNCPayload* UNCPayload::PayloadFromFile(const FString& Path)
{
	UNCPayload* Payload = NewObject<UNCPayload>();

#if PLATFORM_ANDROID
	jobject javaPayload = NCMethodCallUtils::CallStaticObjectMethod(UNearbyConnectionsBPLibrary::NearbyConnectionsClassName, "payloadFromFile",
		"(Ljava/lang/String;)Lcom/google/android/gms/nearby/connection/Payload;", NCConversionUtils::GetJavaString(Path));

	Payload->Init(javaPayload);
#endif

	return Payload;
}

int64 UNCPayload::GetId()
{
	int64 Result = 0;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	Result = NCMethodCallUtils::CallLongMethod(JavaObject, "getId", "()J");
#endif

	return Result;
}

ENCPayloadType UNCPayload::GetType()
{
	ENCPayloadType Result = ENCPayloadType::None;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	Result = (ENCPayloadType) NCMethodCallUtils::CallIntMethod(JavaObject, "getType", "()I");
#endif

	return Result;
}

TArray<uint8> UNCPayload::GetBytes()
{
	TArray<uint8> Result;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	jbyteArray javaBytes = static_cast<jbyteArray>(NCMethodCallUtils::CallObjectMethod(JavaObject, "asBytes", "()[B"));

	if (javaBytes == nullptr)
		return Result;

	Result = NCConversionUtils::ConvertToByteArray(javaBytes);
#endif

	return Result;
}

FString UNCPayload::GetFilePath()
{
	FString Result;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	Result = NCMethodCallUtils::CallStaticStringMethod(UNearbyConnectionsBPLibrary::NearbyConnectionsClassName, "getPayloadFilePath", 
		"(Lcom/google/android/gms/nearby/connection/Payload;)Ljava/lang/String;", JavaObject);
#endif

	return Result;
}

void UNCPayload::Close()
{
	if (!IsNativeObjectValid())
		return;

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallVoidMethod(JavaObject, "close", "()V");
#endif
}

void UNCPayload::SetOffset(int64 Offset)
{
	if (!IsNativeObjectValid())
		return;

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallVoidMethod(JavaObject, "setOffset", "(J)V", Offset);
#endif
}

int64 UNCPayload::GetOffset()
{
	int64 Result = 0;

	if (!IsNativeObjectValid())
		return Result;

#if PLATFORM_ANDROID
	Result = NCMethodCallUtils::CallLongMethod(JavaObject, "getOffset", "()J");
#endif

	return Result;
}

void UNCPayload::SetSensitive(bool IsSensitive)
{
	if (!IsNativeObjectValid())
		return;

#if PLATFORM_ANDROID
	NCMethodCallUtils::CallVoidMethod(JavaObject, "setSensitive", "(Z)V", IsSensitive);
#endif
}

bool UNCPayload::IsNativeObjectValid()
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
void UMGAndroidWrapperObject::Init(jobject javaObject)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	JavaObject = Env->NewGlobalRef(javaObject);
}
#endif