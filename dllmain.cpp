﻿// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"
#include <Windows.h>
#include "offsets.h"
#include "LocalPlayer.h"
#include "Entity.h"
#include <iostream>



DWORD fMain(HMODULE hMod)
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle(TEXT("client.dll"));
    int* maxnumber = GetMaxEntities();

    //waiting key input for cheats
    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1) break;

        if (GetAsyncKeyState(VK_INSERT) & 1) { //main hack
            LocalPlayer* lp = GetLocalPlayer(moduleBase);
            std::cout << "My team number: " << *(lp->GetTeam()) << std::endl;
            std::vector<Entity*> entityList = GetEntities(moduleBase);
            int i = 0;
            for (unsigned int i = 0; i < entityList.size(); i++)
            {
                std::cout << "This entity's team number: " << *(entityList[i]->GetTeam()) << std::endl;
            }
        }
        Sleep(1);
    }

    FreeLibraryAndExitThread(hMod, 0);
    return 0;
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)fMain, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

