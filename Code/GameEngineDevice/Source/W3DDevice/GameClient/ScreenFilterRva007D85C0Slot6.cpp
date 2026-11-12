// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// dxsdk
// platformsdk
//
// Slot 6 (vftable 0x007CF348) of the screen filter the ledger calls
// Rva007D85C0: drop the pixel shader (device slot 107), unbind texture stage
// 0 through Zero Hour's inline Set_DX8_Texture and invalidate the cached
// render states. ScreenHilightFilter's vftable shares the body at 0x007CF32C,
// so it may be a common base's method; the slot is proven, the name is not.

#include <d3d9.h>

#include "../../../../GameEngine/Include/Common/IDirect3DBaseTexture8.h"

struct IDirect3DDevice8;


#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

extern unsigned int number_of_DX8_calls;

// The device keeps its D3D8 type name but is a Direct3D 9 device (SetTexture
// slot 65, SetPixelShader slot 107); the cached textures keep their D3D8
// type name too and are cast at the call.
static inline IDirect3DDevice9 *device9()
{
	return reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8());
}

// BFME2's inline DX8Wrapper::Set_DX8_Texture: Zero Hour's cached path plus the
// direct SetTexture for stages past the 16-entry cache, as every other copy
// (retail 0x00075412) has it. Stage 0 here folds that branch away in the
// caller; without it the emitted copy was a 78-byte body unlike the rest.
__forceinline void DX8Wrapper::Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
{
	if (stage >= 16) {
		device9()->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
		number_of_DX8_calls++;
		return;
	}
	if (Textures[stage] == texture)
		return;
	if (Textures[stage])
		Textures[stage]->Release();
	Textures[stage] = texture;
	if (Textures[stage])
		Textures[stage]->AddRef();
	device9()->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
	number_of_DX8_calls++;
	texture_changes++;
}

class Rva007D85C0
{
public:
	virtual void rva000FB0BC();
};

// ?rva000FB0BC@Rva007D85C0@@UAEXXZ @0x000FB0BC
void Rva007D85C0::rva000FB0BC()
{
	device9()->SetPixelShader(0);
	number_of_DX8_calls++;
	DX8Wrapper::Set_DX8_Texture(0, 0);
	DX8Wrapper::Invalidate_Cached_Render_States();
}
