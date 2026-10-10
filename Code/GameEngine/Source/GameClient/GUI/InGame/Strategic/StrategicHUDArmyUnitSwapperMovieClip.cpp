// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// WB wrappers1641D30/1641DF0 call named Impl SetRegionName/SetArmyName.
// Their native8B tail calls independently identify FD978/FD9BB. Retail
// FD978..FD9BB fixes the whole67B, slot stride24/base1C, comparison/cache08,
// RegionName literal and existing SetSlotString/string providers. Unknown
// fields and cached string meanings retain structural names.
#include "unicode_string.h"
namespace StrategicHUD {class ArmyUnitSwapperMovieClip {public: class Impl;};}
struct ArmySwapSlot {char unknown[8];UnicodeString cache08,cache0C;int commandPoints,maxCommandPoints;};
class StrategicHUD::ArmyUnitSwapperMovieClip::Impl {
public:
 char unknown[0x1C];ArmySwapSlot slots[1];
 void SetSlotString(int,const char*,const UnicodeString&);
 void SetRegionName(int,const UnicodeString&);
 void SetArmyName(int,const UnicodeString&);
};
void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::SetRegionName(int index,const UnicodeString& text)
{
 ArmySwapSlot *slot=&slots[index];
 if(text.compare(slot->cache08)==0)return;
 SetSlotString(index,"RegionName",text);
 slot->cache08.set(text);
}

void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::SetArmyName(int index,const UnicodeString& text)
{
 ArmySwapSlot *slot=&slots[index];
 if(text.compare(slot->cache0C)==0)return;
 SetSlotString(index,"ArmyName",text);
 // Retail compares cache0C but writes cache08; preserve both measured offsets.
 slot->cache08.set(text);
}

// The forwarding owner retains the established FD956 address-derived view.
// WB1641D30 accesses its Impl binding; native FDA0D is the full8B this+4
// dereference and direct tail call to the verified67B region-name setter.
struct Rva005FD956 {
 char m_pad0[4];StrategicHUD::ArmyUnitSwapperMovieClip::Impl *m_p4;
 void rva005FD956(int,int,int);
 void rva005FDA0D(int,const UnicodeString&);
 void rva005FDA15(int,const UnicodeString&);
};
void Rva005FD956::rva005FDA0D(int index,const UnicodeString& text)
{m_p4->SetRegionName(index,text);}

// WB1641DF0 and native FDA15..FDA1D: full8B child-pointer forwarding.
void Rva005FD956::rva005FDA15(int index,const UnicodeString& text)
{m_p4->SetArmyName(index,text);}
