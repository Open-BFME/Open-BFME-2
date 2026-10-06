// ?Rva0056D7A4Movie@@YAXPAXPBDPAVGameWindow@@@Z
// partial score=0.93 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// Retail 0x0056D7A4 369B ref-lane Apt Bink movie registration callback.
// Reads "_MovieName" "_Loop" "_UseAlpha" "_HoldLastFrame" "_CallOnLastFrame"
// via rowed GetParam 0x004128F0, flags 0x04/0x40/0x80 via find('t'),
// copies _CallOnLastFrame into window+0x26C, binds _CallOnLastFrame holder
// 0x0023E8D8 into TreeHintRef, sends 0x1D/1000 to TheWindowManager slot 0xE8.
// Evidence: constant use at 0x00412596, neighbour dtor 0x0056D76B,
// _CallOnLastFrame row 0x0056D6CE, BFME1 donor Rva00465770MovieProperties.
#include "ascii_string.h"

class GameWindow;
void __cdecl _CallOnLastFrame(GameWindow *window);

bool __cdecl Rva004128F0GetParam(const char *params, const char *key, AsciiString &value);

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class Rva0023E8D8
{
public:
	Rva0023E8D8(void *callback);
	~Rva0023E8D8() { if (m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
	void *m_ptr;
};

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	TargetRef00217D4C *m_ptr;
};

class Rva0056D76BRef
{
public:
	~Rva0056D76BRef() { if (m_ref) ReleaseTreeHintRef00217D4C(m_ref); }
	TargetRef00217D4C *m_ref;
};

class Rva0056D76B
{
public:
	~Rva0056D76B();
	AsciiString m_name;
	int m_flags;
	Rva0056D76BRef m_ref;
};

class GameWindowManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57();
	virtual int winSendSystemMsg(GameWindow *window, unsigned message, unsigned data1, void *data2);
};

extern GameWindowManager *TheWindowManager;

struct AptBinkMovieWindow
{
	char m_pad[0x26C];
	AsciiString m_onLastFrame;
};

// ?Rva0056D7A4Movie@@YAXPAXPBD PAVGameWindow@@@Z @0x0056D7A4 369B
void __cdecl Rva0056D7A4Movie(void *, const char *query, GameWindow *win)
{
	GameWindow *w = win;
	if (w == 0)
		return;
	const char *q = query;
	AsciiString param;
	struct Msg16
	{
		Rva0056D76B base;
		GameWindow *m_window;
	} msg;
	GameWindow *&msgWindow = msg.m_window;
	msg.base.m_flags = 0;
	msg.base.m_ref.m_ref = 0;
	msgWindow = 0;
	if (Rva004128F0GetParam(q, "_MovieName", param) == 0)
		return;
	((StringBase<char> *)&msg.base.m_name)->set(param.str());
	Rva004128F0GetParam(q, "_Loop", param);
	if (((const StringBase<char> *)&param)->find('t') != 0)
		msg.base.m_flags |= 4;
	Rva004128F0GetParam(q, "_UseAlpha", param);
	if (((const StringBase<char> *)&param)->find('t') != 0)
		msg.base.m_flags |= 0x40;
	Rva004128F0GetParam(q, "_HoldLastFrame", param);
	if (((const StringBase<char> *)&param)->find('t') != 0)
		msg.base.m_flags |= 0x80;
	if (Rva004128F0GetParam(q, "_CallOnLastFrame", param) != 0) {
		((StringBase<char> *)&((AptBinkMovieWindow *)w)->m_onLastFrame)->set(*(const StringBase<char> *)&param);
		void *callback = (void *)_CallOnLastFrame;
		Rva0023E8D8 holder(&callback);
		((TreeHintRef00217D4C *)&msg.base.m_ref)->operator=(*(const TreeHintRef00217D4C *)&holder);
		msgWindow = w;
	}
	TheWindowManager->winSendSystemMsg(w, 0x1D, 1000, &msg);
}
