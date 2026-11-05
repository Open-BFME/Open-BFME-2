// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// ??1GameSubTitle@@UAE@XZ 0x0025FC61 89B: dtor of SubtitleEntry-derived class with vtable 0x007F63F8
// (GameSubTitle: its ctor row 0x002603D1 stores that vtable, whose slots 1 and 2 are GameSubTitle rows).
// Evidence: stores vtable at [this], loops over count at +0x30 releasing array at +0x24 via global at 0x009FEAD8 slot 0x3c, then calls base ??1SubtitleEntry@@MAE@XZ at 0x006885A0. Caller 0x0025FF73 is its ??_G deleting dtor.
// Views follow the approved TU BfmeItemKA.cpp (GameSubTitle's ctor and factory).
typedef int Int;
typedef float Real;
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
#include "unicode_string.h"
class GameFont;
class SubtitleEntry
{
public:
	SubtitleEntry(const UnicodeString &text, UnsignedInt color, Int style,
		Int alignment, Int line, Int startFrame, Int endFrame);
protected:
	virtual ~SubtitleEntry();

private:
	UnicodeString m_text;
	UnsignedInt m_color;
	Int m_style;
	Int m_alignment;
	Int m_line;
	Int m_startFrame;
	Int m_endFrame;
	bool m_displayed;
};
class DisplayString;
// The VA 0x00DFEAD8 singleton is DisplayStringManager *TheDisplayStringManager,
// reused through its existing owned symbol. This TU keeps its own view of
// the vtable and casts at the use.
class DisplayStringManager;
class SubtitleDisplayFactoryView
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *string);
};
extern DisplayStringManager *TheDisplayStringManager;
static inline SubtitleDisplayFactoryView *theDisplayStringManagerView()
{
	return (SubtitleDisplayFactoryView *)TheDisplayStringManager;
}
class GameSubTitle : public SubtitleEntry
{
public:
	static Int getXFromAlignment(Int alignment, Int textWidth, Int unused, Real low, Real high);
	virtual ~GameSubTitle();
 void rva0025FCBA(GameFont *font);
	GameSubTitle(GameFont *font, const UnicodeString &text,
		UnsignedInt color, Int style, Int alignment, Int line,
		Int startFrame, Int endFrame);

private:
	DisplayString *m_displayStrings[3];
	Int m_displayStringCount;
	Int m_displayStringCapacity;
};

GameSubTitle::~GameSubTitle()
{
	for (Int i = 0; i < m_displayStringCount; ++i)
	{
		theDisplayStringManagerView()->freeDisplayString(m_displayStrings[i]);
		m_displayStrings[i] = 0;
	}
}
