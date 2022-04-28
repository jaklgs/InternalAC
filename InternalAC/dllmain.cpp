#include <iostream>
#include "Helper.h"
#include "Hook.h"

/**
* JAKLGS - TEST AIMBOT 1.1
* Aimbot that targets bot in single player
* (entity list not implemented, targets bot 0)
*/

typedef BOOL(__stdcall* twglSwapBuffers) (HDC hDc);
twglSwapBuffers owglSwapBuffer;
BOOL __stdcall hkwglSwapBuffers(HDC hDc) {

    if (GetAsyncKeyState(VK_CAPITAL)) {
        AlignAim();
    }

    return owglSwapBuffer(hDc);
}

DWORD WINAPI MainThread(HMODULE hModule) {
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    std::cout << "DLL SUCCESSFULLY LOADED" << std::endl;

    base = (DWORD)GetModuleHandle("ac_client.exe");
    std::cout << "[LOG] Found base address "  << base << std::endl;
    std::cout << "Aimbot Loaded - Press caps lock to enable" << std::endl;

    //hook, for some reason gdi instead of opengl
    owglSwapBuffer = (twglSwapBuffers)GetProcAddress(GetModuleHandle("GDI32.dll"), "SwapBuffers"); 
    owglSwapBuffer = (twglSwapBuffers)TrampHook32((BYTE*)owglSwapBuffer, (BYTE*)hkwglSwapBuffers, 6);

    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    //fix ugly switch in future update
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