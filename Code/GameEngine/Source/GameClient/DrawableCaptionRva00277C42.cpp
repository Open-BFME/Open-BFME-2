// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva00277C42@Rva00277C42Host@@QAEXXZ retail 0x00277C42..0x00277DB4
// (370 bytes). Drawable::drawCaption: the name plate over a drawable.
// Called from the Drawable draw-phase switch 0x002796D9 case 0 (already
// pinned under this host name). BFME 1 donor DrawableCaptionAndAmbient.cpp
// (drawCaption 0x00420150) and the WorldBuilder twin 0x00CACFB0 share the
// shape: skip without a caption display string (+0x344 here) take the
// geometry centre (0x00270FEE then Rva0087DC00::get 0x006BD470) plus the
// drawable position (0x00276470) project it through TheTacticalView
// (vtable +0x160) centre by the caption width (DisplayString +0x40 of -1)
// draw a filled rect 0x7D000000 (Display +0xE4) and an open rect 0xFF141414
// width 1 (Display +0xE0) one pixel around the string size (+0x3C) then
// set the caption colour from TheInGameUI +0x7A8 (drop colour black +0x28)
// and draw the string (+0x38).
#include "../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;
typedef int Int;
typedef unsigned int Color;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Rva0087DC00Vec
{
	int x;
	int y;
	int z;
};

class Rva0087DC00
{
public:
	void get(Rva0087DC00Vec *out);
};

class Rva00270FEE
{
public:
	char *rva00270FEE();
};

class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
};

class DisplayString
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void setColor(Color color, Color dropColor); // +0x28
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void draw(Int x, Int y, Int scaleX, Int scaleY); // +0x38
	virtual void getSize(Int *width, Int *height); // +0x3C
	virtual Int getWidth(Int line); // +0x40
};

class Display
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
	virtual void drawOpenRect(Real x, Real y, Real width, Real height, Real lineWidth, Color color); // +0xE0
	virtual void drawFillRect(Real x, Real y, Real width, Real height, Color color); // +0xE4
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
	virtual Int worldToScreen(const Coord3D *world, ICoord2D *screen); // +0x160
};

class InGameUI
{
	char m_pad[0x7a8];

public:
	Color m_drawableCaptionColor; // +0x7A8
};

extern Display *TheDisplay;
extern View *TheTacticalView;
extern InGameUI *TheInGameUI;

class Rva00277C42Host
{
public:
	void rva00277C42();

private:
	char m_pad[0x344];
	DisplayString *m_captionDisplayString; // +0x344
};

void Rva00277C42Host::rva00277C42()
{
	if (m_captionDisplayString == 0)
		return;

	Coord3D center;
	ICoord2D screen;
	reinterpret_cast<Rva0087DC00 *>(reinterpret_cast<Rva00270FEE *>(this)->rva00270FEE())
		->get(reinterpret_cast<Rva0087DC00Vec *>(&center));
	const Coord3D *pos = reinterpret_cast<Rva00276470Drawable *>(this)->rva00276470();
	center.x += pos->x;
	center.y += pos->y;
	center.z += pos->z;

	TheTacticalView->worldToScreen(&center, &screen);
	screen.x += m_captionDisplayString->getWidth(-1) / -2;

	Int width, height;
	m_captionDisplayString->getSize(&width, &height);
	Int xPos = screen.x - 1;
	Int yPos = screen.y - 1;
	TheDisplay->drawFillRect(xPos, yPos, width + 2, height + 2, 0x7d000000);
	TheDisplay->drawOpenRect(xPos, yPos, width + 2, height + 2, 1.0f, 0xff141414);

	m_captionDisplayString->setColor(TheInGameUI->m_drawableCaptionColor, 0xff000000);
	m_captionDisplayString->draw(screen.x, screen.y, 1, 1);
}
