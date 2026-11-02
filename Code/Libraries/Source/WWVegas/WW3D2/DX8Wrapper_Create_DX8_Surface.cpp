// cl: /Oy /DNDEBUG /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// DX8Wrapper::_Create_DX8_Surface, retail 0x0011DC60, 62 bytes.
// Dedicated TU so SurfaceClass's constructor cannot inline this body.

class IDirect3DSurface9;

struct IDirect3DDevice8;
struct IDirect3DDevice9;

struct IDirect3DDevice9Vtbl
{
	void *reserved[36];
	long (__stdcall *CreateOffscreenPlainSurface)(
		IDirect3DDevice9 *self,
		unsigned width,
		unsigned height,
		unsigned format,
		unsigned pool,
		IDirect3DSurface9 **surface,
		void *sharedHandle);
};

struct IDirect3DDevice9
{
	IDirect3DDevice9Vtbl *lpVtbl;
};

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN
};

enum _D3DPOOL
{
	D3DPOOL_DEFAULT
};

#include "DX8WrapperClass.h"

// The DX8 call counter at 0x9EDA98 (the ledger's ?number_of_DX8_calls@@3IA).
extern unsigned number_of_DX8_calls;

IDirect3DSurface9 *DX8Wrapper::_Create_DX8_Surface(
	unsigned width, unsigned height, WW3DFormat format, _D3DPOOL pool)
{
	IDirect3DSurface9 *surface = 0;
	IDirect3DDevice9 *device = (IDirect3DDevice9 *)D3DDevice;
	device->lpVtbl->CreateOffscreenPlainSurface(
		device, width, height, (unsigned)format, (unsigned)pool, &surface, 0);
	++number_of_DX8_calls;
	return surface;
}

