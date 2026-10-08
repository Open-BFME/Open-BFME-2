// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?selectMatchingAcrossScreen@InGameUI@@UAEHXZ, retail 0x0029CEBB, 269 bytes.
// Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/InGameUIBodies.cpp,
// matched 332 bytes there): the whole screen becomes a region and the region
// pass does the work; the two message texts are the only thing this body adds.
// BFME2 adaptations (all retail-measured):
// - The selection-state guard is OUTLINED as a thiscall to 0x0042253A testing
//   bytes at +0xB4/+0xB5 (BFME1 inlines +0x2C/+0x2D). Pinned opaque-method.
// - The tactical view is TheTacticalView (slots getWidth 0x3C, getHeight 0x44,
//   getOrigin 0x4C), not the FadeShim.
// - InGameUI virtuals: message at 0x40 (variadic __cdecl, this on stack),
//   selectMatchingAcrossRegion at 0x190, buildRegion at 0x194.
// - GameText fetch at 0x3C returning UnicodeString by value.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
typedef int Int;
typedef bool Bool;

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

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

class TacticalView
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
	virtual int getWidth();
	virtual void slot16();
	virtual int getHeight();
	virtual void slot18();
	virtual void getOrigin(int *x, int *y);
};

extern TacticalView *TheTacticalView;

// BFME2 selection-state guard: two flag bytes at +0xB4/+0xB5, tested by the
// outlined thiscall at 0x0042253A (returns true only if both non-zero).
class BfmeSelectionState
{
public:
	bool isSelectionLocked() const;

private:
	unsigned char m_pad[0xB4];
	unsigned char m_first;
	unsigned char m_second;
};

// Borrowed prefix: native 29CBCA loads Drawable::m_object at +FC.
class Object;
class Drawable;
struct SelectedDrawableView
{
	char pad[0xfc];
	Object *m_object;
};
static __forceinline Object *selectedObject(Drawable *drawable)
{
	return reinterpret_cast<SelectedDrawableView *>(drawable)->m_object;
}
#include <list>
typedef _STL::list<Drawable *> DrawableList;
// Borrowed list/node prefix proved by 29CBC2/29CBC4/29CBCA/29CBF5.
struct SelectedDrawableNode { SelectedDrawableNode *next, *prev; Drawable *value; };
struct SelectedDrawableListView { SelectedDrawableNode *head; };
class ActionManager
{
public:
	bool canOverrideSpecialPowerDestination(Object *, const Coord3D *, int, int);
};
extern ActionManager *TheActionManager;
enum SpecialPowerType { SPECIAL_INVALID = -1 };

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
	virtual const DrawableList *getAllSelectedDrawables() const;
	virtual void slot74();
	virtual void slot75();
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
	virtual void buildRegion(const ICoord2D *anchor, const ICoord2D *dest, IRegion2D *region);
	virtual int selectMatchingAcrossScreen();
	enum SelectionRules { SELECTION_ANY, SELECTION_ALL };
	bool canSelectedObjectsOverrideSpecialPowerDestination(const Coord3D *, SelectionRules, SpecialPowerType) const;
};

extern InGameUI *TheInGameUI;

// ?selectMatchingAcrossScreen@InGameUI@@UAEHXZ
int InGameUI::selectMatchingAcrossScreen()
{
	BfmeSelectionState *state = (*(BfmeSelectionState **)&TheLivingWorldLogic);
	if (state != 0 && state->isSelectionLocked() != 0)
		return 0;

	ICoord2D origin;
	ICoord2D size;
	IRegion2D region;
	TheTacticalView->getOrigin(&origin.x, &origin.y);
	size.x = TheTacticalView->getWidth();
	size.y = TheTacticalView->getHeight();
	buildRegion(&origin, &size, &region);
	Int numSelected = selectMatchingAcrossRegion(&region);
	if (numSelected == -1)
	{
		UnicodeString message = TheGameText->fetch("GUI:NothingSelected");
		TheInGameUI->message(message);
	}
	else if (numSelected != 0)
	{
		UnicodeString message = TheGameText->fetch("GUI:SelectedAcrossScreen");
		TheInGameUI->message(message);
	}
	return numSelected;
}

// ?TheTacticalView@@3PAVTacticalView@@A: the global at this VA is ?TheTacticalView@@3PAVView@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?TheTacticalView@@3PAVTacticalView@@A=?TheTacticalView@@3PAVView@@A")
// ?TheTacticalView@@3PAVTacticalView@@A: the global at VA 0xdfea3c is ?TheTacticalView@@3PAVView@@A.
#pragma comment(linker, "/alternatename:?TheTacticalView@@3PAVTacticalView@@A=?TheTacticalView@@3PAVView@@A")

// BFME1 ba7ddda7 InGameUI.cpp supplies the source algorithm. Independent
// target corroboration: 29CBA6..29CC19 complete RET12 plus internal return
// branch; UI singleton DFEDF0 slot124, Drawable +FC, rowed ActionManager
// 41BB49 with position/type/player-source arguments, and ANY=0 / ALL=1.
bool InGameUI::canSelectedObjectsOverrideSpecialPowerDestination(
	const Coord3D *loc, SelectionRules rule, SpecialPowerType spType) const
{
	int count = 0;
	int qualify = 0;
	const SelectedDrawableListView *selected =
		reinterpret_cast<const SelectedDrawableListView *>(TheInGameUI->getAllSelectedDrawables());
	for (SelectedDrawableNode *it = selected->head->next;
		it != selected->head; it = it->next) {
		Drawable *other = it->value;
		++count;
		if (TheActionManager->canOverrideSpecialPowerDestination(selectedObject(other), loc, spType, 0)) {
			if (rule == SELECTION_ANY)
				return true;
			++qualify;
		}
	}
	if (rule == SELECTION_ALL && count > 0 && qualify == count)
		return true;
	return false;
}
