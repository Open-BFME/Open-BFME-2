// cl: /MD /EHsc
// Terrain FX parameter binder registered as "Terrain"
// (TerrainFXShaderParameterSourceNamespace, formerly Rva000E19A3). Target facts: ctor 0x000E188F (called from 0x007AB7D2) stores
// vptrs 0x00BCE51C { ??_G 0x000E1A1D, dispatcher 0x000E1F42 } at +0 and
// 0x00BCE50C at +4 (over base vtables 0x00BC6F24 { ??_G, __purecall } and
// 0x00C4EF80 { four __purecall }), five sub-binders at +0x08..+0x18 with
// vtables 0x00BCE4D0..0x00BCE4F0 { 0x005F45C3, dispatchers 0x000E236D,
// 0x000E25DE, 0x000E2A81, 0x000E2CA7, 0x000E2DFD }, zeroes +0x1C/+0x20/+0x24,
// calls the rowed register 0x00153565("Terrain", this) and stores this+4 in
// the singleton at VA 0x00DEBC60. The +4 vtable's slots are 0x002E6A93 (an
// ICF alias storing +0x1C), 0x000E1933 and 0x000E196B (by-value texture
// handle assigned through the rowed RefCountPtr<TextureClass>::operator=
// 0x000424D0 into +0x20/+0x24) and 0x000E190E (releases both via the rowed
// Release_Ref 0x0061ED10). Interface method names are inferred from the
// FX parameters the members feed ("RenderingMode", "BaseTexture",
// "NormalTexture"); the callback handle argument is a proven owning four-byte slot.
// The dtor 0x000E19A3 clears the singleton and erases "Terrain" (0x001532E1).
// Sub-binder dispatchers ("Cloud" 0x000E2A81, "Weather" 0x000E2CA7; the
// "Shroud", "Taint" and "Map" ones 0x000E236D/0x000E25DE/0x000E2DFD share the
// shape): base walk 0x00153664, then the parsed name compared (_strcmpi
// import) against the parameter strings, binding the matching static
// callback rowed in W3DTerrainFX*.cpp through the registry 0x00153ACA.

void __cdecl Rva001532E1Erase(const char *name);
void __cdecl Rva001530E9Parse(const char *name, void *volatile path);
#include <string.h>
void __cdecl Rva00153565Register(const char *name, void *binder);

struct IDirect3DBaseTexture8;
class DummyPtrType;

class TextureBaseClass
{
public:
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const;
};

class TextureClass
{
public:
	void Release_Ref();
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr() : ptr(0) {}
	const RefCountPtr &operator=(const RefCountPtr &that);
	~RefCountPtr()
	{
		if (ptr)
			ptr->Release_Ref();
	}
	operator const DummyPtrType *() const { return (const DummyPtrType *)ptr; }
	// A bool test, not the pointer conversion: retail compares the handle
	// word in memory (cmp [ecx],0) rather than loading it.
	bool isValid() const { return ptr != 0; }
	// BFME 2's TextureBaseClass is the one-word texture handle itself
	// (texture.cpp): Peek_D3D_Base_Texture takes the handle's address.
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const
	{
		return ((const TextureBaseClass *)this)->Peek_D3D_Base_Texture();
	}
	__forceinline void Clear()
	{
		if (ptr)
		{
			ptr->Release_Ref();
			ptr = 0;
		}
	}
	T *ptr;
};

typedef const char *D3DXHANDLE;

struct ID3DXEffect
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25();
	virtual long __stdcall SetInt(D3DXHANDLE parameter, int value); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual long __stdcall SetTexture(D3DXHANDLE parameter, IDirect3DBaseTexture8 *texture);
};

RefCountPtr<TextureClass> Rva00132F30BlackTexture();

// Static effect-parameter callback and the ref-counted callback handle the
// registry 0x00153ACA takes by value. Retail constructs each handle in the
// argument slot through 0x00080221 (12-byte impl holding the callback).
typedef void (*Rva000E19A3Callback)(ID3DXEffect *effect, D3DXHANDLE handle);

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);
struct FunctorBinding
{
 FunctorBinding(FunctorMethod method,FunctorTarget *target):m_target(target),m_method(method) {}
 FunctorTarget *m_target;
 unsigned int m_unmodelled04;
 FunctorMethod m_method;
};
class Rva0057BC63FunctorHolder
{
public:
 Rva0057BC63FunctorHolder(const FunctorBinding &binding);
 void *m_ptr;
};
class Rva00080221
{
public:
 Rva00080221(const int *callback);

 void *m_ptr;
};

struct TreeHintRef00217D4C : public Rva00080221
{
 __forceinline TreeHintRef00217D4C(Rva000E19A3Callback callback) : Rva00080221((const int *)&callback) {}


	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);
	}

};

struct MemberTreeHintRef00217D4C : public Rva0057BC63FunctorHolder {
 __forceinline MemberTreeHintRef00217D4C(FunctorBinding binding):Rva0057BC63FunctorHolder(binding){}
 ~MemberTreeHintRef00217D4C(){if(m_ptr)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_ptr);}
};
class FXShaderParameterBinder
{
public:
	void AddBinding(TreeHintRef00217D4C callback, const char *handle);
};

// Output of the rowed path parser 0x001530E9: the leading component, then
// the remainder the terrain dispatcher hands to a sub-binder.
struct Rva001530E9Path
{
	char m_name[0x48];
	const char *m_rest;
};

void Rva000E2B00CloudTexture(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva000E2BEEScaleUVOffsetPerSecondUV(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva000E2D26Vector(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva000E2DA4Level(ID3DXEffect *effect, D3DXHANDLE handle);

// FX parameter binder base: vtable 0x00BC6F24 = { deleting dtor, __purecall }.
class FXShaderParameterSourceNamespace
{
public:
	virtual ~FXShaderParameterSourceNamespace() {}
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry) = 0;
};

// Default binder, vtable 0x00BC6F24+8 = { 0x001F45C3, 0x00153664 }: the rowed
// 0x00153664 walks a struct parameter's members through this->ResolveBindings. Each
// sub-binder calls it first, so they derive from it (their inline dtors
// still reset straight to the base vtable, as retail's terrain dtor does).
class FXShaderParameterSourceNamespace_Struct : public FXShaderParameterSourceNamespace
{
public:
	~FXShaderParameterSourceNamespace_Struct() {}
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// Terrain-side interface at +4 (base vtable 0x00C4EF80, four __purecall
// slots); the singleton g_00DEBC60 points at this subobject.
class Rva000E19A3Interface
{
public:
	virtual void setRenderingMode(int mode) = 0;
	virtual void setBaseTexture(RefCountPtr<TextureClass> texture) = 0;
	virtual void setNormalTexture(RefCountPtr<TextureClass> texture) = 0;
	virtual void clearTextures() = 0;
};

// g_00DEBC60: matched references place it at VA 0xdebc60 (zero-filled .bss).
Rva000E19A3Interface *g_00DEBC60;

// WorldBuilder: TerrainFXShaderParameterSourceNamespace (FlatHeightMap.cpp;
// ResolveBindings 0x000E1F42 is WB VA 0x007C0630, strings lead score 9.25).
// Its five sub-binders are the SourceNamespace_* members below.
class TerrainFXShaderParameterSourceNamespace : public FXShaderParameterSourceNamespace, public Rva000E19A3Interface
{
public:
	// The five sub-binders (vtables 0x00BCE4D0..0x00BCE4F0, each { 0x005F45C3,
	// dispatcher }) the terrain dispatcher forwards "Shroud", "Taint", "Cloud",
	// "Weather" and "Map" paths to. Slot 1 of each vtable is, in order,
	// 0x000E236D, 0x000E25DE, 0x000E2A81, 0x000E2CA7, 0x000E2DFD; WorldBuilder's
	// FlatHeightMap.cpp names them SourceNamespace_Shroud, _Taint, _Cloud,
	// _Weather and _Map ::ResolveBindings (string leads).
	struct SourceNamespace_Shroud : public FXShaderParameterSourceNamespace_Struct
	{
		~SourceNamespace_Shroud() {}
		virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
	};

	struct SourceNamespace_Cloud : public FXShaderParameterSourceNamespace_Struct
	{
		~SourceNamespace_Cloud() {}
		virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
	};

	struct SourceNamespace_Map : public FXShaderParameterSourceNamespace_Struct
	{
		~SourceNamespace_Map() {}
		virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
	};

	class SourceNamespace_Taint : public FXShaderParameterSourceNamespace_Struct
	{
	public:
		~SourceNamespace_Taint() {}
		virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
	};

	// ?ResolveBindings@SourceNamespace_Weather@TerrainFXShaderParameterSourceNamespace@@UAEXPBD0PAVFXShaderParameterBinder@@@Z @0x000E2CA7 127B:
	// renamed from placeholder Rva000E2CA7Binder — the WorldBuilder twin asserts
	// SourceNamespace_Weather::ResolveBindings at EA's own FlatHeightMap.cpp.
	// Scope spelling follows the landed SourceNamespace_Shroud/Taint siblings.
	struct SourceNamespace_Weather : public FXShaderParameterSourceNamespace_Struct
	{
		~SourceNamespace_Weather() {}
		virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
	};

	TerrainFXShaderParameterSourceNamespace();
	virtual ~TerrainFXShaderParameterSourceNamespace();
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
	// Retail folds this body with GameSlot::setTeamNumber at 0x002E6A93 (vtable 0x00BCE50C slot 0).
	virtual void setRenderingMode(int mode) { m_1C = mode; }
	virtual void setBaseTexture(RefCountPtr<TextureClass> texture);
	virtual void setNormalTexture(RefCountPtr<TextureClass> texture);
	virtual void clearTextures();
	void Rva000E2110RenderingMode(ID3DXEffect *effect, D3DXHANDLE handle);
	void Rva000E214DBaseTexture(ID3DXEffect *effect, D3DXHANDLE handle);
	void Rva000E21BENormalTexture(ID3DXEffect *effect, D3DXHANDLE handle);
private:
	SourceNamespace_Shroud m_08;
	SourceNamespace_Taint m_0C;
	SourceNamespace_Cloud m_10;
	SourceNamespace_Weather m_14;
	SourceNamespace_Map m_18;
	int m_1C;
	RefCountPtr<TextureClass> m_20;
	RefCountPtr<TextureClass> m_24;
};

TerrainFXShaderParameterSourceNamespace::TerrainFXShaderParameterSourceNamespace() : m_1C(0)
{
	Rva00153565Register("Terrain", this);
	g_00DEBC60 = this;
}

TerrainFXShaderParameterSourceNamespace::~TerrainFXShaderParameterSourceNamespace()
{
	g_00DEBC60 = 0;
	Rva001532E1Erase("Terrain");
}

void TerrainFXShaderParameterSourceNamespace::clearTextures()
{
	m_20.Clear();
	m_24.Clear();
}

void TerrainFXShaderParameterSourceNamespace::setBaseTexture(RefCountPtr<TextureClass> texture)
{
	RefCountPtr<TextureClass> &dst = m_20;
	dst = texture;
}

void TerrainFXShaderParameterSourceNamespace::setNormalTexture(RefCountPtr<TextureClass> texture)
{
	RefCountPtr<TextureClass> &dst = m_24;
	dst = texture;
}

// Member callbacks the terrain FX dispatcher 0x000E1F42 binds with this
// object (target fact: it stores 0x004E2110 for "RenderingMode", 0x004E214D
// for "BaseTexture" and 0x004E21BE for "NormalTexture" as functor methods).
// Rendering modes past 4 fall back to 0; missing textures fall back to the
// black 1x1 texture 0x00132F30.
void TerrainFXShaderParameterSourceNamespace::Rva000E2110RenderingMode(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (m_1C < 5)
		effect->SetInt(handle, m_1C);
	else
		effect->SetInt(handle, 0);
}

void TerrainFXShaderParameterSourceNamespace::Rva000E214DBaseTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (m_20.isValid())
		effect->SetTexture(handle, m_20.Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132F30BlackTexture().Peek_D3D_Base_Texture());
}

void TerrainFXShaderParameterSourceNamespace::Rva000E21BENormalTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (m_24.isValid())
		effect->SetTexture(handle, m_24.Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132F30BlackTexture().Peek_D3D_Base_Texture());
}

void TerrainFXShaderParameterSourceNamespace::SourceNamespace_Cloud::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, handle, registry);
	if (name)
	{
		Rva001530E9Path path;
		Rva001530E9Parse(name, &path);
		if (_strcmpi(path.m_name, "Texture") == 0)
			registry->AddBinding(Rva000E2B00CloudTexture, handle);
		else if (_strcmpi(path.m_name, "ScaleUV_OffsetPerSecondUV") == 0)
			registry->AddBinding(Rva000E2BEEScaleUVOffsetPerSecondUV, handle);
	}
}

void TerrainFXShaderParameterSourceNamespace::SourceNamespace_Weather::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, handle, registry);
	if (name)
	{
		Rva001530E9Path path;
		Rva001530E9Parse(name, &path);
		if (_strcmpi(path.m_name, "DarkeningColor") == 0)
			registry->AddBinding(Rva000E2D26Vector, handle);
		else if (_strcmpi(path.m_name, "LightningColor") == 0)
			registry->AddBinding(Rva000E2DA4Level, handle);
	}
}


// Native E1F42..E20DF RET12,413B. The native table BCE51C and registered
// Terrain namespace establish dispatcher identity. Five prefix branches
// use the suffix at parsed+48; seven leaf branches bind four static and
// three member callbacks. Both existing constructor providers produce a
// one-word owning callback handle (53B at80221;59B at57BC63), and the
// existing207B AddBinding copies that word and releases it through7DEEF.
// MemberTreeHintRef is an ABI view of that same incoming handle slot; the
// method cast changes its compile-time construction type without changing
// the verified thiscall/by-value ownership contract. The two base views
// choose the actual constructors directly, preserving native stack storage
// and the four-word FunctorBinding copy without intermediate handle copies.
// No new provider name or pin is introduced. Target member-pointer words
// and callbacks are independently established by this native body.
void setMacroTexture(ID3DXEffect *,const char *);
void Rva000E20DFIsMacroTextureStrechedToMapSize(ID3DXEffect *,const char *);
void setResourceTexture(ID3DXEffect *,const char *);
void Rva000E213CIsResourceTextureEnabled(ID3DXEffect *,const char *);
void TerrainFXShaderParameterSourceNamespace::ResolveBindings(const char *name,const char *handle,FXShaderParameterBinder *registry)
{
 Rva001530E9Path path;
 Rva001530E9Parse(name,&path);
 int (__cdecl *compare)(const char *,const char *)=_strcmpi;
 if(compare(path.m_name,"Shroud")==0) m_08.ResolveBindings(path.m_rest,handle,registry);
 else if(compare(path.m_name,"Taint")==0) m_0C.ResolveBindings(path.m_rest,handle,registry);
 else if(compare(path.m_name,"Cloud")==0) m_10.ResolveBindings(path.m_rest,handle,registry);
 else if(compare(path.m_name,"Weather")==0) m_14.ResolveBindings(path.m_rest,handle,registry);
 else if(compare(path.m_name,"Map")==0) m_18.ResolveBindings(path.m_rest,handle,registry);
 else if(compare(path.m_name,"BaseTexture")==0) (registry->*reinterpret_cast<void(FXShaderParameterBinder::*)(MemberTreeHintRef00217D4C,const char*)>(&FXShaderParameterBinder::AddBinding))(FunctorBinding(reinterpret_cast<FunctorMethod>(&TerrainFXShaderParameterSourceNamespace::Rva000E214DBaseTexture),reinterpret_cast<FunctorTarget *>(this)),handle);
 else if(compare(path.m_name,"NormalTexture")==0) (registry->*reinterpret_cast<void(FXShaderParameterBinder::*)(MemberTreeHintRef00217D4C,const char*)>(&FXShaderParameterBinder::AddBinding))(FunctorBinding(reinterpret_cast<FunctorMethod>(&TerrainFXShaderParameterSourceNamespace::Rva000E21BENormalTexture),reinterpret_cast<FunctorTarget *>(this)),handle);
 else if(compare(path.m_name,"MacroTexture")==0) registry->AddBinding(setMacroTexture,handle);
 else if(compare(path.m_name,"IsMacroTextureStrechedToMapSize")==0) registry->AddBinding(Rva000E20DFIsMacroTextureStrechedToMapSize,handle);
 else if(compare(path.m_name,"RenderingMode")==0) (registry->*reinterpret_cast<void(FXShaderParameterBinder::*)(MemberTreeHintRef00217D4C,const char*)>(&FXShaderParameterBinder::AddBinding))(FunctorBinding(reinterpret_cast<FunctorMethod>(&TerrainFXShaderParameterSourceNamespace::Rva000E2110RenderingMode),reinterpret_cast<FunctorTarget *>(this)),handle);
 else if(compare(path.m_name,"ResourceTexture")==0) registry->AddBinding(setResourceTexture,handle);
 else if(compare(path.m_name,"IsResourceTextureEnabled")==0) registry->AddBinding(Rva000E213CIsResourceTextureEnabled,handle);
}
