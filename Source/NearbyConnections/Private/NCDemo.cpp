// Copyright (c) 2022 Nineva Studios

#include "NCDemo.h"

#include "HAL/UnrealMemory.h"

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