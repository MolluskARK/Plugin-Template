#include "API/ARK/Ark.h"

// Called when the server is ready, do post-"server ready" initialization here
void OnServerReady()
{
    Log::GetLog()->info("Hello, world!");
}

// Hook that triggers once when the server is ready
DECLARE_HOOK(AShooterGameMode_BeginPlay, void, AShooterGameMode*);
void Hook_AShooterGameMode_BeginPlay(AShooterGameMode* _this)
{
    AShooterGameMode_BeginPlay_original(_this);

    OnServerReady();
}

// Called by ArkServerApi when the plugin is loaded, do pre-"server ready" initialization here
extern "C" __declspec(dllexport) void Plugin_Init()
{
    Log::Get().Init(PROJECT_NAME);

    ArkApi::GetHooks().SetHook("AShooterGameMode.BeginPlay", Hook_AShooterGameMode_BeginPlay,
        &AShooterGameMode_BeginPlay_original);

    if (ArkApi::GetApiUtils().GetStatus() == ArkApi::ServerStatus::Ready)
        OnServerReady();
}

// Called by ArkServerApi when the plugin is unloaded, do cleanup here
extern "C" __declspec(dllexport) void Plugin_Unload()
{
    ArkApi::GetHooks().DisableHook("AShooterGameMode.BeginPlay", Hook_AShooterGameMode_BeginPlay);
}