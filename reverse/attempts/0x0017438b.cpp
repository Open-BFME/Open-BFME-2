// ?rva0017438B@Rva0017438B@@QAEXPAURenderingTask@@0@Z
// partial score=0.941391 date=2026-10-10
// BANKED PARTIAL ONLY: not an adopted class/provider contract.
// Target WB identity FXShaderRenderer::PerformRendering; integration must reconcile
// current Rva0017438B and Rva00DF6F94GapFillerContext owners without a second pin.
// stlport
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
extern "C" {
unsigned char *__cdecl _mbscpy(unsigned char *,const unsigned char *);
unsigned char *__cdecl _mbscat(unsigned char *,const unsigned char *);
__declspec(dllimport) int __cdecl sprintf(char *,const char *,...);
}
class RefCountClass {
public:
 virtual void Delete_This();
 int NumRefs;
 void Add_Ref() { ++NumRefs; }
 int Dec_Ref() { return --NumRefs; }
};
namespace FXShader {
class RenderingMethod : public RefCountClass {
public:
 virtual void slot1();
 virtual bool Begin(int *passCount,int flags);
 virtual void Begin_Pass(int pass);
 virtual void slot4(int mode);
 virtual void End_Pass();
 virtual void End();
};
}
class Rva00087A93 {
public:
 Rva00087A93(const Rva00087A93 &p) : Referent(p.Referent) { if(Referent) Referent->Add_Ref(); }
 ~Rva00087A93() { if(Referent && Referent->Dec_Ref()==0) Referent->Delete_This(); }
 bool IsBound() const { return Referent!=0; }
 RefCountClass *GetPtr() const { return Referent; }
 FXShader::RenderingMethod *operator->() const { return (FXShader::RenderingMethod *)Referent; }
 RefCountClass *Referent;
};
class BFME2ScopedRenderEvent {
 char Label[256]; char Group[64];
public:
 BFME2ScopedRenderEvent(const char *,const char *,unsigned);
 ~BFME2ScopedRenderEvent();
};
class Rva001688FFElement;
void Rva001688FFShift(Rva001688FFElement **items,int count);
void Rva00168952Clear(Rva001688FFElement **items,int count);
class Rva00149A90Obj { public: bool rva00149A90(Rva00149A90Obj *); };
class Rva0014A710 { public: void prepare(); };
struct Rva001741EBElement { int a[12]; };
#include <vector>
#include "../../Code/Libraries/Source/WWVegas/WWLib/StlRecordRva0017341B.h"
namespace _STL {
template<> void vector<Rva001741EBElement>::push_back(const Rva001741EBElement &);
template<> Rva0017341BWords *vector<Rva0017341BWords>::erase(Rva0017341BWords *,Rva0017341BWords *);
}
class MeshGeometryClass { public: const char *Get_Name() const; };
struct FXShaderGeometryView { char pad00[0x24]; int maxInstances; };
struct MeshModelView { char pad00[0xbc]; FXShaderGeometryView *geometry; };
class MeshClass {
public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();
 virtual void s05();virtual void s06();virtual void s07();virtual void s08();virtual void s09();
 virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();
 virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();
 virtual void Validate_Transform() const;
 char pad04[0x18-4]; Rva001741EBElement transform;
 char pad48[0xc4-0x48]; MeshModelView *Model;
 bool Is_Rendering_Identical(MeshClass *other) { return ((Rva00149A90Obj *)this)->rva00149A90((Rva00149A90Obj *)other); }
 void Begin_Render_With_FX_Material() { ((Rva0014A710 *)this)->prepare(); }
 void Render_With_FX_Material(Rva00087A93 method,int count);
 void rva00149bb0();
 const char *GetModelName() { return ((MeshGeometryClass *)Model)->Get_Name(); }
 const Rva001741EBElement &GetTransform() const { Validate_Transform(); return transform; }
};
class Rva0014D417 { public: void rva0014D417(int); };
class Rva0014D431 { public: void rva0014D431(); };
class FXShaderParameterSourceNamespaceSAS;
extern FXShaderParameterSourceNamespaceSAS *g_00DF36B4;
struct MeshReference {
 MeshClass *ptr; MeshClass *operator->() const { return ptr; }
 operator MeshClass *() const { return ptr; }
};
bool operator!=(const Rva00087A93 &a,const Rva00087A93 &b) { return a.GetPtr()!=b.GetPtr(); }
struct RenderingTask {
 MeshReference mesh; int methodCount; Rva00087A93 methods[6];
};
class Rva0017438B {
 char opaque00[0x24]; _STL::vector<Rva0017341BWords> transforms;
public:
 void rva0017438B(RenderingTask *begin,RenderingTask *end);
};
void Rva0017438B::rva0017438B(RenderingTask *begin,RenderingTask *end) {
 RenderingTask *batchBegin=begin,*batchEnd=begin;
 for(;batchEnd!=end;batchBegin=batchEnd) {
  for(++batchEnd;batchEnd!=end;++batchEnd) {
   if(!batchBegin->mesh->Is_Rendering_Identical(batchEnd->mesh.operator->())) break;
   if(batchBegin->methodCount!=batchEnd->methodCount) break;
   int i;
   for(i=batchBegin->methodCount-1;i>=0;--i)
    if(batchBegin->methods[i]!=batchEnd->methods[i]) break;
   if(i>=0) break;
  }
  if(batchBegin->methodCount<=0) continue;
  Rva001688FFShift((Rva001688FFElement **)&batchBegin->methods[0],batchBegin->methodCount);
  Rva00087A93 method(batchBegin->methods[0]);
  if(!method.IsBound()) continue;
  BFME2ScopedRenderEvent batchEvent("RenderFXShaderBatch",0,0);
  batchBegin->mesh->Begin_Render_With_FX_Material();
  int passCount;
  if(!method->Begin(&passCount,0xffff)) continue;
  for(int pass=0;pass<passCount;++pass) {
   method->Begin_Pass(pass);
   RenderingTask *chunkBegin=batchBegin,*chunkEnd=batchBegin;
   int maxInstances=batchBegin->mesh->Model->geometry->maxInstances;
   for(;chunkEnd!=batchEnd;chunkBegin=chunkEnd) {
    int remaining=batchEnd-chunkBegin;
    int count=*(maxInstances<remaining?&maxInstances:&remaining);
    chunkEnd=chunkBegin+count;
    if(count<=1) {
     char label[256];
     _mbscpy((unsigned char *)label,(const unsigned char *)"Rendering mesh\tFXShader\t");
     _mbscat((unsigned char *)label,(const unsigned char *)(chunkBegin->mesh->GetModelName()?chunkBegin->mesh->GetModelName():"(unnamed)"));
     BFME2ScopedRenderEvent meshEvent(label,"MeshFXShader",0);
     chunkBegin->mesh->Render_With_FX_Material(method,1);
    } else {
     char label[256];
     sprintf(label,"Rendering %d meshes\tFXShader\t%s",count,chunkBegin->mesh->GetModelName()?chunkBegin->mesh->GetModelName():"(unnamed)");
     BFME2ScopedRenderEvent meshEvent(label,"MeshFXShader",0);
     for(RenderingTask *item=chunkBegin;item!=chunkEnd;++item)
      ((_STL::vector<Rva001741EBElement> *)&transforms)->push_back(item->mesh->GetTransform());
     ((Rva0014D417 *)g_00DF36B4)->rva0014D417((int)&transforms);
     chunkBegin->mesh->Render_With_FX_Material(method,count);
     ((Rva0014D431 *)g_00DF36B4)->rva0014D431();
     _STL::vector<Rva0017341BWords> *v=&transforms; v->erase(v->begin(),v->end());
    }
   }
   method->End_Pass();
  }
  method->End();
  batchBegin->mesh->rva00149bb0();
  Rva00168952Clear((Rva001688FFElement **)&batchBegin->methods[0],batchBegin->methodCount);
 }
}
