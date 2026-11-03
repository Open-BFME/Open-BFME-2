// cl: /DNDEBUG /MD /EHsc
// ?rva0028C0F2@Object@@QAEXI@Z @0x0028C0F2 40B
// Object millisecond-to-frame setter: m_448 = (v / 1000u) * rate + TheGameLogic->getFrame().
// Evidence: unsigned div by 0x3E8 plus imul with VA 0x00DBA4E4 and TheGameLogic VA 0x00DFE78C+0x40;
// sole caller 0x00295844; neighbours ObjectLeaveGroup and Object_bfmeRefreshPartitionCells are Object TUs.
extern int BfmeLogicFramesPerSecond;

#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#define BfmeLogicRate (*(unsigned int *)&BfmeLogicFramesPerSecond)

#include "object.h"

void Object::rva0028C0F2(unsigned int v)
{
	m_448 = (v / 1000u) * BfmeLogicRate + TheGameLogic->getFrame();
}
