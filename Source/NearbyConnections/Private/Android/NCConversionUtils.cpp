// Copyright (c) 2022 Nineva Studios

#include "NCConversionUtils.h"

jbyteArray NCConversionUtils::ConvertToJByteArray(const TArray<uint8>& byteArray)
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

TArray<uint8> NCConversionUtils::ConvertToByteArray(jbyteArray javaArray)
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

jobjectArray NCConversionUtils::ToJavaStringArray(const TArray<FString>& StringArray)
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

TArray<FString> NCConversionUtils::ConvertToStringArray(jobjectArray javaStringArray)
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

jstring NCConversionUtils::GetJavaString(FString string)
{
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();
	jstring local = JEnv->NewStringUTF(TCHAR_TO_UTF8(*string));
	jstring result = (jstring)JEnv->NewGlobalRef(local);
	JEnv->DeleteLocalRef(local);
	return result;
}

FString NCConversionUtils::FromJavaString(jstring javaString)
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
	JNIEnv* JEnv = AndroidJavaEnv::GetJavaEnv();

	jclass OptionsClass = FJavaWrapper::FindClass(Env, "com/ninevastudios/nearbyconnections/Options", false);
	jmethodID OptionsCtor = FJavaWrapper::FindMethod(Env, OptionsClass, "<init>", "(IZZ)V", false);
	return Env->NewObject(OptionsClass, OptionsCtor, (int) Options.Strategy, Options.IsLowPower, Options.IsDisruptiveUpgrade);
}
