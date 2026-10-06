// ?rva00913AF0@PointGroupClass@@QAEXH_N@Z
// partial score=1.0 date=2026-10-06
// ?rva00913AF0@PointGroupClass@@QAEXH_N@Z
// partial score=1.0 date=2026-10-06
// Full body byte-exact; integration still blocked, so this is not progress.
// link_check --new-variants rejects new Set_Shader and Set_Transform COMDAT
// copies. The sorting Insert provider at 0x0012FE00 is now recovered in
// SortingRendererBFME1.cpp; the remaining blocker is COMDAT reconciliation.
// cl: /DBFME_WWSTRING_CTOR_BUFFER_RELOAD /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/banked_segline /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// PointGroup vertex-buffer submission, retail RVA 0x00179B50, 3377 bytes.
// Ported from Open-BFME-1 PointGroupClassSubmit.cpp at 6583b3c1ff;
// resumed bank from 2026-10-05. The donor provides the submission semantics
// and address-derived method name. BFME2 Render's call at RVA 0x0017F6C6
// proves this helper's receiver and two arguments independently.
// Target accesses prove the 24-byte VB access, 12-byte write lock and FVF
// offsets below. Ghidra's 3371-byte extent omits the final six-byte epilogue;
// retail ends at 0x0017A881, before padding to the next entry at 0x0017A890.
// BFME_WWSTRING_CTOR_BUFFER_RELOAD reproduces the target's inlined snapshot
// string constructor at 0x0017A025. Full body and relocations are verified.
#define Matrix4x4 Matrix4
#include "pointgr.h"
#include "vector.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "ww3d.h"
#include "texture.h"
#include "vertmaterial.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"

extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector2> VertexUV;
extern VectorClass<Vector4> VertexDiffuse;
extern DX8IndexBufferClass *Tris;
extern DX8IndexBufferClass *Quads;
extern SortingIndexBufferClass *SortingTris;
extern SortingIndexBufferClass *SortingQuads;
// Retail's second sorting flag at VA 0x00DB5F7D is owned by
// GlobalByteGetters.cpp; reuse that definition instead of the donor's name.
extern unsigned char g_Va00DB5F7D;

// BFME2's FVF record: the stride, location, first texture-coordinate and
// diffuse offsets read here sit at +0x0C/+0x10/+0x24/+0x44 (retail 0x0017A2C5..
// 0x0017A2CE; Line3DClassRender.cpp reads the same stride/location/diffuse).
class PointGroupTargetFVF {
	char beforeStride[12];
	unsigned stride;
	unsigned location;
	char beforeTex[0x24 - 0x14];
	unsigned tex0;
	char beforeDiffuse[0x44 - 0x28];
	unsigned diffuse;

public:
	unsigned Get_FVF_Size() const { return stride; }
	unsigned Get_Location_Offset() const { return location; }
	unsigned Get_Tex_Offset(unsigned) const { return tex0; }
	unsigned Get_Diffuse_Offset() const { return diffuse; }
};

struct BfmeSortingVBAccess {
	const PointGroupTargetFVF &FVFInfo;
	unsigned Type;
	unsigned formatIndex;
	unsigned unused_0x0C;
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	class BoxVertexBufferClass *VertexBuffer;

	BfmeSortingVBAccess(unsigned type, unsigned format_index,
		unsigned short vertex_count, unsigned buffer);
	~BfmeSortingVBAccess();

	const PointGroupTargetFVF &FVF_Info() const { return FVFInfo; }

	class WriteLock {
		BfmeSortingVBAccess *DynamicVBAccess;
		VertexFormatXYZNDUV2 *Vertices;
		unsigned char targetDeviceGuard[4];

	public:
		WriteLock(BfmeSortingVBAccess *vb_access);
		~WriteLock();
		VertexFormatXYZNDUV2 *Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

extern void BoxSetTexture(unsigned stage, TextureBaseClass *&texture);

// Retail 0x0012FE00 takes an xyz center and four 32-bit ranges (the view
// DX8DrawTrianglesDispatch.cpp pins).
struct TargetCenter3 { float x, y, z; TargetCenter3(float a,float b,float c):x(a),y(b),z(c){} };
class BfmeSortingDispatchAt0012FE00 {
public:
	static void Insert(const TargetCenter3& center, unsigned start,
		unsigned polygons, unsigned minimum, unsigned vertices);
};

static __forceinline void InsertPointTriangles(
	unsigned a, unsigned b, unsigned c, unsigned d)
{
	TargetCenter3 center(0.0f, 0.0f, 0.0f);
	BfmeSortingDispatchAt0012FE00::Insert(center, a, b, c, d);
}

static __forceinline void ClampPointColor(Vector4 &color)
{
	if (!CPUDetectClass::Has_CMOV_Instruction()) {
		color.X = color.X <= 0.0f ? 0.0f : (color.X > 1.0f ? 1.0f : color.X);
		color.Y = color.Y <= 0.0f ? 0.0f : (color.Y > 1.0f ? 1.0f : color.Y);
		color.Z = color.Z <= 0.0f ? 0.0f : (color.Z > 1.0f ? 1.0f : color.Z);
		color.W = color.W <= 0.0f ? 0.0f : (color.W > 1.0f ? 1.0f : color.W);
		return;
	}

	// Retain the donor's bounded 94-byte CMOV implementation: VC7.1 emits
	// branches for the equivalent integer clamp expressions. The independently
	// matched BFME1 Clamp_Color at 0x0090F310 and its point-submit evidence
	// establish this codegen blocker; the surrounding algorithm is C++.
	__asm
	{
		mov esi, dword ptr color
		mov edx, 0x3f800000

		mov edi, dword ptr [esi]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi], edi

		mov edi, dword ptr [esi+4]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+4], edi

		mov edi, dword ptr [esi+8]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+8], edi

		mov edi, dword ptr [esi+12]
		mov ebx, edi
		sar edi, 31
		not edi
		and edi, ebx
		cmp edi, edx
		cmovnb edi, edx
		mov dword ptr [esi+12], edi
	}
}

static __forceinline unsigned ConvertPointColor(Vector4 clamped_color)
{
	ClampPointColor(clamped_color);
	return DX8Wrapper::Convert_Color(
		reinterpret_cast<const Vector3 &>(clamped_color), clamped_color[3]);
}

static __forceinline unsigned ConvertDefaultPointColor(Vector4 color)
{
	ClampPointColor(color);
	return DX8Wrapper::Convert_Color(reinterpret_cast<const Vector3 &>(color), color.W);
}

void PointGroupClass::rva00913AF0(int vnum, bool no_diffuse)
{
	Matrix4 world, view;
	DX8Wrapper::Get_Transform(D3DTS_WORLD, world);
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);
	Matrix4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, identity);
	DX8Wrapper::Set_Transform(D3DTS_VIEW, identity);
	DX8Wrapper::Set_Material(PointMaterial);
	DX8Wrapper::Set_Shader(Shader);
	BoxSetTexture(0, reinterpret_cast<TextureBaseClass *&>(Texture));
	const bool sort = (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO)
		&& (Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE)
		&& WW3D::Is_Sorting_Enabled() && g_Va00DB5F7D;
	IndexBufferClass *indexbuffer;
	int verticesperprimitive;
	if (PointMode == QUADS) {
		verticesperprimitive = 2;
		indexbuffer = sort ? static_cast<IndexBufferClass *>(SortingQuads)
			: static_cast<IndexBufferClass *>(Quads);
	} else {
		verticesperprimitive = 3;
		indexbuffer = sort ? static_cast<IndexBufferClass *>(SortingTris)
			: static_cast<IndexBufferClass *>(Tris);
	}
	unsigned default_color = ConvertDefaultPointColor(Vector4(
		DefaultPointColor.X, DefaultPointColor.Y, DefaultPointColor.Z, DefaultPointAlpha));
	int current = 0;
	while (current < vnum) {
		int delta = MIN(vnum - current, 2048);
		BfmeSortingVBAccess PointVerts(
			sort ? BUFFER_TYPE_DYNAMIC_SORTING : BUFFER_TYPE_DYNAMIC_DX8, 5, delta, 0);
		{
			BfmeSortingVBAccess::WriteLock Lock(&PointVerts);
			unsigned char *vb = (unsigned char *)Lock.Get_Formatted_Vertex_Array();
			const PointGroupTargetFVF &fvfinfo = PointVerts.FVF_Info();
			unsigned stride = fvfinfo.Get_FVF_Size();
			unsigned char *position = vb + fvfinfo.Get_Location_Offset();
			unsigned char *uv = vb + fvfinfo.Get_Tex_Offset(0);
			unsigned char *color = vb + fvfinfo.Get_Diffuse_Offset();
			if (no_diffuse) {
				for (int i = current; i < current + delta; i++) {
					*(Vector3 *)position = VertexLoc[i];
					*(Vector2 *)uv = VertexUV[i];
					*(unsigned *)color = default_color;
					position += stride;
					uv += stride;
					color += stride;
				}
			} else {
				for (int i = current; i < current + delta; i++) {
					*(Vector3 *)position = VertexLoc[i];
					*(Vector2 *)uv = VertexUV[i];
					*(unsigned *)color = ConvertPointColor(VertexDiffuse[i]);
					position += stride;
					uv += stride;
					color += stride;
				}
			}
		}
		DX8Wrapper::Set_Index_Buffer(indexbuffer, 0);
		DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass *>(&PointVerts));
		if (sort) {
			InsertPointTriangles(0, delta / verticesperprimitive, 0, delta);
		} else {
			DX8Wrapper::Draw_Triangles(0, delta / verticesperprimitive, 0, delta);
		}
		current += delta;
	}
	DX8Wrapper::Set_Transform(D3DTS_VIEW, view);
	DX8Wrapper::Set_Transform(D3DTS_WORLD, world);
}
