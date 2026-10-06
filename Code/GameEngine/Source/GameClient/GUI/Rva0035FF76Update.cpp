// cl: /DNDEBUG /MD
// ?update@Rva0035FF76@@UAEXH@Z @ 0x0036044A (42B):
// slot 2 offset 0x8 of vtable 0x0081670C (class of ??1Rva0035FF76@@UAE@XZ).
// Range-check frame against m_startFrame (+0x10) and m_endFrame (+0x14),
// set m_isFinished (+0x08) at either end, then m_drawState (+0x2c) is frame.
// No winHide unlike FullFade/TextOnFrame updates. Evidence: vtable 0x0081670C
// slot 2 plus rowed neighbours plus FadeColor init 0x0035FF85 in same class.

typedef int Int;
typedef bool Bool;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

class GameWindow;

class Rva0035FF76
{
public:
	virtual ~Rva0035FF76();
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse();
	virtual void draw();
	virtual void slot5();
	virtual void skip();
	virtual void slot7();

	Int m_frameLength;	// +0x04
	Bool m_isFinished;	// +0x08
	Bool m_isForward;	// +0x09
	Bool m_isReversed;	// +0x0a
	unsigned char m_pad0B;	// +0x0b
	GameWindow *m_win;	// +0x0c
	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
	Int m_posX;		// +0x18
	Int m_posY;		// +0x1c
	Int m_sizeX;		// +0x20
	Int m_sizeY;		// +0x24
	float m_percent;	// +0x28
	Int m_drawState;	// +0x2c
	float m_fadeRed;	// +0x30
	float m_fadeGreen;	// +0x34
	float m_fadeBlue;	// +0x38
	unsigned char m_red;	// +0x3c
	unsigned char m_green;	// +0x3d
	unsigned char m_blue;	// +0x3e
};

void Rva0035FF76::update(Int frame)
{
	m_drawState = -1;
	if (frame < m_startFrame || frame > m_endFrame)
	{
		return;
	}
	if (frame == m_startFrame || frame == m_endFrame)
	{
		m_isFinished = TRUE;
	}
	m_drawState = frame;
}
