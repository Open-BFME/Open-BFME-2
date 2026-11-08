// ?winSetInstanceData@GameWindow@@QAEHPAVWinInstanceData@@@Z, retail 0x0031495C,
// 142 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/GameClient/GUI/GameWindowWinSetInstanceData.cpp
// (reference/open-bfme-1). The donor body does not place at BFME 1's flags;
// compiled /Os it is byte-identical to retail once relocations are masked
// (unique hit on unclaimed .text). Only the placed body is defined here.
//
// 2 callee pins read off retail's REL32 displacements: getText at 0x003148F1
// (tests m_text at this+0x19c, forwards through the DisplayString vtable slot
// +8, else returns TheEmptyString) and getTooltipTextLength at 0x002C027B
// (tests m_tooltip at this+0x1a0, tail-jumps vtable slot +0xc, else 0). Both
// are inline in the donor and out of line in retail; the second is an ICF alias
// of the matched ?rva002C027B body at the same address.
// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI
// readable body of ?winSetInstanceData@GameWindow@@QAEHPAVWinInstanceData@@@Z: game/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// BFME's GameWindow instance-data member begins at +0x30; the vendored ZH
// declaration places it at +0x2c.  Retail also uses the BFME DisplayString
// vtable slot at +0x0c for getTextLength/getTooltipTextLength.  The canonical
// header supplies the +0x30 member; the DisplayString slot view stays local.

#include "Common/UnicodeString.h"

typedef int Int;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual UnicodeString getText(void);
	virtual void unusedDisplayStringSlot0(void);
	virtual void unusedDisplayStringSlot1(void);
	virtual Int getTextLength(void);
};

class GameWindow;

#include "../../../Include/GameClient/Bfme2GameWindow.h"

// The donor's inline length tests; this unit emits the select-any copies.
inline Int WinInstanceData::getTextLength(void)
{
	if (m_text)
		return m_text->getTextLength();
	return 0;
}

inline Int WinInstanceData::getTooltipTextLength(void)
{
	if (m_tooltip)
		return m_tooltip->getTextLength();
	return 0;
}


Int GameWindow::winSetInstanceData(WinInstanceData *data)
{
	DisplayString *text, *tooltipText;

	text = m_instData.m_text;
	tooltipText = m_instData.m_tooltip;

	m_instData = *data;

	m_instData.m_text = text;
	m_instData.m_tooltip = tooltipText;
	m_instData.m_videoBuffer = NULL;

	if (data->getTextLength())
		m_instData.setText(data->getText());
	if (data->getTooltipTextLength())
		m_instData.setTooltipText(data->getTooltipText());

	return 0;
}

UnicodeString GameWindow::winGetText(void)
{
	return m_instData.getText();
}
