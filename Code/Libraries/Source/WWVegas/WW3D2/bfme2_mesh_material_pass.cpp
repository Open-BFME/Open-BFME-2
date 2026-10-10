// ?Render_Material_Pass@MeshClass@@QAEXPAVMaterialPassClass@@PAVIndexBufferClass@@@Z
// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

// BFME2 material-pass rendering reconstructed from retail14C000..14C46A.
// Sparse class views use only independently decoded fields. The Anchor record
// supplies a mesh used to form a relative skin world transform.
// Preserve the donor Set_Transform switch: simplifying it to its WORLD arm
// changes MSVC7.1 block alignment. Unused cases compile away at both call sites.
// Complete1130-byte RET8 body; original math and list templates retain codegen.
// Root reconstructed the body; independent Astra review restored the switch
// and audited the call/data identities before landing.
#include "matrix3d.h"
#include "matrix4.h"
#include "vector3.h"
#include "multilist.h"
class VertexMaterialClass {public: float Get_Opacity() const; void Set_Opacity(float); void Get_Emissive(Vector3*) const;void Set_Emissive(const Vector3&);};
class MaterialPassClass {
public: virtual void Unknown0()=0;virtual void Unknown1()=0;virtual void Install_Materials() const=0;virtual void UnInstall_Materials() const=0;
 char Prefix[40];VertexMaterialClass*Material;
};
class DX8PolygonRendererClass : public MultiListObjectClass {char Prefix[40];public:int Pass;void Render(int);};
struct RenderNode {void*Unknown;RenderNode*Next;void*Previous;DX8PolygonRendererClass*Object;};
struct MeshModelClass {char Prefix[24];unsigned Flags;char Gap[128];MultiListClass<DX8PolygonRendererClass> List;};
class IndexBufferClass;
class LightEnvironmentClass;
// DX8Wrapper::render_state (VA 0x00DEE5D8, dx8wrapper.cpp): Zero Hour's
// RenderStateStruct (bfmestages/dx8wrapper.h) -- shader, material,
// Textures[16], Lights[4] and LightEnable[4], then world at +0x1EC
// (0x00DEE7C4) and view at +0x22C (0x00DEE804). render_state_changed is
// VA 0x00DEC4F4.
struct RenderStateStruct { unsigned char m_pad00[0x1EC]; Matrix4 world,view; };
// IDirect3DDevice8::SetTransform is vtable slot 37 (d3d8.h).
struct IDirect3DDevice8;
struct IDirect3DDevice8Vtbl { void *m_slots[37]; long (__stdcall *SetTransform)(IDirect3DDevice8*,int,const Matrix4*); };
struct IDirect3DDevice8 { IDirect3DDevice8Vtbl *lpVtbl; };
extern unsigned number_of_DX8_calls;
class DX8Wrapper {
public:
 static void Set_Light_Environment(LightEnvironmentClass*);
 static void Set_Index_Buffer(const IndexBufferClass*,unsigned short);
 // Zero Hour dx8wrapper.h Set_Transform(D3DTRANSFORMSTATETYPE,const Matrix3D&)
 // and Set_World_Identity, inline here.
 static __forceinline void Set_Transform(int transform,const Matrix3D&m) {
  Matrix4 m2(m);
  switch(transform) {
  case 256: render_state.world=m2.Transpose();render_state_changed|=1;render_state_changed&=~0x40000;break;
  case 2: render_state.view=m2.Transpose();render_state_changed|=2;render_state_changed&=~0x80000;break;
  default:matrix_changes++;m2=m2.Transpose();D3DDevice->lpVtbl->SetTransform(D3DDevice,transform,&m2);number_of_DX8_calls++;break;
  }
 }
 static __forceinline void Set_World_Identity() {
  if(render_state_changed&0x40000) return;
  render_state.world.Make_Identity();render_state_changed|=0x40001;
 }
protected:
 static RenderStateStruct render_state;
 static unsigned render_state_changed;
 static unsigned matrix_changes;
 static IDirect3DDevice8 *D3DDevice;
};
class MeshClass {
public:
virtual void Unknown0() const=0;
virtual void Unknown1() const=0;
virtual void Unknown2() const=0;
virtual void Unknown3() const=0;
virtual void Unknown4() const=0;
virtual void Unknown5() const=0;
virtual void Unknown6() const=0;
virtual void Unknown7() const=0;
virtual void Unknown8() const=0;
virtual void Unknown9() const=0;
virtual void Unknown10() const=0;
virtual void Unknown11() const=0;
virtual void Unknown12() const=0;
virtual void Unknown13() const=0;
virtual void Unknown14() const=0;
virtual void Unknown15() const=0;
virtual void Unknown16() const=0;
virtual void Unknown17() const=0;
virtual void Unknown18() const=0;
virtual void Unknown19() const=0;

 virtual void Validate_Transform() const=0;
 char Prefix[20];Matrix3D Transform;char Gap48[124];MeshModelClass*Model;LightEnvironmentClass*LightEnvironment;char GapCC[556];float EmissiveOverride,AlphaOverride;int BaseVertexOffset;char Gap304[12];MeshClass**Anchor;
 void Render_Material_Pass(MaterialPassClass*,IndexBufferClass*);
 const Matrix3D&Get_Transform() const {Validate_Transform();return Transform;}
};
void MeshClass::Render_Material_Pass(MaterialPassClass*pass,IndexBufferClass*ib) {
 float oldOpacity=-1.0f;Vector3 oldEmissive(-1,-1,-1);
 if(LightEnvironment) DX8Wrapper::Set_Light_Environment(LightEnvironment);
 if(AlphaOverride!=1.0f) {VertexMaterialClass*mat=pass->Material;if(mat) {oldOpacity=mat->Get_Opacity();mat->Set_Opacity(AlphaOverride);}}
 if(EmissiveOverride!=1.0f) {VertexMaterialClass*mat=pass->Material;if(mat) {mat->Get_Emissive(&oldEmissive);mat->Set_Emissive(EmissiveOverride*oldEmissive);}}
 DX8Wrapper::Set_Index_Buffer(ib,0);
 if(Model->Flags&0x400) {
  if(Anchor && *Anchor && *Anchor!=this) {Matrix3D inv,result;(*Anchor)->Get_Transform().Get_Inverse(inv);Matrix3D::Multiply(Get_Transform(),inv,&result);DX8Wrapper::Set_Transform(256,result);}
  else DX8Wrapper::Set_World_Identity();
 } else DX8Wrapper::Set_Transform(256,Transform);
 pass->Install_Materials();
 MultiListIterator<DX8PolygonRendererClass> it(&Model->List);
 while(!it.Is_Done()) {if(it.Peek_Obj()->Pass==0) it.Peek_Obj()->Render(BaseVertexOffset);it.Next();}
 if(oldOpacity>=0) pass->Material->Set_Opacity(oldOpacity);
 if(oldEmissive.X>=0) pass->Material->Set_Emissive(oldEmissive);
 pass->UnInstall_Materials();
}
