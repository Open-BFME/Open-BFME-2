// cl: /O2 /arch:SSE /G7 /DNDEBUG /MD /GX- /Oy-
//
// ?read_vertex_colors@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z,
// retail 0x00188760 (392 bytes, Ghidra FUN_00588760 389B truncated omits final ret8; retail full 392 incl ret8; next body 0x001888F0).
// BFME1 MeshModelVertexColors.cpp read_vertex_colors (their 373B at
// 0x0096D140) port with BFME2 rewrites (all retail-measured from the
// 0x00188760 body):
// - bool (AL) returns, not WW3DErrorType; ret8 ABI; false arm returns 0.
// - Guard on CurMatDesc (+0x94) ColorArray[0] at matdesc+0x50 (the +0x50
//   anchor is retail-proven by matched Get_Color_Array 0xD1FBD's TU view;
//   donor checks Has_Color_Array(0), same cmp shape as ReadDcg/ReadDig).
// - Per-vertex 4-byte Read via matched ChunkLoadClass::Read 0x6151A0 with the
//   donor's checked-size early-false return (ReadDig arm1 ignores the
//   return; the check here follows the donor and the retail jne fail arm).
// - R/G/B unpack through call-free SSE (cvtsi2ss times the shared 1/255
//   constant, W = 1.0f) exactly like landed ReadDig arm1; the donor's
//   `/ 255.0f` spelling would emit divss, so the ReadDig `* (1/255)`
//   product form is used (retail mulss).
// - The pack is the ZH (Vector3, float) Convert_Color with its hand-written
//   fstcw/chop/fistp asm spliced inline, shared verbatim with the landed
//   ReadDcg/ReadDig TUs (sub esp,20 frame, 255.0f scale, 1.0f alpha).
// - DCGSource lives at matdesc+0x58; COLOR1 == 1 stored by direct member
//   write (same tail as read_dcg/read_dig).
// - W3dRGBStruct is 4 bytes (R,G,B,pad) per the genuine w3d_file.h shape
//   ("padded to an even 4 bytes"), so sizeof(color) == 4 matches the retail
//   push 4; the pad byte is unread, as retail only samples AL/AH/[ebp-2].
// Dedicated TU: mirrors the landed ReadDcg/ReadDig precedent. Get_Color_Array
// resolves via matched row 0xD1FBD; Read via matched row 0x6151A0. No new pins,
// no shared-header edits, no mask-green or alternatename as proof.

#ifndef NULL
#define NULL 0
#endif

#define WWINLINE __forceinline

typedef unsigned int uint32;
typedef unsigned char uint8;

struct W3dRGBStruct
{
	uint8 R;
	uint8 G;
	uint8 B;
	uint8 pad;
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

	WWINLINE Vector4(void) {};
	WWINLINE Vector4(const Vector4 & v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	WWINLINE Vector4 & operator = (const Vector4 & v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	WWINLINE void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	WWINLINE float & operator [](int i) { return (&X)[i]; }
	WWINLINE const float & operator [](int i) const { return (&X)[i]; }
};

class DX8Wrapper
{
public:
	static Vector4 Convert_Color(unsigned color);
	static unsigned int Convert_Color(const Vector3 &color, const float alpha);
	static unsigned int Convert_Color(const Vector4 &color);
};

// ?DX8Wrapper::Convert_Color present-unmatched
WWINLINE Vector4 DX8Wrapper::Convert_Color(unsigned color)
{
	Vector4 col;
	col[3] = ((color & 0xff000000) >> 24) / 255.0f;
	col[0] = ((color & 0xff0000) >> 16) / 255.0f;
	col[1] = ((color & 0xff00) >> 8) / 255.0f;
	col[2] = ((color & 0xff) >> 0) / 255.0f;
	return col;
}

// ?DX8Wrapper::Convert_Color present-unmatched
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector3 &color, const float alpha)
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
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector4 &color)
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
};

class MeshModelClass
{
protected:
	bool read_vertex_colors(ChunkLoadClass &cload, MeshLoadContextClass *context);

private:
	char m_pad0[0x28];

public:
	int VertexCount;

private:
	char m_pad1[0x94 - 0x2C];

public:
	MeshMatDescClass *CurMatDesc;
};

// ?read_vertex_colors@MeshModelClass@@IAE_NAAVChunkLoadClass@@PAVMeshLoadContextClass@@@Z
bool MeshModelClass::read_vertex_colors(ChunkLoadClass &cload, MeshLoadContextClass *context)
{
	if (CurMatDesc->ColorArray[0] == NULL) {
		W3dRGBStruct color;
		unsigned *dcg = CurMatDesc->Get_Color_Array(0);
		for (int i = 0; i < VertexCount; i++) {
			if (cload.Read(&color, sizeof(color)) != sizeof(color)) {
				return false;
			}
			Vector4 col;
			col.X = (float)color.R * (1.0f / 255.0f);
			col.Y = (float)color.G * (1.0f / 255.0f);
			col.Z = (float)color.B * (1.0f / 255.0f);
			col.W = 1.0f;
			dcg[i] = DX8Wrapper::Convert_Color(col);
		}
	}
	CurMatDesc->DCGSource[context->CurPass] = VertexMaterialClass::COLOR1;
	return true;
}
