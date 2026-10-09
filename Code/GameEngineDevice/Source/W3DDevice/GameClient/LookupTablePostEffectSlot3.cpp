// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva00111D65@LookupTablePostEffect@@UAEXXZ, retail 0x00111D65, 53 bytes.
// Virtual slot 3 (offset 0xC) of vtable 0x007CFAC8 (class of
// ??0LookupTablePostEffect@@QAE@XZ in LookupTablePostEffectCtor.cpp).
// Guarded resource release: takes the DX8 device mutex, releases the
// ref-counted handle at +0x08 through the rowed helper 0x005F2577, then
// releases the mutex. Callees all rowed (Lock 0x0011F520, release
// 0x005F2577, Assert 0x00120F50). No callers. Honest address name: class
// plus slot are proven, method identity is not.

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class Rva00111C05Effect;

class Rva005F2577Holder
{
public:
	void rva005F2577();
	Rva00111C05Effect *get() const { return (Rva00111C05Effect *)m_ptr; }
private:
	void *m_ptr;
};

class AsciiString;

#include "ascii_string.h"


class LookupTablePostEffect
{
public:
	virtual AsciiString rva00111BE9() const;
	virtual void s1();
	virtual void s2();
	virtual void rva00111D65();
	// Slot 4 (vtable 0x007CFAC8 entry +0x10); WorldBuilder names it
	// PostEffects::LookupTablePostEffect::doApply.
	virtual void doApply();
private:
	int m_04;
	Rva005F2577Holder m_08;
};

// ?rva00111BE9@LookupTablePostEffect@@UBE?AVAsciiString@@XZ, retail 0x00111BE9, 28 bytes.
// Virtual slot 0 (offset 0x0) of vtable 0x007CFAC8. Returns the AsciiString
// literal "LookupTablePostEffect" (0x00BCFADC) by value through the rowed
// StringBase<char> const-char ctor 0x00037BA0. No callers. Honest address
// name: class plus slot are proven, method identity is not.
AsciiString LookupTablePostEffect::rva00111BE9() const
{
	return AsciiString("LookupTablePostEffect");
}

void LookupTablePostEffect::rva00111D65()
{
	BFMEDX8DeviceLock lock;
	m_08.rva005F2577();
}

// Minimal D3D9 COM views for the calls doApply makes (vtable slots per
// d3d9.h: IUnknown 0..2, IDirect3DSurface9::GetDesc 12, IDirect3DTexture9::
// GetSurfaceLevel 18, IDirect3DDevice9::StretchRect 34 / SetTexture 65 /
// SetVertexShader 92 / SetPixelShader 107).
struct BfmeD3DSurfaceDesc
{
	unsigned int Format;
	unsigned int Type;
	unsigned int Usage;
	unsigned int Pool;
	unsigned int MultiSampleType;
	unsigned int MultiSampleQuality;
	unsigned int Width;
	unsigned int Height;
};

struct IDirect3DBaseTexture8
{
	virtual long __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
};

struct BfmeD3DSurface
{
	virtual long __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
	virtual void __stdcall s3() = 0; virtual void __stdcall s4() = 0; virtual void __stdcall s5() = 0;
	virtual void __stdcall s6() = 0; virtual void __stdcall s7() = 0; virtual void __stdcall s8() = 0;
	virtual void __stdcall s9() = 0; virtual void __stdcall s10() = 0; virtual void __stdcall s11() = 0;
	virtual long __stdcall GetDesc(BfmeD3DSurfaceDesc *desc) = 0;
};

struct BfmeD3DTexture
{
	virtual long __stdcall QueryInterface(const void *riid, void **ppv) = 0;
	virtual unsigned long __stdcall AddRef() = 0;
	virtual unsigned long __stdcall Release() = 0;
	virtual void __stdcall s3() = 0; virtual void __stdcall s4() = 0; virtual void __stdcall s5() = 0;
	virtual void __stdcall s6() = 0; virtual void __stdcall s7() = 0; virtual void __stdcall s8() = 0;
	virtual void __stdcall s9() = 0; virtual void __stdcall s10() = 0; virtual void __stdcall s11() = 0;
	virtual void __stdcall s12() = 0; virtual void __stdcall s13() = 0; virtual void __stdcall s14() = 0;
	virtual void __stdcall s15() = 0; virtual void __stdcall s16() = 0; virtual void __stdcall s17() = 0;
	virtual long __stdcall GetSurfaceLevel(unsigned int level, BfmeD3DSurface **surface) = 0;
};

struct IDirect3DDevice8;

typedef long (__stdcall *BfmeStretchRectFn)(IDirect3DDevice8 *, BfmeD3DSurface *, const void *, BfmeD3DSurface *, const void *, int);
typedef long (__stdcall *BfmeSetTextureFn)(IDirect3DDevice8 *, unsigned long, IDirect3DBaseTexture8 *);
typedef long (__stdcall *BfmeSetShaderFn)(IDirect3DDevice8 *, void *);

class DX8Wrapper
{
public:
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }
	static __declspec(dllimport) __forceinline void Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture);
protected:
	static IDirect3DDevice8 *D3DDevice;
	static IDirect3DBaseTexture8 *Textures[16];
	static unsigned int texture_changes;
};

extern unsigned int number_of_DX8_calls;

static inline void *deviceSlot(int slot)
{
	return (*(void ***)DX8Wrapper::_Get_D3D_Device8())[slot];
}

// Zero Hour's inline DX8Wrapper::Set_DX8_Texture.
__declspec(dllimport) __forceinline void DX8Wrapper::Set_DX8_Texture(unsigned int stage, IDirect3DBaseTexture8 *texture)
{
	if (Textures[stage] == texture)
		return;
	if (Textures[stage])
		Textures[stage]->Release();
	Textures[stage] = texture;
	if (Textures[stage])
		Textures[stage]->AddRef();
	((BfmeSetTextureFn)deviceSlot(65))(_Get_D3D_Device8(), stage, texture);
	number_of_DX8_calls++;
	texture_changes++;
}

// The effect object the +0x08 holder owns: Begin (slot 2) reports the pass
// count, BeginPass (3), EndPass (5), End (6); thiscall, identities from
// the call pattern.
class Rva00111C05Effect
{
public:
	virtual void s0();
	virtual void s1();
	virtual bool begin(int *passes, unsigned int flags);
	virtual void beginPass(int pass);
	virtual void s4();
	virtual void endPass();
	virtual void end();
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();
	BfmeD3DSurface *peek() const { return m_surface; }
private:
	BfmeD3DSurface *m_surface;
};

W3DRadarResetSurface getBackBufferSurface006e(int index);
int Rva00075E36Get();
void Rva00075A23Draw(int width, int height);

// Retail 0x00111C05. Copies the back buffer into the post-effect render
// texture (0x00075E36), then draws a full-screen quad (0x00075A23) for each
// pass of the +0x08 effect with that texture on stage 0, and clears the
// vertex and pixel shaders.
void LookupTablePostEffect::doApply()
{
	if (!m_08.get() || !Rva00075E36Get())
		return;
	BfmeD3DSurface *target = 0;
	if (((BfmeD3DTexture *)Rva00075E36Get())->GetSurfaceLevel(0, &target) < 0)
		return;
	BfmeD3DSurface *backBuffer = getBackBufferSurface006e(0).peek();
	if (!backBuffer) {
		target->Release();
		return;
	}
	((BfmeStretchRectFn)deviceSlot(34))(DX8Wrapper::_Get_D3D_Device8(), backBuffer, 0, target, 0, 0);
	BfmeD3DSurfaceDesc desc;
	target->GetDesc(&desc);
	int passes = 0;
	if (m_08.get()->begin(&passes, 0xffff)) {
		for (int pass = 0; pass < passes; pass++) {
			m_08.get()->beginPass(pass);
			DX8Wrapper::Set_DX8_Texture(0, (IDirect3DBaseTexture8 *)Rva00075E36Get());
			Rva00075A23Draw(desc.Width, desc.Height);
			m_08.get()->endPass();
		}
		m_08.get()->end();
	}
	target->Release();
	target = 0;
	((BfmeSetShaderFn)deviceSlot(92))(DX8Wrapper::_Get_D3D_Device8(), 0);
	number_of_DX8_calls++;
	((BfmeSetShaderFn)deviceSlot(107))(DX8Wrapper::_Get_D3D_Device8(), 0);
	number_of_DX8_calls++;
}
