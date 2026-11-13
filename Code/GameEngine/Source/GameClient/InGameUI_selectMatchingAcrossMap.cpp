// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?selectMatchingAcrossMap@InGameUI@@UAEHXZ, retail 0x0029CFC8, 285 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/InGameUIBodies.cpp
// rva00448700, matched 339 bytes there): the map-wide pass calls the region
// worker with a NULL region and, when nothing was selected, shows the
// across-map message unless the first selected drawable is a structure.
// BFME2 adaptations (all retail-measured):
// - Same outlined selection-state guard as selectMatchingAcrossScreen
//   (?isSelectionLocked@BfmeSelectionState@@QBE_NXZ @0x4253A, +0xB4/+0xB5).
// - No tactical view and no region local: the worker takes NULL.
// - InGameUI virtuals: message at 0x40, getFirstSelectedDrawable at 0x12C,
//   selectMatchingAcrossRegion at 0x190.
// - Structure test is inlined as two loads plus a bit test (no isKindOf call):
//   Drawable+0xFC is the object, Object+0x04 is the template, template+0x108
//   bit 0x80 is STRUCTURE (template kind bytes per isAbleToAttack).
// - GameText fetch at 0x3C; UnicodeString copy@0x37050/release@0x36E70.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
typedef int Int;
typedef bool Bool;

typedef unsigned short wchar_t;

class UnicodeString;
class AsciiString;

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

struct IRegion2D;

#include "../../Include/Common/BfmeSelectionState.h"

#include "../../Include/Common/ThingTemplate.h"

#include "../GameLogic/Object/object.h"

#include "../../Include/GameClient/Drawable.h"

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

// ?selectMatchingAcrossMap@InGameUI@@UAEHXZ
int InGameUI::selectMatchingAcrossMap()
{
	BfmeSelectionState *state = (*(BfmeSelectionState **)&TheLivingWorldLogic);
	if (state != 0 && state->isSelectionLocked() != 0)
		return 0;

	Int numSelected = selectMatchingAcrossRegion(0);
	if (numSelected == -1)
	{
		UnicodeString message = TheGameText->fetch("GUI:NothingSelected");
		TheInGameUI->rva0029E846(message);
	}
	else if (numSelected == 0)
	{
		Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
		if (draw == 0 || draw->m_object == 0 ||
			(draw->m_object->m_template->m_kindof[0] & (1U << 7)) == 0)
		{
			UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossMap");
			TheInGameUI->rva0029E846(message);
		}
	}
	else
	{
		UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossMap");
		TheInGameUI->rva0029E846(message);
	}
	return numSelected;
}

