// cl: /O1 /MD /arch:SSE
// ?draw@ControlBarArrowTransition@@UAEXXZ @0x0035D924 221B: vslot draw slot 4 offset 0x10 of vtable 0x00816530.
// Evidence: same vtable as matched ControlBarArrow update 0x0035D75D slot 2; observed init 0x0035D83E slot 1
// plus reverse 0x0035D1BD slot 3 (clears +0x08/+0x09) plus skip forwarder 0x0035D781 slot 6.
// Retail bytes prove layout: mov edx,[ecx+0x30] drawState, jl return if <0, cmp 16 for fade split,
// float math with 1.0f at 0xBBB8D8 and 255.0f at 0xBC2900, single call to rowed W3DDisplay 0x0004D6B3
// via TheDisplay 0x00DFE9D8, ret (void, no param). Ported from BFME1 GameWindowTransitionsStyles.cpp
// ControlBarArrowTransition::draw plus ControlBarArrowTransition_draw_Thunk.cpp (thunk uses
// begin/drawCore/end + g_bfme globals; BFME2 uses W3DDisplay wrapper + 1.0f/255.0f literals like
// MainMenuSmallScaleDownTransitionDraw.cpp sibling).

// BFME1 donor revision: 6583b3c1ff21db4a561285717028fdafc780b7db.
// Partial view of slots 0..4 and accessed fields only. This TU emits no vtable
// and neither constructs nor allocates the class; later slots remain unmodeled.

typedef int Int;
typedef unsigned char Bool;

struct ICoord2D
{
	Int x;
	Int y;
};

class Image;
class Display;
extern Display *TheDisplay;

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

inline Int GameMakeColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	return ((unsigned int)alpha << 24) | ((unsigned int)red << 16) |
		((unsigned int)green << 8) | blue;
}

class GameWindow;

class ControlBarArrowTransition
{
public:
	virtual ~ControlBarArrowTransition();
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse(void);
	virtual void draw();

	Int m_frameLength;		// +0x04
	Bool m_isFinished;		// +0x08
	Bool m_isForward;		// +0x09
	Bool m_isReversed;		// +0x0a
	unsigned char m_pad0B;		// +0x0b
	GameWindow *m_win;		// +0x0c
	ICoord2D m_pos;			// +0x10
	ICoord2D m_incrementPos;	// +0x18
	ICoord2D m_size;		// +0x20
	float m_percent;		// +0x28
	float m_fadePercent;		// +0x2c
	Int m_drawState;		// +0x30
	const Image *m_arrowImage;	// +0x34
};

void ControlBarArrowTransition::draw(void)
{
	if (m_drawState < 0)
		return;
	if (m_drawState < 16)
	{
		Int yPos = m_pos.y + m_incrementPos.y * m_drawState;
		((W3DDisplay *)TheDisplay)->rva0004D6B3((Image *)m_arrowImage, (float)m_pos.x, (float)yPos,
			(float)(m_pos.x + m_size.x), (float)(yPos + m_size.y), -1, 2);
	}
	else
	{
		Int alpha = (Int)((1.0f - m_fadePercent * (m_drawState - 16)) * 255.0f);
		if (alpha > 255)
			alpha = 255;
		Int yPos = m_pos.y + m_incrementPos.y * 15;
		((W3DDisplay *)TheDisplay)->rva0004D6B3((Image *)m_arrowImage, (float)m_pos.x, (float)yPos,
			(float)(m_pos.x + m_size.x), (float)(yPos + m_size.y),
			GameMakeColor(255, 255, 255, (unsigned char)alpha), 2);
	}
}
