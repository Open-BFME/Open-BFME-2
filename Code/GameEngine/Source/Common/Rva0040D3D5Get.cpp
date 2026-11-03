// cl: /MD
// ?rva0040D3D5@ArmySummarySystem@@QAEHH@Z @0x0040D3D5 19B: army lookup 0x0040D008 then
// the +0x30 dword (0x0040D2FD stores frames there) or 0 when null. Evidence: calls
// rowed 0x0040D008 on its own this; single caller GameLogic forwarder 0x0023D0A1
// (add ecx, 0x184; jmp).
class BfmeY1038
{
public:
	char m_pad[0x30];
	int m_30;
};
#include "../../Include/Common/ArmySummarySystem.h"
int ArmySummarySystem::rva0040D3D5(int v)
{
	BfmeY1038 *y = (BfmeY1038 *)rva0040D008(v);
	if (y == 0)
		return 0;
	return y->m_30;
}
