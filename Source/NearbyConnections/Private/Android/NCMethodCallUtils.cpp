// Copyright (c) 2022 Nineva Studios

#include "NCMethodCallUtils.h"
#include "NearbyConnectionsLog.h"

#include "Android/AndroidJava.h"

FString NCMethodCallUtils::CallStaticStringMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallStaticStringMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	jstring Return = static_cast<jstring>(Env->CallStaticObjectMethodV(Class, Method, Args));
	va_end(Args);

	const char* UTFString = Env->GetStringUTFChars(Return, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(Return, UTFString);

	Env->DeleteLocalRef(Class);

	return Result;
}

bool NCMethodCallUtils::CallStaticBoolMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallStaticBoolMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	bool Result = Env->CallStaticBooleanMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

int NCMethodCallUtils::CallStaticIntMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallStaticIntMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	int Result = Env->CallStaticIntMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

long NCMethodCallUtils::CallStaticLongMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallStaticIntMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	long Result = Env->CallStaticLongMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

jobject NCMethodCallUtils::CallStaticObjectMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallStaticObjectMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	jobject Result = Env->CallStaticObjectMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

void NCMethodCallUtils::CallStaticVoidMethod(const ANSICHAR* ClassName, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallStaticVoidMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = FAndroidApplication::FindJavaClass(ClassName);

	jmethodID Method = FJavaWrapper::FindStaticMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	Env->CallStaticVoidMethodV(Class, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);
}

FString NCMethodCallUtils::CallStringMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallStringMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	jstring Return = static_cast<jstring>(Env->CallObjectMethodV(object, Method, Args));
	va_end(Args);

	const char* UTFString = Env->GetStringUTFChars(Return, nullptr);
	FString Result(UTF8_TO_TCHAR(UTFString));
	Env->ReleaseStringUTFChars(Return, UTFString);

	Env->DeleteLocalRef(Class);

	return Result;
}

bool NCMethodCallUtils::CallBoolMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallBoolMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	bool Result = Env->CallBooleanMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

int NCMethodCallUtils::CallIntMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallIntMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	int Result = Env->CallIntMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}
jobject NCMethodCallUtils::CallObjectMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallObjectMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	jobject Result = Env->CallObjectMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}

void NCMethodCallUtils::CallVoidMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallVoidMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	Env->CallVoidMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);
}

long NCMethodCallUtils::CallLongMethod(jobject object, const ANSICHAR* MethodName, const ANSICHAR* MethodSignature, ...)
{
	UE_LOG(LogNearbyConnections, Verbose, TEXT("Method call CallLongMethod [%s]"), *FString(MethodName));

	bool bIsOptional = false;

	JNIEnv* Env = FAndroidApplication::GetJavaEnv();

	jclass Class = Env->GetObjectClass(object);

	jmethodID Method = FJavaWrapper::FindMethod(Env, Class, MethodName, MethodSignature, bIsOptional);

	va_list Args;
	va_start(Args, MethodSignature);
	long Result = Env->CallLongMethodV(object, Method, Args);
	va_end(Args);

	Env->DeleteLocalRef(Class);

	return Result;
}