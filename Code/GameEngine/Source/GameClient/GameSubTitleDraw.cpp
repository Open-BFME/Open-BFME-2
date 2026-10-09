// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX
//
// ?rva002600DC@GameSubTitle@@UAEXHPAXMMMM@Z, retail 0x002600DC (458 bytes). Slot 1
// of the GameSubTitle vtable 0x007F63F8 (between 0x0025FF73 and 0x0025FCBA);
// the class's constructor and getXFromAlignment are rowed in
// GameSubTitles.cpp, whose layout this view repeats (start frame +0x18, end
// frame +0x1C, style +0x0C, alignment +0x10, line +0x14, colour +0x08,
// display strings +0x24, count +0x30). WorldBuilder twin 0x00DA6550
// (callgraph evidence). Target evidence:
//  - drawn between the start and end frames; with style bit 0 also within
//    15 frames either side with alpha 0xFF less 18 per frame (clamped);
//  - the first display string's slot 15 gives the line size;
//  - per line: slot 16 (-1) width; x from getXFromAlignment 0x0025FF8F;
//    y from the rowed 0x0026003E with the line index; with style bit 2 a
//    background through TheDisplay's helper 0x0004263F (x y width height
//    alpha); then slot 10 (colour or alpha 0) and slot 13 (x y).
// The method name is a placeholder for the vtable slot.

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

class SubtitleDisplayString
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual void setColor(UnsignedInt color, UnsignedInt dropColor); // slot 10
	virtual void slot11(); virtual void slot12();
	virtual void draw(Int x, Int y); // slot 13
	virtual void slot14();
	virtual void getSize(Int *width, Int *height); // slot 15
	virtual Int getWidth(Int charPos); // slot 16
};

// TheDisplay's background helper 0x0004263F.
class Rva0004263F
{
public:
	void rva0004263F(Real x, Real y, Real width, Real height, Int color);
};

class Display;
extern Display *TheDisplay;

Int __cdecl Rva0026003EGet(Int line, void *layout, Real low, Real high);

class GameSubTitle
{
public:
	static Int getXFromAlignment(Int alignment, Int base, Int unused, Real low, Real high);
	virtual ~GameSubTitle();
	virtual void rva002600DC(Int frame, void *layout, Real left, Real top, Real right, Real bottom);
private:
	void *m_text; // +0x04
	UnsignedInt m_color; // +0x08
	Int m_style; // +0x0C
	Int m_alignment; // +0x10
	Int m_line; // +0x14
	Int m_startFrame; // +0x18
	Int m_endFrame; // +0x1C
	bool m_displayed; // +0x20
	SubtitleDisplayString *m_displayStrings[3]; // +0x24
	Int m_displayStringCount; // +0x30
};

void GameSubTitle::rva002600DC(Int frame, void *layout, Real left, Real top, Real right, Real bottom)
{
	bool show = false;
	Int alpha = 0xFF;
	if (frame >= m_startFrame && frame <= m_endFrame)
	{
		show = true;
	}
	else if (m_style & 1)
	{
		if (frame < m_startFrame && frame >= m_startFrame - 15)
		{
			show = true;
			alpha = 0xFF - ((m_startFrame - frame) * 18 < 0xFF ? (m_startFrame - frame) * 18 : 0xFF);
		}
		else if (frame > m_endFrame && frame <= m_endFrame + 15)
		{
			show = true;
			alpha = 0xFF - ((frame - m_endFrame) * 18 < 0xFF ? (frame - m_endFrame) * 18 : 0xFF);
		}
	}
	if (!show)
		return;
	alpha <<= 24;

	Int width;
	Int height = 0;
	m_displayStrings[0]->getSize(&width, &height);

	if (m_style & 4)
	{
		for (Int i = 0; i < m_displayStringCount; ++i)
		{
			Int lineWidth = m_displayStrings[i]->getWidth(-1);
			Int x = getXFromAlignment(m_alignment, lineWidth, (Int)layout, left, right);
			Int y = Rva0026003EGet(m_line + i, layout, top, bottom);
			((Rva0004263F *)TheDisplay)->rva0004263F((Real)x, (Real)y, (Real)lineWidth, (Real)height, alpha);
			m_displayStrings[i]->setColor(m_color | alpha, 0);
			m_displayStrings[i]->draw(x, y);
		}
	}
	else
	{
		for (Int i = 0; i < m_displayStringCount; ++i)
		{
			Int lineWidth = m_displayStrings[i]->getWidth(-1);
			Int x = getXFromAlignment(m_alignment, lineWidth, (Int)layout, left, right);
			Int y = Rva0026003EGet(m_line + i, layout, top, bottom);
			m_displayStrings[i]->setColor(m_color | alpha, 0);
			m_displayStrings[i]->draw(x, y);
		}
	}
}
