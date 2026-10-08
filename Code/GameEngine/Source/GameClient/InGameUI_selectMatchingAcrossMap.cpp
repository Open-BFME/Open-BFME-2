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

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
};

extern GameTextInterface *TheGameText;

struct IRegion2D;

class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;

private:
	unsigned char m_pad[0xB4];
	unsigned char m_first;
	unsigned char m_second;
};

class ThingTemplate
{
public:
	unsigned char m_pad[0x108];
	unsigned char m_kindFlags;
};

class Object
{
public:
	void *m_vptr;
	ThingTemplate *m_template;
};

class Drawable
{
public:
	unsigned char m_pad[0xFC];
	Object *m_object;
};

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void message(UnicodeString format, ...);
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual Drawable *getFirstSelectedDrawable();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual int selectMatchingAcrossRegion(IRegion2D *region);
	virtual int selectMatchingAcrossMap();
};

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
		TheInGameUI->message(message);
	}
	else if (numSelected == 0)
	{
		Drawable *draw = TheInGameUI->getFirstSelectedDrawable();
		if (draw == 0 || draw->m_object == 0 ||
			(draw->m_object->m_template->m_kindFlags & 0x80) == 0)
		{
			UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossMap");
			TheInGameUI->message(message);
		}
	}
	else
	{
		UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossMap");
		TheInGameUI->message(message);
	}
	return numSelected;
}

