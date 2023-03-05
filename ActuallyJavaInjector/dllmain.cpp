#include <Windows.h>
#include <cstdio>
#include <iostream>
#include "Logger.h"
#include "Mapping.h"
#include "MinecraftHandler.h"


HMODULE module;

DWORD WINAPI HookJVM(LPVOID lpParam)
{
    MinecraftHandler(module);
    return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        //DisableThreadLibraryCalls(hModule);
        module = hModule;
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HookJVM, nullptr, 0, nullptr);
    }

	return TRUE;
}

