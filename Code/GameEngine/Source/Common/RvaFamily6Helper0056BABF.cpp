// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ?Helper0056BABF@@YA?AURvaF6Ret@@H@Z @0x0056BABF 205B
// Free helper returning counted InGameSimpleHelp from army pointer at +0x78:
// null army returns null handle, else title from GetArmySummaryName and text
// from Rva00220E30 into 12-byte help object. Evidence: callers 0x003FE078
// 0x005773CD 0x005E193E, LINK BONUS name, callees GetArmySummaryName
// InGameSimpleHelp ctor releaseBuffer, siblings ArmySummaryHelpSource
// StrategicHUDStandardCommandButtonSettings Rva00574499.
#include "unicode_string.h"

class Rva00220808;

struct TargetRef00217D4C
{
	void *m_vtbl;
	int m_refCount;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct RvaF6Ret
{
	RvaF6Ret(TargetRef00217D4C *p) : m_ptr(p)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	~RvaF6Ret()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

class InGameSimpleHelp
{
public:
	InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
private:
	char m_opaque[12];
};

UnicodeString __cdecl Rva00220E30(void *army, bool detailed);
UnicodeString __cdecl GetArmySummaryName(Rva00220808 *src);

struct Holder0056BABF
{
	char m_pad[0x78];
	Rva00220808 *m_army;
};

RvaF6Ret Helper0056BABF(int v)
{
	Rva00220808 *army = ((Holder0056BABF *)v)->m_army;
	if (!army)
		return RvaF6Ret(0);
	return RvaF6Ret((TargetRef00217D4C *)new InGameSimpleHelp(GetArmySummaryName(army), Rva00220E30(army, true)));
}
