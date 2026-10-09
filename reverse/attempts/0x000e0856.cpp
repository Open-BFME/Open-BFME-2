// ?rva000E0856@Rva000E0856@@QAEXPAPAVCameraClass@@@Z
// partial score=0.96 date=2026-10-09
// cl: /O1 /G7 /MD /EHs /arch:SSE /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable
// stlport
// Native E0856..E0AC3 RET4, 621B. WB87DBC0 proves render/update purpose.
// Original owner/API name unknown. Target offsets supersede debug layout.
#include <hash_map>
#include <list>
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
enum NameKeyType { NativeNameKeyUnknown=0 };
// ABI view of the already owned folded clear specialization; no target
// ArmorTemplate payload claim. ZH provider has 38 damage coefficients.
class ArmorTemplate {float donorCoefficients[38];};
namespace rts {template<class T>struct hash {unsigned operator()(T)const;};template<class T>struct equal_to {bool operator()(T,T)const;};}
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorPair>,rts::equal_to<NameKeyType>,_STL::allocator<ArmorPair> > ArmorTable;
namespace _STL {template<> __declspec(noinline) void ArmorTable::clear();}
class Vector2 {public:float x,y;Vector2(float a,float b):x(a),y(b){}};
class BfmeVecHF {public:float x,y,z;BfmeVecHF(float a,float b,float c):x(a),y(b),z(c){}};
class Matrix3D;
class LightEnvironmentClass {public:void Pre_Render_Update(const Matrix3D &);};
class Gen_0094AC70 {public:void bfmeSetPair(const BfmeVecHF *,const BfmeVecHF *);};
class SegmentedLineClass {public:void rva0015E3E0(const Vector2 &);};
class Rva000E0123 {public:void rva000E0123(float);void rva000E00C0(float);};
class Rva000E07F4Obj;
class Rva000E07F4Host {public:void rva000E0584(Rva000E07F4Obj *);};
int rva000E07F4(Rva000E07F4Obj *,Rva000E07F4Host *);
class Object;
class Player {public:int iterateObjects(int (*)(Object *,void *),void *) const;};
class PlayerList {public:char pad[16];Player *local;};
extern PlayerList *ThePlayerList;
class Object {public:Player *getControllingPlayer()const;Object *rva002931F5(bool);void *vtable,*thingTemplate;};
struct RenderDrawable {char pad[0xfc];Object *object;};
struct SelectedNode {SelectedNode *next,*previous;RenderDrawable *drawable;};
typedef _STL::list<RenderDrawable *> SelectedList;
class InGameUI {public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 virtual void v57();
 virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual void v66();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void v70();
 virtual void v71();
 virtual void v72();
 virtual const SelectedList *selected();
 virtual void v74();
 virtual void v75();
 virtual void v76();
 virtual void v77();
 virtual void v78();
 virtual void v79();
 virtual void v80();
 virtual void v81();
 virtual void v82();
 virtual void v83();
 virtual void v84();
 virtual void v85();
 virtual void v86();
 virtual void v87();
 virtual void v88();
 virtual void v89();
 virtual void v90();
 virtual void v91();
 virtual void v92();
 virtual unsigned hovered();
 char pad[0x8b4-4];int mode;
};
extern InGameUI *TheInGameUI;
class GameClient {public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual RenderDrawable *findDrawable(unsigned);
};
extern GameClient *TheGameClient;
class CameraClass {public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void update();
char pad[0x18-4];};
class RenderInfoClass {public:RenderInfoClass(CameraClass &);~RenderInfoClass();char pad[0x28];LightEnvironmentClass *light;char tail[0x148-0x2c];};
float NativeSelectionRenderOpacity=1.0f;
class Rva000E0856 {public:void rva000E0856(CameraClass **camera);void *object00;SegmentedLineClass *lines[4];char pad14[8];RenderInfoClass *renderInfo;char lightBytes[0x238];};
void Rva000E0856::rva000E0856(CameraClass **camera)
{
 if(!TheInGameUI || !TheInGameUI->mode)return;
 ((ArmorTable *)(lightBytes+0x238))->clear();
 float opacity=1.0f-(float)(timeGetTime()%1000)/1000.0f;
 { Vector2 offset(0.0f,opacity);
 lines[2]->rva0015E3E0(offset);
 offset.x=0.0f; offset.y=opacity;
 lines[3]->rva0015E3E0(offset); }
 BfmeVecHF white(1.0f,1.0f,1.0f),black(0.0f,0.0f,0.0f);
 ((Gen_0094AC70 *)lightBytes)->bfmeSetPair(&black,&white);
 { CameraClass *activeCamera=*camera; activeCamera->update();
 ((LightEnvironmentClass *)lightBytes)->Pre_Render_Update(*(Matrix3D *)((char *)activeCamera+0x18)); }
 RenderInfoClass info(**camera);
 renderInfo=&info;info.light=(LightEnvironmentClass *)lightBytes;
 int mode=TheInGameUI->mode;
 if(mode==1 || mode==2){
  unsigned hover=TheInGameUI->hovered();
  if(hover){RenderDrawable *d=TheGameClient->findDrawable(hover);
   if(d){Object *o=d->object;
    if(o && !(((unsigned char *)o->thingTemplate)[0x10d]&0x80)){
     Player *local=ThePlayerList->local;
     if(o->getControllingPlayer()==local){
     Object *contained=o->rva002931F5(false);if(contained)o=contained;
     ((Rva000E0123 *)this)->rva000E0123(3.0f);
     ((Rva000E0123 *)this)->rva000E00C0(1.0f);
     ((Rva000E07F4Host *)this)->rva000E0584((Rva000E07F4Obj *)o);
     ((Rva000E0123 *)this)->rva000E0123(1.5f);
     }
    }
   }
  }
 }
 if(mode==1 || mode==2){
  NativeSelectionRenderOpacity=0.8f;
  SelectedList::const_iterator i;
  const SelectedList *selection=TheInGameUI->selected();
  i=selection->begin();
  for(;i!=selection->end();++i){
   Object *o=(*i)->object;
   ((Rva000E0123 *)this)->rva000E00C0(1.0f);
   rva000E07F4((Rva000E07F4Obj *)o,(Rva000E07F4Host *)this);
  }
 }
 if(mode==2){Player *p=ThePlayerList->local;if(p){
  ((Rva000E0123 *)this)->rva000E00C0(0.4f);
  p->iterateObjects((int (*)(Object *,void *))rva000E07F4,this);
 }}
 renderInfo=0;
}
