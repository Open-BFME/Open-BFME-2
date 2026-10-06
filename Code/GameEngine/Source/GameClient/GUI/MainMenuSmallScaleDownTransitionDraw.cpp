// cl: /MD
// ?draw@MainMenuSmallScaleDownTransition@@UAEXXZ @0x0035DA9F 160B: vslot draw slot 4 offset 0x10 of vtable 0x00816554 (class of ??1Rva0035DA01). Evidence: same vtable as rowed init 0x0035DBF3 slot 1 plus BFME1 MainMenuSmallScaleDownTransition_draw donor plus TheDisplay 0x00DFE9D8 plus rowed W3DDisplay draw 0x0004D6B3 plus image at win+0x48 plus drawState 1..5.

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

class GameWindow;

struct SmallScaleDownWindowImages
{
	unsigned char m_pad[0x48];
	const Image *m_enabledImage;
};

class MainMenuSmallScaleDownTransition
{
public:
	virtual ~MainMenuSmallScaleDownTransition();
	virtual void init(GameWindow *win);
	virtual void slot2();
	virtual void slot3();
	virtual void draw();

	Int m_frameLength;		// +0x04
	Bool m_isFinished;		// +0x08
	Bool m_isForward;		// +0x09
	unsigned char m_pad0a[2];
	GameWindow *m_win;		// +0x0c
	ICoord2D m_pos;			// +0x10
	ICoord2D m_size;		// +0x18
	Int m_drawState;		// +0x20
	ICoord2D m_growPos;		// +0x24
	ICoord2D m_growSize;		// +0x2c
	ICoord2D m_incrementSize;	// +0x34
	GameWindow *m_growWin;		// +0x3c
};

void MainMenuSmallScaleDownTransition::draw()
{
	if (!m_win)
		return;
	const Image *image = ((const SmallScaleDownWindowImages *)m_win)->m_enabledImage;
	if (m_drawState <= 0 || m_drawState >= 6)
		return;
	Int x = m_pos.x - ((m_incrementSize.x * m_drawState) / 2);
	Int y = m_pos.y - ((m_incrementSize.y * m_drawState) / 2);
	Int x1 = m_pos.x + m_size.x + ((m_incrementSize.x * m_drawState) / 2);
	Int y1 = m_pos.y + m_size.y + ((m_incrementSize.y * m_drawState) / 2);
	((W3DDisplay *)TheDisplay)->rva0004D6B3((Image *)image, (float)x, (float)y, (float)x1, (float)y1, -1, 2);
}
