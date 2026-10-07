// BFME1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20 BfmeConv1264.cpp
// is the arithmetic lead. Native 0x380869..0x3808E8 ends RET immediately
// before the rowed AptGuiFX::OnInitialized entry. Existing TooltipHide owns
// TheTooltipString at VA0xE022E4, also created by the native show helper.
// ShowToolTip0x3808F0 pushes output addresses0xE022F0 and0xE022EC to the
// display-string size slot+0x3C at0x3809C6. This body subtracts half those
// measured dimensions and sends integer coordinates to slot+0x34.
// Width/height names describe those proven globals; original names are unknown.
// The slot+0xC nonzero predicate's original name remains unasserted.
// Both inputs have the canonical Coord2D layout; original helper name unknown.
// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD -ICode/Libraries/Include/Lib
// Open-BFME5 conversions.

#include "Coord2D.h"
int TooltipStringWidth;
int TooltipStringHeight;

class Rva00380869Display
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual int slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34(int a, int b);
};

class DisplayString;
extern DisplayString *TheTooltipString;

// ?rva00380869@@YAXPAVCoord2D@@0@Z
void rva00380869(Coord2D *a, Coord2D *b)
{
	if (!reinterpret_cast<Rva00380869Display * &>(TheTooltipString))
		return;
	if (!reinterpret_cast<Rva00380869Display * &>(TheTooltipString)->slot0C())
		return;
	reinterpret_cast<Rva00380869Display * &>(TheTooltipString)->slot34(
		(int)(*(volatile float *)&b->x * 0.5f + a->x - TooltipStringWidth * 0.5f + 0.5f),
		(int)(*(volatile float *)&b->y * 0.5f + a->y - TooltipStringHeight * 0.5f + 0.5f));
}
