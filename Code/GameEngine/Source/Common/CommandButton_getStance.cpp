// ?getStance@CommandButton@@QAEHH@Z retail 0x0035B6B8 16B
// Array indexer returning m_234[index]. Evidence: unlock lane plus 6 callers
// plus ecx-first thiscall shape with ret-4 honest address name.

#include "../../Include/GameClient/CommandButton.h"

int CommandButton::getStance(int index)
{
	return m_stancesBegin[index];
}
