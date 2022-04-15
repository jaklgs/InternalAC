#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

#ifndef HELPERS_H
#define HELPERS_H

struct Vec3 {
	float x;
	float y;
	float z;
};

DWORD GetPointerAddress(DWORD address, std::vector<DWORD> offsets);

Vec3 GetPlayerPosition(DWORD base);

Vec3 GetBotPosition(DWORD base);

float CalcYaw(Vec3 playerPos, Vec3 botPos);

float CalcPitch(Vec3 playerPos, Vec3 botPos);;

void AlignAim(DWORD base);
#endif