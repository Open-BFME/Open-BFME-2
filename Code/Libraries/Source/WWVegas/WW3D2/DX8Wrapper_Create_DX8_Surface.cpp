// cl: /O2 /G7 /Oy /DNDEBUG /MD
//
// DX8Wrapper::_Create_DX8_Surface, retail 0x0011DC60, 62 bytes.
// Dedicated TU so SurfaceClass's constructor cannot inline this body.

class IDirect3DSurface9;

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

class DX8Wrapper
{
public:
	static IDirect3DSurface9 *_Create_DX8_Surface(
		unsigned width, unsigned height, WW3DFormat format, _D3DPOOL pool);

private:
	static IDirect3DDevice9 *D3DDevice;
	static unsigned int D3DCallCount;
};

IDirect3DSurface9 *DX8Wrapper::_Create_DX8_Surface(
	unsigned width, unsigned height, WW3DFormat format, _D3DPOOL pool)
{
	IDirect3DSurface9 *surface = 0;
	D3DDevice->lpVtbl->CreateOffscreenPlainSurface(
		D3DDevice, width, height, (unsigned)format, (unsigned)pool, &surface, 0);
	++D3DCallCount;
	return surface;
}
