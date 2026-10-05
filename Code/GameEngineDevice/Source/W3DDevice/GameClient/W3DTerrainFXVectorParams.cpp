// cl: /O1 /DNDEBUG /MD /arch:SSE
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
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
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
};

class BaseHeightMapRenderObjClass
{
public:
	char m_pad0000[0x37C0];
	struct BfmeTerrain37C0Target *m_37C0;
	char m_pad37C4[0x3878 - 0x37C4];
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

extern float BfmeGlobalBC2428;

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
	float s = BfmeGlobalBC2428;
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
			v = (float)t->m_10 * BfmeGlobalBC2428;
		}
	}
	effect->SetFloat(handle, v);
}

// ?Rva000E2EB7@@YAXPAUID3DXEffect@@PBD@Z present-unmatched
void Rva000E2EB7(ID3DXEffect *effect, D3DXHANDLE handle)
{
	Rva000E2409Vector4 value;
	value.x = 0.0f;
	value.y = 0.0f;
	value.z = 0.0f;
	value.w = 0.0f;
	if (TheTerrainRenderObject)
	{
		if (*(BfmeTerrain37C0Target **)((char *)TheTerrainRenderObject + 0x37C0))
		{
			BfmeTerrain37C0Target *t = *(BfmeTerrain37C0Target **)((char *)TheTerrainRenderObject + 0x37C0);
			value.x = (float)t->m_08 * BfmeGlobalBC2428;
			value.y = (float)t->m_0C * BfmeGlobalBC2428;
		}
	}
	effect->SetVector(handle, &value);
}
