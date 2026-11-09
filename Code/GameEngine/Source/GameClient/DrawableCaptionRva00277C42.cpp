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

#include "../../../Libraries/Include/Lib/ICoord2D.h"

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

struct Rva00290EABElem;
struct Rva00270FEEInner;
class BfmeFloatModule;
class Rva00270FEE
{
public:
	char *rva00270FEE();
	float rva00271008();
	const Rva00290EABElem *rva0027103F(int idx);
	char m_pad00[0x4];
private:
	char *m_04; // +0x04
	char m_pad08[0xF4];
	Rva00270FEEInner *m_fc; // +0xFC
	char m_pad100[0x4C];
	BfmeFloatModule **m_14c; // +0x14C
};

class Rva00276470Drawable
{
public:
	const Coord3D *rva00276470() const;
};

#include "../../Include/GameClient/DisplayString.h"

#include "../../Include/GameClient/Display.h"

#include "../../Include/GameClient/View.h"

#include "../../Include/GameClient/InGameUI.h"

extern Display *TheDisplay;
extern View *TheTacticalView;
extern InGameUI *TheInGameUI;

class Rva00277C42Host
{
public:
	void rva00277C42();
	char m_pad00[0x344];
private:
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

	TheTacticalView->worldToScreenTriReturn(&center, &screen);
	screen.x += m_captionDisplayString->getWidth(-1) / -2;

	Int width, height;
	m_captionDisplayString->getSize(&width, &height);
	Int xPos = screen.x - 1;
	Int yPos = screen.y - 1;
	TheDisplay->drawFillRect(xPos, yPos, width + 2, height + 2, 0x7d000000);
	TheDisplay->drawOpenRect(xPos, yPos, width + 2, height + 2, 1.0f, 0xff141414);

	m_captionDisplayString->setColors(TheInGameUI->m_drawableCaptionColor, 0xff000000);
	m_captionDisplayString->draw(screen.x, screen.y, 1, 1);
}
