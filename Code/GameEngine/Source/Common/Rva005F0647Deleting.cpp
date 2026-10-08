// ?rva005F0647@Rva005F0647@@QAEPAXI@Z @0x005F0647 37B.
// Deleting-dtor shape: releases holder target via rowed fastcall Release at 0x0007DEEF
// then conditionally deletes this when flag bit0 is set and returns this.
// Unblocks 0x005F0C39. TU-local honest-address views.
// cl: /Ireference/shims/bfme2_ascii /MD
struct TargetRef00217D4C { virtual void *destroy(unsigned int); int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
void operator delete(void *);
struct Rva005F0647Holder { char pad[4]; TargetRef00217D4C target; };
struct Rva005F0647 { Rva005F0647Holder *holder; void *rva005F0647(unsigned int); };
void *Rva005F0647::rva005F0647(unsigned int flags)
{
    if (holder)
        ReleaseTreeHintRef00217D4C(&holder->target);
    if (flags & 1)
        ::operator delete(this);
    return this;
}

void Rva005F0C39Destroy(Rva005F0647 *begin, Rva005F0647 *end)
{
    for (; begin != end; ++begin)
        begin->rva005F0647(0);
}

#include "unicode_string.h"

struct RGBColor { float red, green, blue; };

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width) throw();
};
extern Mouse *TheMouse;

class GameTextInterface
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38();
	virtual UnicodeString fetch(const char *label, bool *exists = 0) throw();
};
extern GameTextInterface *TheGameText;


struct Rva005F06EF
{
	char m_pad[0x2D];
	bool m_flag;
	void rva005F06EF();
};

void Rva005F06EF::rva005F06EF()
{
	if (m_flag)
		TheMouse->rva001EEA6D(TheGameText->fetch("STRATEGICHUD:ConstructionTurnsRemainingTooltip"), -1, 0, 1.0f);
}

struct Rva005F09BC
{
	char m_pad[0x34];
	Rva005F06EF **m_begin;
	Rva005F06EF **m_end;
	void rva005F09BC();
};

void Rva005F09BC::rva005F09BC()
{
	Rva005F06EF **begin = m_begin;
	Rva005F06EF **end = m_end;
	for (; begin != end; ++begin)
		(*begin)->rva005F06EF();
}

// ?rva005F0832@Rva005F0832@@QAEXXZ @0x005F0832 60B.
// Hides building-name Apt when flag set: prefix from holder+8 or empty fallback
// g_Rva0107301CEmptyString, AptCall via rowed 0x005FB5E6 with "SetBuildingNameState"
// "_hide" and TheRva00222A8BTarget, then clears flag. Evidence: retail ternary
// plus pushes plus add esp 0x14, caller 0x005F09D7 mov ecx [ecx+4] jmp here.
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *func, const char *a0);
struct Rva005F0832NameHolder
{
	char m_pad[8];
	char m_name[1];
};
// StrategicHUD::RegionDetailsStructuresMovieClip::Impl::HideBuildingName
// (WorldBuilder name, StrategicHUDRegionDetailsStructuresMovieClip.cpp: the
// SetBuildingNameState _hide pair of ShowBuildingName on the same +0x4C flag).
namespace StrategicHUD
{
class RegionDetailsStructuresMovieClip
{
public:
	class Impl;
};
}
class StrategicHUD::RegionDetailsStructuresMovieClip::Impl
{
public:
	char m_pad0[4];
	void *m_level;
	Rva005F0832NameHolder *m_holder;
	char m_pad1[0x4C - 0xC];
	bool m_flag;
	void HideBuildingName();
};

void StrategicHUD::RegionDetailsStructuresMovieClip::Impl::HideBuildingName()
{
	if (m_flag)
	{
		const char *prefix = m_holder ? m_holder->m_name : "";
		Rva005FB5E6AptCall((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_level, prefix, "SetBuildingNameState", "_hide");
		m_flag = false;
	}
}

// ?rva005F09D7@Rva005F09D7@@QAEXXZ @0x005F09D7 8B.
// Forwarder loads Rva005F0832 at +4 and tail-jmps to its rva005F0832.
// Evidence: retail mov ecx [ecx+4] jmp 0x005F0832 plus caller 0x005E24FB same-this call.
struct Rva005F09D7
{
	char m_pad[4];
	StrategicHUD::RegionDetailsStructuresMovieClip::Impl *m_target;
	void rva005F09D7();
};

void Rva005F09D7::rva005F09D7()
{
	return m_target->HideBuildingName();
}

// ?rva005F09F7@Rva005F09F7@@QAEXXZ @0x005F09F7 8B.
// Forwarder loads Rva005F09BC at +4 and tail-jmps to its rva005F09BC.
// Evidence: retail mov ecx [ecx+4] jmp 0x005F09BC plus caller 0x005E257B same-this call.
struct Rva005F09F7
{
	char m_pad[4];
	Rva005F09BC *m_target;
	void rva005F09F7();
};

void Rva005F09F7::rva005F09F7()
{
	return m_target->rva005F09BC();
}

// ?rva005F09EF@Rva005F09EF@@QAEXPBVImage@@@Z @0x005F09EF 8B.
// Forwarder loads Rva005F08C4 at +4 and tail-jmps to its rva005F0940.
// Evidence: retail mov ecx [ecx+4] jmp 0x005F0940 plus caller 0x005E2C7D push eax same-this call.
class Image;
class Rva005F08C4
{
public:
	void rva005F08C4(const Image *image);
	void rva005F0940(const Image *image);
};
struct Rva005F09EF
{
	char m_pad[4];
	Rva005F08C4 *m_target;
	void rva005F09EF(const Image *image);
};

void Rva005F09EF::rva005F09EF(const Image *image)
{
	return m_target->rva005F0940(image);
}

// Forwarders at 0x005F09DF and 0x005F09E7 load their target from +4 and
// tail-jump. The wrapper owners are address-named; only the target method
// identities are established by the respective jump destinations.
class Rva005F086E
{
public:
	void rva005F086E(bool flag);
};

struct Rva005F09DF
{
	char m_pad[4];
	Rva005F086E *m_target;
	void rva005F09DF(bool flag);
};

void Rva005F09DF::rva005F09DF(bool flag)
{
	return m_target->rva005F086E(flag);
}

struct Rva005F09E7
{
	char m_pad[4];
	Rva005F08C4 *m_target;
	void rva005F09E7(const Image *image);
};

void Rva005F09E7::rva005F09E7(const Image *image)
{
	return m_target->rva005F08C4(image);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva005F0C39Destroy@@YAXPAURva005F0647@@0PA_N@Z=?Rva005F0C39Destroy@@YAXPAURva005F0647@@0@Z")
