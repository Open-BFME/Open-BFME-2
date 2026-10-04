// ?getText@WinInstanceData@@QAE?AVUnicodeString@@XZ
// partial score=1.0 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?setTooltipText@WinInstanceData@@QAEXVUnicodeString@@@Z, retail 0x00322352, 97 bytes.
// New file-unit TU (sibling setters init/setText to follow).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/WinInstanceData.cpp,
// setTooltipText): allocate the tooltip display string on first use through
// the display-string manager, then give it the text through DisplayString's
// second virtual. DEBUG_ASSERTCRASH compiles out under /DNDEBUG.
// BFME2 facts (all retail-measured):
// - The manager global (0xDFEAD8) is DIR32-masked, so any extern spelling
//   verifies; the name follows the donor.
// - Retail calls the manager's slot 0x38 for the factory (the BFME1 donor's
//   slot 0x24 predates BFME2's wider manager vtable), and the display
//   string's slot 0x04 for the setter.
// - The by-value parameter is copied for the virtual call and destroyed here
//   at the end (MSVC callee-destroys rule for value parameters); the stack
//   temp becomes the callee's parameter, so this body destroys only [ebp+8].
// - The StringBase copy/destructor pins at 0x37050/0x36E70 carry the private
//   (AAE) spelling, so StringBase keeps its copy and releaseBuffer private.
// - m_tooltip sits at +0x1A0 (sibling m_tooltipString ends at +0x194).

typedef int Int;
typedef bool Bool;
typedef unsigned short wchar_t;

#ifndef NULL
#define NULL 0
#endif

#include "unicode_string.h"


// Retail fetch call uses vtable offset 0x38 for the factory (BFME2 widens
// the manager vtable past the donor's slot 0x24); pads stay declared-only
// so no vtable is emitted from this TU (VersionUnicode.cpp recipe).
class DisplayString
{
public:
	virtual ~DisplayString() {}
	virtual void setText(UnicodeString text);
	virtual UnicodeString getText();
};

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void managerSlot04() = 0;
	virtual void managerSlot08() = 0;
	virtual void managerSlot0C() = 0;
	virtual void managerSlot10() = 0;
	virtual void managerSlot14() = 0;
	virtual void managerSlot18() = 0;
	virtual void managerSlot1C() = 0;
	virtual void managerSlot20() = 0;
	virtual void managerSlot24() = 0;
	virtual void managerSlot28() = 0;
	virtual void managerSlot2C() = 0;
	virtual void managerSlot30() = 0;
	virtual void managerSlot34() = 0;
	virtual DisplayString *newDisplayString();
};

extern DisplayStringManager *TheDisplayStringManager;

class WinInstanceData
{
public:
	void setTooltipText(UnicodeString tip);
	void setText(UnicodeString text);
	UnicodeString getTooltipText();
	UnicodeString getText();

private:
	char m_pad[0x19C];
	DisplayString *m_text;
	DisplayString *m_tooltip;
};

// ?setTooltipText@WinInstanceData@@QAEXVUnicodeString@@@Z
void WinInstanceData::setTooltipText(UnicodeString tip)
{
	// allocate a tooltip display string if needed
	if (m_tooltip == NULL)
		m_tooltip = TheDisplayStringManager->newDisplayString();

	// set text
	m_tooltip->setText(tip);
}

// ?setText@WinInstanceData@@QAEXVUnicodeString@@@Z
void WinInstanceData::setText(UnicodeString text)
{
	// allocate a text display string if needed
	if (m_text == NULL)
		m_text = TheDisplayStringManager->newDisplayString();

	// set text
	m_text->setText(text);
}

inline UnicodeString WinInstanceData::getTooltipText()
{
	if (m_tooltip)
		return m_tooltip->getText();
	return UnicodeString::TheEmptyString;
}

// Reference: whole WinInstanceData_getText.cpp at BFME1
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24; tooltip sibling already matched.
// Target winSetInstanceData at 0x31495C directly calls this header spelling;
// the 53-byte body at 0x3148F1 reads text at +0x19C and calls slot +8.
// Its fallback copies the shared UnicodeString empty object at 0xA0C898
// through the exported wide copy constructor at 0x37050.
inline UnicodeString WinInstanceData::getText()
{
	if (m_text)
		return m_text->getText();
	return UnicodeString::TheEmptyString;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeWinInstanceDataInlineAnchorWinInstanceDataDisplayStrings@@YAXPAVWinInstanceData@@@Z absent-from-retail
void _bfmeWinInstanceDataInlineAnchorWinInstanceDataDisplayStrings(WinInstanceData *p)
{
    p->getTooltipText();
    p->getText();
}
#pragma inline_depth()
