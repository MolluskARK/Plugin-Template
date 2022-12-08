#include "API/ARK/Ark.h"

// Called when the server is ready
void Plugin_ServerReadyInit()
{
    // Do post-"server ready" initialization here
}

// ArkServerApi hook that triggers once when the server is ready
DECLARE_HOOK(AShooterGameMode_BeginPlay, void, AShooterGameMode*);
void Hook_AShooterGameMode_BeginPlay(AShooterGameMode* _this)
{
    Log::GetLog()->info("Hook_AShooterGameMode_BeginPlay()");
    AShooterGameMode_BeginPlay_original(_this);

    // Call Plugin_ServerReadyInit() for post-"server ready" initialization
    Plugin_ServerReadyInit();
}

// Called by ArkServerApi when the plugin is loaded
extern "C" __declspec(dllexport) void Plugin_Init()
{
    // Do pre-"server ready" initialization here
    Log::Get().Init(PROJECT_NAME);

    ArkApi::GetHooks().SetHook("AShooterGameMode.BeginPlay", &Hook_AShooterGameMode_BeginPlay,
        &AShooterGameMode_BeginPlay_original);

    // If the server is ready, call Plugin_ServerReadyInit() for post-"server ready" initialization
    if (ArkApi::GetApiUtils().GetStatus() == ArkApi::ServerStatus::Ready)
        Plugin_ServerReadyInit();
}

// Called by ArkServerApi when the plugin is unloaded
extern "C" __declspec(dllexport) void Plugin_Unload()
{
    // Do cleanup here
    ArkApi::GetHooks().DisableHook("AShooterGameMode.BeginPlay", &Hook_AShooterGameMode_BeginPlay);
}