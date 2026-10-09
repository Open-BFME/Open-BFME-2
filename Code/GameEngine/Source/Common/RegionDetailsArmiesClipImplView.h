#ifndef BFME2_REGION_DETAILS_ARMIES_CLIP_IMPL_VIEW_H
#define BFME2_REGION_DETAILS_ARMIES_CLIP_IMPL_VIEW_H
#include "RegionDetailsArmiesClipOwnerFwd.h"
#include "RegionIconSlotReferenceView.h"
#include "RegionIconSlotResizeView.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
// Native callbacks/caches prove level00, string-buffer name04, slots24,
// cached Unicode string30, counts34/38 and flags3C/3D/3E. Unobserved08..23
// bytes remain opaque; no constructor or ownership is asserted for that span.
class StrategicHUD::RegionDetailsArmiesMovieClip::Impl {
 public:
 void SetIconSlotCount(int);
 void ShowArmyName(const UnicodeString &);
 void HideArmyName();
 void ShowCommandPoints(int,int);
 void HideCommandPoints();
 void Update();
 private:
 unsigned m_level; AsciiString m_name; char m_unknown08[0x1C];
 _STL::vector<Rva005EFD53Element,_STL::allocator<Rva005EFD53Element> > slots;
 UnicodeString m_cached30; int m_a,m_b;
 bool m_armyNameShown,m_shown,m_3E; char m_unknown3F;
};
#endif
