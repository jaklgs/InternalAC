#pragma once
#include <Windows.h>
#include <vector>

struct Vec3 {
	float x;
	float y;
	float z;
};

extern DWORD base;

DWORD GetPointerAddress(DWORD address, std::vector<DWORD> offsets);

Vec3 GetPlayerPosition();

Vec3 GetBotPosition();

float CalcYaw(Vec3 playerPos, Vec3 botPos);

float CalcPitch(Vec3 playerPos, Vec3 botPos);;

void AlignAim();