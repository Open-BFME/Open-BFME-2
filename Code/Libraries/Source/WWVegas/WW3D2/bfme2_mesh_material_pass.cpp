// ?Render_Material_Pass@MeshClass@@QAEXPAVMaterialPassClass@@PAVIndexBufferClass@@@Z
// cl: /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

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
class DX8Wrapper { public: static void Set_Light_Environment(LightEnvironmentClass*); static void Set_Index_Buffer(const IndexBufferClass*,unsigned short); };
extern Matrix4 BFME2World;
extern unsigned BFME2RenderStateChanged;
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
extern Matrix4 BFME2View;
void BFME2Set_Device_Transform(int,const Matrix4&);
static __forceinline void SetTransform(int transform,const Matrix3D&m) {
 Matrix4 m2(m);
 switch(transform) {
 case 256: BFME2World=m2.Transpose();BFME2RenderStateChanged|=1;BFME2RenderStateChanged&=~0x40000;break;
 case 2: BFME2View=m2.Transpose();BFME2RenderStateChanged|=2;BFME2RenderStateChanged&=~0x80000;break;
 default:m2=m2.Transpose();BFME2Set_Device_Transform(transform,m2);break;
 }
}
static __forceinline void SetIdentity() {
 if(BFME2RenderStateChanged&0x40000) return;
 BFME2World.Make_Identity();BFME2RenderStateChanged|=0x40001;
}
void MeshClass::Render_Material_Pass(MaterialPassClass*pass,IndexBufferClass*ib) {
 float oldOpacity=-1.0f;Vector3 oldEmissive(-1,-1,-1);
 if(LightEnvironment) DX8Wrapper::Set_Light_Environment(LightEnvironment);
 if(AlphaOverride!=1.0f) {VertexMaterialClass*mat=pass->Material;if(mat) {oldOpacity=mat->Get_Opacity();mat->Set_Opacity(AlphaOverride);}}
 if(EmissiveOverride!=1.0f) {VertexMaterialClass*mat=pass->Material;if(mat) {mat->Get_Emissive(&oldEmissive);mat->Set_Emissive(EmissiveOverride*oldEmissive);}}
 DX8Wrapper::Set_Index_Buffer(ib,0);
 if(Model->Flags&0x400) {
  if(Anchor && *Anchor && *Anchor!=this) {Matrix3D inv,result;(*Anchor)->Get_Transform().Get_Inverse(inv);Matrix3D::Multiply(Get_Transform(),inv,&result);SetTransform(256,result);}
  else SetIdentity();
 } else SetTransform(256,Transform);
 pass->Install_Materials();
 MultiListIterator<DX8PolygonRendererClass> it(&Model->List);
 while(!it.Is_Done()) {if(it.Peek_Obj()->Pass==0) it.Peek_Obj()->Render(BaseVertexOffset);it.Next();}
 if(oldOpacity>=0) pass->Material->Set_Opacity(oldOpacity);
 if(oldEmissive.X>=0) pass->Material->Set_Emissive(oldEmissive);
 pass->UnInstall_Materials();
}
