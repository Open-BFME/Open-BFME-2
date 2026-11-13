// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?SetCommandPoints@Impl@ArmyUnitSwapperMovieClip@StrategicHUD@@QAEXHHH@Z retail 0x005FD8E5 113B
// Evidence: chain from 0x005FD53E you landed; calls Get 0x005FD53E and SetSlotString 0x005FD788 and releaseBuffer 0x00036E70; entry stride 0x18 base 0x1C offsets 0x10 0x14; string CP literal; /G7 for retail imul 0x18; caller 0x005FD959 jmp
#include "../../Include/Common/BfmeStringData.h"
#include "ascii_string.h"
#include "unicode_string.h"
class UnicodeString;
namespace StrategicHUD
{
	UnicodeString __cdecl FormatCPString(int a, int b);
}
#include "../../Include/Common/Rva005FD788Inner.h"
#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char *g_Va0087A290[];
struct ArmyUnitSwapperSlot
{
	char m_pad[16];
	int m_commandPoints;
	int m_maxCommandPoints;
};
#include "../../Include/GameClient/ArmyUnitSwapperMovieClip.h"
namespace StrategicHUD {
}

class StrategicHUD::ArmyUnitSwapperMovieClip::Impl
{
public:
	char m_pad0[4];
	int m_level4;
	Rva005FD788Inner *m_inner8;
	char m_padC[16];
	ArmyUnitSwapperSlot m_entries[1];
	void SetSlotString(int index, const char *suffix, const UnicodeString &text);
	void SetCommandPoints(int index, int a, int b);
};
void StrategicHUD::ArmyUnitSwapperMovieClip::Impl::SetCommandPoints(int index, int commandPoints, int maxCommandPoints)
{
	ArmyUnitSwapperSlot *entry = &m_entries[index];
	if (commandPoints == entry->m_commandPoints && maxCommandPoints == entry->m_maxCommandPoints)
		return;
	SetSlotString(index, "CP", StrategicHUD::FormatCPString(commandPoints, maxCommandPoints));
	entry->m_commandPoints = commandPoints;
	entry->m_maxCommandPoints = maxCommandPoints;
}

#include "../../Include/Common/Rva005FD956.h"

void Rva005FD956::setCommandPoints(int index, int commandPoints, int maxCommandPoints)
{
	m_p4->SetCommandPoints(index, commandPoints, maxCommandPoints);
}
