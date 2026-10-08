// cl: /DNDEBUG /MD
// Effect-parameter callbacks of the BFME 2 terrain FX binding. Each is a
// cdecl (effect, handle) function whose address a name dispatcher stores
// for a shader parameter, and each ends in ID3DXEffect::SetVector (vtable
// slot 34, +0x88) with a four-float local. Target facts: the dispatcher at
// 0x000E25DE stores 0x004E2700 for "Offset" and 0x004E2763 for "Scale"; the
// other three are referenced the same way from 0x000E23CD, 0x000E2CE9 and
// 0x000E2D03. TheTerrainRenderObject is VA 0x00DE1EAC (W3DFloorDrawDtor.cpp)
// and g_00DFE1E4 is the object Rva0027070C.cpp guards with slot 15.
// Callback, map and field names are address-derived.
//
// ?Rva000E2409ScaleOffset@@YAXPAUID3DXEffect@@PBD@Z @0x000E2409 148B
// ?Rva000E2700Offset@@YAXPAUID3DXEffect@@PBD@Z      @0x000E2700  99B
// ?Rva000E2763Scale@@YAXPAUID3DXEffect@@PBD@Z       @0x000E2763 118B
// ?Rva000E2D26Vector@@YAXPAUID3DXEffect@@PBD@Z      @0x000E2D26 126B
// ?Rva000E2DA4Level@@YAXPAUID3DXEffect@@PBD@Z       @0x000E2DA4  89B
//
// The SetBool/SetInt/SetFloat callbacks below are named by the parameter
// string each dispatcher compares before storing the address (target fact):
// 0x000E1F42 stores 0x004E20DF for "IsMacroTextureStrechedToMapSize" and
// 0x004E213C for "IsResourceTextureEnabled"; 0x000E236D stores 0x004E249D
// for "ObjectShroudStatus"; 0x000E25DE stores 0x004E26CF for "IsEnabled";
// 0x000E2A81 stores 0x004E2BEE for "ScaleUV_OffsetPerSecondUV"; 0x000E2DFD
// stores 0x004E2F5E for "HeightScale". TheWritableGlobalData is VA
// 0x00DFE758 and TheWeatherSetting VA 0x00DFE118; the +0x3834/+0xC6A/+0xA4..
// field names are address-derived.

typedef const char *D3DXHANDLE;

struct Rva000E2409Vector4
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
	virtual long __stdcall SetBool(D3DXHANDLE parameter, int value); virtual void v23();
	virtual void v24(); virtual void v25();
	virtual long __stdcall SetInt(D3DXHANDLE parameter, int value); virtual void v27();
	virtual void v28(); virtual void v29(); virtual long __stdcall SetFloat(D3DXHANDLE parameter, float value); virtual void v31();
	virtual void v32(); virtual void v33();
	virtual long __stdcall SetVector(D3DXHANDLE parameter, const Rva000E2409Vector4 *vector);
};

struct Rva000E2409Map
{
	char m_pad00[0x10];
	float m_10;
	float m_14;
	char m_pad18[8];
	int m_20;
	int m_24;
	char m_pad28[4];
	float m_2c;
	float m_30;
	char m_pad34[0x44 - 0x34];
	int m_44;
};

class BaseHeightMapRenderObjClass
{
public:
	char m_pad0000[0x37C0];
	struct BfmeTerrain37C0Target *m_37C0;
	char m_pad37C4[0x3834 - 0x37C4];
	bool m_3834;
	char m_pad3835[0x3878 - 0x3835];
	Rva000E2409Map *m_3878;
	Rva000E2409Map *m_387c;
};

struct BfmeTerrain37C0Target
{
	char m_pad00[8];
	int m_08;
	int m_0C;
	int m_10;
};


extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

struct Rva000E2D26Vector3
{
	float x, y, z;
};

class Rva0027070CGlobal
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual bool slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual float slot4C();

	Rva000E2D26Vector3 get30() const { return m_30; }

	char m_pad04[0x2c];
	Rva000E2D26Vector3 m_30;
};

extern Rva0027070CGlobal *g_00DFE1E4;

void Rva000E2409ScaleOffset(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 1.0f;
	value.y = 1.0f;
	value.z = 0.0f;
	value.w = 0.0f;
	if (TheTerrainRenderObject)
	{
		Rva000E2409Map *map = TheTerrainRenderObject->m_3878;
		if (map)
		{
			value.x = 1.0f / ((float)map->m_20 * map->m_10);
			value.y = 1.0f / ((float)map->m_24 * map->m_14);
			value.z = map->m_10 - map->m_2c;
			value.w = map->m_14 - map->m_30;
		}
	}
	effect->SetVector(handle, &value);
}

void Rva000E2700Offset(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 0.0f;
	value.y = 0.0f;
	value.z = 0.0f;
	value.w = 0.0f;
	if (TheTerrainRenderObject)
	{
		Rva000E2409Map *map = TheTerrainRenderObject->m_387c;
		if (map)
		{
			value.x = map->m_10 - map->m_2c;
			value.y = map->m_14 - map->m_30;
		}
	}
	effect->SetVector(handle, &value);
}

void Rva000E2763Scale(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 1.0f;
	value.y = 1.0f;
	value.z = 0.0f;
	value.w = 0.0f;
	if (TheTerrainRenderObject)
	{
		Rva000E2409Map *map = TheTerrainRenderObject->m_387c;
		if (map)
		{
			value.x = 1.0f / ((float)map->m_20 * map->m_10);
			value.y = 1.0f / ((float)map->m_24 * map->m_14);
		}
	}
	effect->SetVector(handle, &value);
}

void Rva000E2D26Vector(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 1.0f;
	value.y = 1.0f;
	value.z = 1.0f;
	value.w = 0.0f;
	if (g_00DFE1E4 && g_00DFE1E4->slot3C())
	{
		Rva000E2D26Vector3 v = g_00DFE1E4->get30();
		value.x = v.x;
		value.y = v.y;
		value.z = v.z;
	}
	effect->SetVector(handle, &value);
}

void Rva000E2DA4Level(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 0.0f;
	value.y = 0.0f;
	value.z = 0.0f;
	value.w = 0.0f;
	if (g_00DFE1E4 && g_00DFE1E4->slot3C())
	{
		float level = g_00DFE1E4->slot4C();
		value.x = level;
		value.y = level;
		value.z = level;
	}
	effect->SetVector(handle, &value);
}

void Rva000E2F24(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	float s = 1e+01f;
	value.x = s;
	value.y = s;
	value.z = 0.0f;
	value.w = 0.0f;
	effect->SetVector(handle, &value);
}

void Rva000E2F77(ID3DXEffect *effect, D3DXHANDLE handle)
{
	float v = 0.0f;
	if (TheTerrainRenderObject)
	{
		BfmeTerrain37C0Target *t = TheTerrainRenderObject->m_37C0;
		if (t)
		{
			v = (float)t->m_10 * 1e+01f;
		}
	}
	effect->SetFloat(handle, v);
}

void Rva000E2EB7(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 0.0f;
	value.y = 0.0f;
	value.z = 0.0f;
	value.w = 0.0f;
	if (TheTerrainRenderObject && TheTerrainRenderObject->m_37C0)
	{
		value.x = (float)TheTerrainRenderObject->m_37C0->m_08 * 1e+01f;
		value.y = (float)TheTerrainRenderObject->m_37C0->m_0C * 1e+01f;
	}
	effect->SetVector(handle, &value);
}

class GlobalData
{
public:
	char m_pad000[0xC6A];
	bool m_C6A;
};

extern GlobalData *TheWritableGlobalData;

class WeatherSetting
{
public:
	char m_pad00[0xA4];
	float m_a4;
	float m_a8;
	float m_ac;
	float m_b0;
};

template <class T> class OVERRIDE
{
public:
	const T *operator->() const;

private:
	const T *m_overridable;
};

extern OVERRIDE<WeatherSetting> TheWeatherSetting;

void Rva000E20DFIsMacroTextureStrechedToMapSize(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheTerrainRenderObject)
		effect->SetBool(handle, TheTerrainRenderObject->m_3834);
	else
		effect->SetBool(handle, 0);
}

void Rva000E213CIsResourceTextureEnabled(ID3DXEffect *effect, D3DXHANDLE handle)
{
	effect->SetBool(handle, 0);
}

void Rva000E249DObjectShroudStatus(ID3DXEffect *effect, D3DXHANDLE handle)
{
	int status = 0;
	if (TheTerrainRenderObject)
	{
		Rva000E2409Map *map = TheTerrainRenderObject->m_3878;
		if (map)
			status = map->m_44;
	}
	effect->SetInt(handle, status);
}

void Rva000E26CFIsEnabled(ID3DXEffect *effect, D3DXHANDLE handle)
{
	if (TheWritableGlobalData)
		effect->SetBool(handle, TheWritableGlobalData->m_C6A);
	else
		effect->SetBool(handle, 0);
}

void Rva000E2BEEScaleUVOffsetPerSecondUV(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 0.0015151515f;
	value.y = 0.0015151515f;
	value.z = -0.012f;
	value.w = -0.018f;
	if (TheWeatherSetting.operator->())
	{
		value.x = 1.0f / TheWeatherSetting->m_a4;
		value.y = 1.0f / TheWeatherSetting->m_a8;
		value.z = TheWeatherSetting->m_ac;
		value.w = TheWeatherSetting->m_b0;
	}
	effect->SetVector(handle, &value);
}

void Rva000E2F5EHeightScale(ID3DXEffect *effect, D3DXHANDLE handle)
{
	effect->SetFloat(handle, 0.0390625f);
}

// ?rva000E2DFD@Rva000E2DFD@@QAEXPBD0PAVFXShaderParameterBinder@@@Z @0x000E2DFD 186B
// Terrain FX four-name ResolveBindings dispatcher (Size, CellSize,
// HeightScale, BorderWidth), same WaterDraw member pattern as the rowed
// particle dispatcher Rva001F69B1 and the Rva000E236D terrain twin: base call,
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

// Retail loads the msvcr71.dll _strcmpi import from IAT slot 0x00BBA518.
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

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

typedef void (*Rva000E2DFDCallback)(ID3DXEffect *effect, D3DXHANDLE handle);

class Rva000E2DFD : public FXShaderParameterSourceNamespace_Struct
{
public:
	void rva000E2DFD(const char *name, const char *handle, FXShaderParameterBinder *registry);
};

void Rva000E2EB7(ID3DXEffect *effect, const char *name);
void Rva000E2F24(ID3DXEffect *effect, const char *name);
void Rva000E2F5EHeightScale(ID3DXEffect *effect, const char *name);
void Rva000E2F77(ID3DXEffect *effect, const char *name);

void Rva000E2DFD::rva000E2DFD(const char *name, const char *handle, FXShaderParameterBinder *registry)
{
	FXShaderParameterSourceNamespace_Struct::ResolveBindings(name, handle, registry);
	if (name)
	{
		Rva001530E9Path path;
		Rva001530E9Parse(name, &path);
		int (__cdecl *compare)(const char *, const char *) = _strcmpi;
		if (compare(path.m_name, "Size") == 0)
			registry->AddBinding(Rva000E2EB7, handle);
		else if (compare(path.m_name, "CellSize") == 0)
			registry->AddBinding(Rva000E2F24, handle);
		else if (compare(path.m_name, "HeightScale") == 0)
			registry->AddBinding(Rva000E2F5EHeightScale, handle);
		else if (compare(path.m_name, "BorderWidth") == 0)
			registry->AddBinding(Rva000E2F77, handle);
	}
}
