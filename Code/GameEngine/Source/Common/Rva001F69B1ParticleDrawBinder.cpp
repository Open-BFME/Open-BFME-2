// cl: /O1 /arch:SSE /MD /EHsc
// platformsdk
//
// ?ResolveBindings@SourceNamespace_Draw@ParticleFXShaderParameterSourceNamespace@@UAEXPBD0PAVFXShaderParameterBinder@@@Z
// @0x001F69B1 328B: vtable slot 1 of the "Draw" sub-binder (vtable 0x00BE16E8,
// slot 0 0x001F45C3) that the rowed particle binder select 0x001F4A90 reaches
// at ParticleFXShaderParameterSourceNamespace+4. Defers to the rowed default binder 0x00153664, then
// splits the name through the rowed Rva001530E9Parse 0x001530E9 and binds nine
// callbacks through the rowed FXShaderParameterBinder::AddBinding, the
// WaterDraw member dispatcher's pattern (Rva0007EBFBWaterDraw.cpp). The arm
// strings and callback addresses are read from the retail body.
//
// Callbacks (target evidence: bodies, callees and ID3DXEffect slots; names
// are the parameter strings they are bound to):
//   Texture         0x001F6B10 324B  SetTexture: ParticleSystem+0x10 name
//                   through the rowed TextureAsset::Get 0x00132D89,
//                   white texture 0x00132E76 when absent.
//   DetailTexture   0x001F6C6F 428B  same through the +0x1C4 object's
//                   vtable slot 6 (by-value AsciiString name).
//   TextureLayout   0x001F713E 245B  SetVector (u, v, 0, 0) from 0x001F5300,
//                   default (1, 1, 0, 0).
//   SpeedMultiplier 0x001F7233 181B  SetFloat 0x001F534C, default 1.0.
//   ColorKeys       0x001F6EB7 419B  SetVectorArray of four (r, g, b, 1)
//                   keys from 0x001F53AA (16-byte keyframes), w from the
//                   0x001F53BC random variables (getValue 0x006341A1).
//   ColorScale      0x001F72E8 237B  SetVector (x, y, 0, 0) from 0x001F5373.
//   TimeKeys        0x001F705A 228B  SetVector of the four keyframe frames.
//   ShaderType      0x001F6E1B 156B  SetInt ParticleSystem+0x08, default 1.
//   Reflected       0x001F6AF9  23B  SetBool bfmeCameraProjectionOverride.
// ID3DXEffect slots: SetBool 22, SetInt 26, SetFloat 30, SetVector 34,
// SetVectorArray 36, SetTexture 52.
//
// Every callback but Reflected reads the current system through
// TheParticleSystemManager's rowed by-value getter 0x001F6C54, whose handle
// is released through 0x0044CBC0 when set, and falls back to the rowed
// Make001FCBD7 when the handle is empty. Retail's EH state ranges show that
// neither the getter nor the handle destructor can throw: no state is entered
// for the first conditional temporary while the second is created, and the
// handles share one frame slot. Both are declared throw() to say so.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <windows.h>
#include <string.h>

typedef const char *D3DXHANDLE;

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

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/TextureAsset.h"
RefCountPtr<TextureClass> Rva00132E76WhiteTexture();

#include "../../../Libraries/Include/Lib/RGBColor.h"

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

#include "../../Include/GameClient/GameClientRandomVariable.h"
#include "../../Include/GameClient/GameClientRandomVariableInlines.h"

// Rowed ParticleSystem methods under address-derived classes.
class Rva001F5300 { public: void rva001F5300(float *out); };
#include "../../Include/GameClient/Rva001F553F.h"
class Rva001F5373 { public: void rva001F5373(Vec2001F5373 *out); };
class Rva001F53AASlot { public: const RGBColor *get() const; };
class Rva001F53BCSlot { public: const RGBColor *get() const; };

class Rva001F6C54Draw
{
public:
	virtual void v00(); virtual void v01(); virtual void v02();
	virtual void v03(); virtual void v04(); virtual void v05();
	virtual AsciiString slot06();
};

#include "../../Include/GameClient/ParticleSystemClass.h"

static inline void rva001F5300(ParticleSystem *system, float *out) { ((Rva001F5300 *)system)->rva001F5300(out); }
static inline float rva001F534C(ParticleSystem *system) { return ((Rva001F553F *)system)->rva001F534C(); }
static inline void rva001F5373(ParticleSystem *system, Vec2001F5373 *out) { ((Rva001F5373 *)system)->rva001F5373(out); }
static inline const RGBColor *rva001F53AA(const ParticleSystem *system) { return ((const Rva001F53AASlot *)system)->get(); }
static inline const RGBColor *rva001F53BC(const ParticleSystem *system) { return ((const Rva001F53BCSlot *)system)->get(); }
// +0x1C4, a word of the untyped +0x1AC member.
static inline Rva001F6C54Draw *drawInfo1C4(const ParticleSystem *system) { return (Rva001F6C54Draw *)system->m_1AC[6]; }

#include "../../Include/Common/RvaSmartPtr12.h"

// Preserve the native inline null-guard cleanup.
__forceinline RvaSmartPtr12::~RvaSmartPtr12() throw()
{
    if (field00)
        rva0004CBC0();
}

class Rva001F6C54SmartField
{
public:
	RvaSmartPtr12 get() const throw();
};

class ParticleSystemManager : public Rva001F6C54SmartField
{
};

extern ParticleSystemManager *TheParticleSystemManager;
extern bool bfmeCameraProjectionOverride;

void Rva001F6AF9Reflected(ID3DXEffect *effect, D3DXHANDLE handle)
{
	effect->SetBool(handle, bfmeCameraProjectionOverride);
}

void Rva001F7233SpeedMultiplier(ID3DXEffect *effect, D3DXHANDLE handle)
{
	float speed = 1.0f;
	if (TheParticleSystemManager && TheParticleSystemManager->get())
		speed = rva001F534C(TheParticleSystemManager->get().operator->());
	effect->SetFloat(handle, speed);
}

void Rva001F713ETextureLayout(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 layout(1.0f, 1.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		float uv[2];
		rva001F5300(TheParticleSystemManager->get().operator->(), uv);
		layout = D3DXVECTOR4(uv[0], uv[1], 0.0f, 0.0f);
	}
	effect->SetVector(handle, &layout);
}

void Rva001F72E8ColorScale(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 scale(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		Vec2001F5373 colorScale;
		rva001F5373(TheParticleSystemManager->get().operator->(), &colorScale);
		scale = D3DXVECTOR4(colorScale.x, colorScale.y, 0.0f, 0.0f);
	}
	effect->SetVector(handle, &scale);
}

void Rva001F6E1BShaderType(ID3DXEffect *effect, D3DXHANDLE handle)
{
	int type = 1;
	if (TheParticleSystemManager && TheParticleSystemManager->get())
		type = TheParticleSystemManager->get()->m_shaderType;
	effect->SetInt(handle, type);
}

void Rva001F705ATimeKeys(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 times(0.0f, 0.0f, 0.0f, 0.0f);
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		const RGBColor *keys = rva001F53AA(TheParticleSystemManager->get().operator->());
		if (keys)
		{
			for (int i = 0; i < 4; i++)
				times[i] = (float)((const RGBColorKeyframe *)keys)[i].frame;
		}
	}
	effect->SetVector(handle, &times);
}

void Rva001F6B10Texture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		BFME2ParticleTextureHandle texture = TextureAsset::Get(TheParticleSystemManager->get()->m_particleTypeName.str(), 0, 0);
		if (texture)
			effect->SetTexture(handle, texture.Peek_D3D_Base_Texture());
		else
			effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
	}
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

void Rva001F6C6FDetailTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheParticleSystemManager && TheParticleSystemManager->get() && drawInfo1C4(TheParticleSystemManager->get().operator->()))
	{
		BFME2ParticleTextureHandle texture = TextureAsset::Get(drawInfo1C4(TheParticleSystemManager->get().operator->())->slot06().str(), 0, 0);
		if (texture)
			effect->SetTexture(handle, texture.Peek_D3D_Base_Texture());
		else
			effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
	}
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

void Rva001F6EB7ColorKeys(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 colors[4] =
	{
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f),
		D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f),
	};
	if (TheParticleSystemManager && TheParticleSystemManager->get())
	{
		const RGBColorKeyframe *keys = (const RGBColorKeyframe *)rva001F53AA(TheParticleSystemManager->get().operator->());
		if (keys)
		{
			for (int i = 0; i < 4; i++)
				colors[i] = D3DXVECTOR4(keys[i].color.red, keys[i].color.green, keys[i].color.blue, 1.0f);
		}
		// Alpha keys have a 12-byte random value followed by a four-byte frame.
		const char *alpha = (const char *)rva001F53BC(TheParticleSystemManager->get().operator->());
		if (alpha)
		{
			for (int i = 0; i < 4; i++)
				colors[i].w = ((const GameClientRandomVariable *)(alpha + i * 0x10))->getValue();
		}
	}
	effect->SetVectorArray(handle, colors, 4);
}

void __cdecl Rva001530E9Parse(const char *name, void *volatile path);

typedef void (*Rva001F69B1Callback)(ID3DXEffect *effect, D3DXHANDLE handle);

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

#include "../../Include/Common/Rva00080221.h"

struct TreeHintRef00217D4C : public Rva00080221
{
	TreeHintRef00217D4C(Rva001F69B1Callback callback) : Rva00080221((const int *)&callback) {}
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

#include "../../Include/Common/Rva001530E9Path.h"

// FX parameter binder base: vtable 0x00BC6F24 = { deleting dtor, __purecall }.
#include "../../Include/Common/Base.h"

// Default binder (0x00153664).
class FXShaderParameterSourceNamespace_Struct : public Base
{
public:
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// WorldBuilder names the sub-binders ParticleFXShaderParameterSourceNamespace::SourceNamespace_*.
class ParticleFXShaderParameterSourceNamespace
{
public:
	struct SourceNamespace_Draw;
};

// "Draw" sub-binder, vtable 0x00BE16E8 (dispatcher 0x001F69B1).
struct ParticleFXShaderParameterSourceNamespace::SourceNamespace_Draw : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

void ParticleFXShaderParameterSourceNamespace::SourceNamespace_Draw::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, handle, registry);
	if (name)
	{
		Rva001530E9Path path;
		Rva001530E9Parse(name, &path);
		if (_strcmpi(path.m_name, "Texture") == 0)
			registry->AddBinding(Rva001F6B10Texture, handle);
		else if (_strcmpi(path.m_name, "DetailTexture") == 0)
			registry->AddBinding(Rva001F6C6FDetailTexture, handle);
		else if (_strcmpi(path.m_name, "TextureLayout") == 0)
			registry->AddBinding(Rva001F713ETextureLayout, handle);
		else if (_strcmpi(path.m_name, "SpeedMultiplier") == 0)
			registry->AddBinding(Rva001F7233SpeedMultiplier, handle);
		else if (_strcmpi(path.m_name, "ColorKeys") == 0)
			registry->AddBinding(Rva001F6EB7ColorKeys, handle);
		else if (_strcmpi(path.m_name, "ColorScale") == 0)
			registry->AddBinding(Rva001F72E8ColorScale, handle);
		else if (_strcmpi(path.m_name, "TimeKeys") == 0)
			registry->AddBinding(Rva001F705ATimeKeys, handle);
		else if (_strcmpi(path.m_name, "ShaderType") == 0)
			registry->AddBinding(Rva001F6E1BShaderType, handle);
		else if (_strcmpi(path.m_name, "Reflected") == 0)
			registry->AddBinding(Rva001F6AF9Reflected, handle);
	}
}
