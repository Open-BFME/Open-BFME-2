// cl: /O1 /DNDEBUG /MD /EHsc
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

// Canonical COM base for cached textures (donor-grounded, not invented):
// - Target fact (retail bytes): Release via [ecx+8] => vtable slot2, 0-arg stdcall.
// - Donor fact: reference/shims/d3d8_shim_validated.h:199-202 (IUnknown_D3D
//   QueryInterface slot0/AddRef slot1/Release slot2) + :244-249 (struct
//   IDirect3DBaseTexture8 inherits that prefix); struct tag U matches home TU
//   mangling ?Textures@DX8Wrapper@@1PAPAUIDirect3DBaseTexture8@@A and the real
//   d3d8.h header home dx8wrapper.cpp builds against.
// - Code precedent (matched 139B): BfmeApplyTextureRef_Apply.cpp:19-27 class
//   IUnknown8 + empty IDirect3DBaseTexture8 derived (same slot0-2 order); home
//   call sites dx8wrapper.cpp:825-828 + 4829-4832 prove Textures[a]->Release()
//   goes through this slot. Only the slot0-2 prefix is load-bearing here;
//   the fuller D3DRESOURCE tail is unobserved by this body and omitted per the
//   established minimal-replica practice, not as a new type claim.
// - Home header is reference/shims/bfmestages/dx8wrapper.h (MAX_TEXTURE_STAGES=16)
//   via Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp:58; home storage is
//   dx8wrapper.cpp:172 `IDirect3DBaseTexture8 *DX8Wrapper::Textures[16]`.
struct IDirect3DBaseTexture8
{
public:
	virtual long __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct IDirect3DDevice8;

class DX8Wrapper
{
public:
	static void Invalidate_Cached_Render_States(void);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static IDirect3DBaseTexture8 *Textures[16];

protected:
	static IDirect3DDevice8 *D3DDevice;
};

typedef long (__stdcall *BfmeFilterSetTextureFn)(void *device, unsigned long stage, void *texture);
typedef long (__stdcall *BfmeFilterSetPixelShaderFn)(void *device, void *shader);

enum
{
	BFME_FILTER_SET_TEXTURE_SLOT = 65,
	BFME_FILTER_SET_PIXEL_SHADER_SLOT = 107
};

static __forceinline void filterSetTexture(unsigned long stage, void *texture)
{
	void *device = DX8Wrapper::_Get_D3D_Device8();
	(*(BfmeFilterSetTextureFn **)device)[BFME_FILTER_SET_TEXTURE_SLOT](device, stage, texture);
}

static __forceinline void filterSetPixelShader(void *shader)
{
	void *device = DX8Wrapper::_Get_D3D_Device8();
	(*(BfmeFilterSetPixelShaderFn **)device)[BFME_FILTER_SET_PIXEL_SHADER_SLOT](device, shader);
}

// Retail data VAs (ImageBase 0x400000; RVA = VA - 0x400000):
// - Textures[0..15] base VA 0x00DEC4B0 (RVA 0x009EC4B0, 16x4=64B per
//   data_xrefs rows 21910-21914: 4+4+4+4+48); reset touches stages 0..4 =
//   VAs B0/B4/B8/BC/C0, i.e. Textures[0]+0/4/8/12/16 addends. SOLE storage is
//   dx8wrapper.cpp:172; this TU declares the array public (mangling 2) and
//   binds it with ONE array alias below to home protected (mangling 1).
//   No per-stage whole-array alias; no private COM-type globals.
// - D3DDevice VA 0x00DEDA34 (RVA 0x009EDA34, 739 refs): SOLE storage
//   dx8wrapper.cpp:180 `IDirect3DDevice8 *DX8Wrapper::D3DDevice`; this TU
//   spells the same protected `?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A`
//   so _Get_D3D_Device8 resolves by name, no alias.
// - number_of_DX8_calls VA 0x00DEDA98 (RVA 0x009EDA98, 626 refs): SOLE storage
//   dx8wrapper.cpp:216 `unsigned number_of_DX8_calls`; SortingRendererBFME1
//   precedent binds g_00DEDA98 via alternatename (linker-only).
// - texture_changes VA 0x00DEDA60 (RVA 0x009EDA60, 42 refs): SOLE storage
//   dx8wrapper.cpp:192 `unsigned DX8Wrapper::texture_changes`; consecutive-
//   layout chain (matrix 4C/doc, material 50, vertex 54, index 58, light 5C,
//   TEXTURE 60, render_state 64, stage 68, draw 6C) + SetTexture(+both)/
//   SetPixelShader(+calls only) behavior pairing per seat-45-r7. Bound the
//   same global-to-member way as g_00DEDA4C->matrix_changes precedent.
// All addresses DIR32-masked by the gate, never hardcoded.
extern unsigned int number_of_DX8_calls;
extern unsigned g_00DEDA60;
// ?g_00DEDA98@@3IA: the global at VA 0xdeda98 is ?number_of_DX8_calls@@3IA.
#pragma comment(linker, "/alternatename:?g_00DEDA98@@3IA=?number_of_DX8_calls@@3IA")
// ?g_00DEDA60@@3IA: the global at VA 0xdeda60 is ?texture_changes@DX8Wrapper@@1IA.
#pragma comment(linker, "/alternatename:?g_00DEDA60@@3IA=?texture_changes@DX8Wrapper@@1IA")
// TU-local public Textures -> home protected Textures (type-identical struct U).
#pragma comment(linker, "/alternatename:?Textures@DX8Wrapper@@2PAPAUIDirect3DBaseTexture8@@A=?Textures@DX8Wrapper@@1PAPAUIDirect3DBaseTexture8@@A")

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
		DX8Wrapper::Textures[0]->Release();
		DX8Wrapper::Textures[0] = 0;
		filterSetTexture(0, 0);
		++number_of_DX8_calls;
		++g_00DEDA60;
	}
	if (DX8Wrapper::Textures[1])
	{
		DX8Wrapper::Textures[1]->Release();
		DX8Wrapper::Textures[1] = 0;
		filterSetTexture(1, 0);
		++number_of_DX8_calls;
		++g_00DEDA60;
	}
	if (DX8Wrapper::Textures[2])
	{
		DX8Wrapper::Textures[2]->Release();
		DX8Wrapper::Textures[2] = 0;
		filterSetTexture(2, 0);
		++number_of_DX8_calls;
		++g_00DEDA60;
	}
	if (DX8Wrapper::Textures[3])
	{
		DX8Wrapper::Textures[3]->Release();
		DX8Wrapper::Textures[3] = 0;
		filterSetTexture(3, 0);
		++number_of_DX8_calls;
		++g_00DEDA60;
	}
	if (DX8Wrapper::Textures[4])
	{
		DX8Wrapper::Textures[4]->Release();
		DX8Wrapper::Textures[4] = 0;
		filterSetTexture(4, 0);
		++number_of_DX8_calls;
		++g_00DEDA60;
	}
	filterSetPixelShader(0);
	++number_of_DX8_calls;
	DX8Wrapper::Invalidate_Cached_Render_States();
}
