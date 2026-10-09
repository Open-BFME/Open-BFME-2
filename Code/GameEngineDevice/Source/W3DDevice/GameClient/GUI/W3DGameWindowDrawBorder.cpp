// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?drawBorder@Rva00104DB0@@UAEXPAVGameWindow@@@Z retail 0x00105AF3..0x00105CC7
// (468 bytes EH RET 4). It is slot 0 of the window-drawer vtable 0x007CF800
// (??_7Rva00104DB0@@6B@; slot 5 is the rowed deleting dtor 0x00104F16).
// The base vtable 0x007CF7E8 holds it as a pure slot. Zero Hour's
// W3DGameWindow::winDrawBorder reached through this drawer with the window
// passed explicitly. The body follows the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva0078E570DrawBorder.cpp
// (75fe8bad1b2244e6bc97ae83fbfc96e10d1a302d).
// - It walks the 32 style bits until one is handled.
// - Check box and sliders are skipped.
// - The entry field shrinks by the label width: TheWindowManager slot 74 text
//   size of the rowed winGetFont / winGetText when the rowed winGetTextLength
//   is non-zero.
// - The scroll list box subtracts the slider child's height (+0x2C list data /
//   +0x0A scroll flag / +0x24 slider / rowed child getter 0x003140C8) and
//   lifts by 4 under a label.
// - Buttons / static text / progress bar / user window / tab control blit the
//   plain rect.
// Every border goes through the rowed W3DGameWindow::blitBorderRect 0x00105584.
#include "unicode_string.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

class GameFont;

class GameWindow
{
public:
	Int winGetScreenPosition(Int *x, Int *y);
	Int winGetSize(Int *width, Int *height);
	UnsignedInt winGetStyle();
	Int winGetTextLength();
	UnicodeString winGetText();
	GameFont *winGetFont();
};

class Rva003140C8DwordField
{
public:
	Int get() const;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct Rva00104DB0ListData
{
	char m_pad00[0x0A];
	Bool scrollBar;									// +0x0A
	char m_pad0B[0x24 - 0x0B];
	GameWindow *slider;								// +0x24
};

struct Rva00104DB0WindowView
{
	char m_pad00[0x2C];
	void *m_userData;								// +0x2C
};

class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class Rva00104DB0ManagerView
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V10(1) V10(2) V10(3) V10(4) V10(5) V10(6)
	V(70) V(71) V(72) V(73)
#undef V10
#undef V
	virtual void winGetTextSize(GameFont *font, UnicodeString text, Int *width, Int *height, Int maxWidth);	// slot 74
};

class Rva00104DB0;

class W3DGameWindow
{
	friend class Rva00104DB0;
protected:
	void blitBorderRect(Int x, Int y, Int width, Int height);
};

class Rva00104DB0Base
{
public:
	virtual void drawBorder(GameWindow *window) = 0;
};

class Rva00104DB0 : public Rva00104DB0Base
{
public:
	virtual void drawBorder(GameWindow *window);
};

void Rva00104DB0::drawBorder(GameWindow *window)
{
	Bool found = false;
	Int originalX, originalY;
	Int x, y;
	Int width, height;
	UnsignedInt i;
	Int bits;

	window->winGetScreenPosition(&originalX, &originalY);
	for (i = 0; i < 32 && found == false; ++i)
	{
		bits = 1 << i;
		if (window->winGetStyle() & bits)
		{
			switch (window->winGetStyle() & bits)
			{
				case 4:		// GWS_CHECK_BOX
				case 8:
				case 16:
					found = true;
					break;

				case 0x40:	// GWS_ENTRY_FIELD
				{
					window->winGetSize(&width, &height);
					x = originalX;
					y = originalY;
					if (window->winGetTextLength())
					{
						Int textWidth = 0;
						((Rva00104DB0ManagerView *)TheWindowManager)->winGetTextSize(window->winGetFont(),
							window->winGetText(), &textWidth, 0, 0);
						width -= textWidth + 6;
						x += textWidth + 6;
					}
					reinterpret_cast<W3DGameWindow *>(this)->blitBorderRect(x, y, width, height);
					found = true;
					break;
				}

				case 0x20:	// GWS_SCROLL_LISTBOX
				{
					Rva00104DB0ListData *list = (Rva00104DB0ListData *)((Rva00104DB0WindowView *)window)->m_userData;
					Int sliderAdjustment = 0;
					Int labelAdjustment = 0;
					if (list->scrollBar)
					{
						GameWindow *child = (GameWindow *)((const Rva003140C8DwordField *)list->slider)->get();
						ICoord2D size;
						child->winGetSize(&size.x, &size.y);
						sliderAdjustment = size.y;
					}
					if (window->winGetTextLength())
						labelAdjustment = 4;
					window->winGetSize(&width, &height);
					reinterpret_cast<W3DGameWindow *>(this)->blitBorderRect(originalX - 3,
						originalY - (3 + labelAdjustment), width + 3 - sliderAdjustment, height + 6);
					found = true;
					break;
				}

				case 1:
				case 2:
				case 0x80:
				case 0x100:
				case 0x200:
				case 0x2000:
					window->winGetSize(&width, &height);
					reinterpret_cast<W3DGameWindow *>(this)->blitBorderRect(originalX, originalY, width, height);
					found = true;
					break;
			}
		}
	}
}
