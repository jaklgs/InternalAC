#pragma once
#include <Windows.h>
#include <iostream>

bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len);

BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t	len);