#ifndef BFME2_REGION_DETAILS_ARMIES_CLIP_IMPL_VIEW_H
#define BFME2_REGION_DETAILS_ARMIES_CLIP_IMPL_VIEW_H
#include "RegionDetailsArmiesClipOwnerFwd.h"
#include "RegionIconSlotReferenceView.h"
#include "RegionIconSlotResizeView.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include <vector>
class Rva0052413E {
public:Rva0052413E();~Rva0052413E();
private:_STL::vector<AsciiString> names;
};
class Rva005241B0 {
public:Rva005241B0();~Rva005241B0();
private:_STL::vector<AsciiString> names;
};
namespace _STL {template<> vector<Rva005EFD53Element,allocator<Rva005EFD53Element> >::~vector();}
// Native callbacks/caches prove level00, string-buffer name04, slots24,
// cached Unicode string30, counts34/38 and flags3C/3D/3E.
// Native constructor5EF92D proves color08 command-map0C and extern-list18.
// Their lifetimes agree with destructor5EFB05; slots are owned counted handles.
class StrategicHUD::RegionDetailsArmiesMovieClip::Impl {
 public:
 Impl(int,const AsciiString&,unsigned);~Impl();
 void OnRollOverCommandPoints(const char*);void OnRollOutCommandPoints(const char*);void PlayerColor(int,char*,bool);
 void SetIconSlotCount(int);
 void ShowArmyName(const UnicodeString &);
 void HideArmyName();
 void ShowCommandPoints(int,int);
 void HideCommandPoints();
 void Update();
 private:
 unsigned m_level; AsciiString m_name; unsigned m_color;Rva0052413E m_commandMaps;Rva005241B0 m_externHandlers;
 _STL::vector<Rva005EFD53Element,_STL::allocator<Rva005EFD53Element> > slots;
 UnicodeString m_cached30; int m_a,m_b;
 bool m_armyNameShown,m_shown,m_3E;
};
#endif
