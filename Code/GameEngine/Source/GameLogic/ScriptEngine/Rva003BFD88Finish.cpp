// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /EHsc
// ?doDisplayText@ScriptActions@@IAEXABVAsciiString@@@Z @0x003BFD88 35B
//
// Target identity (BFME2 evidence): ScriptActions::executeAction action-template
// index 78 is DISPLAY_TEXT, and that arm calls retail 0x003BFD88. The target
// bytes call InGameUI slot +0x3C (slot 15) with a by-value AsciiString copied
// through the rowed StringBase copy ctor 0x000365F0; the source pointer is the
// InGameUI singleton TheInGameUI (retail VA 0x00DFEDF0), the same extern the
// matched ScriptActions siblings use.
//
// Donor provenance: the BFME1 donor body at 0x002F3BA0 registers this method for
// DISPLAY_TEXT and forwards the display string to InGameUI::message. The target
// arm/name mapping and boundary are BFME2 evidence; the InGameUI method identity
// is carried from the donor pending independent target-vtable naming.
#include "ascii_string.h"

extern class InGameUI *TheInGameUI;

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

class ScriptActions
{
protected:
	void doDisplayText(const AsciiString &);
};

void ScriptActions::doDisplayText(const AsciiString &displayText)
{
	TheInGameUI->message(displayText);
}
