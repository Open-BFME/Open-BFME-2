// ?Rva005FD978@Impl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEXHABVUnicodeString@@@Z
// partial score=0.95 date=2026-10-09
// ?Rva005FD978@Impl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEXHABVUnicodeString@@@Z
// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /G7 /arch:SSE /MD /EHsc
// Target5FD978..5FD9BB calls existing SetSlotString with RegionName only
// when the supplied text differs from slot+8, then shares that text.
// Slot24 and prefix1C agree with the matched SetSlotString home view.
// Native computes slot address then member address; compiler merges them,
// giving64B instead of67B. Method spelling remains structural.
#include "unicode_string.h"
struct Rva005FD978Slot {
 char prefix[8]; UnicodeString regionName; UnicodeString unitName; int a,b;
};
namespace StrategicHUD {
class ArmyUnitSwapperMovieClip {public:class Impl;};
class ArmyUnitSwapperMovieClip::Impl {
public:
 void SetSlotString(int,const char*,const UnicodeString&);
 void Rva005FD978(int,const UnicodeString&);
private:char prefix[0x1c];Rva005FD978Slot slots[2];
};
void ArmyUnitSwapperMovieClip::Impl::Rva005FD978(int index,const UnicodeString&text){
 UnicodeString &stored=slots[index].regionName;
 if(text.compare(stored)!=0){SetSlotString(index,"RegionName",text);stored.set(text);}
}
}
