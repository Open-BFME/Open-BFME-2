// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicHUD::RegionDetailsStructuresMovieClip (WorldBuilder
// StrategicHUDRegionDetailsStructuresMovieClip.cpp names Impl::Impl).
// Target facts: the owner's ctor 0x005F16F9 (ret 0x10) installs vtable
// 0x00878EFC and builds its Impl (new 0x50) with this and its four
// arguments. The Impl ctor 0x005F141D (ret 0x14, unrowed, pinned) stores
// owner +0x00, level +0x04, the name copy +0x08 and the last word +0x0C,
// builds three name lists, sends SetIconSlotCount with the count and
// reserves and fills that many icon slots. The Impl's callbacks are rowed
// under the address-named view in GameClient/GUI/AptWotrIconSlotCallbacks.cpp.
#include "ascii_string.h"

namespace StrategicHUD {
class RegionDetailsStructuresMovieClip
{
public:
	class Impl;

	RegionDetailsStructuresMovieClip(int level, const AsciiString &name, int iconSlotCount, int arg);
	virtual ~RegionDetailsStructuresMovieClip();

private:
	Impl *m_impl; // +0x04
};
}

class StrategicHUD::RegionDetailsStructuresMovieClip::Impl
{
public:
	Impl(RegionDetailsStructuresMovieClip *owner, int level, const AsciiString &name, int iconSlotCount, int arg); // 0x005F141D (pinned)

private:
	char m_data[0x50];
};

StrategicHUD::RegionDetailsStructuresMovieClip::RegionDetailsStructuresMovieClip(int level, const AsciiString &name, int iconSlotCount, int arg)
	: m_impl(new Impl(this, level, name, iconSlotCount, arg))
{
}
