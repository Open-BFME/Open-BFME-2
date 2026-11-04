// cl: /GX-
// ?Rva0011009AGet@@YAHXZ @ 0x0011009A (6B): global dword getter reading
// 0x00DB5FD4 (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape).
// First of an adjacent pair (0x11009A/A0, themselves preceded by an A0-form
// global byte getter); dedicated TU so no caller inlines the load
// (Rva007EB810Get precedent).

// 0x00DB5FD4/0x00DB5FD8 are the data ledger's DX8Wrapper::ResolutionWidth
// and ResolutionHeight (dx8wrapper.cpp's protected statics, @@1): both getters
// read them as friends of the canonical DX8WrapperClass.h.
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

int Rva0011009AGet(void)
{
	return DX8Wrapper::ResolutionWidth;
}

// ?Rva001100A0Get@@YAHXZ @ 0x001100A0 (6B): same shape over 0x00DB5FD8.


int Rva001100A0Get(void)
{
	return DX8Wrapper::ResolutionHeight;
}
