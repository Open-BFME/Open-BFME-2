// ?doDisplayText@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.94 date=2026-09-26
// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?doDisplayText@ScriptActions@@IAEXABVAsciiString@@@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
//
// Target identity: ScriptActions::executeAction's action-template index 78
// is DISPLAY_TEXT; that arm calls retail 0x003BFD88 (Ghidra boundary 35B).
// Its handler body matches the BFME1 35B donor recorded at 0x002F3BA0.
// Donor facts: BFME1 registers this method for DISPLAY_TEXT and forwards the
// display string to InGameUI::message. The target arm/name mapping and target
// boundary come from BFME2 evidence; the InGameUI method identity is carried
// from the donor pending independent target-vtable naming. Target bytes call
// vtable +0x3C (slot 15) with a by-value AsciiString copied via 0x365F0.

#include "../../../../../reference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
// slot index from target bytes (call [vtable+0x3C])
class InGameUI
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void message(AsciiString, ...) = 0;
};

extern InGameUI *TheInGameUI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doDisplayText(const AsciiString &);
};

// ?doDisplayText@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doDisplayText(const AsciiString &displayText)
{
	TheInGameUI->message(displayText);
}
