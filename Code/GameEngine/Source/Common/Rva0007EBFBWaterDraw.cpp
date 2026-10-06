// cl: /EHsc /MD /O1
// ??0Rva0007EBFB@@QAE@XZ @0x0007EBFB 73B WaterDraw registering ctor with vtable plus two members.
// Evidence: stores 0x007C6F80/5C/64 then Register WaterDraw; empty base arms EH state 0. Precedents Rva000E6350Ctor.cpp Rva0018BEC7Ctor.cpp.
//
// The "WaterDraw" FX parameter binder, the water twin of the Terrain binder
// in Rva000E19A3Dtor.cpp and modelled the same way. Target facts: vtable
// 0x00BC6F80 = { ??_G 0x0007EC87, dispatcher 0x0007FFED } over the base
// vtable 0x00BC6F24; the two members at +0x04/+0x08 carry vtables
// 0x00BC6F5C/0x00BC6F64 = { 0x001F45C3, dispatchers 0x000806F3/0x00080E30 },
// the shape of the terrain sub-binders. The dtor 0x0007EC44 erases
// "WaterDraw" (0x001532E1) and leaves all three vptrs at the base vtable.
//
// The dispatcher 0x0007FFED parses the parameter path (0x001530E9), compares
// the leading component (_strcmpi import) and binds through the registry
// 0x00153ACA the callback whose address it stores: 0x00080168 for
// "ReflectionTexture", 0x000800D6 for "BlendUsingTerrainAlpha", 0x000800FA
// for "TransparentWaterDepth" and 0x00080131 for "MinWaterOpacity". "PCAWater"
// and "PCAWater_M" forward the rest of the path to the +0x04 and +0x08 member
// through vtable slot 1. Callback names come from those strings; field names
// are address-derived. TheTerrainRenderObject is VA 0x00DE1EAC, g_00DFEF18 the
// singleton Rva002D3627Check.cpp reads, TheWritableGlobalData VA 0x00DFE758,
// W3DGCData00DE2000 VA 0x00DE2000 and the OVERRIDE at VA 0x00DFF488 holds the
// Overridable whose final override (0x001E35DF) carries the +0x50 flag.
//
// Compiler shape: /O1 throughout (push-imm SetBool arms cross-jumped into one
// call, pop ecx cleanups and the dispatcher's ebp frame); with /O2 the
// dispatcher omits the frame and 0x000800D6 duplicates its call. The member
// classes declare no dtor, so the WaterDraw dtor schedules the three base
// vptr stores after its EH epilogue load as retail does.
//
// ??1Rva0007EBFB@@UAE@XZ                                             @0x0007EC44  67B
// ?ResolveBindings@Rva0007EBFB@@UAEXPBD0PAVFXShaderParameterBinder@@@Z @0x0007FFED 233B
// ?Rva000800D6BlendUsingTerrainAlpha@@YAXPAUID3DXEffect@@PBD@Z      @0x000800D6  36B
// ?Rva000800FATransparentWaterDepth@@YAXPAUID3DXEffect@@PBD@Z       @0x000800FA  55B
// ?Rva00080131MinWaterOpacity@@YAXPAUID3DXEffect@@PBD@Z             @0x00080131  55B
// ?Rva00080168ReflectionTexture@@YAXPAUID3DXEffect@@PBD@Z           @0x00080168 185B

void __cdecl Rva00153565Register(const char *name, void *obj);
void __cdecl Rva001532E1Erase(const char *name);
void __cdecl Rva001530E9Parse(const char *name, void *volatile path);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

struct IDirect3DBaseTexture8;

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
	~RefCountPtr()
	{
		if (ptr)
			ptr->Release_Ref();
	}
	// BFME 2's TextureBaseClass is the one-word texture handle itself
	// (texture.cpp): Peek_D3D_Base_Texture takes the handle's address.
	IDirect3DBaseTexture8 *Peek_D3D_Base_Texture() const
	{
		return ((const TextureBaseClass *)this)->Peek_D3D_Base_Texture();
	}
	T *ptr;
};

typedef const char *D3DXHANDLE;
typedef int BOOL;
#define FALSE 0
#define TRUE 1

struct ID3DXEffect
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21();
	virtual long __stdcall SetBool(D3DXHANDLE parameter, BOOL value); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29();
	virtual long __stdcall SetFloat(D3DXHANDLE parameter, float value); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual long __stdcall SetTexture(D3DXHANDLE parameter, IDirect3DBaseTexture8 *texture);
};

RefCountPtr<TextureClass> Rva00132F30BlackTexture();

// Static effect-parameter callback and the ref-counted callback handle the
// registry 0x00153ACA takes by value. Retail pushes the handle, then stores
// the callback into that dead argument slot, saves esp before "mov ecx, esp"
// and calls the rowed ctor 0x00080221 with the slot's address: the shape of
// an inline converting ctor whose by-value parameter forwards to the base
// ctor (the AsciiString order in Rva0006B76CMethod.cpp), so AddBinding takes
// the bare function and converts it in its argument slot.
typedef void (*Rva0007EBFBCallback)(ID3DXEffect *effect, D3DXHANDLE handle);

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

// The rowed ctor 0x00080221 (Rva00080221Ctor.cpp), spelled as its row.
class Rva00080221
{
public:
	Rva00080221(const int *arg);
	TargetRef00217D4C *m_ptr;
};

struct TreeHintRef00217D4C : public Rva00080221
{
	TreeHintRef00217D4C(Rva0007EBFBCallback callback) : Rva00080221((const int *)&callback) {}
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

// Output of the rowed path parser 0x001530E9: the leading component, then
// the remainder the dispatcher hands to a sub-binder.
struct Rva001530E9Path
{
	char m_name[0x48];
	const char *m_rest;
};

// FX parameter binder base: vtable 0x00BC6F24 = { deleting dtor, __purecall }.
class Base
{
public:
	virtual ~Base() {}
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry) = 0;
};

// Default binder (0x00153664); its implicit dtor leaves the base vtable.
class FXShaderParameterSourceNamespace_Struct : public Base
{
public:
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// "PCAWater" sub-binder, vtable 0x00BC6F5C (dispatcher 0x000806F3).
struct Rva0007EBFB_Member0 : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

// "PCAWater_M" sub-binder, vtable 0x00BC6F64 (dispatcher 0x00080E30).
struct Rva0007EBFB_Member1 : public FXShaderParameterSourceNamespace_Struct
{
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

class Rva0007EBFB : public Base
{
public:
	Rva0007EBFB();
	virtual ~Rva0007EBFB();
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);

private:
	Rva0007EBFB_Member0 m_04;
	Rva0007EBFB_Member1 m_08;
};

class BaseHeightMapRenderObjClass
{
public:
	char m_pad0000[0x37E4];
	float m_37E4;
	float m_37E8;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class Rva002D3627Host
{
public:
	char m_pad00[0x18];
	unsigned char m_18;
};
extern Rva002D3627Host *g_00DFEF18;

class GlobalData
{
public:
	char m_pad00[0x5E];
	bool m_5E;
};
extern GlobalData *TheWritableGlobalData;

struct Rva00080168Owner
{
	char m_pad000[0xF8];
	RefCountPtr<TextureClass> m_F8;
};
extern void *W3DGCData00DE2000;

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride( void ) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;
	bool m_isOverride;
};

class Rva00DFF488Setting : public Overridable
{
public:
	char m_pad0C[0x50 - 0x0C];
	bool m_50;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->( void ) const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}
	operator const T *( void ) const
	{
		if (!m_overridable)
			return 0;
		return (const T *)m_overridable->getFinalOverride();
	}

private:
	const T *m_overridable;
};
extern OVERRIDE<Rva00DFF488Setting> TheRva00DFF488Setting;

void Rva00080168ReflectionTexture(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva000800D6BlendUsingTerrainAlpha(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva000800FATransparentWaterDepth(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva00080131MinWaterOpacity(ID3DXEffect *effect, D3DXHANDLE handle);

Rva0007EBFB::Rva0007EBFB()
{
    Rva00153565Register("WaterDraw", this);
}

Rva0007EBFB::~Rva0007EBFB()
{
	Rva001532E1Erase("WaterDraw");
}

void Rva0007EBFB::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	Rva001530E9Path path;
	Rva001530E9Parse(name, &path);
	if (_strcmpi(path.m_name, "ReflectionTexture") == 0)
		registry->AddBinding(Rva00080168ReflectionTexture, handle);
	else if (_strcmpi(path.m_name, "BlendUsingTerrainAlpha") == 0)
		registry->AddBinding(Rva000800D6BlendUsingTerrainAlpha, handle);
	else if (_strcmpi(path.m_name, "TransparentWaterDepth") == 0)
		registry->AddBinding(Rva000800FATransparentWaterDepth, handle);
	else if (_strcmpi(path.m_name, "MinWaterOpacity") == 0)
		registry->AddBinding(Rva00080131MinWaterOpacity, handle);
	else
	{
		Base *binder;
		if (_strcmpi(path.m_name, "PCAWater") == 0)
			binder = &m_04;
		else if (_strcmpi(path.m_name, "PCAWater_M") == 0)
			binder = &m_08;
		else
			return;
		binder->ResolveBindings(path.m_rest, handle, registry);
	}
}

void Rva000800D6BlendUsingTerrainAlpha(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (g_00DFEF18 && g_00DFEF18->m_18)
		effect->SetBool(handle, FALSE);
	else
		effect->SetBool(handle, TRUE);
}

void Rva000800FATransparentWaterDepth(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheTerrainRenderObject)
		effect->SetFloat(handle, TheTerrainRenderObject->m_37E4);
	else
		effect->SetFloat(handle, 0.0f);
}

void Rva00080131MinWaterOpacity(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheTerrainRenderObject)
		effect->SetFloat(handle, TheTerrainRenderObject->m_37E8);
	else
		effect->SetFloat(handle, 0.0f);
}

void Rva00080168ReflectionTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheWritableGlobalData->m_5E && W3DGCData00DE2000 && TheRva00DFF488Setting && TheRva00DFF488Setting->m_50)
		effect->SetTexture(handle, ((Rva00080168Owner *)W3DGCData00DE2000)->m_F8.Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132F30BlackTexture().Peek_D3D_Base_Texture());
}
