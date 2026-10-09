// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva002778E1@Drawable@@QAEXXZ retail 0x002778E1 (237B): draws a numeral
// over the drawable's icon anchor in the manner of Zero Hour's
// drawGroupNumber. The anchor (0x002775C9) is projected by TheTacticalView
// (+0x160, zero means on screen); the owning object (+0xFC) must answer the
// unrowed 0x0028D900 query; the numeral is TheDisplayStringManager's
// string (+0x40) for min(object +0x04 record's +0x0C count + 1, 9), scaled
// 2.0 x 1.5 (+0x44), coloured with the controlling player's +0x280 colour
// on frames where (TheGameClient frame (+0x7C) + count) & 0xA, else -1, over
// an opaque black drop colour (+0x28), drawn at the screen point with
// TheDrawGroupInfo's +0x14/+0x18 offsets (+0x38) and scaled back to 1 x 1.
// Views follow DrawableDrawVeterancy.cpp; slot names are inferred.
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct ICoord2D
{
	Int x;
	Int y;
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
	virtual void slot72();
	virtual Real getZoom(); // +0x124
	virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81();
	virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85();
	virtual void slot86(); virtual void slot87();
	virtual Int worldToScreen(const Coord3D *world, ICoord2D *screen); // +0x160
};
extern View *TheTacticalView;

class DisplayString
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void setColor(Int color, Int dropColor); // +0x28
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void draw(Int x, Int y, Int xOffset, Int yOffset); // +0x38
	virtual void slot15(); virtual void slot16();
	virtual void setScale(Real x, Real y); // +0x44
};

class DisplayStringManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual DisplayString *getNumeralString(Int number); // +0x40
};
extern DisplayStringManager *TheDisplayStringManager;

class GameClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30();
	virtual UnsignedInt getFrame(); // +0x7C
};
extern GameClient *TheGameClient;

struct DrawGroupInfo
{
	char m_pad00[0x14];
	Int m_dropShadowOffsetX; // +0x14
	Int m_dropShadowOffsetY; // +0x18
};
extern DrawGroupInfo *TheDrawGroupInfo;

class Player
{
public:
	Int getPlayerColor() const { return m_color; }
private:
	char m_pad000[0x280];
	Int m_color; // +0x280
};

struct ObjectLevelRecord
{
	char m_pad00[0x0C];
	Int m_count; // +0x0C
};

class Object
{
public:
	Bool rva0028D900(Real *a, Real *b);
	Player *getControllingPlayer() const;
	const ObjectLevelRecord *getLevelRecord() const { return m_record; }
private:
	void *m_vtable;
	const ObjectLevelRecord *m_record; // +0x04
};

class Drawable
{
public:
	void rva002778E1();
	void rva002775C9(Coord3D *pos);
private:
	char m_pad000[0xFC];
	Object *m_object; // +0xFC
};

void Drawable::rva002778E1()
{
	Object *obj = m_object;
	Coord3D pos;
	ICoord2D screen;
	rva002775C9(&pos);
	if (TheTacticalView->worldToScreen(&pos, &screen) != 0)
		return;

	Real a, b;
	if (!obj->rva0028D900(&a, &b))
		return;

	Int count = obj->getLevelRecord()->m_count;
	Int number = count + 1;
	if (number > 9)
		number = 9;
	DisplayString *string = TheDisplayStringManager->getNumeralString(number);
	if (string == 0)
		return;

	string->setScale(2.0f, 1.5f);
	Int color;
	if ((TheGameClient->getFrame() + count) & 0xA)
		color = obj->getControllingPlayer()->getPlayerColor();
	else
		color = -1;
	string->setColor(color, 0xFF000000);
	string->draw(screen.x, screen.y, TheDrawGroupInfo->m_dropShadowOffsetX, TheDrawGroupInfo->m_dropShadowOffsetY);
	string->setScale(1.0f, 1.0f);
}
