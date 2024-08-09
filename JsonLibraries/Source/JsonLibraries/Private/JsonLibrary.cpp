// Fill out your copyright notice in the Description page of Project Settings.

#include "JsonLibrary.h"

bool UJsonLibrary::ParseJSON(const FString& JSONString, FBlueprintJsonObject& OutJsonObject)
{
    TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
    TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JSONString);
    if (FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        OutJsonObject = FBlueprintJsonObject(JsonObject);
        return true;
    }
    return false;
}

bool UJsonLibrary::GetStringField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, FString& OutValue)
{
    if (!JsonObject.InternalObject.IsValid())
        return false;
    return JsonObject.InternalObject->TryGetStringField(FieldName, OutValue);
}

bool UJsonLibrary::GetIntegerField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, int32& OutValue)
{
    if (!JsonObject.InternalObject.IsValid())
        return false;

    if (JsonObject.InternalObject->TryGetNumberField(FieldName, OutValue))
        return true;

    FString StringValue;
    if (JsonObject.InternalObject->TryGetStringField(FieldName, StringValue))
    {
        if (StringValue.IsNumeric())
        {
            OutValue = FCString::Atoi(*StringValue);
            return true;
        }
    }

    return false;
}

bool UJsonLibrary::GetFloatField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, float& OutValue)
{
    if (!JsonObject.InternalObject.IsValid())
        return false;
    double TempValue;
    if (JsonObject.InternalObject->TryGetNumberField(FieldName, TempValue))
    {
        OutValue = static_cast<float>(TempValue);
        return true;
    }
    return false;
}

bool UJsonLibrary::GetBoolField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, bool& OutValue)
{
    if (!JsonObject.InternalObject.IsValid())
        return false;
    return JsonObject.InternalObject->TryGetBoolField(FieldName, OutValue);
}

bool UJsonLibrary::GetArrayField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, TArray<FBlueprintJsonObject>& OutArray)
{
    if (!JsonObject.InternalObject.IsValid())
        return false;

    const TArray<TSharedPtr<FJsonValue>>* JsonArray;
    if (JsonObject.InternalObject->TryGetArrayField(FieldName, JsonArray))
    {
        for (const auto& Value : *JsonArray)
        {
            if (Value->Type == EJson::Object)
            {
                OutArray.Add(FBlueprintJsonObject(Value->AsObject()));
            }
            else if (Value->Type == EJson::String)
            {
                TSharedPtr<FJsonObject> StringObject = MakeShared<FJsonObject>();
                StringObject->SetStringField("value", Value->AsString());
                OutArray.Add(FBlueprintJsonObject(StringObject));
            }
        }
        return true;
    }
    return false;
}

bool UJsonLibrary::GetObjectField(const FBlueprintJsonObject& JsonObject, const FString& FieldName, FBlueprintJsonObject& OutObject)
{
    if (!JsonObject.InternalObject.IsValid())
        return false;
    const TSharedPtr<FJsonObject>* TempObject = nullptr;
    if (JsonObject.InternalObject->TryGetObjectField(FieldName, TempObject) && TempObject != nullptr)
    {
        OutObject = FBlueprintJsonObject(*TempObject);
        return true;
    }
    return false;
}
