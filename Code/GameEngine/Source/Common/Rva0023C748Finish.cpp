// ?rva0023C748@Rva0023C748@@QAEDXZ
// partial score=0.95 date=2026-09-30
// ?rva0023C748@Rva0023C748@@QAEDXZ
// partial score=0.95 date=2026-09-30
//
// ?rva0023C748@Rva0023C748@@QAEDXZ @0x0023C748, 97B.
// Predicate on this+0x110 mode 5/1/2 with selection-locked gate and 939 helper.
// Evidence: __thiscall ret no args returns al 1/0; callees rowed isSelectionLocked
// and NetWrapperCommandMsg::getData; helper state +0xE74 2/1/5 like sibling
// BfmeConv939Call939D; globals g_009FEF10 and g_bfme939Helper in use.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../Include/Common/BfmeSelectionState.h"

#include "../../Include/GameLogic/Rva002BA8F1Logic.h"

#include "../../Include/GameNetwork/NetWrapperCommandMsg.h"

struct Bfme939Helper
{
	char m_lead[0x1C];
	int m_value;
	char m_pad[0xE54];
	int m_state;
};

class RecorderClass; extern RecorderClass *TheRecorder;

class Rva0023C748
{
public:
	char _pad[0x110];
	int m_mode;
	char rva0023C748();
};

char Rva0023C748::rva0023C748()
{
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) != 0 && ((BfmeSelectionState *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->isSelectionLocked())
		return 0;
	if (m_mode == 5)
		return 1;
	if (m_mode == 1)
		return 1;
	if (m_mode == 2)
		return 1;
	if (((Bfme939Helper *)TheRecorder) != 0 && ((NetWrapperCommandMsg *)((Bfme939Helper *)TheRecorder))->getData() == (unsigned char *)1)
	{
		int state = ((Bfme939Helper *)TheRecorder)->m_state;
		if (state == 2)
			return 1;
		if (state != 1 && state != 5)
			return 0;
		return 1;
	}
	return 0;
}
