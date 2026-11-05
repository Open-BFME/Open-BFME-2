// cl: /DNDEBUG /MD /EHsc
// ?countsAsMoveIntoCamp@@YAEIPBUBfmePointFD@@@Z, retail 0x004D93F7, 92 bytes.
// Shroud-audio bounds check: TheAudio slot 77 (+0x134, getAudioSettings) bounds vs two
// Rva00739830 cell sums via TheShroudManager; unsigned char return.
// Evidence: TheAudio 0x00DFE6E8; TheShroudManager 0x00DFE74C precedent
// Rva000D1BEA; rowed rva00739830; sbb-inc unsigned char per §4.6;
// caller 0x004DA8C4.
extern class PartitionManager *TheShroudManager;

#include "../../Include/Common/GameAudio.h"

struct BfmePointFD;
// The settings record slot 77 (getAudioSettings) returns; only the two
// bounds this check reads are known.
struct AudioSettings
{
	char m_pad[0x44];
	unsigned int m_44;
	unsigned int m_48;
};
extern AudioManager *TheAudio;
class Rva00739830
{
public:
	int rva00739830(const BfmePointFD *pt, int a, unsigned int b) const;
};
#define TheShroudManager (*(Rva00739830 **)&TheShroudManager)
unsigned char __cdecl countsAsMoveIntoCamp(unsigned int a, const BfmePointFD *pt1, const BfmePointFD *pt2)
{
	AudioManager *audio = TheAudio;
	if (audio == 0)
		return 0;
	const AudioSettings *audioBounds = audio->getAudioSettings();
	if (audioBounds == 0)
		return 0;
	if (TheShroudManager == 0)
		return 0;
	int x = TheShroudManager->rva00739830(pt1, 2, a);
	if (x > audioBounds->m_44)
		return 0;
	int y = TheShroudManager->rva00739830(pt2, 2, a);
	return (unsigned char)(y >= audioBounds->m_48);
}

