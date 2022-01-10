// Copyright (c) 2022 Nineva Studios

#include "NCDemo.h"

#include "NearbyConnectionsLog.h"

#include "HAL/UnrealMemory.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

FString UNCDemo::StringFromBytes(const TArray<uint8>& Bytes)
{
    return BytesToString(Bytes.GetData(), Bytes.Num());
}

TArray<uint8> UNCDemo::BytesFromString(const FString& String)
{
    int Size = String.Len() * sizeof(TCHAR);
    uint8* ByteArray = reinterpret_cast<uint8*>(FMemory::Malloc(Size + 1));

    StringToBytes(String, ByteArray, Size + 1);

    return TArray<uint8>(ByteArray, Size);
}

FString UNCDemo::GenerateAndSaveTextFile()
{
	FString path;
	FString text = FGuid::NewGuid().ToString();
#if PLATFORM_ANDROID
	path = FPaths::ProjectPersistentDownloadDir() + "/DemoFiles/";
	path = path + text + ".txt";
#endif
	FFileHelper::SaveStringToFile(text, *path);
	return path;
}

FString UNCDemo::ReadTextFile(const FString& Path)
{
	FString Result;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.FileExists(*Path))
	{
	 	FFileHelper::LoadFileToString(Result, *Path);
	}
	else
	{
		UE_LOG(LogNearbyConnections, Error, TEXT("File not found"));
	}

	return Result;
}