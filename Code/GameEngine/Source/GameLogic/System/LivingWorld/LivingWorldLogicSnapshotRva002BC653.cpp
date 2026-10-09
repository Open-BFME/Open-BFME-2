// cl: /O1 /G7 /arch:SSE /MD
// Native2BC653..2BC830 RET4 and WBd8b3e0 establish the complete snapshot
// transfer. The original owner/method name remains unknown; native receiver
// is the snapshot view at whole+0C. Target establishes all accessed fields,
// ID transfer roles90..A0 and versions1/6,5,6,2; WB is the structural guide.
// Recompute the whole receiver at each use: a long-lived parent local adds
// an early EBX save that retail lacks. Canonical globals and their providers
// are reused; three first-name in-image pins describe opaque native methods
// with proven Xfer/no-argument ABIs, not reconstructed callee progress.
struct Version {unsigned char minimum,current;Version(unsigned char a,unsigned char b):minimum(a),current(b){}};
class Xfer {public:
virtual void s0();
virtual bool IsLoading() const;
virtual void s2();
virtual bool IsCRC() const;
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void xferVersion(Version*);
virtual void s11();
virtual void xferSnapshot(void*);
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void xferInt(int*);
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void xferBool(bool*);
virtual void s37();
};
void XferLivingWorldArmyID(Xfer*,int*);
class Rva004E075FObj;int Rva004E075FGet(Rva004E075FObj*,int);
void XferLivingWorldBuildPlotID(Xfer*,void*);
void Rva004E12D7Parse(void*,void*);
void XferLivingWorldPlayerID(Xfer*,int*);
class BfmeSelectionState{public:bool isSelectionLocked()const;};
class Rva002BBA45{public:void rva002BBA45(Xfer*);};
class Rva002BB5DD{public:void rva002BB5DD(Xfer*);};
class Rva002B7C74{public:void rva002B7C74();};
class Glo012F1028Type{public:void rva002B7D03();};
class Rva002B6AA2{public:void rva002B6AA2();};
class Rva002BED10{public:void rva002BED10();};
class Rva002D3627Host;extern Rva002D3627Host*g_00DFEF18;
class Rva00E02D6C;extern Rva00E02D6C*TheCampaignManager;
class LivingWorldManager;extern LivingWorldManager*TheLivingWorldManager;
#include "../../../Common/GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
class Rva002BBBE7{public:void rva002BC39D();};extern unsigned g_Va00E04544;
class RvaSnapshotView {public:virtual void s0();virtual void s1();virtual void s2();virtual void transfer(Xfer*);};
class RvaSnapshotResetView {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void reset(int);
};
class Rva002BC653Snapshot {public:void rva002BC653(Xfer*);
 char unknown00[0x90];int army90,building94,plot98,spawn9C,playerA0;RvaSnapshotView*otherA4;bool enabledA8,flagA9;char unknownAA[0xBD-0xAA];bool loadEnabledBD;char unknownBE[0xF0-0xBE];int counterF0;
};
void Rva002BC653Snapshot::rva002BC653(Xfer*xfer){
 if(xfer->IsCRC()){
  if(!enabledA8 || !((BfmeSelectionState*)((char*)this-12))->isSelectionLocked())return;
 }
 Version version(1,6);
 xfer->xferVersion(&version);
 XferLivingWorldArmyID(xfer,&army90);
 Rva004E075FGet((Rva004E075FObj*)xfer,(int)&building94);
 XferLivingWorldBuildPlotID(xfer,&plot98);
 Rva004E12D7Parse(xfer,&spawn9C);
 if(version.current>=5)XferLivingWorldPlayerID(xfer,&playerA0);
 if(xfer->IsLoading()){
  xfer->xferBool(&loadEnabledBD);
  if(!loadEnabledBD){((Rva002BED10*)g_00DFEF18)->rva002BED10();return;}
  ((Rva002BED10*)g_00DFEF18)->rva002BED10();
  ((Rva002BBA45*)((BfmeSelectionState*)((char*)this-12)))->rva002BBA45(xfer);
 }else{
  loadEnabledBD=enabledA8;
  xfer->xferBool(&loadEnabledBD);
  if(!loadEnabledBD)return;
  ((Rva002BB5DD*)((BfmeSelectionState*)((char*)this-12)))->rva002BB5DD(xfer);
 }
 ((RvaSnapshotView*)((char*)TheCampaignManager+12))->transfer(xfer);
 xfer->xferBool(&flagA9);
 if(xfer->IsLoading()){
  ((Rva002BBBE7*)&g_Va00E04544)->rva002BC39D();
  if(flagA9)((Glo012F1028Type*)((BfmeSelectionState*)((char*)this-12)))->rva002B7D03();
  else ((Rva002B7C74*)((BfmeSelectionState*)((char*)this-12)))->rva002B7C74();
 }
 otherA4->transfer(xfer);
 TheGameLogic->rva0023CFE4(xfer);
 if(!xfer->IsCRC()){
  ((RvaSnapshotView*)((char*)TheLivingWorldManager+12))->transfer(xfer);
  if(version.current>=6)xfer->xferSnapshot(g_00DFEF18);
 }
 if(xfer->IsLoading()){
  if(((BfmeSelectionState*)((char*)this-12))->isSelectionLocked())((Rva002B6AA2*)((BfmeSelectionState*)((char*)this-12)))->rva002B6AA2();
  else ((RvaSnapshotResetView*)g_00DFEF18)->reset(0);
 }
 if(version.current>=2)xfer->xferInt(&counterF0);
 else if(xfer->IsLoading())counterF0=0;
}
