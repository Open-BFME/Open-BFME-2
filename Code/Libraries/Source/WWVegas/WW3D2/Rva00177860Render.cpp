// cl: /O1 /arch:SSE /G7 /DBFME_WWSTRING_CTOR_BUFFER_RELOAD /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/banked_segline /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// platformsdk
// dxsdk
// Rva00177860::rva00177F82: the renderer of the four-buffer point batch whose
// constructor (0x00177825) and destructor (0x00177860) are rowed in
// Rva00177860Dtor.cpp. Target evidence: native body 0x00177F82..0x00178E47
// (3781 B, thiscall, RET 4) and its retail callees. Structure carried from
// ZH PointGroupClass::Render's vertex fill (512-point
// chunks of four vertices, sorting or DX8 submission). Structural inference:
// the TU's out-of-line helpers at 0x00177ACB..0x00177F34 sit in this body's
// usage order (colour pack, vec3 copy, colour convert, strided fill, normal
// fill, UV step, pair copy, UV fill); retail inlines them here, so they are
// written as __forceinline helpers (cl 7.1 /O1 does not inline them otherwise).
// The original class, method and helper names are unknown.
// The donor WW3D2 headers spell the 4x4 matrix Matrix4x4.
#define Matrix4x4 Matrix4
// Keep retail helper calls available without emitting non-retail SSE copies.
#include "../../../../../reference/shims/bfme_matrix3d_sse_link/vector4.h"
#define BFME_POINT_MATRIX4_TRANSFORM_INLINE
#include "sharebuf.h"
#include "vector.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "ww3d.h"
#include "texture.h"
#include "vertmaterial.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "sortingrenderer.h"

class Rva00177860Ref;
extern Rva00177860Ref *Rva009F7044;
extern Rva00177860Ref *Rva009F7048;
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
 unsigned reserved14;
 unsigned normal;
	char beforeTex[0x24 - 0x1C];
	unsigned tex0;
	char beforeDiffuse[0x44 - 0x28];
	unsigned diffuse;

public:
	unsigned Get_FVF_Size() const { return stride; }
	unsigned Get_Location_Offset() const { return location; }
 unsigned Get_Normal_Offset() const { return normal; }
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

static __forceinline void CopyPointVectors(Vector3 *dst,int stride,const Vector3 *src,int count)
{
 for(;count;--count){dst->X=src->X;dst->Y=src->Y;dst->Z=src->Z;++src;dst=(Vector3*)((char*)dst+stride);}
}
static __forceinline void ConvertPointColors(unsigned *out,int stride,const Vector4 *colors,int count)
{
 for(;count;--count){const Vector4 *vector4;*out=ConvertPointColor(*(vector4=colors));++colors;out=(unsigned*)((char*)out+stride);}
}
static __forceinline void FillPointDiffuse(char *dest,int stride,int value,int count)
{
 while(count--){*(int*)dest=value;dest+=stride;}
}
static __forceinline void FillPointNormals(float *dst,int stride,float normalX,float normalY,float normalZ,int count)
{
 if(count==0)return;
 int n=count;
 do{dst[0]=normalX;dst[1]=normalY;dst[2]=normalZ;dst=(float*)((char*)dst+stride);--n;}while(n!=0);
}
struct PointUVPair{int a;int b;};
static __forceinline void CopyPointUVs(void *dst,int stride,const PointUVPair *src,int count)
{
 for(;count;--count){((PointUVPair*)dst)->a=src->a;((PointUVPair*)dst)->b=src->b;++src;dst=(char*)dst+stride;}
}
static __forceinline void FillPointUVs(float *output,int stride,float first,float second,int count)
{
 float uCoordinate=first,s=second;
 register int remaining=count;
 if(remaining==0)return;
 float zero=0.0f;
 float one=1.0f;
 do{
  output[0]=uCoordinate;output[1]=s;
  if(uCoordinate!=0.0f){uCoordinate=zero;s=one-s;}else{uCoordinate=one;}
  output=reinterpret_cast<float*>(reinterpret_cast<char*>(output)+stride);
 }while(--remaining!=0);
}
// Native177F82..178E47: four vertex buffers at0/4/8/C; count10,texture14,
// shader18,color1C and alpha28. This is distinct from PointGroupClass.
// BF1 f989 and rowed3377B PointGroup submission provide the shared pipeline.
class Rva0007671F {public:Rva0007671F();private:Vector4 rows[4];};
class RenderInfoClass;
class Rva00177860 {public:void Render(RenderInfoClass&);
 ShareBufferClass<Vector3> *locations;
 ShareBufferClass<Vector4> *diffuse;
 ShareBufferClass<Vector3> *normals;
 ShareBufferClass<Vector2> *texcoords;
 int count;TextureClass *texture;ShaderClass shader;Vector3 defaultColor;float defaultAlpha;
};
void Rva00177860::Render(RenderInfoClass&)
{
 if(count==0)return;
 shader.Set_Primary_Gradient(static_cast<ShaderClass::PriGradientType>(6));
 shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
 Rva0007671F worldStorage,viewStorage;
 Matrix4 &world=reinterpret_cast<Matrix4&>(worldStorage);
 Matrix4 &view=reinterpret_cast<Matrix4&>(viewStorage);
 DX8Wrapper::Get_Transform(D3DTS_WORLD,world);
 DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
 Matrix4 identity(true);
 DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);
 DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);
 VertexMaterialClass *material=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
 DX8Wrapper::Set_Material(material);material->Release_Ref();
 DX8Wrapper::Set_Shader(shader);
 BoxSetTexture(0,reinterpret_cast<TextureBaseClass*&>(texture));
 bool sort=(shader.Get_Dst_Blend_Func()!=ShaderClass::DSTBLEND_ZERO)
  && shader.Get_Alpha_Test()==ShaderClass::ALPHATEST_DISABLE
  && WW3D::Is_Sorting_Enabled() && g_Va00DB5F7D;
 DX8Wrapper::Set_Index_Buffer(sort?reinterpret_cast<IndexBufferClass*>(Rva009F7048):reinterpret_cast<IndexBufferClass*>(Rva009F7044),0);
 unsigned defaultDiffuse=ConvertDefaultPointColor(Vector4(defaultColor.X,defaultColor.Y,defaultColor.Z,defaultAlpha));
 int current=0;
 while(current<count) {
  int delta=MIN(count-current,512);
  BfmeSortingVBAccess vertices(sort?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8,5,delta*4,0);
  {
   BfmeSortingVBAccess::WriteLock lock(&vertices);
   unsigned stride=vertices.FVF_Info().Get_FVF_Size();
   unsigned char *vb=(unsigned char*)lock.Get_Formatted_Vertex_Array();
   const PointGroupTargetFVF &fvf=vertices.FVF_Info();
   CopyPointVectors((Vector3*)(vb+fvf.Get_Location_Offset()),stride,locations->Get_Array()+current*4,delta*4);
   if(diffuse) ConvertPointColors((unsigned*)(vb+fvf.Get_Diffuse_Offset()),stride,diffuse->Get_Array()+current*4,delta*4);
   else FillPointDiffuse((char*)(vb+fvf.Get_Diffuse_Offset()),stride,defaultDiffuse,delta*4);
   if(normals) CopyPointVectors((Vector3*)(vb+fvf.Get_Normal_Offset()),stride,normals->Get_Array()+current*4,delta*4);
   else FillPointNormals((float*)(vb+fvf.Get_Normal_Offset()),stride,0.0f,0.0f,1.0f,delta*4);
   if(texcoords) CopyPointUVs(vb+fvf.Get_Tex_Offset(0),stride,(const PointUVPair*)(texcoords->Get_Array()+current*4),delta*4);
   else FillPointUVs((float*)(vb+fvf.Get_Tex_Offset(0)),stride,0.0f,0.0f,delta*4);
  }
  DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass*>(&vertices));
  if(sort)SortingRendererClass::Insert_Triangles(0,delta*2,0,delta*6);
  else DX8Wrapper::Draw_Triangles(0,delta*2,0,delta*6);
  current+=delta;
 }
 DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
 DX8Wrapper::Set_Transform(D3DTS_WORLD,world);
}

