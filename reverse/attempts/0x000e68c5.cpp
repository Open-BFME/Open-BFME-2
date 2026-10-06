// ?Rva000E68C5SwayOffsets@@YAXPAUID3DXEffect@@PBD@Z
// partial score=0.98 date=2026-10-06
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// ??1Rva000E6387@@UAE@XZ @0x000E6387 57B: destructor of the FX parameter
// binder registered as "Vegetation" (address-derived name Rva000E6387, as
// pinned). Target facts: vtable 0x00BCEA04 = { ??_G 0x000E63C0 (rowed),
// dispatcher 0x000E67E3 }; base vtable 0x00BC6F24 = { deleting dtor,
// __purecall }, the binder base modelled in the rowed Rva000E19A3Dtor.cpp
// ("Terrain"). The dtor erases its "Vegetation" registration through the
// rowed Rva001532E1Erase 0x001532E1 (same as the Terrain dtor erases
// "Terrain") and resets to the base vtable; the EH state around the erase
// covers the base subobject. Callers: rowed ??_G 0x000E63C0 and the gap
// thunk 0x007B6E18 on the singleton g_Va00DEBC98.

void __cdecl Rva001532E1Erase(const char *name);
void __cdecl Rva001530E9Parse(const char *name, void *volatile path);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);
extern "C" __declspec(dllimport) double __cdecl floor(double);
extern "C" void *__cdecl memset(void *destination, int value, unsigned int bytes);

typedef const char *D3DXHANDLE;
typedef int BOOL;
#define FALSE 0
#define TRUE 1

struct IDirect3DBaseTexture8;
class DummyPtrType;

struct D3DXVECTOR4
{
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
	virtual long __stdcall SetBool(D3DXHANDLE parameter, BOOL value); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
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

RefCountPtr<TextureClass> Rva00132E76WhiteTexture();

__forceinline long FloatToLong(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator*=(float k) { X *= k; Y *= k; Z *= k; return *this; }
	friend Vector3 operator*(float k, const Vector3 &a) { return Vector3(a.X * k, a.Y * k, a.Z * k); }
	friend Vector3 operator+(const Vector3 &a, const Vector3 &b) { return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z); }
	float X;
	float Y;
	float Z;
};

enum
{
	MAX_SWAY_TYPES = 10,
	NUM_SWAY_ENTRIES = 100
};

class Rva000E6AC0
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual bool slot04() = 0;
	RefCountPtr<TextureClass> rva000E6AA4();

	char m_pad004[0x38 - 4];
	RefCountPtr<TextureClass> m_38;
	char m_pad03c[0x90 - 0x3c];
	Vector3 m_swayOffsets[NUM_SWAY_ENTRIES];
	int m_curSwayVersion;
	float m_curSwayOffset[MAX_SWAY_TYPES];
	float m_curSwayStep[MAX_SWAY_TYPES];
	float m_curSwayFactor[MAX_SWAY_TYPES];
};

extern Rva000E6AC0 *g_009EBC90;

class GlobalData
{
public:
	char m_pad000[0xd45];
	bool m_D45;
};

extern GlobalData *TheWritableGlobalData;

typedef void (*Rva000E67E3Callback)(ID3DXEffect *effect, D3DXHANDLE handle);

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
	TreeHintRef00217D4C(Rva000E67E3Callback callback) : Rva00080221((const int *)&callback) {}
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

void Rva000E6878IsAlphaBlendEnabled(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva000E68C5SwayOffsets(ID3DXEffect *effect, D3DXHANDLE handle);
void Rva000E69E6BaseTexture(ID3DXEffect *effect, D3DXHANDLE handle);

// FX parameter binder base: vtable 0x00BC6F24 = { deleting dtor, __purecall }.
class Base
{
public:
	virtual ~Base() {}
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry) = 0;
};

class Rva000E6387 : public Base
{
public:
	virtual ~Rva000E6387();
	virtual void ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

Rva000E6387::~Rva000E6387()
{
	Rva001532E1Erase("Vegetation");
}

void Rva000E6387::ResolveBindings(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	Rva001530E9Path path;
	Rva001530E9Parse(name, &path);
	if (_strcmpi(path.m_name, "BaseTexture") == 0)
		registry->AddBinding(Rva000E69E6BaseTexture, handle);
	else if (_strcmpi(path.m_name, "IsAlphaBlendEnabled") == 0)
		registry->AddBinding(Rva000E6878IsAlphaBlendEnabled, handle);
	else if (_strcmpi(path.m_name, "SwayOffsets") == 0)
	{
		if (!path.m_hasBracket || path.m_index == 0)
			registry->AddBinding(Rva000E68C5SwayOffsets, handle);
	}
}

void Rva000E6878IsAlphaBlendEnabled(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E6AC0 *buffer = g_009EBC90;
	if (TheWritableGlobalData && buffer)
		effect->SetBool(handle, !TheWritableGlobalData->m_D45 && !buffer->slot04());
	else
		effect->SetBool(handle, TRUE);
}

void Rva000E68C5SwayOffsets(ID3DXEffect *effect, D3DXHANDLE handle)
{
	D3DXVECTOR4 sway[MAX_SWAY_TYPES + 1];
	memset(sway, 0, sizeof(sway));
	Rva000E6AC0 *buffer = g_009EBC90;
	if (buffer)
	{
		for (int i = 0; i < MAX_SWAY_TYPES; i++)
		{
			int minOffset = FloatToLong((float)floor(buffer->m_curSwayOffset[i]));
			if (minOffset >= 0 && minOffset + 1 < NUM_SWAY_ENTRIES)
			{
				float f2 = buffer->m_curSwayOffset[i] - minOffset;
				float f1 = 1.0f - f2;
				Vector3 swayFactor = f1 * buffer->m_swayOffsets[minOffset] + f2 * buffer->m_swayOffsets[minOffset + 1];
				float factor = buffer->m_curSwayFactor[i];
				sway[i + 1].x = swayFactor.X * factor;
				sway[i + 1].y = swayFactor.Y * factor;
				sway[i + 1].z = swayFactor.Z * factor;
			}
		}
	}
	effect->SetVectorArray(handle, sway, MAX_SWAY_TYPES + 1);
}

void Rva000E69E6BaseTexture(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E6AC0 *buffer = g_009EBC90;
	if (buffer && buffer->rva000E6AA4())
		effect->SetTexture(handle, buffer->rva000E6AA4().Peek_D3D_Base_Texture());
	else
		effect->SetTexture(handle, Rva00132E76WhiteTexture().Peek_D3D_Base_Texture());
}

RefCountPtr<TextureClass> Rva000E6AC0::rva000E6AA4()
{
	return m_38;
}
