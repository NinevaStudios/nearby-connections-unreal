// Copyright (c) 2022 Nineva Studios

#pragma once

#include "Android/AndroidJava.h"
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"

namespace NCConversionUtils
{
	jbyteArray ConvertToJByteArray(const TArray<uint8>& byteArray);

	TArray<uint8> ConvertToByteArray(jbyteArray javaArray);

	jstring GetJavaString(FString string);

	FString FromJavaString(jstring javaString);
};