// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /GX- /Oy-
// platformsdk
//
// ?read_dcg@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x00188BB0 (562 bytes).
// BFME1 MeshModelVertexColors.cpp read_dcg port with BFME2 rewrites (all
// retail-measured from the 0x00188BB0 body):
// - bool (AL) returns, not WW3DErrorType.
// - First arm (no color array yet): single bulk Read of VertexCount*4 bytes
//   straight into the array, then an in-place R<->B byte-swap loop.
// - Second arm (array present, PrelitChunkID == PRELIT_VERTEX): per-vertex
//   4-byte Read; the packed color decomposes through the ZH unsigned
//   Convert_Color inline (x87 fild batch), alpha comes from the fresh byte
//   via SSE, and the pack is the ZH (Vector3, float) Convert_Color with its
//   hand-written fstcw/chop/fistp asm spliced inline (sub esp,20 frame,
//   255.0f scale hoisted to the loop preheader).
// - DCGSource lives at matdesc+0x58 (MATERIAL == 0 selects DefMatDesc,
//   else context AlternateMatDesc at +0x124); the array pointer at
//   matdesc+0x50; COLOR1 == 1 is stored back by an inlined Set.
// Dedicated TU: the enum-typed meshmdlio.cpp cannot take rows (PostProcess
// precedent). Get_Color_Array and Read resolve via matched rows.

#include <windows.h>

#define WWINLINE __forceinline

typedef unsigned int uint32;
typedef unsigned char uint8;

struct W3dRGBAStruct
{
	uint8 R;
	uint8 G;
	uint8 B;
	uint8 A;
};

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	WWINLINE float & operator [](int i) { return (&X)[i]; }
	WWINLINE const float & operator [](int i) const { return (&X)[i]; }
};

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;

	__declspec(dllimport) __forceinline Vector4(void) {};
	__declspec(dllimport) __forceinline Vector4(const Vector4 & v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	__declspec(dllimport) __forceinline Vector4 & operator = (const Vector4 & v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__declspec(dllimport) __forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	__declspec(dllimport) __forceinline float & operator [](int i) { return (&X)[i]; }
	__declspec(dllimport) __forceinline const float & operator [](int i) const { return (&X)[i]; }
};

class DX8Wrapper
{
public:
	__declspec(dllimport) static Vector4 Convert_Color(unsigned color);
	__declspec(dllimport) static unsigned int Convert_Color(const Vector3 &color, const float alpha);
	__declspec(dllimport) static unsigned int Convert_Color(const Vector4 &color);
};

// ?DX8Wrapper::Convert_Color present-unmatched
__declspec(dllimport) __forceinline Vector4 DX8Wrapper::Convert_Color(unsigned color)
{
	Vector4 col;
	col[3] = ((color & 0xff000000) >> 24) / 255.0f;
	col[0] = ((color & 0xff0000) >> 16) / 255.0f;
	col[1] = ((color & 0xff00) >> 8) / 255.0f;
	col[2] = ((color & 0xff) >> 0) / 255.0f;
	return col;
}

// ?DX8Wrapper::Convert_Color present-unmatched
__declspec(dllimport) __forceinline unsigned int DX8Wrapper::Convert_Color(const Vector3 &color, const float alpha)
{
	const float scale = 255.0f;
	unsigned int col = 0;

	__asm
	{
		sub esp,20

		fwait
		fstcw [esp+16]
		mov eax,[esp+16]
		mov edi,eax
		and eax,~(1024|2048)
		or eax,(1024|2048)
		sub edi,eax
		jz skip
		mov [esp],eax
		fldcw [esp]
skip:

		mov esi,dword ptr color
		fld dword ptr[scale]

		fld dword ptr[esi]
		fld dword ptr[esi+4]
		fld dword ptr[esi+8]
		fld dword ptr[alpha]
		fld st(4)
		fmul st(4),st
		fmul st(3),st
		fmul st(2),st
		fmulp st(1),st
		fistp dword ptr[esp+0]
		fistp dword ptr[esp+4]
		fistp dword ptr[esp+8]
		fistp dword ptr[esp+12]
		mov ecx,[esp]
		mov eax,[esp+4]
		mov edx,[esp+8]
		mov ebx,[esp+12]
		shl ecx,24
		shl ebx,16
		shl edx,8
		or eax,ecx
		or eax,ebx
		or eax,edx

		fstp st(0)

		cmp edi,0
		je not_changed
		fwait
		fldcw [esp+16]
not_changed:
		add esp,20

		mov col,eax
	}
	return col;
}

// ?DX8Wrapper::Convert_Color present-unmatched
__declspec(dllimport) __forceinline unsigned int DX8Wrapper::Convert_Color(const Vector4 &color)
{
	return Convert_Color(reinterpret_cast<const Vector3 &>(color), color[3]);
}

class VertexMaterialClass
{
public:
	enum ColorSourceType
	{
		MATERIAL = 0,
		COLOR1
	};
};

class ChunkLoadClass
{
public:
	unsigned long Read(void *dst, unsigned long size);
	unsigned long Cur_Chunk_Length();
	unsigned long Cur_Chunk_ID();
	bool Open_Chunk();
	bool Close_Chunk();
	unsigned long Seek(unsigned long pos);
};

class MeshMatDescClass
{
public:
	unsigned *Get_Color_Array(int array, bool create = true);

private:
	char m_pad0[0x50];

public:
	void *ColorArray[2];
	int DCGSource[4];
};

class MeshLoadContextClass
{
private:
	char m_pad0[0x88];

public:
	uint32 PrelitChunkID;
	int CurPass;

private:
	char m_pad1[0x124 - 0x90];

public:
	MeshMatDescClass AlternateMatDesc;
};

class MeshModelClass
{
protected:
	bool read_dcg(ChunkLoadClass &cload, MeshLoadContextClass *context);

private:
	char m_pad0[0x28];

public:
	int VertexCount;

private:
	char m_pad1[0x8C - 0x2C];

public:
	MeshMatDescClass *DefMatDesc;
};

enum
{
	W3D_CHUNK_PRELIT_VERTEX = 0x24
};

// ?read_dcg@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_dcg(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	MeshMatDescClass *matdesc = DefMatDesc;
	if (DefMatDesc->DCGSource[context->CurPass] != VertexMaterialClass::MATERIAL) {
		matdesc = &context->AlternateMatDesc;
	}

	if (matdesc->ColorArray[0] == NULL) {
		unsigned *dcg = matdesc->Get_Color_Array(0);
		cload.Read(dcg, VertexCount * 2 * 2);
		for (int i = 0; i < VertexCount; i++) {
			unsigned c = dcg[i];
			unsigned lo = (c >> 16) & 0xFF;
			unsigned hi = (c & 0xFF) << 16;
			dcg[i] = lo | hi | (c & 0xFF00FF00);
		}
	} else if (context->PrelitChunkID == W3D_CHUNK_PRELIT_VERTEX) {
		W3dRGBAStruct color;
		unsigned *dcg = matdesc->Get_Color_Array(0);
		for (int i = 0; i < VertexCount; i++) {
			cload.Read(&color, sizeof(color));
			Vector4 col;
			col = DX8Wrapper::Convert_Color(dcg[i]);
			col.W = (float)color.A / 255.0f;
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}

	matdesc->DCGSource[context->CurPass] = VertexMaterialClass::COLOR1;
	return true;
}
