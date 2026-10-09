// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
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

class Vector2
{
public:
	float X;
	float Y;

	Vector2(float x, float y) : X(x), Y(y) {}
};

class Render2DSentenceClass
{
public:
	void Reset_Polys();
	void Set_Location(const Vector2 &loc);
	void Draw_Sentence(Int color0, Int color1, Int color2, Int color3);

	char m_body[0xC4];
};

class Rva00155AD0
{
public:
	void rva00155AD0();
};

class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class Rva00105216ManagerView
{
public:
#define V(n) virtual void slot##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09)
	V10(1) V10(2) V10(3) V10(4) V10(5) V10(6)
#undef V10
#undef V
	virtual Color winMakeColor(UnsignedByte red, UnsignedByte green, UnsignedByte blue, UnsignedByte alpha); // slot 70
};

class Rva00104DB0
{
public:
	virtual ~Rva00104DB0();
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
