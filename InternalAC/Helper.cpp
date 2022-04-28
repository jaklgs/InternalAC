#include "Helper.h"
#define PI 3.141592653589f

DWORD base = NULL;

DWORD GetPointerAddress(DWORD address, std::vector<DWORD> offsets) {
	for (int i = 0; i < offsets.size(); i++) {
		address = *(DWORD*)address;
		address += offsets[i];
	}
	return address;
}

Vec3 GetPlayerPosition() {
	Vec3 pos;
	pos.x = *(float*)GetPointerAddress(base + 0x00187C0C, { 0x28 });
	pos.y = *(float*)GetPointerAddress(base + 0x00187C0C, { 0x2C });
	pos.z = *(float*)GetPointerAddress(base + 0x00187C0C, { 0x30 });

	return pos;
}

Vec3 GetBotPosition() {
	Vec3 pos;
	pos.x = *(float*)GetPointerAddress(base + 0x0018EFDC, { 0x0, 0x28 });
	pos.y = *(float*)GetPointerAddress(base + 0x0018EFDC, { 0x0, 0x2C });
	pos.z = *(float*)GetPointerAddress(base + 0x0018EFDC, { 0x0, 0x30 });

	return pos;
}

float CalcYaw(Vec3 playerPos, Vec3 botPos) {
	float dx = botPos.x - playerPos.x;
	float dy = botPos.y - playerPos.y;

	float relDeg = (float)atan(dy / dx) * (180.0f / PI);
	float theta = dx > 0 ? 90 + relDeg : 270 + relDeg;
	return theta;
}

float CalcPitch(Vec3 playerPos, Vec3 botPos) {
	float dx = botPos.x - playerPos.x;
	float dy = botPos.y - playerPos.y;
	float height = botPos.z - playerPos.z + 0.5f;
	float horizontal = (float)sqrt(dx * dx + dy * dy);

	float theta = (float)asin(height / horizontal) * (180.0f / PI);
	return theta;
}

void AlignAim() {
	*(float*)GetPointerAddress(base + 0x0017B0B8, { 0x34 }) =
		CalcYaw(GetPlayerPosition(), GetBotPosition());

	*(float*)GetPointerAddress(base + 0x0017B0B8, { 0x38 }) =
			CalcPitch(GetPlayerPosition(), GetBotPosition());
}