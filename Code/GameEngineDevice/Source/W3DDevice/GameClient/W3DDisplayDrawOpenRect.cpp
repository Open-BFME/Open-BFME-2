// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ?drawOpenRect@W3DDisplay@@UAEXMMMMMI@Z, retail 0x00044A1A..0x00044C9A (640 bytes)
// thiscall RET 0x18.
//
// Identity: W3DDisplay vtable slot +0xE0 (absolute reference at 0x007C3D60)
// right after the two rowed line slots 0x00044928 (+0xD8 two colours) and
// 0x000448CF (+0xDC one colour) -- Zero Hour's Display order drawLine,
// drawLine, drawOpenRect. Body follows Zero Hour W3DDisplay::drawOpenRect
// (GeneralsMD W3DDisplay.cpp) with BFME 2's float coordinates: with clipping
// (+0x17C, region +0x16C) four edges go through rowed ClipLine2D 0x0025F406
// and the +0xDC line virtual; otherwise the +0x168 Render2D clears its +0x48
// texturing byte and takes rowed Add_Outline 0x0011C1C0 (Reset/Render calls
// of Zero Hour are gone in retail). Same receiver layout as the sibling
// W3DDisplayRva000448CF.cpp. WB twin 0x00971150 (vtable evidence) is unnamed;
// the method name and argument types are carried from Zero Hour.
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Int;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };
bool ClipLine2D(ICoord2D *start, ICoord2D *end, ICoord2D *returnStart, ICoord2D *returnEnd, IRegion2D *region);

class RectClass
{
public:
	RectClass(float left, float top, float right, float bottom) : Left(left), Top(top), Right(right), Bottom(bottom) {}
	float Left;
	float Top;
	float Right;
	float Bottom;
};

class Render2DClass
{
public:
	void Enable_Texturing(bool onoff) { m_texturing = onoff; }
	void Add_Outline(const RectClass &rect, float width, unsigned long color);

private:
	char m_pad00[0x48];
	bool m_texturing;					// +0x48
};

#define W3DDISPLAY_SLOT(n) virtual void slot##n();

class W3DDisplay
{
public:
	W3DDISPLAY_SLOT(00) W3DDISPLAY_SLOT(01) W3DDISPLAY_SLOT(02) W3DDISPLAY_SLOT(03)
	W3DDISPLAY_SLOT(04) W3DDISPLAY_SLOT(05) W3DDISPLAY_SLOT(06) W3DDISPLAY_SLOT(07)
	W3DDISPLAY_SLOT(08) W3DDISPLAY_SLOT(09) W3DDISPLAY_SLOT(10) W3DDISPLAY_SLOT(11)
	W3DDISPLAY_SLOT(12) W3DDISPLAY_SLOT(13) W3DDISPLAY_SLOT(14) W3DDISPLAY_SLOT(15)
	W3DDISPLAY_SLOT(16) W3DDISPLAY_SLOT(17) W3DDISPLAY_SLOT(18) W3DDISPLAY_SLOT(19)
	W3DDISPLAY_SLOT(20) W3DDISPLAY_SLOT(21) W3DDISPLAY_SLOT(22) W3DDISPLAY_SLOT(23)
	W3DDISPLAY_SLOT(24) W3DDISPLAY_SLOT(25) W3DDISPLAY_SLOT(26) W3DDISPLAY_SLOT(27)
	W3DDISPLAY_SLOT(28) W3DDISPLAY_SLOT(29) W3DDISPLAY_SLOT(30) W3DDISPLAY_SLOT(31)
	W3DDISPLAY_SLOT(32) W3DDISPLAY_SLOT(33) W3DDISPLAY_SLOT(34) W3DDISPLAY_SLOT(35)
	W3DDISPLAY_SLOT(36) W3DDISPLAY_SLOT(37) W3DDISPLAY_SLOT(38) W3DDISPLAY_SLOT(39)
	W3DDISPLAY_SLOT(40) W3DDISPLAY_SLOT(41) W3DDISPLAY_SLOT(42) W3DDISPLAY_SLOT(43)
	W3DDISPLAY_SLOT(44) W3DDISPLAY_SLOT(45) W3DDISPLAY_SLOT(46) W3DDISPLAY_SLOT(47)
	W3DDISPLAY_SLOT(48) W3DDISPLAY_SLOT(49) W3DDISPLAY_SLOT(50) W3DDISPLAY_SLOT(51)
	W3DDISPLAY_SLOT(52) W3DDISPLAY_SLOT(53) W3DDISPLAY_SLOT(54)
	// +0xDC (retail 0x000448CF): the one-colour line.
	virtual void drawLineSingleColor(Real startX, Real startY, Real endX, Real endY, Real lineWidth, UnsignedInt lineColor);
	// +0xE0 (retail 0x00044A1A).
	virtual void drawOpenRect(Real startX, Real startY, Real width, Real height, Real lineWidth, UnsignedInt lineColor);

private:
	char m_pad004[0x168 - 0x004];
	Render2DClass *m_2DRender;			// +0x168
	IRegion2D m_clipRegion;				// +0x16C
	bool m_isClippedEnabled;			// +0x17C
};

void W3DDisplay::drawOpenRect(Real startX, Real startY, Real width, Real height, Real lineWidth, UnsignedInt lineColor)
{
	if (m_isClippedEnabled)
	{
		ICoord2D start, end, returnStart, returnEnd;
		start.x = startX;
		start.y = startY;

		end.x = start.x;
		end.y = start.y + height;
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion))
			drawLineSingleColor(returnStart.x, returnStart.y, returnEnd.x, returnEnd.y, lineWidth, lineColor);

		end.x = start.x + width;
		end.y = start.y;
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion))
			drawLineSingleColor(returnStart.x, returnStart.y, returnEnd.x, returnEnd.y, lineWidth, lineColor);

		start.x = startX + width;
		start.y = startY;
		end.x = start.x;
		end.y = start.y + height;
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion))
			drawLineSingleColor(returnStart.x, returnStart.y, returnEnd.x, returnEnd.y, lineWidth, lineColor);

		start.x = startX;
		start.y = startY + height;
		end.x = start.x + width;
		end.y = start.y;
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion))
			drawLineSingleColor(returnStart.x, returnStart.y, returnEnd.x, returnEnd.y, lineWidth, lineColor);
	}
	else
	{
		m_2DRender->Enable_Texturing(false);
		m_2DRender->Add_Outline(RectClass(startX, startY, startX + width, startY + height), lineWidth, lineColor);
	}
}
