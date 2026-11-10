// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme_projection_matrix_link /Ireference/shims/bfme_vp_math /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
// The vector constructor iterator (??_H) takes the optimization state of the
// first function that needs it; retail links the /O1 body at 0x00001423.
// Instantiate it first in an unemitted anchor so this unit's copy is that body.
#include "../../../../GameEngine/Include/Common/BfmeVciAnchorElem.h"
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
// Rebase note: upstream d7b143eb97 retains the earlier 0.866 near-match in
// history; this bank preserves the whole2821B byte/EH-exact canonical-owner body.
// Copyright 2025 Electronic Arts Inc. SPDX-License-Identifier: GPL-3.0-or-later
//
// Native sentence-renderer operation 0x00118F50..0x00119A55, 2821 bytes.
// The existing 0x00155AD0 caller iterates renderer pointers at sentence+0x38.
// Retail proves the packed 44-byte vertex and 16-bit index arrays, owning
// texture at renderer+0x40, global bindings, device calls and full EH graph.
// ZH render2d.cpp Render2DClass::Render is the semantic source; WB9C07A0 is a
// callgraph lead, not proof that this older layout has that original name.
// Keep the independently pinned Rva00118F50 entry and its measured layout.
//
// ZH's identity local and BFME 2's Get_Transform/Set_Transform switches (every
// arm, as in W3DAptRendererRva00111319.cpp) spend c2's inline budget so the
// last two Transpose temps build their rows through ??_H, as retail does,
// with the /O1 iterator; a temporary final texture reference gives retail's
// lifetimes and 0x118-byte frame. The identity is spelled Make_Identity() so
// no /O2 Matrix4(bool) copy competes with retail's /O1 one (0x000A682E). ComposeShader preserves the native
// two-word evaluation order; no volatile local or new code/data pin is used.
// Existing data owners are declared with their actual types/access so this
// consumer does not introduce separate globals at the same retail addresses.
// BFME1 semantic inputs remain at verified pointer5bb8ca80ae66.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <string.h>
#include "vector4.h"
#include "matrix4.h"
class DynamicVBAccessClass {
public:
    DynamicVBAccessClass(unsigned,unsigned,unsigned short,unsigned);
    ~DynamicVBAccessClass();
    unsigned char native[24];
    class WriteLock {
    public:
        WriteLock(DynamicVBAccessClass*);~WriteLock();
        DynamicVBAccessClass*owner;void *data;char guard[4];
    };
};
class DynamicIBAccessClass {
public:
    DynamicIBAccessClass(unsigned short,unsigned short);~DynamicIBAccessClass();
    unsigned char native[12];
    class WriteLockClass {
    public:
        WriteLockClass(DynamicIBAccessClass*);~WriteLockClass();
        DynamicIBAccessClass*owner;unsigned short *data;char guard[4];
    };
};
#include "VertexMaterialClass.h"
class TextureBaseClass {public:void Release_Ref();};
typedef TextureBaseClass BFME2TextureResource;
struct BFME2TextureRef {
    BFME2TextureResource*texture;
    __declspec(dllimport) __forceinline BFME2TextureRef():texture(0) {}
    __forceinline ~BFME2TextureRef() {if(texture)texture->Release_Ref();}
};
void BFME2Set_Texture(unsigned,const BFME2TextureRef&);
#define renderDeviceWidth ((unsigned)DX8Wrapper::Get_Device_Resolution_Width())
#define renderDeviceHeight ((unsigned)DX8Wrapper::Get_Device_Resolution_Height())
extern int G00DB5FC0,G00DB5FC4,G00DB5FBC;
extern unsigned int g_Va00DEC4A0,g_Va00DEC4A4;
#define render2DSrcBlend ((unsigned)G00DB5FC0)
#define render2DDstBlend ((unsigned)G00DB5FC4)
#define render2DShaderBits ((unsigned)G00DB5FBC)
#define render2DExtraShaderBits g_Va00DEC4A0
#define render2DShaderAlphaFlag g_Va00DEC4A4
extern unsigned number_of_DX8_calls;
struct _D3DVIEWPORT8 {unsigned X,Y,Width,Height;float MinZ,MaxZ;};
struct IDirect3DDevice8 { void **vtable; };
#include "RenderStateStruct.h"
#include "ShaderClass.h"
class DX8Wrapper {
public:
    static void Set_Viewport(const _D3DVIEWPORT8*);
    static void Set_Vertex_Buffer(const DynamicVBAccessClass&);
    static void Set_Index_Buffer(const DynamicIBAccessClass&,unsigned short);
    static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned);
protected:
    static unsigned render_state_changed;
    static RenderStateStruct render_state;
    static Matrix4 ProjectionMatrix;
    static Matrix4 DeviceProjectionMatrix;
    static float ZFar,ZNear;
    static IDirect3DDevice8 *D3DDevice;
    static int ResolutionWidth; // dx8wrapper.cpp's protected static (@@1)
    static int ResolutionHeight;
    friend class Rva00118F50;
public:
    static __forceinline int Get_Device_Resolution_Width() { return ResolutionWidth; }
    static __forceinline int Get_Device_Resolution_Height() { return ResolutionHeight; }
public:
    static __forceinline void SetMaterial(VertexMaterialClass*vertexMaterial) {
        if(vertexMaterial)vertexMaterial->Add_Ref();
        if(render_state.material)render_state.material->Release_Ref();
        render_state.material=vertexMaterial;render_state_changed|=0x4000;
    }
    static __forceinline void SetWorldIdentity() {if(!(render_state_changed&0x40000)){render_state.world.Make_Identity();render_state_changed|=0x40001;}}
    static __forceinline void SetViewIdentity() {if(!(render_state_changed&0x80000)){render_state.view.Make_Identity();render_state_changed|=0x80002;}}
    static __forceinline void Get_Transform(int transform,Matrix4&matrix4) {
        switch(transform) {
        case 0x100: if(render_state_changed&0x40000)matrix4.Make_Identity(); else matrix4=render_state.world.Transpose(); break;
        case 2: if(render_state_changed&0x80000)matrix4.Make_Identity(); else matrix4=render_state.view.Transpose(); break;
        case 3: matrix4=DeviceProjectionMatrix.Transpose(); break;
        default: matrix4.Make_Identity(); break;
        }
    }
    static __forceinline void Set_Transform(int transform,const Matrix4&matrix4) {
        typedef long(__stdcall *SetTransformFn)(IDirect3DDevice8*,unsigned,const Matrix4*);
        switch(transform) {
        case 0x100: render_state.world=matrix4.Transpose();render_state_changed&=~0x40000;render_state_changed|=1;break;
        case 2: render_state.view=matrix4.Transpose();render_state_changed&=~0x80000;render_state_changed|=2;break;
        case 3: ProjectionMatrix=matrix4.Transpose();DeviceProjectionMatrix=ProjectionMatrix;ZFar=0.0f;ZNear=0.0f;
            ((SetTransformFn)D3DDevice->vtable[0xB0/4])(D3DDevice,3,&DeviceProjectionMatrix);++number_of_DX8_calls;break;
        default: {Matrix4 m2=matrix4.Transpose();((SetTransformFn)D3DDevice->vtable[0xB0/4])(D3DDevice,transform,&m2);++number_of_DX8_calls;} break;
        }
    }
    static __forceinline void SetShader(unsigned shader) {
        if(!ShaderClass::ShaderDirty && shader==render_state.shader.ShaderBits)return;
        render_state.shader.ShaderBits=shader;render_state_changed|=0x8000;
        StringClass text(0,false);
    }
};
struct Render2DRawArray {void *Data;unsigned Size,Count;int GrowthStep;};
class Rva00118F50 {
public:
    void Render();
private:
    unsigned shader;float scale[2],offset[2];Render2DRawArray vertices,indices;
    char batches[12];BFME2TextureRef texture;
};
// ?<ComposeShader> absent-from-retail
static __forceinline unsigned ComposeShader(unsigned state,unsigned extra) { return state | (extra<<3); }
void Rva00118F50::Render() {
    if(vertices.Count) {
    Matrix4 view,proj;
    Matrix4 identity;identity.Make_Identity();
    _ReadWriteBarrier();
    DX8Wrapper::Get_Transform(2,view);DX8Wrapper::Get_Transform(3,proj);
    _D3DVIEWPORT8 vp={0,0,renderDeviceWidth,renderDeviceHeight,0.0f,1.0f};
    DX8Wrapper::Set_Viewport(&vp);
    VertexMaterialClass*vm=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    DX8Wrapper::SetMaterial(vm);if(vm)vm->Release_Ref();
    DX8Wrapper::SetWorldIdentity();DX8Wrapper::SetViewIdentity();
    DX8Wrapper::Set_Transform(3,identity);
    // Keep the native DWORD count argument loads; the equivalent conditional
    // preserves MSVC 7.1's argument lowering for these WORD-parameter ABIs.
    DynamicVBAccessClass vb(2,5,(vertices.Count ? vertices.Count : vertices.Count),0);
    DynamicIBAccessClass ib(2,(indices.Count ? indices.Count : indices.Count));
    {
        DynamicVBAccessClass::WriteLock vblock(&vb);
        memcpy(vblock.data,vertices.Data,vertices.Count*44);
        DynamicIBAccessClass::WriteLockClass iblock(&ib);
        memcpy(iblock.data,indices.Data,indices.Count*2);
    }
    DX8Wrapper::Set_Vertex_Buffer(vb);DX8Wrapper::Set_Index_Buffer(ib,0);
    BFME2Set_Texture(0,texture);
    DX8Wrapper::SetShader(ComposeShader(
    ((render2DShaderBits & 0xFFFF3F1F) | (((render2DSrcBlend<<9)|render2DDstBlend)<<5)) &0xFFFFF8FF,
    (render2DExtraShaderBits&0xFFFE6703) | (render2DShaderAlphaFlag<<15) |0x22302));
    DX8Wrapper::Draw_Triangles(0,indices.Count/3,0,vertices.Count);
    DX8Wrapper::Set_Transform(2,view);DX8Wrapper::Set_Transform(3,proj);
    BFME2Set_Texture(0,BFME2TextureRef());
}
}



// Sentence-level dispatch, retained with its existing 47-byte row.
class Rva00154FD0
{
public:
	void rva00154FD0();
};

void __cdecl Rva00118810();
void __cdecl Rva001188A0();

struct Rva00155AD0Entry
{
	Rva00118F50 *obj;
	void *second;
};

class Rva00155AD0
{
public:
	void rva00155AD0();
private:
	char m_pad[0x38];
	Rva00155AD0Entry *m_array; // +0x38
	char m_pad2[8]; // +0x3C
	int m_count; // +0x44
};

void Rva00155AD0::rva00155AD0()
{
	((Rva00154FD0 *)this)->rva00154FD0();
	Rva00118810();
	for (int i = 0; i < m_count; ++i) {
		m_array[i].obj->Render();
	}
	Rva001188A0();
}
