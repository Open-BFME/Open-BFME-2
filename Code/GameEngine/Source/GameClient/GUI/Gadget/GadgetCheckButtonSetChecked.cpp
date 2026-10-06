// cl: /DNDEBUG /MD
// ?GadgetCheckLikeButtonSetVisualCheck@@YAXPAVGameWindow@@_N@Z @0x00327C61 58B
// Check-like button set-checked: sets or clears bit 2 of WinInstanceData::m_state.
// Evidence: sibling ?GadgetCheckLikeButtonIsChecked@@YA_NPAVGameWindow@@@Z at 0x00327C9B
// reads the same bit; instance via rowed disp8 lea 0x00314046; status bit 0x80000 via
// GameWindow::winGetStatus pin 0x0030F45F (ICF twin of CategoryModuleClass getName).

typedef bool Bool;
typedef unsigned int UnsignedInt;

#ifndef NULL
#define NULL 0
#endif

class WinInstanceData
{
public:
	unsigned char m_pad[8];
	UnsignedInt m_state;
};

class GameWindow
{
public:
	UnsignedInt winGetStatus();
};

class Rva00314046LeaField
{
public:
	void *get() const;
};

void GadgetCheckLikeButtonSetVisualCheck(GameWindow *button, Bool checked)
{
	if (button == NULL)
		return;
	WinInstanceData *instData = (WinInstanceData *)((Rva00314046LeaField *)button)->get();
	if (instData == NULL)
		return;
	if ((button->winGetStatus() & 0x80000) == 0)
		return;
	if (checked == 1)
		instData->m_state |= 4;
	else
		instData->m_state &= ~4;
}
