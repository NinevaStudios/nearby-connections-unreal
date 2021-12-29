// Copyright (c) 2022 Nineva Studios

#include "NCConversionUtils.h"
#include "NCMethodCallUtils.h"

namespace NCConversionUtils
{
	jbyteArray ConvertToJByteArray(const TArray<uint8>& byteArray)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jbyteArray javaByteArray = (jbyteArray)Env->NewByteArray(byteArray.Num());

		jbyte* javaByteArrayPtr = (jbyte*)malloc(byteArray.Num() * sizeof(jbyte));

		for (int i = 0; i < byteArray.Num(); i++)
		{
			javaByteArrayPtr[i] = byteArray[i];
		}

		Env->SetByteArrayRegion(javaByteArray, 0, byteArray.Num(), javaByteArrayPtr);

		free(javaByteArrayPtr);

		return javaByteArray;
	}

	TArray<uint8> ConvertToByteArray(jbyteArray javaArray)
	{
		TArray<uint8> byteArray;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		jbyte* javaByte = Env->GetByteArrayElements(javaArray, 0);

		int length = Env->GetArrayLength(javaArray);

		for (int i = 0; i < length; i++)
		{
			byteArray.Add(javaByte[i]);
		}

		return byteArray;
	}

	jobjectArray ToJavaStringArray(const TArray<FString>& StringArray)
	{
		JNIEnv* Env = FAndroidApplication::GetJavaEnv();
		jobjectArray JStringArray = (jobjectArray)Env->NewObjectArray(StringArray.Num(), FJavaWrapper::JavaStringClass, nullptr);

		for (int i = 0; i < StringArray.Num(); i++)
		{
			auto JString = FJavaClassObject::GetJString(StringArray[i]);
			Env->SetObjectArrayElement(JStringArray, i, *JString);
		}

		return JStringArray;
	}

	TArray<FString> ConvertToStringArray(jobjectArray javaStringArray)
	{
		TArray<FString> stringArray;

		JNIEnv* Env = FAndroidApplication::GetJavaEnv();

		int length = Env->GetArrayLength(javaStringArray);

		for (int i = 0; i < length; i++)
		{
			jstring javaString = static_cast<jstring>(Env->GetObjectArrayElement(javaStringArray, i));

			stringArray.Add(FromJavaString(javaString));
		}

		return stringArray;
	}

	jstring GetJavaString(FString string)
	{
		JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
		jstring local = Env->NewStringUTF(TCHAR_TO_UTF8(*string));
		jstring result = (jstring)Env->NewGlobalRef(local);
		Env->DeleteLocalRef(local);
		return result;
	}

	FString FromJavaString(jstring javaString)
	{
		JNIEnv* Env = AndroidJavaEnv::GetJavaEnv();
		const char* UTFString = Env->GetStringUTFChars(javaString, nullptr);
		FString Result(UTF8_TO_TCHAR(UTFString));
		Env->ReleaseStringUTFChars(javaString, UTFString);
		Env->DeleteLocalRef(javaString);

		return Result;
	}

	jobject ToJavaOptions(const FNCConnectionOptions& Options)
	{
		return NCMethodCallUtils::CallStaticObjectMethod(UNearbyConnectionsBPLibrary::NearbyConnectionsClassName, "createOptions", 
			"(IZZ)Lcom/ninevastudios/nearbyconnections/Options;", (int) Options.Strategy, Options.IsLowPower, Options.IsDisruptiveUpgrade);
	}
}