// ?InitMovieClipSlot@Impl@ArmyUnitSwapperDialog@StrategicInGameUI@@QAEXABUArmySwapSlotInput@@@Z
// partial score=0.9257311217808817 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
#include "unicode_string.h"
class Rva00318C32Ret;
class Rva00318C79Owner {public:Rva00318C32Ret *rva00318C32();};
class Rva0020E89C {public:UnicodeString rva0020E89C();};
class Rva00318FBE {public:int rva00318FBE();};
int GetMaxCommandPoints(void*);
struct Rva005FD956 {char pad[4];void *inner;
 void rva005FD956(int,int,int);void rva005FDA0D(int,const UnicodeString&);void rva005FDA15(int,const UnicodeString&);};
struct ArmySwapSlotInput {char unknown[12];int index;Rva00318C79Owner *army;};
namespace StrategicInGameUI {
UnicodeString GetDisplayName(void*);
class ArmyUnitSwapperDialog {public:class Impl;};
class ArmyUnitSwapperDialog::Impl {public:char unknown[0x14];Rva005FD956 *movieClip;void InitMovieClipSlot(const ArmySwapSlotInput&);};
void ArmyUnitSwapperDialog::Impl::InitMovieClipSlot(const ArmySwapSlotInput& input)
{
 Rva00318C79Owner *army=input.army;int index=input.index;
 Rva00318C32Ret *region=army->rva00318C32();
 if(region)movieClip->rva005FDA0D(index,((Rva0020E89C*)region)->rva0020E89C());
 movieClip->rva005FDA15(index,GetDisplayName(army));
 Rva005FD956 *pointsClip=movieClip;
 pointsClip->rva005FD956(index,((Rva00318FBE*)army)->rva00318FBE(),GetMaxCommandPoints(army));
}
}
