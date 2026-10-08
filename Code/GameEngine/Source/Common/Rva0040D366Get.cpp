// cl: /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ?GetArmyBannerByID@ArmySummarySystem@@QAEPBVAsciiString@@H@Z @0x0040D366 26B: chain from bfmeFind1038 0x0040D008 returns +0x20 AsciiString or TheEmptyString when null. Evidence: calls rowed 0x0040D008; TheEmptyString 0x009E0878; single caller jmp at 0x0023D070; prev 0x0040D34C next 0x0040D380 in Common.
class BfmeY1038
{
public:
	char m_pad[0x20];
	AsciiString m_20;
};
extern BfmeY1038 *__stdcall bfmeFind1038(int v);
class ArmySummarySystem {public:const AsciiString *GetArmyBannerByID(int v);};
const AsciiString *ArmySummarySystem::GetArmyBannerByID(int v)
{
	BfmeY1038 *y = bfmeFind1038(v);
	if (y == 0)
		return &AsciiString::TheEmptyString;
	return &y->m_20;
}

// WB wrapper D0B960/D0B980 calls ArmySummarySystem::GetArmyNameByID/
// GetArmyBannerByID. Retail23D05F/23D06A tail-jump here after adjusting
// GameLogic by184. Native body ignores ECX; member ABI preserves that
// observed call interface. Pointer return follows the native stable string.
