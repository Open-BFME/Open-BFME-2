// ?render@Rva000E0856@@QAEXPAVRenderContext@@@Z
// partial score=0.9742 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHs /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <stl/_hashtable.h>
class BfmeVecHF {public:float x,y,z;};
class Gen_0094AC70 {public:void bfmeSetPair(const BfmeVecHF*,const BfmeVecHF*);};
class Matrix3D {public:float cells[12];};
class LightEnvironmentClass {public:void Pre_Render_Update(const Matrix3D&);};
class Vector2 {public:float x,y;__forceinline Vector2(float a,float b):x(a),y(b){}};
class SegmentedLineClass {public:void rva0015E3E0(const Vector2&);};
class CameraClass {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void update();char unknown4[0x14];Matrix3D transform;
};
class RenderInfoClass {public:RenderInfoClass(CameraClass&);~RenderInfoClass();char prefix[0x28];LightEnvironmentClass*lights;char rest[0x11c];};
class RenderContext {public:CameraClass*camera;};
class Player;class Object {public:Player*getControllingPlayer()const;Object*rva002931F5(bool);};
class Player {public:int iterateObjects(int(*)(Object*,void*),void*)const;};
class PlayerList {public:char prefix[16];Player*local;};extern PlayerList*ThePlayerList;
class Rva000E07F4Obj {public:char prefix[4];void*inner;};
struct DrawableView {char prefix[0xFC];Rva000E07F4Obj*object;};
struct SelectionNode {SelectionNode*next,*prev;DrawableView*drawable;};
struct SelectionList {SelectionNode*head;};
class InGameUI {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual SelectionList*slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual void slot87();
virtual void slot88();
virtual void slot89();
virtual void slot90();
virtual void slot91();
virtual void slot92();
virtual unsigned slot93();
char prefix[0x8B0];int mode;};extern InGameUI*TheInGameUI;
class GameClient {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual DrawableView*lookup(unsigned);};extern GameClient*TheGameClient;
class Rva000E0123 {public:void rva000E0123(float);void rva000E00C0(float);};
class Rva000E07F4Host {public:void rva000E0584(Rva000E07F4Obj*);};
int rva000E07F4(Rva000E07F4Obj*,Rva000E07F4Host*);
extern "C" __declspec(dllimport) unsigned __stdcall timeGetTime();
extern float terrainLineOpacity;
enum NameKeyType{NativeNameKeyUnknown=0};
class ArmorTemplate{float payload[38];};namespace rts{template<class T>struct hash{unsigned operator()(const T&t)const{return(unsigned)t;}};}
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmorPair;
typedef _STL::hashtable<ArmorPair,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmorPair>,_STL::equal_to<NameKeyType>,_STL::allocator<ArmorPair> > ArmorTable;
namespace _STL{template<>void ArmorTable::clear();}
class Rva000E0856 {public:void render(RenderContext*);void*hint;SegmentedLineClass*lines[4];char unknown14[8];RenderInfoClass*info;char lights[0x22c];char points[12];char hash[20];};
void Rva000E0856::render(RenderContext*ctx){
 if(!TheInGameUI||!TheInGameUI->mode)return;
 ((ArmorTable*)hash)->clear();
 float phase;
 Vector2 uv(0,phase=1.0f-(timeGetTime()%1000)/1000.0f);lines[2]->rva0015E3E0(uv);
 uv.x=0;uv.y=phase;lines[3]->rva0015E3E0(uv);
 BfmeVecHF one={1,1,1},zero={0,0,0};((Gen_0094AC70*)lights)->bfmeSetPair(&zero,&one);
 CameraClass*camera=ctx->camera;camera->update();((LightEnvironmentClass*)lights)->Pre_Render_Update(camera->transform);
 RenderInfoClass ri(*ctx->camera);info=&ri;ri.lights=(LightEnvironmentClass*)lights;
 int mode=TheInGameUI->mode;
 if(mode==1||mode==2){
  unsigned selected=TheInGameUI->slot93();
  if(selected){DrawableView*d=TheGameClient->lookup(selected);
   if(d){Rva000E07F4Obj*o=d->object;
    if(o&&((((unsigned char*)o->inner)[0x10D]&0x80)==0) ){Player*local=ThePlayerList->local;if(((Object*)o)->getControllingPlayer()==local){
     Object*adjusted=((Object*)o)->rva002931F5(false);if(adjusted)o=(Rva000E07F4Obj*)adjusted;
     ((Rva000E0123*)this)->rva000E0123(3.0f);((Rva000E0123*)this)->rva000E00C0(1.0f);((Rva000E07F4Host*)this)->rva000E0584(o);((Rva000E0123*)this)->rva000E0123(1.5f);
    }}
   }
  }
 }
 if(mode==1||mode==2){
  terrainLineOpacity=0.8f;
  SelectionNode*i;SelectionList*selected=TheInGameUI->slot73();
  for(i=selected->head->next;i!=selected->head;i=i->next){Rva000E07F4Obj*o=i->drawable->object;((Rva000E0123*)this)->rva000E00C0(1.0f);rva000E07F4(o,(Rva000E07F4Host*)this);}
  if(mode==2){Player*local=ThePlayerList->local;if(local){((Rva000E0123*)this)->rva000E00C0(0.4f);local->iterateObjects((int(*)(Object*,void*))rva000E07F4,this);}}
 }
 info=0;
}
