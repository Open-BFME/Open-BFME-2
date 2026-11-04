// cl: /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/GameEngineDevice/Source/W3DDevice/GameClient
// dxsdk
// platformsdk

#include <d3d9.h>

typedef int Int;
typedef unsigned long UnsignedLong;

// The rectangle and surface types keep the names this unit's decorations carry
// (getBackBufferSurface006e, copySurfaceRects006e, W3DRadarResetSurface), but
// the objects are a RECT and an IDirect3DSurface9 (AddRef slot 1, Release 2).
struct BfmeRect;
class SurfaceResource;

// The device at 0x00DEDA34 is DX8Wrapper's protected D3DDevice (defined in
// dx8wrapper.cpp), read through its public inline accessor. It keeps its D3D8
// type name but is a Direct3D 9 device (GetBackBuffer slot 18, StretchRect 34).
struct IDirect3DDevice8;

#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

// This unit's view of that device.
static __forceinline IDirect3DDevice9 *backBufferDevice()
{
	return reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
}
extern unsigned number_of_DX8_calls;

class W3DRadarResetSurface
{
public:
	W3DRadarResetSurface(SurfaceResource *surface);
	W3DRadarResetSurface(unsigned width, unsigned height, unsigned format, unsigned pool);

	__forceinline W3DRadarResetSurface(const W3DRadarResetSurface &other) : m_surface(other.m_surface)
	{
		if (m_surface)
			reinterpret_cast<IDirect3DSurface9 *>(m_surface)->AddRef();
	}

	~W3DRadarResetSurface();

	__forceinline SurfaceResource *getSurface() const
	{
		return m_surface;
	}

private:
	SurfaceResource *m_surface;
};

W3DRadarResetSurface getBackBufferSurface006e(Int index)
{
	SurfaceResource *surface = 0;
	backBufferDevice()->GetBackBuffer(0, index, D3DBACKBUFFER_TYPE_MONO,
		reinterpret_cast<IDirect3DSurface9 **>(&surface));
	++number_of_DX8_calls;

	if (surface)
	{
		W3DRadarResetSurface result(surface);
		reinterpret_cast<IDirect3DSurface9 *>(surface)->Release();
		surface = 0;
		return result;
	}

	return W3DRadarResetSurface(0x40, 0x40, 0x16, 2);
}

void copySurfaceRects006e(W3DRadarResetSurface source, const BfmeRect *sourceRect,
	W3DRadarResetSurface destination, const BfmeRect *destinationRect, Int mode)
{
	backBufferDevice()->StretchRect(
		reinterpret_cast<IDirect3DSurface9 *>(source.getSurface()), reinterpret_cast<const RECT *>(sourceRect),
		reinterpret_cast<IDirect3DSurface9 *>(destination.getSurface()), reinterpret_cast<const RECT *>(destinationRect),
		(D3DTEXTUREFILTERTYPE)mode);
	++number_of_DX8_calls;
}
