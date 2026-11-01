// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?ShowProductionCount@Impl@CommandButtonMovieClip@StrategicHUD@@QAEXH@Z @0x005E0EE1 221B
// Chain via rowed Fire 0x005277D9 plus Apt ProductionCount update.
// First half mirrors Rva005E0FBE/Rva005E1008: flags +0x40 +0x42 with true
// temp and ShowProductionCount; second half mirrors Rva005F6220Apt plus
// Rva005FF207Unicode: int param vs +0x38, Unicode tmp via g_Va007C9260,
// Ascii key APT:_level%u.%s_ProductionCount, pinned bfmeSetText 0x00225301
// with false, rowed releaseBuffers. Evidence: rowed Fire, rowed formats
// 0x006CB5D0 0x00038150, pinned 0x00225301, globals empty/TheTarget/g_Va,
// strings ShowProductionCount + APT key, caller jmp at 0x005E116B.
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/Common/Rva00222A8BTarget.h"
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr);

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

extern const unsigned short g_Va007C9260[];

struct Rva005E0EE1Inner
{
	char m_pad8[8];
	char m_name[1];
};

namespace StrategicHUD {
class CommandButtonMovieClip
{
public:
	class Impl;
};
}

class StrategicHUD::CommandButtonMovieClip::Impl
{
public:
	void ShowProductionCount(int val);
private:
	char m_pad00[8];
	unsigned int m_level08;
	Rva005E0EE1Inner *m_inner0C;
	char m_pad10[0x38 - 0x10];
	int m_count38;
	char m_pad3C[0x40 - 0x3C];
	bool m_flag40;
	char m_pad41;
	bool m_flag42;
};

void StrategicHUD::CommandButtonMovieClip::Impl::ShowProductionCount(int val)
{
	if (m_flag42 == 0)
	{
		if (m_flag40 != 0)
		{
			bool flag = true;
			const char *prefix = m_inner0C ? (const char *)((char *)m_inner0C + 8) : "";
			Rva005277D9Fire((Rva00222A8BTarget *)g_bfmeAptWindowManager, (void *)m_level08, prefix, "ShowProductionCount", &flag);
		}
		m_flag42 = 1;
	}
	if (val != m_count38)
	{
		UnicodeString tmp;
		tmp.format(g_Va007C9260, val);
		AsciiString key;
		const char *mid = m_inner0C ? (const char *)((char *)m_inner0C + 8) : "";
		key.format("APT:_level%u.%s_ProductionCount", m_level08, mid);
		g_bfmeAptWindowManager->bfmeSetText(key, tmp, false);
		m_count38 = val;
	}
}
