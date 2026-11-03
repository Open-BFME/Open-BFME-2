// cl: /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
// ?rva0040D041@ArmySummarySystem@@QAEPBVAsciiString@@H@Z @0x0040D041 26B: army lookup 0x0040D008 (on its own this; GameLogic forwarder 0x0023D01D adds 0x184) returns +0x64 AsciiString or TheEmptyString when null. Evidence: calls rowed 0x0040D008; TheEmptyString 0x009E0878; same TU family as rowed Rva0040D366Get 0x0040D366.
class BfmeY1038
{
public:
	char m_pad[0x64];
	AsciiString m_64;
};
#include "../../Include/Common/ArmySummarySystem.h"
const AsciiString *ArmySummarySystem::rva0040D041(int armyId)
{
	BfmeY1038 *army = (BfmeY1038 *)rva0040D008(armyId);
	if (army == 0)
		return &AsciiString::TheEmptyString;
	return &army->m_64;
}
