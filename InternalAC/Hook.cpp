#include "Hook.h"

bool Detour32(BYTE* src, BYTE* dst, const uintptr_t len) {
	if (len < 5)
		return false;

	DWORD curProtection;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &curProtection);

	uintptr_t relAddress = dst - src - 5;

	*src = 0xE9; //assembly jmp instruction opcode

	*(uintptr_t*)(src + 1) = relAddress;

	VirtualProtect(src, len, curProtection, &curProtection);
	return true;
}


BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t	len) {
	if (len < 5)
		return 0;

	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy_s(gateway, len, src, len);


	//gateway destination address
	uintptr_t gateWayRelAddr = src - gateway - 5;

	*(gateway + len) = 0xE9;


	*(uintptr_t*)((uintptr_t)gateway + len + 10) = gateWayRelAddr;

	Detour32(src, dst, len);
	
	return gateway;
}