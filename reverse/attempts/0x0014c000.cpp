// ?Render_Material_Pass@MeshClass@@QAEXPAVMaterialPassClass@@PAVIndexBufferClass@@@Z
// partial score=0.8653395784543325 date=2026-09-08
// cl: /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// Retail1130 bytes; this draft1129. All concrete bytes before offset3DA
// match except branch displacement232. Tail differs in alignment only plus
// resulting offsets: retail pads common join to3E0 and leaves loop401;
// VC7.1 draft leaves join3DA and aligns loop400. No executable claim.
// Sparse class views are independently decoded; Anchor at310 points to a
// mesh pointer used to make skin transforms relative to another mesh.
// Render list deliberately cached once as the retail/donor iterator does.
#include "matrix3d.h"
#include "matrix4.h"
#include "vector3.h"
#include "multilist.h"
class VertexMaterialClass {public: float Get_Opacity() const; void Set_Opacity(float); void Get_Emissive(Vector3*) const;void Set_Emissive(const Vector3&);};
class MaterialPassClass {
public: virtual void Unknown0()=0;virtual void Unknown1()=0;virtual void Install_Materials()=0;virtual void UnInstall_Materials()=0;
 char Prefix[40];VertexMaterialClass*Material;
};
class DX8PolygonRendererClass : public MultiListObjectClass {char Prefix[40];public:int Pass;void Render(int);};
struct RenderNode {void*Unknown;RenderNode*Next;void*Previous;DX8PolygonRendererClass*Object;};
struct MeshModelClass {char Prefix[24];unsigned Flags;char Gap[128];MultiListClass<DX8PolygonRendererClass> List;};
class IndexBufferClass;
class LightEnvironmentClass;
void BFME2Set_Light_Environment(LightEnvironmentClass*);
void BFME2Set_Index_Buffer(IndexBufferClass*,unsigned short);
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
static __forceinline void SetWorld(const Matrix3D&m) {
 Matrix4 m2(m);BFME2World=m2.Transpose();BFME2RenderStateChanged|=1;BFME2RenderStateChanged&=~0x40000;
}
static __forceinline void SetIdentity() {
 if(BFME2RenderStateChanged&0x40000) return;
 BFME2World.Make_Identity();BFME2RenderStateChanged|=0x40001;
}
void MeshClass::Render_Material_Pass(MaterialPassClass*pass,IndexBufferClass*ib) {
 float oldOpacity=-1.0f;Vector3 oldEmissive(-1,-1,-1);
 if(LightEnvironment) BFME2Set_Light_Environment(LightEnvironment);
 if(AlphaOverride!=1.0f) {VertexMaterialClass*mat=pass->Material;if(mat) {oldOpacity=mat->Get_Opacity();mat->Set_Opacity(AlphaOverride);}}
 if(EmissiveOverride!=1.0f) {VertexMaterialClass*mat=pass->Material;if(mat) {mat->Get_Emissive(&oldEmissive);mat->Set_Emissive(EmissiveOverride*oldEmissive);}}
 BFME2Set_Index_Buffer(ib,0);
 if(Model->Flags&0x400) {
  if(Anchor && *Anchor && *Anchor!=this) {Matrix3D inv,result;(*Anchor)->Get_Transform().Get_Inverse(inv);Matrix3D::Multiply(Get_Transform(),inv,&result);SetWorld(result);}
  else SetIdentity();
 } else SetWorld(Transform);
 pass->Install_Materials();
 MultiListIterator<DX8PolygonRendererClass> it(&Model->List);
 while(!it.Is_Done()) {if(it.Peek_Obj()->Pass==0) it.Peek_Obj()->Render(BaseVertexOffset);it.Next();}
 if(oldOpacity>=0) pass->Material->Set_Opacity(oldOpacity);
 if(oldEmissive.X>=0) pass->Material->Set_Emissive(oldEmissive);
 pass->UnInstall_Materials();
}
