// cl: /DNDEBUG /MD
// Retail RVA 0x00327B33, 19 bytes.
// GadgetCheckBoxIsChecked, the checkbox selected-state query.
// Ported from Open-BFME-1 GadgetCheckBox.cpp; retail tests the selected bit
// with a shift-and-mask rather than the mask-form BitTest, and keeps
// WinInstanceData::m_state at +0x08. The TU defines only this body.

typedef int Int;
typedef short Short;
typedef bool Bool;

class WinInstanceData
{
public:
	char unused00[0x08];
	unsigned int m_state;
};

class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
};

Bool GadgetCheckBoxIsChecked(GameWindow *g)
{
	WinInstanceData *instData = g->winGetInstanceData();
	return (instData->m_state >> 2) & 1;
}
