// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// dxsdk
// platformsdk
// Retail RVA 0x0093D050 is the five-argument BFME D3D9 UpdateSurface helper.
// It copies one source RECT to one destination POINT per count, advancing the
// source RECT array by 16 bytes and the destination POINT array by 8 bytes.
// The device call is IDirect3DDevice9::UpdateSurface (slot 30, +0x78), and every call records
// one DX8 wrapper call despite the underlying device being D3D9.

#include <d3d9.h>

// The device at 0x00DEDA34 is DX8Wrapper's protected D3DDevice (defined in
// dx8wrapper.cpp), read through its public inline accessor. It keeps its D3D8
// type name but is a Direct3D 9 device.
struct IDirect3DDevice8;

#include "DX8WrapperClass.h"

// This unit's view of that device.
static __forceinline IDirect3DDevice9 *copyDevice()
{
	return reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
}
extern unsigned number_of_DX8_calls;

extern "C" void __cdecl rva0093D050(
	IDirect3DSurface9 *source_surface,
	const RECT *source_rects,
	unsigned count,
	IDirect3DSurface9 *destination_surface,
	const POINT *destination_points)
{
	if (count != 0 && source_rects != 0)
	{
		if (count > 0)
		{
			do
			{
				copyDevice()->UpdateSurface(source_surface, source_rects,
					destination_surface, destination_points);
				++number_of_DX8_calls;
				destination_points += 1;
				source_rects += 1;
				--count;
			} while (count != 0);
		}
		return;
	}

	copyDevice()->UpdateSurface(source_surface, 0, destination_surface, 0);
	++number_of_DX8_calls;
}
