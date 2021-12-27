// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

#include "NearbyConnectionsBPLibrary.h"

namespace NCConversionUtils
{
	jbyteArray ConvertToJByteArray(const TArray<uint8>& byteArray);
	TArray<uint8> ConvertToByteArray(jbyteArray javaArray);

	jobjectArray ToJavaStringArray(const TArray<FString>& StringArray);
	TArray<FString> ConvertToStringArray(jobjectArray javaStringArray);

	jstring GetJavaString(FString string);
	FString FromJavaString(jstring javaString);

	jobject ToJavaOptions(const FNCConnectionOptions& Options);
};