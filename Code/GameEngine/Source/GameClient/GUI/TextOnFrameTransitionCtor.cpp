// cl: /DNDEBUG /MD
// ??0TextOnFrameTransition@@QAE@XZ @0x0035FA03 39B: ctor stores vtable 0x0081669C, calls rowed base ??0Rva001DBAA4 at 0x001DBAA4, then startFrame +0x10 zero endFrame +0x14 30 frameLength +0x04 30 forward +0x09 true win +0x0C zero. Evidence: vtable-proven TextOnFrameTransition with rowed update reverse init plus base ctor row plus prev CountUp deleting dtor next honest dtor 0x0035FA2A; BFME2 END 30 vs donor 1 follow retail.
typedef int Int;
typedef bool Bool;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	Int m_4;		// +0x04
	Bool m_8;		// +0x08
	Bool m_9;		// +0x09
	Bool m_A;		// +0x0a
	unsigned char m_pad0B;	// +0x0b
	Int m_C;		// +0x0c
};

class TextOnFrameTransition : public Rva001DBAA4
{
public:
	virtual ~TextOnFrameTransition(void);
	virtual void init(class GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse(void);
	virtual void draw(void);
	virtual void skip(void);
	TextOnFrameTransition(void);

	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
};

TextOnFrameTransition::TextOnFrameTransition(void)
{
	m_startFrame = 0;
	m_C = 0;
	m_endFrame = 30;
	m_4 = 30;
	m_9 = TRUE;
}
