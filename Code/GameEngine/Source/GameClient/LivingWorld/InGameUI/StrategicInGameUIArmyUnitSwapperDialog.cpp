// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// Native 0x005F4BB4..0x005F4C52 is the complete 158-byte slot refresh.
// WorldBuilder 0x01629020 names ArmyUnitSwapperDialog::Impl::InitMovieClipSlot
// in StrategicInGameUIArmyUnitSwapperDialog.cpp:486. Keep the existing owner
// and parameter symbols: callback 0x005F4EED passes its two 0x34-byte handlers.
// Handler +0xC is the slot index and +0x10 the army; Impl +0x14 is its bound
// movie clip. WB 0x01629700 identifies the inline strict-pointer accessor.
// Loading the index before getRegion, together with that visible accessor,
// reproduces army=EBX/index=EDI and kills the handler before the region call.
// Both UnicodeString temporary lifetimes follow the two-state retail EH map.
#include "unicode_string.h"
class Rva00318C32Ret;
#include "../../../../Include/GameLogic/Rva00318C79Owner.h"
class Rva0020E89C {public:UnicodeString rva0020E89C();};
#include "../../../../Include/GameClient/Rva00318FBE.h"
int GetMaxCommandPoints(void*);
struct Rva005FD956 {char pad[4];void *inner;
 void setCommandPoints(int,int,int);void rva005FDA0D(int,const UnicodeString&);void rva005FDA15(int,const UnicodeString&);};
class Rva005F501E {public:char unknown[12];int index;Rva00318C79Owner *army;char tail[0x20];};
namespace StrategicInGameUI {UnicodeString GetDisplayName(void*);}
template<class T> struct Rva005FBoundPointer { T *p; T *operator->()const {return p;} T *get()const{return p;} };
class Rva005F54DA {public:char unknown[0x14];Rva005FBoundPointer<Rva005FD956> movieClip;void rva005F4BB4(Rva005F501E*);};
void Rva005F54DA::rva005F4BB4(Rva005F501E* input)
{
 int index=input->index;
 Rva00318C79Owner *army=input->army;
 Rva00318C32Ret *region=army->rva00318C32();
 if(region)movieClip->rva005FDA0D(index,((Rva0020E89C*)region)->rva0020E89C());
 movieClip->rva005FDA15(index,StrategicInGameUI::GetDisplayName(army));
 Rva005FD956 *pointsClip=movieClip.get();
 pointsClip->setCommandPoints(index,((Rva00318FBE*)army)->rva00318FBE(),GetMaxCommandPoints(army));
}
