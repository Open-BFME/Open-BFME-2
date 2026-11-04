// cl: /GX-
// ?Rva00042F6DGet@@YAHXZ @ 0x00042F6D (6B): global dword getter reading
// 0x00DEDA7C (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape; the
// load address is a .data global). Dedicated TU so no caller inlines the
// load (Rva007EB810Get precedent).

// dx8wrapper.cpp's protected ?CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A, read through a
// friend of the canonical DX8WrapperClass.h (real decoration, no alias).
class DX8Caps;
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

int Rva00042F6DGet(void)
{
	return (int)DX8Wrapper::CurrentCaps;
}
