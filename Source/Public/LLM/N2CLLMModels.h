// Copyright (c) 2025 Nick McClure (Protospatial). All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "N2CLLMPricing.h"
#include "N2CLLMModels.generated.h"



/** Available OpenAI models */
UENUM(BlueprintType)
enum class EN2COpenAIModel : uint8
{
    // GPT-5.2 family (December 2025)
    GPT_5_2                 UMETA(DisplayName = "GPT-5.2", Value = "gpt-5.2"),
    GPT_5_2_Pro             UMETA(DisplayName = "GPT-5.2 Pro", Value = "gpt-5.2-pro"),
    // GPT-5 family (August 2025)
    GPT_5                   UMETA(DisplayName = "GPT-5", Value = "gpt-5"),
    GPT_5_Mini              UMETA(DisplayName = "GPT-5 Mini", Value = "gpt-5-mini"),
    GPT_5_Nano              UMETA(DisplayName = "GPT-5 Nano", Value = "gpt-5-nano"),
    // o-series reasoning models
    GPT_o4_mini             UMETA(DisplayName = "o4 Mini", Value = "o4-mini"),
    GPT_o3                  UMETA(DisplayName = "o3", Value = "o3"),
    GPT_o3_mini             UMETA(DisplayName = "o3 Mini", Value = "o3-mini"),
    GPT_o1                  UMETA(DisplayName = "o1", Value = "o1"),
    GPT_o1_Preview          UMETA(DisplayName = "o1 Preview", Value = "o1-preview-2024-09-12"),
    GPT_o1_Mini             UMETA(DisplayName = "o1 Mini", Value = "o1-mini-2024-09-12"),
    // GPT-4 family
    GPT_4_1                 UMETA(DisplayName = "GPT-4.1", Value = "gpt-4.1"),
    GPT4o_2024_08_06        UMETA(DisplayName = "GPT-4o", Value = "gpt-4o-2024-08-06"),
    GPT4o_Mini_2024_07_18   UMETA(DisplayName = "GPT-4o Mini", Value = "gpt-4o-mini-2024-07-18"),
};

/** Available Anthropic models */
UENUM(BlueprintType)
enum class EN2CAnthropicModel : uint8
{
    Claude4_5_Opus          UMETA(DisplayName = "Claude Opus 4.5", Value = "claude-opus-4-5-20251101"),
    Claude4_5_Sonnet        UMETA(DisplayName = "Claude Sonnet 4.5", Value = "claude-sonnet-4-5-20250929"),
    Claude4_1_Opus          UMETA(DisplayName = "Claude Opus 4.1", Value = "claude-opus-4-1-20250805"),
    Claude4_Opus            UMETA(DisplayName = "Claude Opus 4", Value = "claude-opus-4-20250514"),
    Claude4_Sonnet          UMETA(DisplayName = "Claude Sonnet 4", Value = "claude-sonnet-4-20250514"),
    Claude3_7_Sonnet        UMETA(DisplayName = "Claude 3.7 Sonnet", Value = "claude-3-7-sonnet-20250219"),
    Claude3_5_Sonnet        UMETA(DisplayName = "Claude 3.5 Sonnet", Value = "claude-3-5-sonnet-20241022"),
    Claude3_5_Haiku         UMETA(DisplayName = "Claude 3.5 Haiku", Value = "claude-3-5-haiku-20241022"),
};

/** Available Gemini models */
UENUM(BlueprintType)
enum class EN2CGeminiModel : uint8
{
    Gemini_3_Pro_Preview         UMETA(DisplayName = "Gemini 3 Pro Preview", Value = "gemini-3-pro-preview"),
    Gemini_3_Flash_Preview       UMETA(DisplayName = "Gemini 3 Flash Preview", Value = "gemini-3-flash-preview"),
    Gemini_2_5_Pro            UMETA(DisplayName = "Gemini 2.5 Pro Preview", Value = "gemini-2.5-pro-preview-05-06"),
    Gemini_2_5_Flash          UMETA(DisplayName = "Gemini 2.5 Flash Preview", Value = "gemini-2.5-flash-preview-05-20"),
    Gemini_Flash_2_0             UMETA(DisplayName = "Gemini 2.0 Flash", Value = "gemini-2.0-flash"),
    Gemini_Flash_Lite_2_0        UMETA(DisplayName = "Gemini 2.0 Flash-Lite-Preview-02-05", Value = "gemini-2.0-flash-lite-preview-02-05"),
    Gemini_1_5_Flash             UMETA(DisplayName = "Gemini 1.5 Flash", Value = "gemini-1.5-flash"),
    Gemini_1_5_Pro               UMETA(DisplayName = "Gemini 1.5 Pro", Value = "gemini-1.5-pro"),
    Gemini_2_0_ProExp_02_05      UMETA(DisplayName = "Gemini 2.0 Pro Exp 02-05", Value = "gemini-2.0-pro-exp-02-05"),
    Gemini_2_0_FlashThinkingExp  UMETA(DisplayName = "Gemini 2.0 Flash Thinking Exp 01-21", Value = "gemini-2.0-flash-thinking-exp-01-21"),
};

/** Available DeepSeek models */
UENUM(BlueprintType)
enum class EN2CDeepSeekModel : uint8
{
    DeepSeek_R1        UMETA(DisplayName = "DeepSeek R1", Value = "deepseek-reasoner"),
    DeepSeek_V3        UMETA(DisplayName = "DeepSeek V3", Value = "deepseek-chat"),
    DeepSeek_V4_Flash  UMETA(DisplayName = "DeepSeek V4 Flash", Value = "deepseek-v4-flash"),
};


/** Helper functions for model enums */
struct FN2CLLMModelUtils
{
    /** Model value getters */
    static FString GetOpenAIModelValue(EN2COpenAIModel Model);
    static FString GetAnthropicModelValue(EN2CAnthropicModel Model);
    static FString GetGeminiModelValue(EN2CGeminiModel Model);
    static FString GetDeepSeekModelValue(EN2CDeepSeekModel Model);

    /** Pricing getters */
    static FN2COpenAIPricing GetOpenAIPricing(EN2COpenAIModel Model);
    static FN2CAnthropicPricing GetAnthropicPricing(EN2CAnthropicModel Model);
    static FN2CDeepSeekPricing GetDeepSeekPricing(EN2CDeepSeekModel Model);
    static FN2CGeminiPricing GetGeminiPricing(EN2CGeminiModel Model);

    /** System prompt support checks - delegates to FN2CLLMModelRegistry */
    static bool SupportsSystemPrompts(EN2COpenAIModel Model);
    static bool SupportsSystemPrompts(EN2CAnthropicModel Model);
};
