// cl: /DNDEBUG /MD /EHsc
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

class IUnknown8
{
public:
	virtual long __stdcall QueryInterface(const void *riid, void **ppvObject) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

class IDirect3DBaseTexture8 : public IUnknown8
{
};

class BfmeApplyDevice9
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
	virtual void _V10() = 0;
	virtual void _V11() = 0;
	virtual void _V12() = 0;
	virtual void _V13() = 0;
	virtual void _V14() = 0;
	virtual void _V15() = 0;
	virtual void _V16() = 0;
	virtual void _V17() = 0;
	virtual void _V18() = 0;
	virtual void _V19() = 0;
	virtual void _V20() = 0;
	virtual void _V21() = 0;
	virtual void _V22() = 0;
	virtual void _V23() = 0;
	virtual void _V24() = 0;
	virtual void _V25() = 0;
	virtual void _V26() = 0;
	virtual void _V27() = 0;
	virtual void _V28() = 0;
	virtual void _V29() = 0;
	virtual void _V30() = 0;
	virtual void _V31() = 0;
	virtual void _V32() = 0;
	virtual void _V33() = 0;
	virtual void _V34() = 0;
	virtual void _V35() = 0;
	virtual void _V36() = 0;
	virtual void _V37() = 0;
	virtual void _V38() = 0;
	virtual void _V39() = 0;
	virtual void _V40() = 0;
	virtual void _V41() = 0;
	virtual void _V42() = 0;
	virtual void _V43() = 0;
	virtual void _V44() = 0;
	virtual void _V45() = 0;
	virtual void _V46() = 0;
	virtual void _V47() = 0;
	virtual void _V48() = 0;
	virtual void _V49() = 0;
	virtual void _V50() = 0;
	virtual void _V51() = 0;
	virtual void _V52() = 0;
	virtual void _V53() = 0;
	virtual void _V54() = 0;
	virtual void _V55() = 0;
	virtual void _V56() = 0;
	virtual void _V57() = 0;
	virtual void _V58() = 0;
	virtual void _V59() = 0;
	virtual void _V60() = 0;
	virtual void _V61() = 0;
	virtual void _V62() = 0;
	virtual void _V63() = 0;
	virtual void _V64() = 0;
	// slot 65 is SetTexture, reached via an explicit __stdcall vtable call
	// below (retail pushes device/stage/texture and calls [ecx+0x104]).
};

// TU-local replica of DX8Wrapper statics; DIR32 slots patch from retail.
class DX8Wrapper
{
public:
	static const unsigned int MAX_TEXTURE_STAGES = 16;
	static IDirect3DBaseTexture8 *Textures[MAX_TEXTURE_STAGES];
	static BfmeApplyDevice9 *D3DDevice;
	static unsigned int number_of_DX8_calls;
protected:
	static unsigned int texture_changes;
public:
	static __forceinline void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
	{
		typedef long (__stdcall *BfmeSetTextureFn)(BfmeApplyDevice9 *, unsigned int, IDirect3DBaseTexture8 *);

		if (stage >= MAX_TEXTURE_STAGES) {
			BfmeApplyDevice9 *device = D3DDevice;
			(*(BfmeSetTextureFn **)device)[65](device, stage, texture);
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
		BfmeApplyDevice9 *device = D3DDevice;
		(*(BfmeSetTextureFn **)device)[65](device, stage, texture);
		number_of_DX8_calls++;
		texture_changes++;
	}
};

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

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?D3DDevice@DX8Wrapper@@2PAVBfmeApplyDevice9@@A=?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A")
#pragma comment(linker, "/alternatename:?Textures@DX8Wrapper@@2PAPAVIDirect3DBaseTexture8@@A=?Textures@DX8Wrapper@@1PAPAUIDirect3DBaseTexture8@@A")
#pragma comment(linker, "/alternatename:?number_of_DX8_calls@DX8Wrapper@@2IA=?number_of_DX8_calls@@3IA")
