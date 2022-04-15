#include <iostream>
#include <Windows.h>
#include "Helper.h"

/**
* JAKLGS - TEST AIMBOT 1.0
* Aimbot that targets bot in single player
* (entity list not implemented, targets bot 0)
*/
DWORD WINAPI MainThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "DLL SUCCESSFULLY LOADED" << std::endl;

    DWORD base = (DWORD)GetModuleHandle("ac_client.exe");
    std::cout << "Found base address" << std::endl;
    std::cout << "Aimbot Loaded. Press caps lock to enable" << std::endl;

    while (!GetAsyncKeyState(VK_DELETE)) {
        while (GetAsyncKeyState(VK_CAPITAL)) {
            AlignAim(base);
            //Assuming 60 fps
            Sleep(16);
        }
        Sleep(16);
    }

    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}