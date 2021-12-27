// Copyright (c) 2022 Nineva Studios

#include "NCConnectionInfo.h"

#include "NearbyConnectionsLog.h"

#if PLATFORM_ANDROID
#include "Android/Utils/MGJavaConvertor.h"
#include "Android/Utils/NCMethodCallUtils.h"
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
void UMGAndroidWrapperObject::Init(jobject javaObject)
{
	JNIEnv* Env = FAndroidApplication::GetJavaEnv();
	JavaObject = Env->NewGlobalRef(javaObject);
}
#endif