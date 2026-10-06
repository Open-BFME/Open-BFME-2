// ?rva00434337@Rva00434337@@QAEXH@Z
// partial score=0.8182 date=2026-10-05
// ?rva00434337@Rva00434337@@QAEXH@Z
// partial score=0.93 date=2026-10-01
// cl: /Ireference/shims/bfme2_ascii /Os /MD /EHsc /Op
// ?rva00434337@Rva00434337@@QAEXH@Z, retail 0x00434337, 251 bytes.
// State machine on +0x27C with arg 1 vs 3 paths; 3-path fires closeDelayed/OnClosed
// via Rva00222547Get and TheRva00222A8BTarget invoker; 1-path uses entry text.
// Evidence: callees rowed 0x00222547 0x00320AAB, strings OnClosed closeDelayed,
// globals TheRva00222A8BTarget TheGameState TheGameLogic, caller none.
#include "unicode_string.h"
class GameWindow;
class GameState;
class GameLogic;
extern GameState *TheGameState;
extern GameLogic *TheGameLogic;
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
GameWindow *Rva00222547Get(GameWindow *w);
UnicodeString GadgetTextEntryGetText(GameWindow *textentry);
void *__stdcall Rva002DBC97Get(int v);
void __stdcall Rva0023D30FCall(int a, int b, int c);
void Rva00433D27Enable();
class Rva00434337
{
public:
	void rva00434337(int v);
private:
	char m_pad[0x27C];
	int m_27C;
	char m_pad27C[0x290 - 0x280];
	GameWindow *m_win290;
};
// ?rva00434337@Rva00434337@@QAEXH@Z present-unmatched
void Rva00434337::rva00434337(int v)
{
	if (1 != v)
	{
		if (v != 3)
			return;
		if (9 == m_27C)
		{
			TheRva00222A8BTarget->invoke(Rva00222547Get((GameWindow *)this), "closeDelayed", 1, "OnClosed", 0, 0, 0, 0);
			m_27C = 0xA;
			Rva00433D27Enable();
			return;
		}
		if (0xC == m_27C)
		{
			m_27C = 0xD;
			return;
		}
		if (0x17 == m_27C || m_27C == 0x16)
			const m_27C = 1;
		return;
	}
	if (8 == m_27C)
		m_27C = 7;
	else if (0xB == m_27C)
	{
		UnicodeString s = GadgetTextEntryGetText(m_win290);
		void *p = Rva002DBC97Get(6);
		s.concat((const unsigned short *)p);
		Rva0023D30FCall(1, 0, (int)&s);
	}
}
