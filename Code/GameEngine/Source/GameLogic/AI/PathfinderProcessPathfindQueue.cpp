// cl: /ICode/Libraries/Include /ICode/GameEngine/Source/Common /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc
// ?rva002F0F07@Pathfinder@@QAEXXZ (existing pin: callee of GameLogic::update)
// Retail 0x002F0F07..0x002F11A1 (666 bytes), thiscall void. WorldBuilder twin
// 0x00D30070 is Pathfinder::ProcessPathfindQueue (pathfinder.cpp asserts
// 341..387); ZH AIPathfind.cpp processPathfindQueue is the semantic reference.
// Unless the map is not ready it lets the zone manager (pinned 0x00533BEC)
// rebuild zones, recomputes the logical extent from the terrain extent in
// 10-unit cells, then drains the priority queue up to half the cell quota
// (slot +0x234) and the normal queue up to the full quota (slot +0x230)
// under the "pathfind" profile range, with optional QueryPerformanceCounter
// timing that tints slow pathers (rowed 0x002EBD99). The quota is
// GlobalData +0x11E8 cells, times 100 for the first 5 * g_00DBA4E4 frames.
// The cell indices round through BaseType's REAL_TO_INT_FLOOR spelled with
// math.h's inline floorf (as the WB twin's floorf/fast_float2long_round
// parameter stores show); that shape is what places retail's floor-result
// stores and the quota spill.
#include "GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
#include "../../../../Libraries/Source/profile/profile.h"
#include <math.h>
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *);
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(floorf(x)))
struct Region3D {Coord3D lo,hi;};
struct ICoord2D {int x,y;};
struct IRegion2D {ICoord2D lo,hi;};
struct RGBColor00271779;
void Rva002EBD99(Object *,const RGBColor00271779 *);
class Pathfinder;
class AIUpdateInterface {
public:
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
 virtual void slot73();
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
 virtual void slot93();
 virtual void slot94();
 virtual void slot95();
 virtual void slot96();
 virtual void slot97();
 virtual void slot98();
 virtual void slot99();
 virtual void slot100();
 virtual void slot101();
 virtual void slot102();
 virtual void slot103();
 virtual void slot104();
 virtual void slot105();
 virtual void slot106();
 virtual void slot107();
 virtual void slot108();
 virtual void slot109();
 virtual void slot110();
 virtual void slot111();
 virtual void slot112();
 virtual void slot113();
 virtual void slot114();
 virtual void slot115();
 virtual void slot116();
 virtual void slot117();
 virtual void slot118();
 virtual void slot119();
 virtual void slot120();
 virtual void slot121();
 virtual void slot122();
 virtual void slot123();
 virtual void slot124();
 virtual void slot125();
 virtual void slot126();
 virtual void slot127();
 virtual void slot128();
 virtual void slot129();
 virtual void slot130();
 virtual void slot131();
 virtual void slot132();
 virtual void slot133();
 virtual void slot134();
 virtual void slot135();
 virtual void slot136();
 virtual void slot137();
 virtual void slot138();
 virtual void slot139();
 virtual void slot230(Pathfinder *);
 virtual void slot234(Pathfinder *);
};
struct QueueObjectView {char pad00[0x258];AIUpdateInterface *ai;};
class TerrainLogic {
public:
 virtual void slot0();virtual void slot4();virtual void slot8();virtual void slotC();
 virtual void slot10();virtual void slot14();virtual void slot18();virtual void slot1C();
 virtual void getExtent(Region3D *);
};
class GlobalData {public:char pad00[0x11C0];unsigned int limitMs;char pad11C4[0x11E8-0x11C4];int cellsPerFrame;};
class Rva002E713F460 {public:void rva00533BEC(void *,void *,void *);char pad[4];};
class Rva002E713FOwner {public:void rva0052F294();};
class Rva002EAC7CPool {public:void *rva002EAC7C();bool empty()const {return head==tail;}void *items[0x200];int head,tail;};
extern TerrainLogic *TheTerrainLogic;
extern GlobalData *TheWritableGlobalData;
extern GameLogic *TheGameLogic;
extern int g_00DBA4E4;
class Pathfinder {
public:
 void rva002F0F07();
 char pad00[8];bool ready;char pad09[0x10-9];void *map;IRegion2D extent;IRegion2D logicalExtent;
 char pad34[0x3C-0x34];int cumulative,word40,word44;
 char pad48[0x60-0x48];char layers[0x400];Rva002E713F460 zones;
 char pad464[0x1BEB4-0x464];bool flagA,flagB;
 char pad1BEB6[0x1C1E0-0x1BEB6];Rva002EAC7CPool queue;
 Rva002EAC7CPool priorityQueue;
};
void Pathfinder::rva002F0F07()
{
 if(!ready)return;
 if(flagA || flagB) {((Rva002E713FOwner *)this)->rva0052F294();return;}
 zones.rva00533BEC(map,layers,&extent);
 Region3D terrainExtent;TheTerrainLogic->getExtent(&terrainExtent);
 IRegion2D bounds;
 bounds.lo.x=REAL_TO_INT_FLOOR(terrainExtent.lo.x/10.0f);
 bounds.hi.x=REAL_TO_INT_FLOOR(terrainExtent.hi.x/10.0f);
 bounds.lo.y=REAL_TO_INT_FLOOR(terrainExtent.lo.y/10.0f);
 bounds.hi.y=REAL_TO_INT_FLOOR(terrainExtent.hi.y/10.0f);
 --bounds.hi.x;--bounds.hi.y;
 logicalExtent=bounds;
 cumulative=0;word40=0;word44=0;
 int quota=TheWritableGlobalData->cellsPerFrame;
 if(TheGameLogic->getFrame()<(unsigned int)(5*g_00DBA4E4))quota*=100;
 while(cumulative<quota/2 && !priorityQueue.empty()) {
  Object *obj=TheGameLogic->findObjectByID((ObjectID)(int)priorityQueue.rva002EAC7C());
  if(obj) {AIUpdateInterface *ai=((QueueObjectView *)obj)->ai;if(ai)ai->slot234(this);}
 }
 while(cumulative<quota && !queue.empty()) {
  Object *obj=TheGameLogic->findObjectByID((ObjectID)(int)queue.rva002EAC7C());
  if(obj) {
   AIUpdateInterface *ai=((QueueObjectView *)obj)->ai;
   if(ai) {
    __int64 startTime=0,endTime=0,freq=0;
    if(TheWritableGlobalData->limitMs) {QueryPerformanceFrequency(&freq);QueryPerformanceCounter(&startTime);}
    Profile::StartRange("pathfind");
    ai->slot230(this);
    Profile::StopRange("pathfind");
    if(TheWritableGlobalData->limitMs) {
     QueryPerformanceCounter(&endTime);
     double elapsed=(double)(endTime-startTime)*1000.0/(double)freq;
     if(elapsed>=TheWritableGlobalData->limitMs)Rva002EBD99(obj,0);
    }
   }
  }
 }
}
