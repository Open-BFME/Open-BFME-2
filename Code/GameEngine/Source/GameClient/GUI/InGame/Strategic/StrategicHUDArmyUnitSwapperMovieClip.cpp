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
