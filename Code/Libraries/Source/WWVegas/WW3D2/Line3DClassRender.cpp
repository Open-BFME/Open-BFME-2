// cl: /G7 /arch:SSE /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Support types and wrapper algorithms follow BFME 1 WWVegas headers. Retail
// evidence places Line3D Render at vtable slot 12, Get_Sort_Level at 94, and
// Is_Not_Hidden_At_All at 97 (table 0xBD3FA8). Its C4 base and Shader/vert/Color
// offsets CC/D0/130 come from matched target accessors/copy construction. Other
// base slots stay opaque. The target dynamic-index lock is 12 bytes; its fields
// are supported by the matched index-buffer lock body.
/*
** Command & Conquer Generals Zero Hour(tm)
** Copyright 2025 Electronic Arts Inc.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#define Matrix4x4 Matrix4
#include "winbase_shim.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix3d.h"
#include "aabox.h"
#include "always.h"
#include "shader.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "rinfo.h"
#include "wwdebug.h"
#include "d3d8.h"
#include "matrix4.h"
#include "texture.h"
#include "dx8vertexbuffer.h"
#include "dx8fvf.h"
#define DynamicIBAccessClass DonorDynamicIBAccessClass
#include "dx8indexbuffer.h"
#undef DynamicIBAccessClass
class DynamicIBAccessClass : public W3DMPO {
    unsigned Type;
    unsigned short IndexCount;
    unsigned short IndexBufferOffset;
    IndexBufferClass* IndexBuffer;
public:
    DynamicIBAccessClass(unsigned short, unsigned short);
    ~DynamicIBAccessClass();
    class WriteLockClass {
        DynamicIBAccessClass* DynamicIBAccess;
        unsigned short* Indices;
        unsigned char targetDeviceGuard[4];
    public:
        WriteLockClass(DynamicIBAccessClass*);
        ~WriteLockClass();
        unsigned short* Get_Index_Array() { return Indices; }
    };
};
// Matched texture-stage state code and the bfmestages shim establish 16 stages.
const unsigned MAX_TEXTURE_STAGES=16;
const unsigned MAX_VERTEX_STREAMS=2;
enum { BUFFER_TYPE_DX8, BUFFER_TYPE_SORTING, BUFFER_TYPE_DYNAMIC_DX8,
       BUFFER_TYPE_DYNAMIC_SORTING, BUFFER_TYPE_INVALID };
extern unsigned number_of_DX8_calls;
#define DX8_RECORD_MATRIX_CHANGE() matrix_changes++
#define DX8CALL(x) DX8Wrapper::_Get_D3D_Device8()->x; number_of_DX8_calls++
struct RenderStateStruct {
    ShaderClass shader;
    VertexMaterialClass* material;
    TextureBaseClass* Textures[MAX_TEXTURE_STAGES];
    D3DLIGHT8 Lights[4];
    bool LightEnable[4];
    Matrix4x4 world;
    Matrix4x4 view;
    unsigned vertex_buffer_types[MAX_VERTEX_STREAMS];
    unsigned index_buffer_type;
    unsigned short vba_offset;
    unsigned short vba_count;
    unsigned short iba_offset;
    VertexBufferClass* vertex_buffers[MAX_VERTEX_STREAMS];
    IndexBufferClass* index_buffer;
    unsigned short index_base_offset;
    RenderStateStruct();
    ~RenderStateStruct();
    RenderStateStruct& operator=(const RenderStateStruct&);
};
class DX8Wrapper {
    enum ChangedStates {
        WORLD_CHANGED=1<<0, VIEW_CHANGED=1<<1,
        MATERIAL_CHANGED=1<<14, SHADER_CHANGED=1<<15,
        WORLD_IDENTITY=1<<18, VIEW_IDENTITY=1<<19
    };
protected:
    static RenderStateStruct render_state;
    static unsigned render_state_changed;
    static unsigned matrix_changes;
public:
    static IDirect3DDevice8 *_Get_D3D_Device8();
    static void Set_Shader(const ShaderClass&);
    static void Set_Material(const VertexMaterialClass*);
    static void Set_Transform(D3DTRANSFORMSTATETYPE, const Matrix3D&);
    static unsigned Convert_Color(const Vector3&, float);
    static unsigned Convert_Color(const Vector4&);
    static void Set_Vertex_Buffer(const DynamicVBAccessClass&);
    static void Set_Index_Buffer(const DynamicIBAccessClass&, unsigned short);
    static void Draw_Triangles(unsigned, unsigned, unsigned, unsigned);
};

WWINLINE void DX8Wrapper::Set_Shader(const ShaderClass& shader)
{
	if (!ShaderClass::ShaderDirty && ((unsigned&)shader==(unsigned&)render_state.shader)) {
		return;
	}
	render_state.shader=shader;
	render_state_changed|=SHADER_CHANGED;
#ifdef MESH_RENDER_SNAPSHOT_ENABLED
	StringClass str;
#endif
	SNAPSHOT_SAY(("DX8Wrapper::Set_Shader(%s)\n",shader.Get_Description(str)));
}

// ?Set_Material@DX8Wrapper@@SAXPBVVertexMaterialClass@@@Z present-unmatched
// Retained for its verified inline expansion in Render; no separate body claim.
WWINLINE void DX8Wrapper::Set_Material(const VertexMaterialClass* material)
{
	REF_PTR_SET(render_state.material,const_cast<VertexMaterialClass*>(material));
	render_state_changed|=MATERIAL_CHANGED;
	SNAPSHOT_SAY(("DX8Wrapper::Set_Material(%s)\n",material ? material->Get_Name() : "NULL"));
}

// ?Set_Transform@DX8Wrapper@@SAXW4_D3DTRANSFORMSTATETYPE@@ABVMatrix3D@@@Z present-unmatched
// Retained for its verified inline expansion in Render; no separate body claim.
WWINLINE void DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE transform,const Matrix3D& m)
{
	Matrix4x4 m2(m);
	switch ((int)transform) {
	case D3DTS_WORLD:
		render_state.world=m2.Transpose();
		render_state_changed|=(unsigned)WORLD_CHANGED;
		render_state_changed&=~(unsigned)WORLD_IDENTITY;
		break;
	case D3DTS_VIEW:
		render_state.view=m2.Transpose();
		render_state_changed|=(unsigned)VIEW_CHANGED;
		render_state_changed&=~(unsigned)VIEW_IDENTITY;
		break;
	default:
		DX8_RECORD_MATRIX_CHANGE();
		m2=m2.Transpose();
		DX8CALL(SetTransform(transform,(D3DMATRIX*)&m2));
		break;
	}
}

// Adapted from reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/
// dx8wrapper.h. Clean C++ and sqrt/intrinsic variants failed exact matching,
// so retain this donor x87 sequence. Input is expected clamped to [0,1]; the
// control word selects truncation for RGBA*255, packs AARRGGBB, then restores
// the caller's rounding mode. The target-derived col=0 initialization remains.
WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector3& color,float alpha)
{
	const float scale = 255.0;
	unsigned int col = 0;

	__asm
	{
		sub	esp,20					// a, r, g, b and saved FPU control word
		fwait
		fstcw		[esp+16]				// save caller control word
		mov		eax,[esp+16]
		mov		edi,eax
		and		eax,~(1024|2048)	// clear rounding-control bits
		or			eax,(1024|2048)	// select truncation
		sub		edi,eax
		jz			skip
		mov		[esp],eax
		fldcw		[esp]
skip:
		mov	 esi,dword ptr color
		fld	dword ptr[scale]
		fld	dword ptr[esi]
		fld	dword ptr[esi+4]
		fld	dword ptr[esi+8]
		fld	dword ptr[alpha]
		fld	st(4)
		fmul	st(4),st
		fmul	st(3),st
		fmul	st(2),st
		fmulp	st(1),st
		fistp	dword ptr[esp+0]
		fistp	dword ptr[esp+4]
		fistp	dword ptr[esp+8]
		fistp	dword ptr[esp+12]
		mov		ecx,[esp]
		mov		eax,[esp+4]
		mov		edx,[esp+8]
		mov		ebx,[esp+12]
		shl		ecx,24
		shl		ebx,16
		shl		edx,8
		or			eax,ecx
		or			eax,ebx
		or			eax,edx
		fstp	st(0)
		cmp		edi,0
		je			not_changed
		fwait
		fldcw	[esp+16]				// restore caller control word
not_changed:
		add		esp,20
		mov		col,eax
	}
	return col;
}

WWINLINE unsigned int DX8Wrapper::Convert_Color(const Vector4& color)
{
	return Convert_Color(reinterpret_cast<const Vector3&>(color),color[3]);
}

class RenderInfoClass;
class RenderObjClass {
public:
    virtual void Delete_This();
#define V(n) virtual void slot##n();
    V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10)
    V(11)
    virtual void Render(RenderInfoClass&);
    V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20)
    V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30)
    V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40)
    V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50)
    V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59) V(60)
    V(61) V(62) V(63) V(64) V(65) V(66)
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass&) const;
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass&) const;
    virtual void Update_Obj_Space_Bounding_Volumes();
    V(70)
    V(71) V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79) V(80)
    V(81) V(82) V(83) V(84) V(85) V(86) V(87) V(88) V(89) V(90)
    virtual void Scale(float, float, float);
    virtual void Scale(float);
    V(93)
#undef V
    virtual int Get_Sort_Level() const;
    virtual void Set_Sort_Level(int);
    virtual int Is_Really_Visible();
    virtual int Is_Not_Hidden_At_All();
    // Retail code accesses flags@0x12, Transform@0x18, Container@0x7C,
    // and the Line3D members begin at 0xC4. Names follow the donor view.
    char beforeFlags[0x0E];
    unsigned char Flags;
    char beforeTransform[5];
    Matrix3D Transform;
    char beforeContainer[0x34];
    RenderObjClass* Container;
    char trailing[0x44];
    void Invalidate_Cached_Bounding_Volumes() { Flags &= 0xFD; }
    RenderObjClass* Get_Container() { return Container; }
};

class Line3DClass : public RenderObjClass {
public:
    virtual void Render(RenderInfoClass &);
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass& sphere) const;
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass& box) const;
    virtual void Scale(float, float, float);
    virtual void Scale(float);
    void Re_Color(float r, float g, float b);
    void Set_Opacity(float opacity);
    float Length;
    float Width;
    ShaderClass Shader;
    Vector3 vert[8];
    Vector4 Color;
    char SortLevel;
};

// All 36 words match the retail table at VA 0xBD3F58..0xBD3FA0.
const unsigned short Line3DRenderIndices[] = {
	3, 5, 1,
	7, 5, 3,
	1, 5, 0,
	5, 4, 0,
	4, 2, 0,
	4, 6, 2,
	7, 3, 2,
	6, 7, 2,
	7, 6, 5,
	5, 6, 4,
	2, 3, 1,
	2, 1, 0
};

class Line3DTargetFVF {
	char beforeStride[12];
	unsigned stride;
	unsigned location;
	char beforeDiffuse[0x44 - 0x14];
	unsigned diffuse;

public:
	unsigned Get_FVF_Size() const { return stride; }
	unsigned Get_Location_Offset() const { return location; }
	unsigned Get_Diffuse_Offset() const { return diffuse; }
};

class BoxVertexBufferClass;

struct BfmeSortingVBAccess {
	const Line3DTargetFVF& FVFInfo;
	unsigned Type;
	unsigned formatIndex; // The target constructor receives format index 5.
	unsigned unused_0x0C;  // Retained for layout; target meaning is unresolved.
	unsigned short VertexCount;
	unsigned short VertexBufferOffset;
	BoxVertexBufferClass* VertexBuffer;

	BfmeSortingVBAccess(unsigned type, unsigned format_index,
		unsigned short vertex_count, unsigned buffer);
	~BfmeSortingVBAccess();

	const Line3DTargetFVF& FVF_Info() const { return FVFInfo; }

	class WriteLock {
		BfmeSortingVBAccess* DynamicVBAccess;
		VertexFormatXYZNDUV2* Vertices;
		unsigned char targetDeviceGuard[4];

	public:
		WriteLock(BfmeSortingVBAccess* vb_access);
		~WriteLock();
		VertexFormatXYZNDUV2* Get_Formatted_Vertex_Array() { return Vertices; }
	};
};

extern void BoxSetTexture(unsigned stage, TextureBaseClass*& texture);

class Line3DTextureRef {
	TextureBaseClass* Texture;

public:
	Line3DTextureRef() : Texture(NULL) {}
	~Line3DTextureRef() { if (Texture) Texture->Release_Ref(); }
	operator TextureBaseClass*&() { return Texture; }
};

// Donor body: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/Line3DClass_Render.cpp
void Line3DClass::Render(RenderInfoClass& rinfo)
{
	if (Is_Not_Hidden_At_All() == false) {
		return;
	}

	unsigned int sort_level = (unsigned int)Get_Sort_Level();
	if (WW3D::Are_Static_Sort_Lists_Enabled() && sort_level != SORT_LEVEL_NONE) {
		WW3D::Add_To_Static_Sort_List(this, sort_level);
		return;
	}

	DX8Wrapper::Set_Shader(Shader);
	{
		Line3DTextureRef texture;
		BoxSetTexture(0, texture);
	}

	VertexMaterialClass* vm = VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
	DX8Wrapper::Set_Material(vm);
	REF_PTR_RELEASE(vm);

	DX8Wrapper::Set_Transform(D3DTS_WORLD, Transform);

	BfmeSortingVBAccess vb(BUFFER_TYPE_DYNAMIC_DX8, 5, 8, 0);
	{
		BfmeSortingVBAccess::WriteLock lock(&vb);
		const Line3DTargetFVF& fvf_info = vb.FVF_Info();
		unsigned char* vertex_bytes = (unsigned char*)lock.Get_Formatted_Vertex_Array();
		unsigned int color = DX8Wrapper::Convert_Color(Color);

		for (int i = 0; i < 8; ++i) {
			*(Vector3*)(vertex_bytes + fvf_info.Get_Location_Offset()) = vert[i];
			*(unsigned int*)(vertex_bytes + fvf_info.Get_Diffuse_Offset()) = color;
			vertex_bytes += fvf_info.Get_FVF_Size();
		}
	}

	DynamicIBAccessClass ib(BUFFER_TYPE_DYNAMIC_DX8, 36);
	{
		DynamicIBAccessClass::WriteLockClass lock(&ib);
		unsigned short* index_memory = lock.Get_Index_Array();
		const unsigned short* indices = Line3DRenderIndices;
		const unsigned short* end = Line3DRenderIndices + 36;
		while ((int)indices < (int)end) {
			*index_memory++ = *indices++;
		}
	}

	DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<DynamicVBAccessClass*>(&vb));
	DX8Wrapper::Set_Index_Buffer(ib, 0);
	DX8Wrapper::Draw_Triangles(0, 36 / 3, 0, 8);
}


// Direct vtable entries at BFME2 VA 0xBD40B4 / 0xBD40B8 identify these as
// Line3DClass slots 67 and 68; the implementation uses matched Length@0xC4.
void Line3DClass::Get_Obj_Space_Bounding_Sphere(SphereClass& sphere) const
{
    float half_l = Length * 0.5f;
    sphere.Center.Set(half_l, 0.0f, 0.0f);
    sphere.Radius = half_l;
}

void Line3DClass::Get_Obj_Space_Bounding_Box(AABoxClass& box) const
{
    float half_l = Length * 0.5f;
    box.Center.Set(half_l, 0.0f, 0.0f);
    box.Extent.Set(half_l, 0.0f, 0.0f);
}


// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/line3d.cpp.
// Retail 0x167370 selects the same alpha/opaque shader globals, calls the
// vtable Set_Sort_Level slot, and stores opacity in Color.W@0x13C. The target
// Line3D constructor at 0x1673D0 performs the same sequence inline.
void Line3DClass::Set_Opacity(float opacity)
{
    if (opacity < 1.0f) {
        Shader = ShaderClass::_PresetAlphaSolidShader;
        Set_Sort_Level(1);
    } else {
        Shader = ShaderClass::_PresetOpaqueSolidShader;
        Set_Sort_Level(SORT_LEVEL_NONE);
    }
    Color.W = opacity;
}

// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/line3d.cpp.
// Retail 0x167330 writes RGB at Color@0x130 and preserves Color.W@0x13C.
void Line3DClass::Re_Color(float r, float g, float b)
{
    Color = Vector4(r, g, b, Color.W);
}


// Donor: reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/line3d.cpp.
void Line3DClass::Scale(float scale)
{
    for (int i = 0; i < 8; ++i) vert[i] *= scale;
    Length *= scale;
    Width *= scale;
    Invalidate_Cached_Bounding_Volumes();
    RenderObjClass* container = Get_Container();
    if (container) container->Update_Obj_Space_Bounding_Volumes();
}

void Line3DClass::Scale(float scale_x, float scale_y, float scale_z)
{
    Vector3 scale(scale_x, scale_y, scale_z);
    for (int i = 0; i < 8; ++i) vert[i].Scale(scale);
    Length *= scale_x;
    Width *= scale_y;
    Invalidate_Cached_Bounding_Volumes();
    RenderObjClass* container = Get_Container();
    if (container) container->Update_Obj_Space_Bounding_Volumes();
}
