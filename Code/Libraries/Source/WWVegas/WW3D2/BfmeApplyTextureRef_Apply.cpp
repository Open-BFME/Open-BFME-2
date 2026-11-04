// cl: /DNDEBUG /MD /EHsc
// dxsdk
// platformsdk
// ?Apply@BfmeApplyTextureRef@@QAEXI@Z @0x132AF8 (139B): per-stage texture apply.
//
// Null-resource path is DX8Wrapper::Set_DX8_Texture(stage, pointer) inlined
// (reference/shims/bfmestages/dx8wrapper.h, WWINLINE = __forceinline): the
// direct SetTexture + number_of_DX8_calls++ when stage >= MAX_TEXTURE_STAGES,
// else the cached Textures[stage] Release + NULL + SetTexture +
// number_of_DX8_calls++ + texture_changes++. Inlining with the caller's
// pointer (NULL on this path, value-numbered into esi) reproduces retail's
// push-esi in the direct arm vs push-0 in the cached arm, and the dead NULL
// lets the compiler reuse esi for &Textures[stage].
//
// /O1 (no /G7): ++ on the two globals emits inc-mem (retail FF05), where the
// home dx8wrapper.cpp TU (/G7) emits add-mem -- hence the dedicated TU.
// Globals are TU-local externs; DIR32 slots patch from retail, no pins.

#include <d3d9.h>

// d3d8.h declares its interfaces with DECLARE_INTERFACE_, i.e. as structs:
// every other copy of Set_DX8_Texture spells the parameter PAU. The texture and
// device keep those D3D8 names but are Direct3D 9 objects (texture AddRef /
// Release slots 1 / 2, device SetTexture slot 65, retail's [ecx+0x104]).
struct IDirect3DBaseTexture8;
struct IDirect3DDevice8;

extern unsigned int number_of_DX8_calls;

// DX8Wrapper's statics under dx8wrapper.cpp's own spellings (protected
// members, the global call counter).
#include "DX8WrapperClass.h"

__forceinline void DX8Wrapper::Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
{
	if (stage >= 16) {
		IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(D3DDevice);
		device->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
		number_of_DX8_calls++;
		return;
	}

	if (Textures[stage] == texture)
		return;

	if (Textures[stage])
		reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->Release();
	Textures[stage] = texture;
	if (Textures[stage])
		reinterpret_cast<IDirect3DBaseTexture9 *>(Textures[stage])->AddRef();
	IDirect3DDevice9 *device = reinterpret_cast<IDirect3DDevice9 *>(D3DDevice);
	device->SetTexture(stage, reinterpret_cast<IDirect3DBaseTexture9 *>(texture));
	number_of_DX8_calls++;
	texture_changes++;
}

// Reset-resource backend behind +0x14; single observed virtual at slot 0.
// TU-local replica: only the slot order is load-bearing for the byte match.
class BfmeResetBackend
{
public:
	virtual void ApplyStage(unsigned int stage) = 0;
};

// Reset-resource behind BfmeApplyTextureRef::pointer. Retail observes virtual
// slots 0x28 (bool), 0x2C and 0x40 (unsigned-taking) plus the backend at
// +0x14; the remaining slots/members are unobserved here and carried as pads.
// TU-local replica: only slot order and the +0x14 member are load-bearing.
class BfmeResetResource
{
public:
	virtual void _V00() = 0;
	virtual void _V01() = 0;
	virtual void _V02() = 0;
	virtual void _V03() = 0;
	virtual void _V04() = 0;
	virtual void _V05() = 0;
	virtual void _V06() = 0;
	virtual void _V07() = 0;
	virtual void _V08() = 0;
	virtual void _V09() = 0;
	virtual bool IsApplied() = 0;			// slot 10 (0x28)
	virtual void PrepareForApply() = 0;		// slot 11 (0x2C)
	virtual void _V0C() = 0;
	virtual void _V0D() = 0;
	virtual void _V0E() = 0;
	virtual void _V0F() = 0;
	virtual void ApplyStage(unsigned int stage) = 0;	// slot 16 (0x40)

	void *_pad04;
	void *_pad08;
	void *_pad0C;
	void *_pad10;
	BfmeResetBackend *m_backend;			// +0x14
};

struct BfmeApplyTextureRef
{
	BfmeResetResource *pointer;
	void Apply(unsigned int stage);
};

// ?Apply@BfmeApplyTextureRef@@QAEXI@Z
void BfmeApplyTextureRef::Apply(unsigned int stage)
{
	BfmeResetResource *res = pointer;
	if (res == 0) {
		DX8Wrapper::Set_DX8_Texture(stage, (IDirect3DBaseTexture8 *)res);
	} else {
		if (!res->IsApplied())
			res->PrepareForApply();
		res->m_backend->ApplyStage(stage);
		res->ApplyStage(stage);
	}
}

