// Copyright (c) 2025 Nick McClure (Protospatial). All Rights Reserved.

#include "LLM/Providers/N2CDeepSeekService.h"

#include "Core/N2CSettings.h"
#include "LLM/N2CLLMModels.h"
#include "LLM/N2CSystemPromptManager.h"
#include "Utils/N2CLogger.h"

UN2CResponseParserBase* UN2CDeepSeekService::CreateResponseParser()
{
    UN2CDeepSeekResponseParser* Parser = NewObject<UN2CDeepSeekResponseParser>(this);
    return Parser;
}

void UN2CDeepSeekService::GetConfiguration(
    FString& OutEndpoint,
    FString& OutAuthToken,
    bool& OutSupportsSystemPrompts)
{
    OutEndpoint = Config.ApiEndpoint;
    OutAuthToken = Config.ApiKey;
    OutSupportsSystemPrompts = true;  // DeepSeek always supports system prompts
}

void UN2CDeepSeekService::GetProviderHeaders(TMap<FString, FString>& OutHeaders) const
{
    OutHeaders.Add(TEXT("Authorization"), FString::Printf(TEXT("Bearer %s"), *Config.ApiKey));
    OutHeaders.Add(TEXT("Content-Type"), TEXT("application/json"));
}

FString UN2CDeepSeekService::FormatRequestPayload(const FString& UserMessage, const FString& SystemMessage) const
{
    // Create and configure payload builder
    UN2CLLMPayloadBuilder* PayloadBuilder = NewObject<UN2CLLMPayloadBuilder>();
    PayloadBuilder->Initialize(Config.Model);
    PayloadBuilder->ConfigureForDeepSeek();
    
    // Set common parameters
    PayloadBuilder->SetTemperature(0.0f);

    // Max output tokens - configurable (reasoning models consume part of this budget)
    const UN2CSettings* Settings = GetDefault<UN2CSettings>();
    PayloadBuilder->SetMaxTokens(Settings ? FMath::Max(Settings->MaxOutputTokens, 1024) : 65536);
    
    // Try prepending source files to the user message
    FString FinalUserMessage = UserMessage;
    PromptManager->PrependSourceFilesToUserMessage(FinalUserMessage);
    
    // Add messages
    PayloadBuilder->AddSystemMessage(SystemMessage);
    PayloadBuilder->AddUserMessage(FinalUserMessage);
    
    // Use the model ID actually in use (honors the "Custom Model ID" override).
    // The reasoner model does not support json_object response format.
    const FString ModelValue = Config.Model;
    if (ModelValue != TEXT("deepseek-reasoner"))
    {
        PayloadBuilder->SetJsonResponseFormat(UN2CLLMPayloadBuilder::GetN2CResponseSchema());
    }
    
    // Build and return the payload
    return PayloadBuilder->Build();
}
