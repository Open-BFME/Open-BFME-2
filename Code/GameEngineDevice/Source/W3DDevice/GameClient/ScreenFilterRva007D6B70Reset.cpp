// cl: /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
// Retail 0x000F8735 (279B, [0xF8735,0xF884C)): vtable 0x7CF254 slot6 reset.
// Target facts (retail bytes, independent of donor):
// - vtable 0x7CF254 slot6 == 0xF8735 (raw decode: F6D4F/F70EB/F6D56/F7187/5CB9FA/F816E/F8735;
//   next 0x7CF270 starts F839B/F884C; 0x7CF26C+0x7CF288 both point at F8735).
// - ctor-like 0xF8348 installs 0xBCF254 (VA) and zeroes +0x04..+0x44 (BFME1 Rva007D6B70Ctor
//   shape + vector at +0x2C via rowed 0x211E58); shutdown 0xF70EB (rowed Rva007D6B70::shutdown)
//   and set 0xF816E (rowed Rva007D6B70::set) live in the same vtable, so slot6 is the
//   same object's reset; ABI has 0 stack args, no ebp frame, no this-use, tail jmp to
//   rowed 0x11FD10 (DX8Wrapper::Invalidate_Cached_Render_States) => void reset() with unused ecx.
// - body is 5x (Release global + clear + SetTexture stage 0..4 via device slot65 + inc
//   0xDEDA98 + inc 0xDEDA60) then SetPixelShader(0) via device slot107 + incs, then tail
//   Invalidate; Release via [ecx+8] slot2; abuts matched 0xF884C (Rva007DB820::shutdown).
// Donor guides (6583b3c1 verified, read-only, no fetch):
// - reference/open-bfme-1/.../ScreenFilterResets.cpp: Hilight/Zoom reset shape
//   {SetPixelShader(0); SetTexture(0,0); Invalidate();} (slots 65/107, stage count differs 1 vs 5).
// - Rva007D6B70FilterShutdown.cpp: 8-9x Release chain (matched F70EB /O1 /Ob0).
// Inference: slot6-after-set + shutdown/set co-location + slots + abutment + matched tail
// make Rva007D6B70::reset moderate-strong but NOT proven (5-release delta, global names
// unproven); TU-scoped names only, donor layout never copied. Original Westwood class name
// unknown (same caveat as rowed shutdown/set TUs).

#include <d3d9.h>

// The cached textures and the device keep their D3D8 type names (the decorations of
// ?Textures@DX8Wrapper@@1PAPAUIDirect3DBaseTexture8@@A and
// ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A, defined in dx8wrapper.cpp), but are
// Direct3D 9 objects: texture Release is slot 2, SetTexture slot 65, SetPixelShader slot 107.
#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

static __forceinline void filterSetTexture(unsigned long stage, IDirect3DBaseTexture9 *texture)
{
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetTexture(stage, texture);
}

static __forceinline void filterSetPixelShader(IDirect3DPixelShader9 *shader)
{
	reinterpret_cast<IDirect3DDevice9 *>(DX8Wrapper::_Get_D3D_Device8())->SetPixelShader(shader);
}

// Retail data VAs (ImageBase 0x400000; RVA = VA - 0x400000):
// - Textures[0..15] base VA 0x00DEC4B0 (RVA 0x009EC4B0, 16x4=64B per
//   data_xrefs rows 21910-21914: 4+4+4+4+48); reset touches stages 0..4 =
//   VAs B0/B4/B8/BC/C0, i.e. Textures[0]+0/4/8/12/16 addends. SOLE storage is
//   dx8wrapper.cpp:172; this TU declares it protected (mangling 1) like
//   its home. No per-stage whole-array alias; no private COM-type globals.
// - D3DDevice VA 0x00DEDA34 (RVA 0x009EDA34, 739 refs): SOLE storage
//   dx8wrapper.cpp:180 `IDirect3DDevice8 *DX8Wrapper::D3DDevice`; this TU
//   spells the same protected `?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A`
//   so _Get_D3D_Device8 resolves by name, no alias.
// - number_of_DX8_calls VA 0x00DEDA98 (RVA 0x009EDA98, 626 refs): SOLE storage
//   dx8wrapper.cpp:216 `unsigned number_of_DX8_calls`, named directly here
//   and in SortingRendererBFME1.
// - texture_changes VA 0x00DEDA60 (RVA 0x009EDA60, 42 refs): SOLE storage
//   dx8wrapper.cpp:192 `unsigned DX8Wrapper::texture_changes`; consecutive-
//   layout chain (matrix 4C/doc, material 50, vertex 54, index 58, light 5C,
//   TEXTURE 60, render_state 64, stage 68, draw 6C) + SetTexture(+both)/
//   SetPixelShader(+calls only) behavior pairing per seat-45-r7.
// All addresses DIR32-masked by the gate, never hardcoded.
// The view above declares Textures and texture_changes protected, as their
// home does, and befriends the reset, so both resolve by name.
extern unsigned int number_of_DX8_calls;

class Rva007D6B70
{
protected:
	// Only slot positions are known for this prefix; no calls or vtable are emitted.
	virtual void unknownSlot0() = 0;
	virtual void unknownSlot1() = 0;
	virtual void unknownSlot2() = 0;
	virtual void unknownSlot3() = 0;
	virtual void unknownSlot4() = 0;
	virtual int set(int mode);
	virtual void reset(void);
};

void Rva007D6B70::reset(void)
{
	if (DX8Wrapper::Textures[0])
	{
		reinterpret_cast<IDirect3DBaseTexture9 *>(DX8Wrapper::Textures[0])->Release();
		DX8Wrapper::Textures[0] = 0;
		filterSetTexture(0, 0);
		++number_of_DX8_calls;
		++DX8Wrapper::texture_changes;
	}
	if (DX8Wrapper::Textures[1])
	{
		reinterpret_cast<IDirect3DBaseTexture9 *>(DX8Wrapper::Textures[1])->Release();
		DX8Wrapper::Textures[1] = 0;
		filterSetTexture(1, 0);
		++number_of_DX8_calls;
		++DX8Wrapper::texture_changes;
	}
	if (DX8Wrapper::Textures[2])
	{
		reinterpret_cast<IDirect3DBaseTexture9 *>(DX8Wrapper::Textures[2])->Release();
		DX8Wrapper::Textures[2] = 0;
		filterSetTexture(2, 0);
		++number_of_DX8_calls;
		++DX8Wrapper::texture_changes;
	}
	if (DX8Wrapper::Textures[3])
	{
		reinterpret_cast<IDirect3DBaseTexture9 *>(DX8Wrapper::Textures[3])->Release();
		DX8Wrapper::Textures[3] = 0;
		filterSetTexture(3, 0);
		++number_of_DX8_calls;
		++DX8Wrapper::texture_changes;
	}
	if (DX8Wrapper::Textures[4])
	{
		reinterpret_cast<IDirect3DBaseTexture9 *>(DX8Wrapper::Textures[4])->Release();
		DX8Wrapper::Textures[4] = 0;
		filterSetTexture(4, 0);
		++number_of_DX8_calls;
		++DX8Wrapper::texture_changes;
	}
	filterSetPixelShader(0);
	++number_of_DX8_calls;
	DX8Wrapper::Invalidate_Cached_Render_States();
}
