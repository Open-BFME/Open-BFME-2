// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// dxsdk
// platformsdk
// ?rva000EF7B8@Rva000EF7B8Texture@@UAEXH@Z, retail 0x000EF7B8..0x000EF876 (190 bytes, RET 4),
// the stage-apply entry of the texture class vtable at 0x007CEF60 (slot +0x18; its neighbours
// are the rowed texture-surface helpers). After the base apply step (rowed 0x00131CEA) it sets
// stage 0 to an unprojected, clamped (D3D9 sampler states through the device, slot +0x114),
// texture-times-diffuse colour with texture alpha, enables source-alpha blending and disables
// stage 1. The owning class and method names are not recovered.
#include <d3d9.h>

// The device keeps its D3D8 type name but is a Direct3D 9 device
// (SetSamplerState, vtable slot 69).
struct IDirect3DDevice8;

extern unsigned number_of_DX8_calls;

class DX8Wrapper
{
public:
	static void Set_DX8_Texture_Stage_State(unsigned stage, unsigned long state, unsigned value);
	static void Set_DX8_Render_State(unsigned long state, unsigned value);
	static __forceinline void Set_DX8_Sampler_State(unsigned stage, unsigned long state, unsigned value)
	{
		reinterpret_cast<IDirect3DDevice9 *>(D3DDevice)->SetSamplerState(stage, (D3DSAMPLERSTATETYPE)state, value);
		number_of_DX8_calls++;
		texture_stage_state_changes++;
	}
protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned texture_stage_state_changes;
};

#include "../../../../GameEngine/Include/Common/Rva00131CEAForwarder.h"

class Rva000EF7B8Texture
{
public:
	virtual void rva000EF7B8(int stage);
};

void Rva000EF7B8Texture::rva000EF7B8(int stage)
{
	reinterpret_cast<Rva00131CEAForwarder *>(this)->rva00131CEA(stage);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);
	DX8Wrapper::Set_DX8_Sampler_State(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	DX8Wrapper::Set_DX8_Sampler_State(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	DX8Wrapper::Set_DX8_Texture_Stage_State(0, D3DTSS_TEXCOORDINDEX, 0);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_ALPHABLENDENABLE, TRUE);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	DX8Wrapper::Set_DX8_Render_State(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	DX8Wrapper::Set_DX8_Texture_Stage_State(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
}
