// ?Render@Render2DClass@@QAEXXZ
// partial score=0.96 date=2026-10-09
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme_vp_math /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Semantic donor: GeneralsMD/WW3D2/render2d.cpp Render2DClass::Render.
// BFME2 native118F50..119A55: direct packed44B vertex and ushort-index upload;
// save/restore view and projection matrices and bind single owning texture.
// WB9C07A0 establishes Render2DClass::Render identity but contains newer batch
// loops absent from this target. Only target-native control flow is claimed.
#include <string.h>
#include "../../../../../reference/shims/bfme_vp_math/vector4.h"
#include "../../../../../reference/shims/bfme_projection_matrix_link/matrix4.h"
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
class VertexMaterialClass {
public:
    virtual void Delete_This();
    int references;
    enum PresetType { PRELIT_DIFFUSE };
    static VertexMaterialClass *Get_Preset(PresetType);
    __forceinline void Add_Ref() {++references;}
    __forceinline void Release_Ref() {if(--references==0) Delete_This();}
};
class BFME2TextureResource {public:void Release_Ref();};
struct BFME2TextureRef {
    BFME2TextureResource*texture;
    __forceinline BFME2TextureRef():texture(0) {}
    __forceinline ~BFME2TextureRef() {if(texture)texture->Release_Ref();}
};
void BFME2Set_Texture(unsigned,const BFME2TextureRef&);
class StringClass {
public:
    StringClass(int length,bool isTemp) {m_Buffer=m_EmptyString;Get_String(length,isTemp);m_Buffer[0]=m_NullChar;}
    ~StringClass() {Free_String();}
    char *m_Buffer;
    static char*m_EmptyString;static char m_NullChar;
private:
    void Get_String(int,bool);void Free_String();
};
extern unsigned renderDeviceWidth,renderDeviceHeight;
extern unsigned render2DSrcBlend,render2DDstBlend,render2DShaderBits,render2DExtraShaderBits;
extern unsigned render2DShaderAlphaFlag;
struct _D3DVIEWPORT8 {unsigned X,Y,Width,Height;float MinZ,MaxZ;};
struct NativeDevice9 { void **vtable; };
class DX8Wrapper {
public:
    static void Set_Viewport(const _D3DVIEWPORT8*);
    static void Set_Vertex_Buffer(const DynamicVBAccessClass&);
    static void Set_Index_Buffer(const DynamicIBAccessClass&,unsigned short);
    static void Draw_Triangles(unsigned,unsigned,unsigned,unsigned);
    static unsigned render_state_changed;
    static bool ShaderDirty;
    struct State { unsigned shader;VertexMaterialClass*material;unsigned char unmodelled[0x1EC-8];Matrix4 world,view; };
    static State render_state;
    static Matrix4 ProjectionMatrix,DeviceProjectionMatrix;
    static float ZFar,ZNear;
    static NativeDevice9 *D3DDevice;
    static unsigned matrix_changes;
    static __forceinline void SetMaterial(VertexMaterialClass*m) {
        if(m)m->Add_Ref();
        if(render_state.material)render_state.material->Release_Ref();
        render_state.material=m;render_state_changed|=0x4000;
    }
    static __forceinline void GetView(Matrix4&m) {if(render_state_changed&0x80000)m.Make_Identity();else {const Matrix4 &src=render_state.view;m[0][0]=src[0][0];m[0][1]=src[1][0];m[0][2]=src[2][0];m[0][3]=src[3][0];m[1][0]=src[0][1];m[1][1]=src[1][1];m[1][2]=src[2][1];m[1][3]=src[3][1];m[2][0]=src[0][2];m[2][1]=src[1][2];m[2][2]=src[2][2];m[2][3]=src[3][2];m[3][0]=src[0][3];m[3][1]=src[1][3];m[3][2]=src[2][3];m[3][3]=src[3][3];}}
    static __forceinline void GetProjection(Matrix4&m) {const Matrix4 &src=DeviceProjectionMatrix;m[0][0]=src[0][0];m[0][1]=src[1][0];m[0][2]=src[2][0];m[0][3]=src[3][0];m[1][0]=src[0][1];m[1][1]=src[1][1];m[1][2]=src[2][1];m[1][3]=src[3][1];m[2][0]=src[0][2];m[2][1]=src[1][2];m[2][2]=src[2][2];m[2][3]=src[3][2];m[3][0]=src[0][3];m[3][1]=src[1][3];m[3][2]=src[2][3];m[3][3]=src[3][3];}
    static __forceinline void SetWorldIdentity() {if(!(render_state_changed&0x40000)){render_state.world.Make_Identity();render_state_changed|=0x40001;}}
    static __forceinline void SetViewIdentity() {if(!(render_state_changed&0x80000)){render_state.view.Make_Identity();render_state_changed|=0x80002;}}
    static __forceinline void SetProjection(const Matrix4&m) {
        ProjectionMatrix=m.Transpose();DeviceProjectionMatrix=ProjectionMatrix;ZFar=0.0f;ZNear=0.0f;
        typedef long(__stdcall *SetTransform)(NativeDevice9*,unsigned,const Matrix4*);
        ((SetTransform)D3DDevice->vtable[0xB0/4])(D3DDevice,3,&DeviceProjectionMatrix);++matrix_changes;
    }
    static __forceinline void SetView(const Matrix4&m) {render_state.view=m.Transpose();render_state_changed&=~0x80000;render_state_changed|=2;}
    static __forceinline void SetShader(unsigned shader) {
        if(!ShaderDirty && shader==render_state.shader)return;
        render_state.shader=shader;render_state_changed|=0x8000;
        StringClass text(0,false);
    }
};
struct Render2DRawArray {void *Data;unsigned Size,Count;int GrowthStep;};
class Render2DClass {
public:
    void Render();
private:
    unsigned shader;float scale[2],offset[2];Render2DRawArray vertices,indices;
    char batches[12];BFME2TextureRef texture;
};
void Render2DClass::Render() {
    if(vertices.Count) {
    Matrix4 view,proj;
    DX8Wrapper::GetView(view);DX8Wrapper::GetProjection(proj);
    _D3DVIEWPORT8 vp={0,0,renderDeviceWidth,renderDeviceHeight,0.0f,1.0f};
    DX8Wrapper::Set_Viewport(&vp);
    VertexMaterialClass*vm=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
    DX8Wrapper::SetMaterial(vm);if(vm)vm->Release_Ref();
    DX8Wrapper::SetWorldIdentity();DX8Wrapper::SetViewIdentity();
    DX8Wrapper::ProjectionMatrix.Make_Identity();DX8Wrapper::DeviceProjectionMatrix.Make_Identity();DX8Wrapper::ZFar=0.0f;DX8Wrapper::ZNear=0.0f;
    typedef long(__stdcall *SetTransform)(NativeDevice9*,unsigned,const Matrix4*);
    ((SetTransform)DX8Wrapper::D3DDevice->vtable[0xB0/4])(DX8Wrapper::D3DDevice,3,&DX8Wrapper::DeviceProjectionMatrix);++DX8Wrapper::matrix_changes;
    DynamicVBAccessClass vb(2,5,vertices.Count,0);
    DynamicIBAccessClass ib(2,indices.Count);
    {
        DynamicVBAccessClass::WriteLock vblock(&vb);
        memcpy(vblock.data,vertices.Data,vertices.Count*44);
        DynamicIBAccessClass::WriteLockClass iblock(&ib);
        memcpy(iblock.data,indices.Data,indices.Count*2);
    }
    DX8Wrapper::Set_Vertex_Buffer(vb);DX8Wrapper::Set_Index_Buffer(ib,0);
    BFME2Set_Texture(0,texture);
    unsigned state=((render2DShaderBits & 0xFFFF3F1F) | (((render2DSrcBlend<<9)|render2DDstBlend)<<5)) &0xFFFFF8FF;
    unsigned extra=(render2DExtraShaderBits&0xFFFE6703) | (render2DShaderAlphaFlag<<15) |0x22302;
    DX8Wrapper::SetShader(state|(extra<<3));
    DX8Wrapper::Draw_Triangles(0,indices.Count/3,0,vertices.Count);
    DX8Wrapper::SetView(view);DX8Wrapper::SetProjection(proj);
    BFME2TextureRef empty;BFME2Set_Texture(0,empty);
}
}
