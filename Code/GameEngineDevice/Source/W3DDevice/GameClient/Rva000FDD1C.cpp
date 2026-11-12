// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// dxsdk
// platformsdk
// ?rva000FDD1C@Rva000FDD1C@@QAE_NHHHH@Z @0x000FDD1C 147B: stored function pointer at table slot 3 near GameFileClass::Create and RenderObjClass::_bfme_ro_v50; renderer behavior follows the table role and retail call sequence, while class identity remains unproven.

#include <d3d9.h>

// The D3D8 type names stay for decoration (Textures@DX8Wrapper, endRenderToTexture), but
// the objects are Direct3D 9 ones: texture AddRef / Release are slots 1 / 2, and the
// device's SetTexture is slot 65.
#include "../../../../GameEngine/Include/Common/IDirect3DBaseTexture8.h"
struct IDirect3DTexture8 : IDirect3DBaseTexture8 {};
struct IDirect3DDevice8;

#include "../../../../../reference/shims/wwmath/Vector2.h"

#include "../../../Include/W3DDevice/GameClient/W3DShaderManagerClass.h"

struct Rva000FDD1C;

#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"
extern unsigned int number_of_DX8_calls;

struct Rva000FDD1C
{
	virtual void f00() = 0;
	virtual void f01() = 0;
	virtual void f02() = 0;
	virtual void f03() = 0;
	virtual void f04() = 0;
	virtual int rva000FDD1CFirst(int arg);
	virtual void rva000FDD1CNext();
	bool rva000FDD1C(int arg1, int arg2, int arg3, int arg4);
};

bool Rva000FDD1C::rva000FDD1C(int arg1, int arg2, int arg3, int arg4)
{
	IDirect3DTexture8 *texture = W3DShaderManager::endRenderToTexture();
	if (!texture)
		return false;
	if (!rva000FDD1CFirst(arg1))
		return false;
	{
		if (DX8Wrapper::Textures[0] != texture)
		{
			if (DX8Wrapper::Textures[0])
				reinterpret_cast<IDirect3DBaseTexture9 *>(DX8Wrapper::Textures[0])->Release();
			DX8Wrapper::Textures[0] = texture;
			reinterpret_cast<IDirect3DTexture9 *>(texture)->AddRef();
			reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::D3DDevice)->SetTexture(0,
				reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
			++number_of_DX8_calls;
			++DX8Wrapper::texture_changes;
		}
		Vector2 uv;
		uv.X = 1.0f;
		uv.Y = 1.0f;
		W3DShaderManager::drawViewport(-1, false, &uv);
		rva000FDD1CNext();
		return true;
	}
	return false;
}
