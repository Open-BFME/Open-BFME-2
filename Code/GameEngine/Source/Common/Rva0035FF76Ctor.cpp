// cl: /MD
// ??0Rva0035FF76@@QAE@XZ @ 0x0036006F 75B: Rva0035FF76 ctor, base ??0Rva001DBAA4 at 0x001DBAA4.
// Vtable 0x0081670C, m_drawState=-1 m_endFrame=30 m_frameLength=30 m_startFrame=0 m_win=0
// m_percent=0.0f m_isForward true m_fadeRed/Green/Blue=0.0f m_red/green/blue=0.
// Layout from Rva0035FF76Init.cpp; caller 0x003600F8 factory news 0x40.
class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_frameLength;
	bool m_isFinished;
	bool m_isForward;
	bool m_isReversed;
	void *m_win;
};

class Rva0035FF76 : public Rva001DBAA4
{
public:
	virtual ~Rva0035FF76();
	virtual void init(void *win);
	virtual void update(int frame);
	virtual void reverse();
	virtual void draw();
	virtual void skip();
	virtual bool isFinished();
	virtual int getFrameLength();
	Rva0035FF76();
	int m_startFrame;
	int m_endFrame;
	int m_posX;
	int m_posY;
	int m_sizeX;
	int m_sizeY;
	float m_percent;
	int m_drawState;
	float m_fadeRed;
	float m_fadeGreen;
	float m_fadeBlue;
	unsigned char m_red;
	unsigned char m_green;
	unsigned char m_blue;
};

Rva0035FF76::Rva0035FF76()
{
	m_startFrame = 0;
	m_drawState = -1;
	m_endFrame = 30;
	m_frameLength = 30;
	m_win = 0;
	m_percent = 0.0f;
	m_isForward = true;
	m_fadeRed = 0.0f;
	m_fadeGreen = 0.0f;
	m_fadeBlue = 0.0f;
	m_red = 0;
	m_green = 0;
	m_blue = 0;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?init@Rva0035FF76@@UAEXPAX@Z=?init@Rva0035FF76@@UAEXPAVGameWindow@@@Z")
#pragma comment(linker, "/alternatename:?skip@Rva0035FF76@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?getFrameLength@Rva0035FF76@@UAEHXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
