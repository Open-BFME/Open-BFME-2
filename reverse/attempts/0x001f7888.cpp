// ?Rva001F7888Size@@YAXPAUID3DXEffect@@PBD@Z
// partial score=0.98 date=2026-10-06
// cl: /O1 /arch:SSE /MD /EHsc
// Banked near miss for ?Rva001F7888Size@@YAXPAUID3DXEffect@@PBD@Z @0x001F7888 262B
// ("Size" callback of the particle Update binder 0x001F7740; siblings rowed in
// Code/GameEngine/Source/Common/Rva001F73D5ParticlePhysicsUpdateBinder.cpp).
// 4 diffs: the two spilled floats sit at ebp-0x14/-0x1C instead of retail's
// -0x10 (+0x30) / -0x18 (+0x2C). Retail also gives the second handle its own
// slot (-0x28); a 12-byte holder for the pair reproduces that, plain scalars
// or a 2-float struct let the handle share the first one's slot (22-32 diffs).
// The 3-float holder is a layout probe, not a claimed source shape.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

typedef const char *D3DXHANDLE;
typedef int BOOL;

struct IDirect3DBaseTexture8;
class DummyPtrType;

struct D3DXVECTOR4
{
	D3DXVECTOR4() {}
	D3DXVECTOR4(float fx, float fy, float fz, float fw) { x = fx; y = fy; z = fz; w = fw; }
	operator float *() { return &x; }
	float x, y, z, w;
};

struct ID3DXEffect
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21();
	virtual long __stdcall SetBool(D3DXHANDLE parameter, BOOL value);
	virtual void v23(); virtual void v24(); virtual void v25();
	virtual long __stdcall SetInt(D3DXHANDLE parameter, int value);
	virtual void v27(); virtual void v28(); virtual void v29();
	virtual long __stdcall SetFloat(D3DXHANDLE parameter, float value);
	virtual void v31(); virtual void v32(); virtual void v33();
	virtual long __stdcall SetVector(D3DXHANDLE parameter, const D3DXVECTOR4 *vector);
	virtual void v35();
	virtual long __stdcall SetVectorArray(D3DXHANDLE parameter, const D3DXVECTOR4 *vectors, unsigned int count);
	virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual long __stdcall SetTexture(D3DXHANDLE parameter, IDirect3DBaseTexture8 *texture);
};

class TextureClass
{
public:
	__forceinline void Add_Ref() { ++m_refCount; }
	void Release_Ref();

private:
	void *m_vtable;
	unsigned short m_refCount;
};

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

template <class T> class RefCountPtr
{
public:
	__forceinline RefCountPtr(const RefCountPtr &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}
	~RefCountPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	operator const DummyPtrType *() const { return (const DummyPtrType *)m_ptr; }
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const
	{
		return ((const TextureBaseClass *)this)->Peek_D3D_Base_Texture();
	}

private:
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

BFME2ParticleTextureHandle __cdecl BFME2LoadParticleTexture(const char *filename, int a, int b);
RefCountPtr<TextureClass> Rva00132E76WhiteTexture();

struct RGBColor
{
	float r;
	float g;
	float b;
};

struct Vec2001F5373
{
	float x;
	float y;
};

struct RGBColorKeyframe
{
	RGBColor color;
	unsigned int frame;
};

class GameClientRandomVariable
{
public:
	float getValue() const;

private:
	char m_pad[0x10];
};

// Rowed ParticleSystem methods under address-derived classes.
class Rva001F5300 { public: void rva001F5300(float *out); };
class Rva001F553F { public: float rva001F534C(); };
class Rva001F5373 { public: void rva001F5373(Vec2001F5373 *out); };
class Rva001F53AASlot { public: const RGBColor *get() const; };
class Rva001F53BCSlot { public: const RGBColor *get() const; };
class Rva001F510D { public: float rva001F510D(); };
class Rva001F512FSlot { public: const RGBColor *get() const; };
struct Out001F5141 { float x; float y; };
class Rva001F5141 { public: Out001F5141 *rva001F5141(Out001F5141 *out); };
#define VEC2(R) struct Vec2##R { float x; float y; }; class Rva##R { public: void rva##R(Vec2##R *out); };
VEC2(001F517E) VEC2(001F51AD) VEC2(001F51DC) VEC2(001F520B) VEC2(001F523A) VEC2(001F526E) VEC2(001F529D) VEC2(001F52CC)

class Rva001F6C54Draw
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual AsciiString slot06();
};

class ParticleSystem
{
public:
	float rva001F510D() { return ((Rva001F510D *)this)->rva001F510D(); }
	const RGBColor *rva001F512F() const { return ((const Rva001F512FSlot *)this)->get(); }
	Out001F5141 *rva001F5141(Out001F5141 *out) { return ((Rva001F5141 *)this)->rva001F5141(out); }
#define FWD(R) void rva##R(Vec2##R *out) { ((Rva##R *)this)->rva##R(out); }
	FWD(001F517E) FWD(001F51AD) FWD(001F51DC) FWD(001F520B) FWD(001F523A) FWD(001F526E) FWD(001F529D) FWD(001F52CC)

	void getSize(float &lo, float &hi) const { hi = m_30; lo = m_2C; }
	char m_pad000[0x2C];
	float m_2C;
	float m_30;
};

ParticleSystem *Make001FCBD7();

class BfmeParticleSystemHandle
{
public:
	~BfmeParticleSystemHandle() throw();
};

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	__forceinline ~RvaSmartPtr12()
	{
		if (m_system)
			((BfmeParticleSystemHandle *)this)->~BfmeParticleSystemHandle();
	}
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const { return m_system ? m_system : Make001FCBD7(); }

private:
	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class Rva001F6C54SmartField
{
public:
	RvaSmartPtr12 get() const throw();
};

class ParticleSystemManager : public Rva001F6C54SmartField
{
};

extern ParticleSystemManager *TheParticleSystemManager;

void Rva001F7471Gravity(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 gravity(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		float g = TheParticleSystemManager->get()->rva001F510D();
		gravity = D3DXVECTOR4(0.0f, 0.0f, g, 0.0f);
	}
	effect->SetVector(handle, &gravity);
}

void Rva001F7558DriftVelocity(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 drift(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		const RGBColor *velocity = TheParticleSystemManager->get()->rva001F512F();
		if (velocity)
			drift = D3DXVECTOR4(velocity->r, velocity->g, velocity->b, 0.0f);
	}
	effect->SetVector(handle, &drift);
}

void Rva001F764BVelocityDamping(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 damping(1.0f, 1.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Out001F5141 d;
		TheParticleSystemManager->get()->rva001F5141(&d);
		damping = D3DXVECTOR4(d.x, d.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &damping);
}

void Rva001F7888Size(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 size(1.0f, 10.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		struct { float lo, mid, hi; } range;
		TheParticleSystemManager->get()->getSize(range.lo, range.hi);
		size = D3DXVECTOR4(range.lo, range.hi, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &size);
}

void Rva001F798ESizeRate(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 value(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F517E v;
		TheParticleSystemManager->get()->rva001F517E(&v);
		value = D3DXVECTOR4(v.x, v.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &value);
}

void Rva001F7A7BSizeRateDamping(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 value(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F51AD v;
		TheParticleSystemManager->get()->rva001F51AD(&v);
		value = D3DXVECTOR4(v.x, v.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &value);
}

void Rva001F7B68XyRotation(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 value(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F51DC v;
		TheParticleSystemManager->get()->rva001F51DC(&v);
		value = D3DXVECTOR4(v.x, v.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &value);
}

void Rva001F7C55XyRotationRate(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 value(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F520B v;
		TheParticleSystemManager->get()->rva001F520B(&v);
		value = D3DXVECTOR4(v.x, v.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &value);
}

void Rva001F7D42XyRotationDamping(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 value(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F523A v;
		TheParticleSystemManager->get()->rva001F523A(&v);
		value = D3DXVECTOR4(v.x, v.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &value);
}

void Rva001F7E2FZRotation(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 value(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F526E v;
		TheParticleSystemManager->get()->rva001F526E(&v);
		value = D3DXVECTOR4(v.x, v.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &value);
}

void Rva001F7F1CZRotationRate(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 value(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F529D v;
		TheParticleSystemManager->get()->rva001F529D(&v);
		value = D3DXVECTOR4(v.x, v.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &value);
}

void Rva001F8009ZRotationDamping(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 value(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F52CC v;
		TheParticleSystemManager->get()->rva001F52CC(&v);
		value = D3DXVECTOR4(v.x, v.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &value);
}
