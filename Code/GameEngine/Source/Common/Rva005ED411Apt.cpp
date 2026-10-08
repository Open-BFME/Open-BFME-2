// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva005ED411@StrategicHUD::RegionAwardMovieClip::Impl@@QAEXXZ @0x005ED411 52B: Apt FadeOut call with level and prefix from +4 and +8 then state 2 at +0x24. Evidence: calls rowed 0x00524EF4 AptCall; caller thunk 0x005ED5EB loads ecx+4; same +4 level and +8 outer layout as StrategicHUD::RegionAwardMovieClip::Impl neighbour; FadeOut literal; empty-string and TheTarget globals.
#include "ascii_string.h"

struct Rva005ED445Inner
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva005ED445Outer
{
	Rva005ED445Inner *m_ptr;
};

class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

namespace StrategicHUD {
class RegionAwardMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::RegionAwardMovieClip::Impl
{
public:
	void rva005ED411();
private:
	int m_pad0;
	int m_level;
	Rva005ED445Outer m_outer;
	char m_padC[0x24 - 0x0C];
	int m_state24;
};

class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

void StrategicHUD::RegionAwardMovieClip::Impl::rva005ED411()
{
	const char *prefix = m_outer.m_ptr ? m_outer.m_ptr->m_name : "";
	Rva00524EF4AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), (void *)m_level, prefix, "FadeOut");
	m_state24 = 2;
}
