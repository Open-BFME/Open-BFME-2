// cl: /DNDEBUG /MD /EHsc
// By-value texture-handle getters the terrain FX texture callbacks call
// (0x000E28C3 calls 0x000E2983 on TheTerrainRenderObject, VA 0x00DE1EAC, and
// tests the returned handle before Peek_D3D_Base_Texture). Each copies one
// member handle into the hidden return slot, bumping the 16-bit reference
// count at +4 that the rowed TextureClass::Release_Ref (0x0061ED10) drops.
// Target facts: thiscall, ret 4, hidden return pointer, member offsets below.
// The handle template and method names are inferred/address-derived.
//
// ?getMacroTexture@BaseHeightMapRenderObjClass@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ @0x000E234E 31B (+0x3828)
// ?getLowTexture@BaseHeightMapRenderObjClass@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ @0x000E2983 31B (+0x3838)
// ?getHighTexture@BaseHeightMapRenderObjClass@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ @0x000E2A62 31B (+0x3844)
// ?getCloudTexture@BaseHeightMapRenderObjClass@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ @0x000E2BCF 31B (+0x381C)
// ?getMaskTexture@Rva000E28A7@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ               @0x000E28A7 28B (+0x1C)

#include <string.h>

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class TextureClass
{
public:
	__forceinline void Add_Ref() { ++m_refCount; }
	void Release_Ref();

private:
	void *m_vtable;
	unsigned short m_refCount;
};

struct IDirect3DBaseTexture8;
class DummyPtrType;

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

template <class T> class RefCountPtr
{
public:
    RefCountPtr(const RefCountPtr &that);
    struct InlineCopyTag {};
    __forceinline RefCountPtr(const RefCountPtr &that, InlineCopyTag) : m_ptr(that.m_ptr)
    {
        if (m_ptr) m_ptr->Add_Ref();
    }
	~RefCountPtr()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	operator const DummyPtrType *() const { return (const DummyPtrType *)m_ptr; }
	// BFME 2's TextureBaseClass is the one-word texture handle itself
	// (texture.cpp): Peek_D3D_Base_Texture takes the handle's address, and
	// retail passes the address of the RefCountPtr.
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const
	{
		return ((const TextureBaseClass *)this)->Peek_D3D_Base_Texture();
	}

private:
	T *m_ptr;
};

class BaseHeightMapRenderObjClass
{
public:
	RefCountPtr<TextureClass> getMacroTexture();
	RefCountPtr<TextureClass> getLowTexture();
	RefCountPtr<TextureClass> getHighTexture();
	RefCountPtr<TextureClass> getCloudTexture();

private:
	char m_pad0000[0x381c];
	RefCountPtr<TextureClass> m_381c;
	char m_pad3820[0x3828 - 0x3820];
	RefCountPtr<TextureClass> m_3828;
	char m_pad382c[0x3838 - 0x382c];
	RefCountPtr<TextureClass> m_3838;
	char m_pad383c[0x3844 - 0x383c];
	RefCountPtr<TextureClass> m_3844;
	char m_pad3848[0x3878 - 0x3848];

public:
	class Rva00072B3A *get3878() const { return m_3878; }
	class Rva000E28A7 *get387c() const { return m_387c; }

	class Rva00072B3A *m_3878;
	class Rva000E28A7 *m_387c;
};

RefCountPtr<TextureClass> BaseHeightMapRenderObjClass::getMacroTexture()
{
	return RefCountPtr<TextureClass>(m_3828, RefCountPtr<TextureClass>::InlineCopyTag());
}

RefCountPtr<TextureClass> BaseHeightMapRenderObjClass::getLowTexture()
{
	return RefCountPtr<TextureClass>(m_3838, RefCountPtr<TextureClass>::InlineCopyTag());
}

RefCountPtr<TextureClass> BaseHeightMapRenderObjClass::getHighTexture()
{
	return RefCountPtr<TextureClass>(m_3844, RefCountPtr<TextureClass>::InlineCopyTag());
}

RefCountPtr<TextureClass> BaseHeightMapRenderObjClass::getCloudTexture()
{
	return RefCountPtr<TextureClass>(m_381c, RefCountPtr<TextureClass>::InlineCopyTag());
}

class Rva000E28A7
{
public:
	RefCountPtr<TextureClass> getMaskTexture();

private:
	char m_pad00[0x1c];
	RefCountPtr<TextureClass> m_maskTexture;
};

RefCountPtr<TextureClass> Rva000E28A7::getMaskTexture()
{
	return RefCountPtr<TextureClass>(m_maskTexture, RefCountPtr<TextureClass>::InlineCopyTag());
}

// Effect-parameter texture callbacks of the BFME 2 terrain FX binding (the
// scalar and vector ones are in W3DTerrainFXVectorParams.cpp). Each is a
// cdecl (effect, handle) function ending in ID3DXEffect::SetTexture (vtable
// slot 52, +0xD0) on a by-value texture handle; retail places each beside
// the getter above that it calls. Target facts: the dispatchers store
// 0x004E222F for "ResourceTexture" and 0x004E227F for "MacroTexture"
// (0x000E1F42), 0x004E24C5 for "Texture" (0x000E236D), 0x004E27D9,
// 0x004E28C3 and 0x004E29A2 for "MaskTexture", "LowTexture" and
// "HighTexture" (0x000E25DE) and 0x004E2B00 for "Texture" (0x000E2A81).
// The fallbacks 0x00132E76 and 0x00132F30 return a lazily created 1x1
// A8R8G8B8 texture filled with 0xFFFFFFFF and 0 respectively; their names,
// like the field names, are address-derived.

typedef const char *D3DXHANDLE;

struct ID3DXEffect
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual long __stdcall SetTexture(D3DXHANDLE parameter, IDirect3DBaseTexture8 *texture);
};

RefCountPtr<TextureClass> Rva00132E76WhiteTexture();
RefCountPtr<TextureClass> Rva00132F30BlackTexture();

// The native 72B3A getter returns the existing four-byte handle view,
// whose only base is this same nullable texture reference.
class RvaTextureHandleView : public RefCountPtr<TextureClass> {};

class Rva00072B3A
{
public:
	RvaTextureHandleView getShroudTexture() const;
};

class GlobalData
{
public:
	char m_pad00[0x3c];
	bool m_useCloudMap;
	char m_pad3d[0x48 - 0x3d];
	bool m_useLightMap;
};

extern GlobalData *TheWritableGlobalData;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class Rva002BA8F1Logic
{
public:
	char m_pad00[0xb4];
	bool m_b4;
	bool m_b5;
};

void setResourceTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	effect->SetTexture(handle, Rva00132F30BlackTexture().Peek_D3D_Base_Texture());
}

void setMacroTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getMacroTexture() && TheWritableGlobalData && TheWritableGlobalData->m_useLightMap)
		effect->SetTexture(handle, TheTerrainRenderObject->getMacroTexture().Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

void Rva000E24C5ShroudTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) && (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_b4 && (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_b5)
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
	else if (TheTerrainRenderObject && TheTerrainRenderObject->m_3878 && TheTerrainRenderObject->m_3878->getShroudTexture())
		effect->SetTexture(handle, TheTerrainRenderObject->get3878()->getShroudTexture().Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

void setMaskTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->m_387c && TheTerrainRenderObject->m_387c->getMaskTexture())
		effect->SetTexture(handle, TheTerrainRenderObject->get387c()->getMaskTexture().Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

void setLowTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getLowTexture())
		effect->SetTexture(handle, TheTerrainRenderObject->getLowTexture().Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

void setHighTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getHighTexture())
		effect->SetTexture(handle, TheTerrainRenderObject->getHighTexture().Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

void Rva000E2B00CloudTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheTerrainRenderObject && TheTerrainRenderObject->getCloudTexture() && TheWritableGlobalData && TheWritableGlobalData->m_useCloudMap)
		effect->SetTexture(handle, TheTerrainRenderObject->getCloudTexture().Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

// Terrain FX three-name ResolveBindings dispatcher (Texture, ScaleUV_OffsetUV,
// ObjectShroudStatus), same WaterDraw member pattern as the rowed particle
// dispatcher Rva001F69B1 (Common/Rva001F69B1ParticleDrawBinder.cpp): base call,
// Rva001530E9Parse split, comparator calls, selected callback wrapped for
// AddBinding. Retail loads the comparator address once and reuses the name
// slot for the selected callback, so the source models both explicitly.
// Identity is address-derived: no vtable slot evidence yet.
void __cdecl Rva001530E9Parse(const char *name, void *volatile path);

struct Rva001530E9Path
{
	char m_name[0x40];
	bool m_hasStar;
	bool m_hasBracket;
	int m_index;
	const char *m_rest;
};

class Rva00080221
{
public:
	Rva00080221(const int *arg);
	void *m_ptr;
};

struct TreeHintRef00217D4C : public Rva00080221
{
	TreeHintRef00217D4C(const void *callback) : Rva00080221((const int *)&callback) {}
	~TreeHintRef00217D4C();
};

class FXShaderParameterBinder
{
public:
	void AddBinding(TreeHintRef00217D4C callback, const char *handle);
};

class Base
{
public:
	virtual ~Base() {}
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry) = 0;
};

class FXShaderParameterSourceNamespace_Struct : public Base
{
public:
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// ?ResolveBindings@SourceNamespace_Shroud@TerrainFXShaderParameterSourceNamespace@@UAEXPBD0PAVFXShaderParameterBinder@@@Z @0x000E236D 156B:
// renamed from placeholder Rva000E236D::rva000E236D — the WorldBuilder twin
// asserts the name at EA's own FlatHeightMap.cpp line 316. Virtual override
// of the base ResolveBindings (UAE); scope spelling follows the landed
// SourceNamespace_Taint sibling.

void Rva000E24C5ShroudTexture(ID3DXEffect *effect, const char *name);
void Rva000E2409ScaleOffset(ID3DXEffect *effect, const char *name);
void Rva000E249DObjectShroudStatus(ID3DXEffect *effect, const char *name);

typedef void (*Rva000E236DCallback)(ID3DXEffect *effect, D3DXHANDLE handle);

void Rva000E26CFIsEnabled(ID3DXEffect *, const char *);
void Rva000E2700Offset(ID3DXEffect *, const char *);
void Rva000E2763Scale(ID3DXEffect *, const char *);
// Target identity: native BCE4D8 slot 1 in the Terrain binder's +0C subobject,
// WB 7C1080 names SourceNamespace_Taint::ResolveBindings and the full six-arm CFG.
// Native E25DE..E26CF RET12; six named parameter callbacks. Qualified name follows WorldBuilder; storage is the proven four-byte polymorphic base.
void setMaskTexture(ID3DXEffect *, const char *);
void setLowTexture(ID3DXEffect *, const char *);
void setHighTexture(ID3DXEffect *, const char *);
// Scope-only containing type; no storage or extent claim is made for it.
class TerrainFXShaderParameterSourceNamespace
{
public:
 class SourceNamespace_Taint;
 class SourceNamespace_Shroud;
};
class TerrainFXShaderParameterSourceNamespace::SourceNamespace_Shroud : public FXShaderParameterSourceNamespace_Struct
{
public:
 ~SourceNamespace_Shroud() {}
 virtual void ResolveBindings(const char *name,const char *handle,FXShaderParameterBinder *registry);
};
void TerrainFXShaderParameterSourceNamespace::SourceNamespace_Shroud::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, handle, registry);
	if (name)
	{
		Rva001530E9Path path;
		Rva001530E9Parse(name, &path);
		int (__cdecl *compare)(const char *, const char *) = _strcmpi;
		if (compare(path.m_name, "Texture") == 0)
			registry->AddBinding(Rva000E24C5ShroudTexture, handle);
		else if (compare(path.m_name, "ScaleUV_OffsetUV") == 0)
			registry->AddBinding(Rva000E2409ScaleOffset, handle);
		else if (compare(path.m_name, "ObjectShroudStatus") == 0)
			registry->AddBinding(Rva000E249DObjectShroudStatus, handle);
	}
}
class TerrainFXShaderParameterSourceNamespace::SourceNamespace_Taint : public FXShaderParameterSourceNamespace_Struct
{
public:
 ~SourceNamespace_Taint() {}
 virtual void ResolveBindings(const char *name,const char *handle,FXShaderParameterBinder *registry);
};
void TerrainFXShaderParameterSourceNamespace::SourceNamespace_Taint::ResolveBindings(const char *name,const char *handle,FXShaderParameterBinder *registry)
{
 FXShaderParameterSourceNamespace_Struct::ResolveBindings(name,handle,registry);
 if(name)
 {
  Rva001530E9Path path;
  Rva001530E9Parse(name,&path);
  int (__cdecl *compare)(const char *,const char *)=_strcmpi;
  if(compare(path.m_name,"IsEnabled")==0) registry->AddBinding(Rva000E26CFIsEnabled,handle);
  else if(compare(path.m_name,"MaskTexture")==0) registry->AddBinding(setMaskTexture,handle);
  else if(compare(path.m_name,"LowTexture")==0) registry->AddBinding(setLowTexture,handle);
  else if(compare(path.m_name,"HighTexture")==0) registry->AddBinding(setHighTexture,handle);
  else if(compare(path.m_name,"Offset")==0) registry->AddBinding(Rva000E2700Offset,handle);
  else if(compare(path.m_name,"Scale")==0) registry->AddBinding(Rva000E2763Scale,handle);
 }
}
