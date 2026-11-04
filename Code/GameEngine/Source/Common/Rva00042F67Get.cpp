// cl: /GX-
// ?Rva00042F67Get@@YAHXZ @ 0x00042F67 (6B): global dword getter reading
// 0x00DEDA34 (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape; the
// load address is a .data global). Dedicated TU so no caller inlines the
// load (Rva007EB810Get precedent).

// dx8wrapper.cpp's protected ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A, read through a
// friend of the canonical DX8WrapperClass.h (real decoration, no alias).
struct IDirect3DDevice8;
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

int Rva00042F67Get(void)
{
	return (int)DX8Wrapper::D3DDevice;
}
