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
//    Object); an Object qualifies when the rowed rva002907A1 holds, it is
//    the player's (rowed getControllingPlayer), not contained (+0x274),
//    not kind 91, and kind 3 or neither kind 14 nor 16, not effectively dead
//    (+0x438 bit 0), not status 3 (rowed testStatus) and the rowed
//    rva00292FAC holds;
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

class Player
{
public:
	UnsignedInt getPlayerMask() const { return 1 << m_playerIndex; }
private:
	unsigned char m_pad00[0x54];
	Int m_playerIndex; // +0x54
};

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

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(KindOfType kind) const
	{
		return (((const unsigned char *)m_kindOf)[kind >> 3] & (1 << (kind & 7))) != 0;
	}
private:
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[4]; // +0x108
};

class Object
{
public:
	Bool rva002907A1();
	Player *getControllingPlayer() const;
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool rva00292FAC() const;
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

class Drawable
{
public:
	Object *getObject() const { return m_object; }
	Drawable *getNextDrawable() const { return m_next; }
private:
	unsigned char m_pad000[0xFC];
	Object *m_object; // +0xFC
	unsigned char m_pad100[0x104 - 0x100];
	Drawable *m_next; // +0x104
};

#define V(n) virtual void r##n() = 0;

class GameClient
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16)
	virtual Drawable *firstDrawable() = 0; // slot 17
};

extern GameClient *TheGameClient;

class GameMessage;

class MessageStream
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17)
	virtual GameMessage *appendMessage(int type) = 0; // slot 18
};

extern MessageStream *TheMessageStream;

class GameTextInterface
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14)
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0; // slot 15
};

extern GameTextInterface *TheGameText;

// GameLogic::selectObject 0x0023C924 (row) through its pinned selection-view
// spelling; the shared GameLogic view does not declare it.
class Rva0047BA10SelectionView
{
public:
	void rva0023C924(Object *obj, Bool createNewGroup, UnsignedInt playerMask, Bool affectClient);
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	virtual void __cdecl message(UnicodeString format, ...) = 0; // slot 16
	V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65)
	virtual void selectDrawable(Drawable *draw) = 0; // slot 66
	V(67)
	virtual void deselectAllDrawables() = 0; // slot 68
	V(69)
	virtual Int getSelectCount() = 0; // slot 70
	virtual Int getMaxSelectCount() = 0; // slot 71
	V(72)
	virtual void rva0029BE05(Bool viaLogic, Player *player); // slot 73
	V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
	V(88) V(89) V(90) V(91) V(92) V(93) V(94) V(95)
	V(96) V(97) V(98) V(99) V(100) V(101)
	virtual Bool getDisplayedMaxWarning() = 0; // slot 102
	virtual void setDisplayedMaxWarning(Bool selected) = 0; // slot 103
};

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
		if (!obj->rva002907A1())
			continue;
		if (obj->getControllingPlayer() != player)
			continue;
		if (obj->getContainedBy())
			continue;
		const ThingTemplate *tmpl = obj->getTemplate();
		if (tmpl->isKindOf(KINDOF_BFME_91))
			continue;
		if (tmpl->isKindOf(KINDOF_BFME_3))
		{
		}
		else if (tmpl->isKindOf(KINDOF_BFME_14))
			continue;
		else if (tmpl->isKindOf(KINDOF_BFME_16))
			continue;
		if (obj->isEffectivelyDead())
			continue;
		if (obj->testStatus(OBJECT_STATUS_BFME_3))
			continue;
		if (!obj->rva00292FAC())
			continue;

		if (TheInGameUI->getMaxSelectCount() > 0 && TheInGameUI->getSelectCount() >= TheInGameUI->getMaxSelectCount())
		{
			if (!viaLogic && !TheInGameUI->getDisplayedMaxWarning())
			{
				TheInGameUI->setDisplayedMaxWarning(true);
				UnicodeString msg;
				msg.format(TheGameText->fetch("GUI:MaxSelectionSize").str(), TheInGameUI->getMaxSelectCount());
				TheInGameUI->message(msg);
			}
		}
		else if (!viaLogic)
		{
			TheInGameUI->selectDrawable(draw);
			TheInGameUI->setDisplayedMaxWarning(false);
		}
		else
		{
			((Rva0047BA10SelectionView *)TheGameLogic)->rva0023C924(obj, createNewGroup, player->getPlayerMask(), false);
			createNewGroup = false;
		}
	}

	if (TheInGameUI->getSelectCount() && !viaLogic)
	{
		UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossMap");
		TheInGameUI->message(message);
	}
}
