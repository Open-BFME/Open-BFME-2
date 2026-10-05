// ?rva0008E335@TerrainTracksRenderObjClass@@QAEHH@Z
// partial score=0.97 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmeterraintracks /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// ?rva0008E1F2@TerrainTracksRenderObjClass@@QAEHXZ 0x0008E1F2 323B
// BFME2 byte-exact reconstruction. Chain from ?freeTerrainTracksResources 0x0008E187 which this
// calls first after setting the dirty flag byte at 0x009E207C. Builds the four DX8 resources at
// the free layout (index buffer +0xD4 via DX8IndexBuffer count m_count*3 usage 0 with a sequential
// 0..59 WriteLock fill; vertex buffers +0xE0 count m_count*3 and +0xE4 count 6 via
// BfmeDynamicNativeVB FVF 0x142; material +0xDC via VertexMaterial Get_Preset PRELIT_DIFFUSE;
// shader dword 0x1198B7 at +0xD8; count 0x14 at +0xC4) and returns 0. Called once from Render
// 0x0008E7A4 slot 12 of 0x007C7850 when +0xD4 is null with the same this which proves the
// TerrainTracksRenderObjClass owner. /O1 for xor-first push-pop EBP shape with /G7 for the
// word-load imul ax form of the ushort vertex counts.
typedef int Int;
typedef unsigned int Uint;
typedef unsigned short UShort;
typedef unsigned char Bool;
void *__cdecl operator new(Uint s);
void __cdecl operator delete(void *p);
class RefCountClass
{
public:
	virtual void Delete_This() {}
	void Release_Ref()
	{
		if (--m_refs == 0)
			Delete_This();
	}
	int m_refs;
};
class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock();
	~BFMEDX8DeviceLock();
};
class IndexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(IndexBufferClass *b, int flags);
		~WriteLockClass();
		UShort *Get_Index_Array() { return m_indices; }
	private:
		IndexBufferClass *m_buf;
		UShort *m_indices;
		BFMEDX8DeviceLock m_lock;
	};
};
class DX8IndexBufferClass : public RefCountClass
{
public:
	enum UsageType { USAGE_DEFAULT = 0 };
	DX8IndexBufferClass(Uint count, UsageType u);
private:
	char _t[0x10];
};
class BfmeDynamicNativeVB : public RefCountClass
{
public:
	BfmeDynamicNativeVB(Uint a, UShort b, Uint c, Uint d);
private:
	char _t[0x18];
};
class VertexMaterialClass : public RefCountClass
{
public:
	enum PresetType { PRELIT_DIFFUSE = 0 };
	static VertexMaterialClass *Get_Preset(PresetType t);
};
extern Bool g_trackDirty;
// g_trackDirty: matched references place it at VA 0xde207c (zero-filled .bss).
unsigned char g_trackDirty;
class TerrainTracksRenderObjClass
{
public:
	int rva0008E1F2();
	int freeTerrainTracksResources();
	int rva0008E335(int color);
private:
	char _padC0[0xC4];
	int m_count;
	char _padC8[12];
	RefCountClass *m_indexBuffer;
	unsigned int m_shader;
	RefCountClass *m_material;
	RefCountClass *m_vb1;
	RefCountClass *m_vb2;
};
int TerrainTracksRenderObjClass::rva0008E1F2()
{
	g_trackDirty = true;
	freeTerrainTracksResources();
	m_count = 0x14;
	m_indexBuffer = new DX8IndexBufferClass(m_count * 3, DX8IndexBufferClass::USAGE_DEFAULT);
	{
		IndexBufferClass::WriteLockClass lock((IndexBufferClass *)m_indexBuffer, 0);
		UShort *dst = lock.Get_Index_Array();
		for (int i = 0; i < m_count * 3; i += 3)
		{
			dst[0] = (UShort)i;
			dst[1] = (UShort)(i + 1);
			dst[2] = (UShort)(i + 2);
			dst += 3;
		}
		m_vb1 = new BfmeDynamicNativeVB(0x142, (UShort)(m_count * 3), 0, 0);
		m_vb2 = new BfmeDynamicNativeVB(0x142, 6, 0, 0);
		m_material = (RefCountClass *)VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		m_shader = 0x1198B7;
	}
	return 0;
}

// Retail 0x0008E335 (257 B): fills the 6-vertex status-circle VB at +0xE4
// (two triangles of a quad) with alternating corner positions from the shared
// float pair and the caller's diffuse color, then clears the status-circle
// dirty flag. Caller 0x0008E7A4 (Render) proves the
// TerrainTracksRenderObjClass owner; the +0xE4 null check returns -1.
// ?rva0008E335@TerrainTracksRenderObjClass@@QAEHH@Z present-unmatched
class W3DStatusCircle
{
public:
	static Bool m_needUpdate;
};

#pragma comment(linker, "/alternatename:?m_needUpdate@W3DStatusCircle@@1_NA=?g_trackDirty@@3EA")

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *b, int flags);
		~WriteLockClass();
		VertexBufferClass *m_buf;
		void *Vertices;
		char m_lock;
	};
};

struct StatusVert
{
	float x, y, z;
	unsigned int color;
	float u, v;
};

extern float g_00BBB9AC;
extern float g_Va00BBB8D8;

int TerrainTracksRenderObjClass::rva0008E335(int color)
{
	VertexBufferClass *vb = (VertexBufferClass *)m_vb2;
	if (vb != 0)
	{
		W3DStatusCircle::m_needUpdate = false;
		VertexBufferClass::WriteLockClass lock(vb, 0);
		StatusVert *v = (StatusVert *)lock.Vertices;
		unsigned c = color;
		float a = g_00BBB9AC;
		v->color = c;
		float b = g_Va00BBB8D8;
		v->x = a; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = a; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = a; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = a; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f; ++v;
		v->color = color; v->x = b; v->y = b; v->z = 0.0f; v->u = 0.0f; v->v = 0.0f;
		return 0;
	}
	return -1;
}
