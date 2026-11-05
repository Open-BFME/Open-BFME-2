// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ?rva0029BE05@InGameUI@@UAEX_NPAVPlayer@@@Z, retail 0x0029BE05 (657 bytes).
// An InGameUI virtual (slot 73 of vtable 0x007FD400; slot 78 of 0x007C7A64)
// that never reads this: selects every eligible Object of the given player
// across the map, BFME 2's form of Zero Hour's InGameUI.cpp across-map
// selection (same "GUI:MaxSelectionSize" cap message and
// "GUI:SelectedAcrossMap" notice). Target evidence:
//  - unless the flag is set: TheInGameUI slot 68 (deselectAllDrawables) and
//    TheMessageStream slot 18 message 0x461 first;
//  - walks TheGameClient slot 17's drawable list (+0x104 next, +0xFC
//    Object); an Object qualifies when the rowed isMobile holds, it is
//    the player's (rowed getControllingPlayer), not contained (+0x274),
//    not kind 91, and kind 3 or neither kind 14 nor 16, not effectively dead
//    (+0x438 bit 0), not status 3 (rowed testStatus) and the rowed
//    isMassSelectable holds;
//  - over the select cap (slots 71 and 70) the unflagged call shows the cap
//    message once (slots 102/103; GameText slot 15; rowed
//    UnicodeString::format; slot 16 message); else unflagged it selects the
//    drawable (slot 66) and clears the warning, flagged it selects the Object
//    through the rowed GameLogic::selectObject (via its pinned selection-view
//    spelling) with the player's mask
//    (+0x54 index), creating the group only for the first;
//  - unflagged with a selection it posts "GUI:SelectedAcrossMap".

#include "unicode_string.h"
#include "../Common/GameLogicObjectLookupView.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Drawable;

#include "../../Include/Common/Player.h"

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_3 = 3
};

enum KindOfType
{
	KINDOF_BFME_3 = 3,
	KINDOF_BFME_14 = 14,
	KINDOF_BFME_16 = 16,
	KINDOF_BFME_91 = 91
};

#include "../../Include/Common/ThingTemplate.h"
// The view's inline kind test: a byte test on the canonical +0x108 mask.
static __forceinline bool thingTemplateIsKindOf(const ThingTemplate *tmpl, KindOfType t)
{
	return (((const unsigned char *)tmpl->m_kindof)[t >> 3] & (1 << (t & 7))) != 0;
}

class Object
{
public:
	Bool isMobile() const;
	Player *getControllingPlayer() const;
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isMassSelectable() const;
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getContainedBy() const { return m_containedBy; }
	Bool isEffectivelyDead() const { return (m_438 & 1) != 0; }
private:
	unsigned char m_pad000[0x04];
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad008[0x274 - 0x08];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_438; // +0x438
};

#include "../../Include/GameClient/Drawable.h"

#define V(n) virtual void r##n() = 0;

#include "../../Include/GameClient/GameClientClass.h"

extern GameClient *TheGameClient;

class GameMessage;

#include "../../Include/Common/MessageStream.h"

extern MessageStream *TheMessageStream;

#include "../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

// GameLogic::selectObject 0x0023C924 (row) through its pinned selection-view
// spelling; the shared GameLogic view does not declare it.
extern GameLogic *TheGameLogic;

#include "../../Include/GameClient/InGameUI.h"

#undef V

extern InGameUI *TheInGameUI;

void InGameUI::rva0029BE05(Bool viaLogic, Player *player)
{
	if (!viaLogic)
	{
		TheInGameUI->deselectAllDrawables();
		TheMessageStream->appendMessage(0x461);
	}

	Drawable *draw = TheGameClient->firstDrawable();
	Bool createNewGroup = true;
	for (; draw; draw = draw->getNextDrawable())
	{
		Object *obj = draw->getObject();
		if (!obj)
			continue;
		if (!obj->isMobile())
			continue;
		if (obj->getControllingPlayer() != player)
			continue;
		if (obj->getContainedBy())
			continue;
		const ThingTemplate *thingTemplate = obj->getTemplate();
		if (thingTemplateIsKindOf(thingTemplate, KINDOF_BFME_91))
			continue;
		if (thingTemplateIsKindOf(thingTemplate, KINDOF_BFME_3))
		{
		}
		else if (thingTemplateIsKindOf(thingTemplate, KINDOF_BFME_14))
			continue;
		else if (thingTemplateIsKindOf(thingTemplate, KINDOF_BFME_16))
			continue;
		if (obj->isEffectivelyDead())
			continue;
		if (obj->testStatus(OBJECT_STATUS_BFME_3))
			continue;
		if (!obj->isMassSelectable())
			continue;

		if (TheInGameUI->getMaxSelectCount() > 0 && TheInGameUI->getSelectCount() >= TheInGameUI->getMaxSelectCount())
		{
			if (!viaLogic && !TheInGameUI->getDisplayedMaxWarning())
			{
				TheInGameUI->setDisplayedMaxWarning(true);
				UnicodeString msg;
				msg.format(TheGameText->fetch("GUI:MaxSelectionSize").str(), TheInGameUI->getMaxSelectCount());
				TheInGameUI->rva0029E846(msg);
			}
		}
		else if (!viaLogic)
		{
			TheInGameUI->selectDrawable(draw);
			TheInGameUI->setDisplayedMaxWarning(false);
		}
		else
		{
			TheGameLogic->selectObject(obj, createNewGroup, player->getPlayerMask(), false);
			createNewGroup = false;
		}
	}

	if (TheInGameUI->getSelectCount() && !viaLogic)
	{
		UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossMap");
		TheInGameUI->rva0029E846(message);
	}
}
