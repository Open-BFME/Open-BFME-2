// cl: /O1 /arch:SSE /MD /EHsc
//
// ?ResolveBindings@Rva001F4A90Host_Physics@@UAEXPBD0PAVFXShaderParameterBinder@@@Z
// @0x001F73D5 156B and
// ?ResolveBindings@Rva001F4A90Host_Update@@UAEXPBD0PAVFXShaderParameterBinder@@@Z
// @0x001F7740 328B: vtable slot 1 of the "Physics" (vtable 0x00BE16F0) and
// "Update" (vtable 0x00BE16F8) sub-binders that the rowed particle binder
// select 0x001F4A90 reaches at Rva001F4A90Host+8 and +0xC; the "Draw"
// sibling 0x001F69B1 lives in Rva001F69B1ParticleDrawBinder.cpp. Both defer
// to the rowed default binder 0x00153664, split the name through the rowed
// Rva001530E9Parse 0x001530E9 and bind callbacks through the rowed
// FXShaderParameterBinder::AddBinding. Arm strings and callback addresses
// are read from the retail bodies.
//
// Callbacks (SetVector, ID3DXEffect slot 34; names are the bound parameter
// strings). Each reads the current system through TheParticleSystemManager's
// rowed by-value getter 0x001F6C54 like the Draw callbacks:
//   Gravity          0x001F7471 231B  (0, 0, 0x001F510D, 0)
//   DriftVelocity    0x001F7558 243B  (x, y, z, 0) of 0x001F512F when set
//   VelocityDamping  0x001F764B 245B  (x, y, 0, 0) of 0x001F5141, default
//                                     (1, 1, 0, 0)
//   Size             0x001F7888 262B  pinned in reverse/symbols.csv; the
//                                     (+0x2C, +0x30, 0, 0) body, default
//                                     (1, 10, 0, 0), is banked in
//                                     reverse/attempts/0x001f7888.cpp
//   SizeRate .. zRotationDamping      (x, y, 0, 0) of the rowed 2-float
//                                     helpers 0x001F517E .. 0x001F52CC,
//                                     237B each
// The 0x001F5141 helper copies its second float with an integer move, so its
// row declares it int; this TU reads the same 8 bytes as two floats, which
// is how the callback moves them (movss).
//
// As in the Draw binder, retail's EH state ranges show that the getter and
// the handle destructor 0x0044CBC0 cannot throw; both are declared throw().
//
// ??1Rva001F4B01@@UAE@XZ @0x001F4B01 70B: destructor of the "Particle" binder
// that owns the three sub-binders (vtable 0x00BE171C = { ??_G 0x001F4B47
// (rowed), select 0x001F4A90 (rowed as Rva001F4A90Host) }). Like the
// WaterDraw dtor 0x0007EC44 it erases its registration (0x001532E1,
// "Particle") and leaves all four vptrs at the base vtable 0x00BC6F24; the
// sub-binders declare no dtor.

typedef const char *D3DXHANDLE;
typedef int BOOL;

struct IDirect3DBaseTexture8;

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

struct RGBColor
{
	float r;
	float g;
	float b;
};

struct Out001F5141
{
	float x;
	float y;
};

// Rowed ParticleSystem methods under address-derived classes.
class Rva001F510D { public: float rva001F510D(); };
class Rva001F512FSlot { public: const RGBColor *get() const; };
class Rva001F5141 { public: Out001F5141 *rva001F5141(Out001F5141 *out); };
struct Vec2001F517E { float x; float y; };
class Rva001F517E { public: void rva001F517E(Vec2001F517E *out); };
struct Vec2001F51AD { float x; float y; };
class Rva001F51AD { public: void rva001F51AD(Vec2001F51AD *out); };
struct Vec2001F51DC { float x; float y; };
class Rva001F51DC { public: void rva001F51DC(Vec2001F51DC *out); };
struct Vec2001F520B { float x; float y; };
class Rva001F520B { public: void rva001F520B(Vec2001F520B *out); };
struct Vec2001F523A { float x; float y; };
class Rva001F523A { public: void rva001F523A(Vec2001F523A *out); };
struct Vec2001F526E { float x; float y; };
class Rva001F526E { public: void rva001F526E(Vec2001F526E *out); };
struct Vec2001F529D { float x; float y; };
class Rva001F529D { public: void rva001F529D(Vec2001F529D *out); };
struct Vec2001F52CC { float x; float y; };
class Rva001F52CC { public: void rva001F52CC(Vec2001F52CC *out); };

class ParticleSystem
{
public:
	float rva001F510D() { return ((Rva001F510D *)this)->rva001F510D(); }
	const RGBColor *rva001F512F() const { return ((const Rva001F512FSlot *)this)->get(); }
	Out001F5141 *rva001F5141(Out001F5141 *out) { return ((Rva001F5141 *)this)->rva001F5141(out); }
	void rva001F517E(Vec2001F517E *out) { ((Rva001F517E *)this)->rva001F517E(out); }
	void rva001F51AD(Vec2001F51AD *out) { ((Rva001F51AD *)this)->rva001F51AD(out); }
	void rva001F51DC(Vec2001F51DC *out) { ((Rva001F51DC *)this)->rva001F51DC(out); }
	void rva001F520B(Vec2001F520B *out) { ((Rva001F520B *)this)->rva001F520B(out); }
	void rva001F523A(Vec2001F523A *out) { ((Rva001F523A *)this)->rva001F523A(out); }
	void rva001F526E(Vec2001F526E *out) { ((Rva001F526E *)this)->rva001F526E(out); }
	void rva001F529D(Vec2001F529D *out) { ((Rva001F529D *)this)->rva001F529D(out); }
	void rva001F52CC(Vec2001F52CC *out) { ((Rva001F52CC *)this)->rva001F52CC(out); }
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

void Rva001F7888Size(ID3DXEffect *effect, D3DXHANDLE handle);

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

void __cdecl Rva001532E1Erase(const char *name);
void __cdecl Rva001530E9Parse(const char *name, void *volatile path);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

typedef void (*Rva001F73D5Callback)(ID3DXEffect *effect, D3DXHANDLE handle);

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva00080221
{
public:
	Rva00080221(const int *arg);
	TargetRef00217D4C *m_ptr;
};

struct TreeHintRef00217D4C : public Rva00080221
{
	TreeHintRef00217D4C(Rva001F73D5Callback callback) : Rva00080221((const int *)&callback) {}
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

class FXShaderParameterBinder
{
public:
	void AddBinding(TreeHintRef00217D4C callback, const char *handle);
};

struct Rva001530E9Path
{
	char m_name[0x40];
	bool m_hasStar;
	bool m_hasBracket;
	int m_index;
	const char *m_rest;
};

// FX parameter binder base: vtable 0x00BC6F24 = { deleting dtor, __purecall }.
class Base
{
public:
	virtual ~Base() {}
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry) = 0;
};

// Default binder (0x00153664).
class FXShaderParameterSourceNamespace_Struct : public Base
{
public:
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// "Physics" sub-binder, vtable 0x00BE16F0 (dispatcher 0x001F73D5).
struct Rva001F4A90Host_Physics : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// "Update" sub-binder, vtable 0x00BE16F8 (dispatcher 0x001F7740).
struct Rva001F4A90Host_Update : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// "Draw" sub-binder, vtable 0x00BE16E8 (dispatcher 0x001F69B1, rowed in
// Rva001F69B1ParticleDrawBinder.cpp).
struct Rva001F4A90Host_Draw : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// The "Particle" binder, vtable 0x00BE171C = { ??_G 0x001F4B47, select
// 0x001F4A90 }, holding the three sub-binders at +4/+8/+0xC.
class Rva001F4B01 : public Base
{
public:
	virtual ~Rva001F4B01();
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);

private:
	Rva001F4A90Host_Draw m_04;
	Rva001F4A90Host_Physics m_08;
	Rva001F4A90Host_Update m_0C;
};

Rva001F4B01::~Rva001F4B01()
{
	Rva001532E1Erase("Particle");
}

void Rva001F4A90Host_Physics::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, handle, registry);
	if (name)
	{
		Rva001530E9Path path;
		Rva001530E9Parse(name, &path);
		if (_strcmpi(path.m_name, "Gravity") == 0)
			registry->AddBinding(Rva001F7471Gravity, handle);
		else if (_strcmpi(path.m_name, "DriftVelocity") == 0)
			registry->AddBinding(Rva001F7558DriftVelocity, handle);
		else if (_strcmpi(path.m_name, "VelocityDamping") == 0)
			registry->AddBinding(Rva001F764BVelocityDamping, handle);
	}
}

void Rva001F4A90Host_Update::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, handle, registry);
	if (name)
	{
		Rva001530E9Path path;
		Rva001530E9Parse(name, &path);
		if (_strcmpi(path.m_name, "Size") == 0)
			registry->AddBinding(Rva001F7888Size, handle);
		else if (_strcmpi(path.m_name, "SizeRate") == 0)
			registry->AddBinding(Rva001F798ESizeRate, handle);
		else if (_strcmpi(path.m_name, "SizeRateDamping") == 0)
			registry->AddBinding(Rva001F7A7BSizeRateDamping, handle);
		else if (_strcmpi(path.m_name, "xyRotation") == 0)
			registry->AddBinding(Rva001F7B68XyRotation, handle);
		else if (_strcmpi(path.m_name, "xyRotationRate") == 0)
			registry->AddBinding(Rva001F7C55XyRotationRate, handle);
		else if (_strcmpi(path.m_name, "xyRotationDamping") == 0)
			registry->AddBinding(Rva001F7D42XyRotationDamping, handle);
		else if (_strcmpi(path.m_name, "zRotation") == 0)
			registry->AddBinding(Rva001F7E2FZRotation, handle);
		else if (_strcmpi(path.m_name, "zRotationRate") == 0)
			registry->AddBinding(Rva001F7F1CZRotationRate, handle);
		else if (_strcmpi(path.m_name, "zRotationDamping") == 0)
			registry->AddBinding(Rva001F8009ZRotationDamping, handle);
	}
}
