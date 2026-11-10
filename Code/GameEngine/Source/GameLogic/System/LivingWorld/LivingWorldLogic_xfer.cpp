// cl: /O1 /G7 /arch:SSE /MD /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
// Native2BC653..2BC830 RET4 and WBd8b3e0 establish the complete snapshot
// transfer. The name slot identifies LivingWorldLogic; its native receiver
// is the Snapshot view at whole+0C. Target establishes all accessed fields,
// ID transfer roles90..A0 and versions1/6,5,6,2; WB is the structural guide.
// Recompute the whole receiver at each use: a long-lived parent local adds
// an early EBX save that retail lacks. Canonical globals and their providers
// are reused; three first-name in-image pins describe opaque native methods
// with proven Xfer/no-argument ABIs, not reconstructed callee progress.
struct Version {unsigned char minimum,current;Version(unsigned char a,unsigned char b):minimum(a),current(b){}};
class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"
void XferLivingWorldArmyID(Xfer*,int*);
class Rva004E075FObj;int Rva004E075FGet(Rva004E075FObj*,int);
void XferLivingWorldBuildPlotID(Xfer*,void*);
void Rva004E12D7Parse(void*,void*);
void XferLivingWorldPlayerID(Xfer*,int*);
#include "../../../../Include/Common/BfmeSelectionState.h"
class Rva002BBA45{public:unsigned int rva002BBA45(Xfer*);};
class Rva002BB5DD{public:void rva002BB5DD(Xfer*);};
#include "../../../../Include/Common/Rva002B7C74.h"
class Glo012F1028Type{public:void rva002B7D03();};
class Rva002B6AA2{public:void rva002B6AA2();};
#include "../../../../Include/Common/Rva002BED10.h"
class Rva002D3627Host;class LivingWorld; extern LivingWorld *TheLivingWorld;
class Rva00E02D6C;extern Rva00E02D6C*TheCampaignManager;
class LivingWorldManager;extern LivingWorldManager*TheLivingWorldManager;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
class Rva002BBBE7{public:void rva002BC39D();};extern unsigned g_Va00E04544;
class RvaSnapshotView {public:virtual void s0();virtual void s1();virtual void s2();virtual void transfer(Xfer*);};
class RvaSnapshotResetView {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void reset(int);
};
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../../Include/GameLogic/LivingWorldLogic.h"
#include "../../../../Include/GameLogic/LivingWorldRegionManager.h"
void LivingWorldLogic::xfer(Xfer*xfer){
 if(xfer->IsCRC()){
  if(!fieldB4 || !((BfmeSelectionState*)((char*)this))->isSelectionLocked())return;
 }
 Version version(1,6);
 (*xfer == reinterpret_cast<Xfer::Version &>(version));
 XferLivingWorldArmyID(xfer,&field9C);
 Rva004E075FGet((Rva004E075FObj*)xfer,(int)&fieldA0);
 XferLivingWorldBuildPlotID(xfer,&fieldA4);
 Rva004E12D7Parse(xfer,&fieldA8);
 if(version.current>=5)XferLivingWorldPlayerID(xfer,&fieldAC);
 if(xfer->IsLoading()){
  (*xfer == fieldC9);
  if(!fieldC9){((Rva002BED10*)((Rva002D3627Host *)TheLivingWorld))->rva002BED10();return;}
  ((Rva002BED10*)((Rva002D3627Host *)TheLivingWorld))->rva002BED10();
  ((Rva002BBA45*)((BfmeSelectionState*)((char*)this)))->rva002BBA45(xfer);
 }else{
  fieldC9=fieldB4;
  (*xfer == fieldC9);
  if(!fieldC9)return;
  ((Rva002BB5DD*)((BfmeSelectionState*)((char*)this)))->rva002BB5DD(xfer);
 }
 ((RvaSnapshotView*)((char*)TheCampaignManager+12))->transfer(xfer);
 (*xfer == fieldB5);
 if(xfer->IsLoading()){
  ((Rva002BBBE7*)&g_Va00E04544)->rva002BC39D();
  if(fieldB5)((Glo012F1028Type*)((BfmeSelectionState*)((char*)this)))->rva002B7D03();
  else ((Rva002B7C74*)((BfmeSelectionState*)((char*)this)))->rva002B7C74();
 }
 fieldB0->xfer(xfer);
 TheGameLogic->rva0023CFE4(xfer);
 if(!xfer->IsCRC()){
  ((RvaSnapshotView*)((char*)TheLivingWorldManager+12))->transfer(xfer);
  if(version.current>=6)(*xfer == *reinterpret_cast<Snapshot *>((Rva002D3627Host *)TheLivingWorld));
 }
 if(xfer->IsLoading()){
  if(((BfmeSelectionState*)((char*)this))->isSelectionLocked())((Rva002B6AA2*)((BfmeSelectionState*)((char*)this)))->rva002B6AA2();
  else ((RvaSnapshotResetView*)((Rva002D3627Host *)TheLivingWorld))->reset(0);
 }
 if(version.current>=2)(*xfer == fieldFC);
 else if(xfer->IsLoading())fieldFC=0;
}
