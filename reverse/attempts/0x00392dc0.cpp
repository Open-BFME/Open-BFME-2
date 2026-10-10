// ?rva00392DC0@BuildAssistant@@QAE_NPAVObject@@PBVThingTemplate@@PBUCoord3D@@PAVPlayer@@IPAPAV2@@Z
// partial score=0.8931489049261417 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /I.
// Bank: complete native392DC0..39321C RET24; six words and low-byte result.
// ZH BuildAssistant line-building and BF1@575ba2b supply subsystem purpose;
// target bytes establish the BF2 tile/rebuild and object-ID adjacency work.
// Native24B tile plan: count0,cost4,array8,flagsC/D,status10,objectID14;
// existing39205C cleanup and392CC5/CF9/D1D/D49/D71 bodies prove this ABI.
// Query625340 consumes position/radius/distance and returns Object*, now
// corrected in its provider with exact30B and all21 source rows passing.
// REQUIRED canonical PartitionRangeQueryCallView.h declaration:
// Object *rva00625340(const Coord3D*,float,int);
// Adding this declaration currently swaps two spill homes in guard369FDF;
// its full1034 is exact with the previous header. This blocker is retained,
// not bypassed by a private new PartitionManager view or a pin/ABI adapter.
// Body residue: iterator temporary and sentinel reload scheduling, index
// liveness around nested virtual calls, output argument/register homes.
// stlport
#include <list>
namespace _STL {
template<> list<int>::iterator list<int>::insert(list<int>::iterator,const int&);
template<class T,class Traits> static inline bool operator!=(const _List_iterator<T,Traits>&a,const _List_iterator<T,Traits>&b){return a._M_node!=b._M_node;}
}
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
class Player; class ThingTemplate;
struct Rva0039BAD2Input;class Rva0039B795;
class Rva003B0D7C {public:unsigned rva003B0CB3(unsigned,Rva0039B795*,bool);};
class Rva0039BAD2 {public:void rva0039BAD2(Rva0039BAD2Input*,int);};
struct NativeBuildPlayerView {char head[0x94];unsigned money;};
struct NativeBuildTemplateView {char head[0x11B];unsigned char flag11B;char rest[0xC8-0x11C+0x100];};
struct NativeBuildRadiusView {char head[0xC8];float radius;};
class ThingTemplate {public:bool isEquivalentTo(const ThingTemplate*)const;int rva0033A69A(const Player*,int,int)const;};
class Rva004D9A3C;
class Rva0039205C {public:
 unsigned count,cost;Rva004D9A3C *array;bool flagC,flagD;short padE;int status;ObjectID objectID;
 Rva0039205C(){status=-1;count=0;array=0;flagC=false;flagD=false;cost=0;objectID=INVALID_OBJECT_ID;}
 ~Rva0039205C();
 void *rva00392CC5(unsigned);Rva004D9A3C *rva00392CF9(unsigned);float rva00392D1D(unsigned);unsigned char rva00392D49(unsigned);int rva00392D71(int);
};
class NativeBuildBehavior {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4(int);
 virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual int s14();virtual void s15();virtual void s16();virtual void s17(int);virtual void s18(Object*);
};
class NativeBuildBody {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual float s4(bool);
 virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();virtual void s20();virtual void s21();virtual void s22();virtual void s23();virtual void s24();virtual void s25();virtual void s26();virtual void s27();virtual void s28();virtual void s29();virtual void s30();virtual void s31();virtual void s32(float);
};
class Drawable {public:void fadeIn(unsigned);};
enum ObjectStatusTypes {NATIVE_STATUS2=2,NATIVE_STATUS57=0x57};
class Object {public:void *rva0028BD17()const;void rva0028AFE7(Object*);void teleportTo(const Coord3D*,bool);void setStatus(ObjectStatusTypes,bool);};
class Rva00293330 {public:void *rva00293330(unsigned);};
class Thing {public:Drawable *getDrawable()const;};
struct NativeBuildObjectView {char head[4];const ThingTemplate *thing;char head8[0x74-8];int id;char pad78[0x254-0x78];NativeBuildBody *body;char pad258[0x280-0x258];float construction;char pad284[0x324-0x284];float cost;char pad328[0x438-0x328];unsigned char dead;};
class Rva001E4912 {public:Rva001E4912 *rva001E4912(int,unsigned,unsigned);int bits[19];};
class Rva001E431E {public:void rva001E431E(const int*);};
extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
class BuildAssistant {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();
 virtual Object *buildObjectNow(Object*,const ThingTemplate*,const Coord3D*,float,Player*);
 virtual void s15();virtual void s16();virtual void s17();virtual void s18();virtual void s19();
 virtual bool fillNativeTiles(Rva0039205C*,Object*,const ThingTemplate*,const Coord3D*,unsigned);
 bool rva00392DC0(Object*,const ThingTemplate*,const Coord3D*,Player*,unsigned,Object**);
};
bool BuildAssistant::rva00392DC0(Object *builder,const ThingTemplate *what,const Coord3D *pos,Player *player,unsigned kind,Object **result) {
 if(!builder||!what||!pos||!player)return false;
 Rva0039205C tiles;
 if(!fillNativeTiles(&tiles,builder,what,pos,kind))return false;
 if(tiles.status!=0&&tiles.status!=10)return false;
 if(((NativeBuildPlayerView*)player)->money<tiles.cost)return false;
 std::list<int> created;
 for(unsigned i=0;i<tiles.count;++i) {
  if(tiles.rva00392D71(i)==10) {
   float radius=tiles.rva00392CC5(i)?((NativeBuildRadiusView*)tiles.rva00392CC5(i))->radius:20.0f;
   Object *old=ThePartitionManager->rva00625340((const Coord3D*)tiles.rva00392CF9(i),radius*0.25f,1);
   if(old && (((NativeBuildObjectView*)old)->dead&1)) {
    const ThingTemplate *oldTemplate=((NativeBuildObjectView*)old)->thing;
    if(oldTemplate->isEquivalentTo((const ThingTemplate*)tiles.rva00392CC5(i))) {
     NativeBuildBehavior *behavior=(NativeBuildBehavior*)old->rva0028BD17();if(behavior)behavior->s4(0);
    }
   }
  } else {
   Object *made=buildObjectNow(builder,(const ThingTemplate*)tiles.rva00392CC5(i),(const Coord3D*)tiles.rva00392CF9(i),tiles.rva00392D1D(i),player);
   if(!made)continue;
   int id=((NativeBuildObjectView*)made)->id;
   created.push_back(id);
   made->rva0028AFE7(builder);
   if(tiles.rva00392D49(i))made->teleportTo((const Coord3D*)tiles.rva00392CF9(i),false);
   NativeBuildBody *body=((NativeBuildObjectView*)made)->body;if(body)body->s32(1.0f-body->s4(false));
   NativeBuildBehavior *behavior=(NativeBuildBehavior*)made->rva0028BD17();
   NativeBuildBehavior *producer=(NativeBuildBehavior*)((Rva00293330*)builder)->rva00293330(kind);
   if(behavior&&producer&&!(((NativeBuildTemplateView*)((NativeBuildObjectView*)made)->thing)->flag11B&0x10)&&tiles.status!=10)behavior->s17(producer->s14()*i);
   ((NativeBuildObjectView*)made)->construction=0.0f;
   made->setStatus(NATIVE_STATUS57,false);made->setStatus(NATIVE_STATUS2,true);
   Rva001E4912 mask;((Rva001E431E*)made)->rva001E431E((const int*)mask.rva001E4912(0,0x44,0x45));
   if(((Thing*)made)->getDrawable())((Thing*)made)->getDrawable()->fadeIn(0x8A);
   if(result&&(((NativeBuildTemplateView*)((NativeBuildObjectView*)made)->thing)->flag11B&0x10))*result=made;
   const ThingTemplate *tile=(const ThingTemplate*)tiles.rva00392CC5(i);
   if(tile)((NativeBuildObjectView*)made)->cost=(float)(unsigned)tile->rva0033A69A(player,(int)builder,-1);
  }
 }
 Object *parent=TheGameLogic->findObjectByID(tiles.objectID);
 if(parent) {
  NativeBuildBehavior *behavior=(NativeBuildBehavior*)parent->rva0028BD17();if(behavior)behavior->s18(builder);
  NativeBuildBehavior *producer=(NativeBuildBehavior*)builder->rva0028BD17();if(producer)producer->s18(parent);
  for(std::list<int>::iterator it=created.begin();it!=created.end();++it) {
   Object *child=TheGameLogic->findObjectByID((ObjectID)*it);if(child&&producer)producer->s18(child);
  }
 }
 for(std::list<int>::iterator it=created.begin();it!=created.end();++it) {
  Object *made=TheGameLogic->findObjectByID((ObjectID)*it);if(!made)continue;
  NativeBuildBehavior *behavior=(NativeBuildBehavior*)made->rva0028BD17();
  if(behavior) {
   if(parent)behavior->s18(parent);
   behavior->s18(builder);
   for(std::list<int>::iterator jt=created.begin();jt!=created.end();++jt) {Object *other=TheGameLogic->findObjectByID((ObjectID)*jt);if(other)behavior->s18(other);}
  }
  NativeBuildBehavior *producer=(NativeBuildBehavior*)builder->rva0028BD17();if(producer)producer->s18(made);
 }
 ((Rva003B0D7C*)((char*)player+0x90))->rva003B0CB3(tiles.cost,(Rva0039B795*)((char*)player+0x3BC),true);
 ((Rva0039BAD2*)((char*)player+0x3BC))->rva0039BAD2((Rva0039BAD2Input*)tiles.rva00392CC5(0),tiles.cost);
 return true;
}
