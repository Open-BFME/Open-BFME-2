// cl: /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
// Ported from Open-BFME-1's game/GameEngineDevice/Source/W3DDevice/GameClient/W3DSmudge_copyRect.cpp
// (donor revision 6583b3c1ff21db4a561285717028fdafc780b7db) with /O1 /arch:SSE
// added to its flags, the settings W3DView.cpp's donor bodies match under.
// Searched by masked whole-.text search, the body places once on unclaimed
// game.dat .text at 0x000A6270 (272B).

// Free copyRect from GeneralsMD W3DSmudge.cpp, adapted to BFME's D3D9 device:
// GetRenderTarget(index, surface) at vtable +0x98, CreateRenderTarget at +0x70,
// StretchRect at +0x88 (CopyRects replacement), surface GetDesc/LockRect/UnlockRect
// at +0x30/+0x34/+0x38.

#include <string.h>

// The native calls use Direct3D 9 slots; take the SDK signatures and
// Windows types from their owning headers.
#include <d3d9.h>

typedef int Int;

struct IDirect3DDevice8;
#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
#define g_d3dDevice (reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8()))

Int copyRect(unsigned char *buf, Int bufSize, int oX, int oY, int width, int height)
{
	IDirect3DSurface9 *surface = 0;
	IDirect3DSurface9 *direct3DSurface9 = 0;
	Int result = 0;
	HRESULT hr = S_OK;
	RECT dstRect;

	IDirect3DDevice9 *m_pDev = g_d3dDevice;

	if (!m_pDev)
		goto error;

	m_pDev->GetRenderTarget(0, &surface);

	if (!surface)
		goto error;

	D3DSURFACE_DESC desc;
	surface->GetDesc(&desc);

	RECT srcRect;
	srcRect.left = oX;
	srcRect.top = oY;
	srcRect.right = oX + width;
	srcRect.bottom = oY + height;

	hr = m_pDev->CreateRenderTarget((UINT)width, (UINT)height, desc.Format,
		D3DMULTISAMPLE_NONE, 0, TRUE, &direct3DSurface9, 0);

	if (hr != S_OK)
		goto error;

	dstRect.left = 0;
	dstRect.top = 0;
	dstRect.right = width;
	dstRect.bottom = height;

	hr = m_pDev->StretchRect(surface, &srcRect, direct3DSurface9, &dstRect, D3DTEXF_NONE);

	if (hr != S_OK)
		goto error;

	D3DLOCKED_RECT lrect;
	hr = direct3DSurface9->LockRect(&lrect, 0, D3DLOCK_READONLY);

	if (hr != S_OK)
		goto error;

	direct3DSurface9->GetDesc(&desc);

	{
		Int copySize = lrect.Pitch * height;
		if (copySize < bufSize)
			bufSize = copySize;
		memcpy(buf, lrect.pBits, (unsigned int)bufSize);
		result = bufSize;
	}

	direct3DSurface9->UnlockRect();

error:
	if (surface)
		surface->Release();
	if (direct3DSurface9)
		direct3DSurface9->Release();

	return result;
}
