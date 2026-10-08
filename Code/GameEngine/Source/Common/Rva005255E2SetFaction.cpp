// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva005255E2@Impl@InGameHeroSelectInterface@@QAEXPBVAsciiString@@@Z, retail 0x005255E2 47B chain via 0x00525203.
// Same InGameHeroSelectInterface::Impl layout as 0x0052557E: m_name GetStr plus m_08 level plus SetFaction.
// Evidence: callee rowed 0x00525203 Fire; callers 0x00527650 plus 0x005258BB thunk; data SetFaction plus g_Rva0107301CEmptyString plus TheRva00222A8BTarget.
#include "ascii_string.h"

int __cdecl Rva00525203Fire(void *a1, void *a2, const char *a3, const char *a4, const AsciiString *a5);
class Rva00222A8BTarget;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

class InGameHeroSelectInterface
{
public:
	class Impl;
};

class InGameHeroSelectInterface::Impl
{
public:
	void *m_00;
	void *m_04;
	void *m_08;
	AsciiString m_name;
	void rva005255E2(const AsciiString *a);
};

void InGameHeroSelectInterface::Impl::rva005255E2(const AsciiString *a)
{
	void *raw = *(void **)&m_name;
	const char *s = raw ? (const char *)raw + 8 : "";
	Rva00525203Fire((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager), m_08, s, "SetFaction", a);
}
