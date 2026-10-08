// cl: /Ireference/shims/bfme2_ascii -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?rva002D3AB5@Rva002D3AB5Target@@QAEXH@Z @ 0x002D3AB5 123B
// Evidence: LINK BONUS caller jmp 0x002D4683 names this mangled name; first-field state index >=0 like neighbour Gen0058BCD0::handle 0x002D3A53; g_009FEF10 null plus BfmeSelectionState::isSelectionLocked selects NonCommand_CommandPointsLivingWorld else NonCommand_CommandPoints; ControlBar::findCommandButton 0x31BE3C then ControlBar::rva004C1B60 0x405DBC.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include "ascii_string.h"

class Rva002BA8F1Logic;

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;
};

struct BfmeWorldRV;
extern struct BfmeWorldRV *g_bfmeWorldRV;

class GameWindow;
class CommandButton;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &s);
	void rva004C1B60(GameWindow *window, void *data);
};

struct Rva002D3AB5State
{
	int m_index;
};

class Rva002D3AB5Target
{
public:
	void rva002D3AB5(int);
private:
	Rva002D3AB5State *m_state;
};

void Rva002D3AB5Target::rva002D3AB5(int)
{
	if (m_state->m_index < 0)
		return;
	const char *text;
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) != 0 && ((BfmeSelectionState *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->isSelectionLocked() != 0)
		text = "NonCommand_CommandPointsLivingWorld";
	else
		text = "NonCommand_CommandPoints";
	const CommandButton *button;
	{
		AsciiString name(text);
		button = ((ControlBar *)g_bfmeWorldRV)->findCommandButton(name);
	}
	if (button != 0)
		((ControlBar *)g_bfmeWorldRV)->rva004C1B60(0, (void *)button);
}
