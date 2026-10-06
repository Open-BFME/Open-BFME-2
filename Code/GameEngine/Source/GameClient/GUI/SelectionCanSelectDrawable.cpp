// cl: /O1 /DNDEBUG /MD /EHsc
// ?CanSelectDrawable@@YA_NPBVDrawable@@_N@Z @0x0042FA63 300B: selection gate for selectFriends. Evidence: donor SelectionXlatCanSelectDrawable plus retail callers 0x0042FE95 0x00430F98, rowed callees, TheWindowManager TheTacticalView.
typedef bool Bool;
typedef unsigned int UnsignedInt;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct ICoord2D
{
	int x;
	int y;
};

enum ObjectStatusTypes;
enum KindOfType;

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	UnsignedInt m_flags108;
	unsigned char m_pad10C[0x10F - 0x10C];
	unsigned char m_byte10F;
	unsigned char m_byte110;
	unsigned char m_pad111[0x118 - 0x111];
	unsigned char m_byte118;
	unsigned char m_pad119[0x632 - 0x119];
	unsigned char m_byte632;
};

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isKindOf(KindOfType kind) const;
	Bool isSelectable() const;
	Bool isLocallyControlled() const;

public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x74 - 0x08];
	int m_id;
	unsigned char m_pad78[0x438 - 0x78];
	unsigned char m_priv438;
	unsigned char m_sup439;
};

class Drawable
{
public:
	unsigned char m_pad00[0xFC];
	Object *m_object;
};

class Rva00270260
{
public:
	Bool rva00270260();
};

class BFMERopeDrawable
{
public:
	const Coord3D *getPosition() const;
};

class GameWindow
{
public:
	UnsignedInt winGetStatus();
	GameWindow *winGetParent();
};

class View
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual int worldToScreen(const Coord3D *world, ICoord2D *screen);
};

extern View *TheTacticalView;

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76();
	virtual GameWindow *getWindowUnderCursor(int x, int y, Bool ignore);
};

extern GameWindowManager *TheWindowManager;

Bool CanSelectDrawable(const Drawable *draw, Bool dragSelecting)
{
	if (draw == 0 || draw->m_object == 0)
		return false;
	const Object *obj = draw->m_object;
	if ((obj->m_priv438 & 1) != 0)
	{
		ThingTemplate *tmpl = obj->m_template;
		if (tmpl->m_byte632 == 0)
		{
			if ((tmpl->m_byte10F & 4) == 0)
				return false;
		}
	}
	{
		ThingTemplate *tmpl = obj->m_template;
		if ((tmpl->m_flags108 & 2) == 0)
		{
			if ((tmpl->m_byte110 & 0x10) != 0)
				return false;
		}
		if ((tmpl->m_byte118 & 0x40) != 0)
			return false;
	}
	if (((Rva00270260 *)draw)->rva00270260())
		return false;
	GameWindow *window = 0;
	if (TheWindowManager != 0)
	{
		const Coord3D *pos = ((BFMERopeDrawable *)draw)->getPosition();
		ICoord2D screen;
		TheTacticalView->worldToScreen(pos, &screen);
		window = TheWindowManager->getWindowUnderCursor(screen.x, screen.y, false);
	}
	while (window != 0)
	{
		if ((window->winGetStatus() & 0x10000) == 0)
			return false;
		window = window->winGetParent();
	}
	if (dragSelecting)
	{
		UnsignedInt f = obj->m_template->m_flags108;
		if ((f & 0x80) != 0)
			return false;
		if ((f & 0x4000) != 0)
		{
			if (obj->isKindOf((KindOfType)0x49))
				return false;
		}
	}
	if (obj->testStatus((ObjectStatusTypes)3))
		return false;
	if (obj->m_sup439 != 0)
		return false;
	if (!obj->isSelectable())
		return false;
	if (dragSelecting && !obj->isLocallyControlled())
		return false;
	return true;
}
