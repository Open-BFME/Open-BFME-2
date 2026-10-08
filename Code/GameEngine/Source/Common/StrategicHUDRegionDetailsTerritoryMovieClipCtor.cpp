// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// The matched owner constructor's unrecovered implementation constructor and
// virtual destructor remain link dependencies of this unit. Keep those
// dependencies separate from AptImageKeySetters.cpp's verified setters.
#include "ascii_string.h"

namespace StrategicHUD {
class RegionDetailsTerritoryMovieClip
{
public:
	class Impl;
	RegionDetailsTerritoryMovieClip(unsigned int level, const AsciiString &name);
	virtual ~RegionDetailsTerritoryMovieClip();
private:
	Impl *m_impl; // +0x04
};
}

class StrategicHUD::RegionDetailsTerritoryMovieClip::Impl
{
public:
	Impl(unsigned int level, const AsciiString &name); // 0x005F1DB0 (pinned)
private:
	char m_storage[0x48]; // allocation size proven by the owner constructor
};

// ??0RegionDetailsTerritoryMovieClip@StrategicHUD@@QAE@IABVAsciiString@@@Z
// @0x005F207C (73B, ret 8): vtable 0x00879138; new 0x48 bytes, then
// WorldBuilder-named Impl::Impl at 0x005F1DB0 from level and name into +0x04.
StrategicHUD::RegionDetailsTerritoryMovieClip::RegionDetailsTerritoryMovieClip(unsigned int level, const AsciiString &name)
	: m_impl(new Impl(level, name))
{
}
