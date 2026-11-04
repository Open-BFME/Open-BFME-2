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

#include "../../../Include/GameClient/InGameUI.h"

class ScriptActions
{
protected:
	void doDisplayText(const AsciiString &);
};

void ScriptActions::doDisplayText(const AsciiString &displayText)
{
	TheInGameUI->rva0029E656(displayText);
}
