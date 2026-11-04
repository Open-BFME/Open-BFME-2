// cl: /O2 /Ob2
// dxsdk
// platformsdk
// ?rva00903C20DeviceQuery@@YA_NXZ @ 0x0011CC30 (36B): reads the DX8 device global
// at 0x00DEDA34 (inlined DX8Wrapper::_Get_D3D_Device8), calls
// IDirect3DDevice9::ValidateDevice (vtable slot 70, offset 0x118) with an
// out-parameter for the pass count, and returns whether the call succeeded.
// Name is donor-derived from WW3D2 Rva00903C20DeviceQuery.cpp and is NOT proven
// by target evidence.
#include <d3d9.h>

// dx8wrapper.cpp's protected ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A, read through its
// public inline accessor. The device keeps its D3D8 type name but is a Direct3D 9 device.
struct IDirect3DDevice8;
#include "DX8WrapperClass.h"

bool rva00903C20DeviceQuery()
{
	DWORD passes = 0;
	return reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->ValidateDevice(&passes) == D3D_OK;
}
