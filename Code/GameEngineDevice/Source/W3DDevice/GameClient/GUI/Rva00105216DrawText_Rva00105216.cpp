// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Split from Rva00105216DrawText.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// The drawer owns the background pass below (519B at 0x0010500F) and this
// text pass. Vtable 0x007CF800 independently puts background at slot 1
// and the deleting destructor at slot 5.
//
// ?rva00105216@Rva00104DB0@@QAEXH@Z retail 0x00105216..0x001052F9
// (227 bytes RET 4). The window drawer's text pass in the shape of Zero
// Hour's W3DGameWindow::drawText(Color): a pending rebuild flag (+0xD5) or
// a new colour (+0xD0) marks the text dirty; when dirty or when the
// position flag (+0xD4) is set the +0x04 Render2DSentenceClass (layout from
// the rowed dtor 0x00104DB0) is rebuilt: rowed Reset_Polys 0x00154EC0 and
// Set_Location 0x00154EF0 and pinned Draw_Sentence 0x00155B00 draw a black
// outline (TheWindowManager slot 70 winMakeColor 0 0 0 255) one pixel off
// the +0xC8/+0xCC text position and then the text in the current colour;
// the position flag is cleared. The rowed render 0x00155AD0 always runs.
// It sits between the drawer's draw slot 0x0010500F and initBorders in the
// W3DGameWindow.cpp region. Class identity is address-derived.

typedef int Int;
typedef int Color;
typedef unsigned char UnsignedByte;
class Image;

#include "../../../../../../reference/shims/wwmath/Vector2.h"

#include "../../../../../Libraries/Source/WWVegas/WW3D2/Render2DSentenceClass.h"

#include "../../../../Include/W3DDevice/GameClient/Rva00155AD0.h"

class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class Rva00105216ManagerView
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V10(1) V10(2) V10(3) V10(4) V10(5)
 V(60) V(61) V(62) V(63) V(64) V(65)
 virtual void winDrawImage(const Image *,Int,Int,Int,Int,Color);
 virtual void winFillRect(Color,float,Int,Int,Int,Int);
 virtual void winOpenRect(Color,float,Int,Int,Int,Int);
 V(69)
#undef V10
#undef V
	virtual Color winMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha); // slot 70
};

class Image;
#include "../../../../../GameEngine/Include/GameClient/Bfme2GameWindow.h"
struct Rva0010500FDrawData {
 char unknown00[8]; unsigned int state;
 char unknown0c[0x17c-0xc]; Int imageOffsetX,imageOffsetY;
 char unknown184[0x1a4-0x184]; void *videoBuffer;
};
class Display; extern Display *TheDisplay;
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"
class Rva00104DB0
{
public:
	virtual void drawBorder(GameWindow *);                       // slot 0
 virtual void rva0010500F(GameWindow *,Rva0010500FDrawData *); // slot 1
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual ~Rva00104DB0();                                    // slot 5
	void rva00105216(Color color);

private:
	Render2DSentenceClass m_textRenderer; // +0x04
	Int m_textPosX;                       // +0xC8
	Int m_textPosY;                       // +0xCC
	Color m_currTextColor;                // +0xD0
	bool m_newTextPos;                    // +0xD4
	bool m_needPolyDraw;                  // +0xD5
};

void Rva00104DB0::rva00105216(Color color)
{
	bool needDraw = false;

	if (m_needPolyDraw)
	{
		m_needPolyDraw = false;
		needDraw = true;
	}

	if (m_currTextColor != color)
	{
		m_currTextColor = color;
		needDraw = true;
	}

	if (needDraw || m_newTextPos)
	{
		Color outline = reinterpret_cast<Rva00105216ManagerView *>(TheWindowManager)->winMakeColor(0, 0, 0, 255);

		m_textRenderer.Reset_Polys();
		m_textRenderer.Set_Location(Vector2(m_textPosX + 1, m_textPosY + 1));
		m_textRenderer.Draw_Sentence(outline, outline, outline, outline);

		m_textRenderer.Set_Location(Vector2(m_textPosX, m_textPosY));
		m_textRenderer.Draw_Sentence(m_currTextColor, m_currTextColor, m_currTextColor, m_currTextColor);

		m_newTextPos = false;
	}

	reinterpret_cast<Rva00155AD0 *>(&m_textRenderer)->rva00155AD0();
}

