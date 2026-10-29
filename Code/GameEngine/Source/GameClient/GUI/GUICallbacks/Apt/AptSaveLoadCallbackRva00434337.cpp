// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// State machine on +0x27C with arg 1 vs 3 paths; 3-path fires closeDelayed/OnClosed
// via AptPlayer::GetLevelIndex and TheRva00222A8BTarget invoker; 1-path uses entry text.
// Evidence: callees rowed 0x00222547 0x00320AAB, strings OnClosed closeDelayed,
// globals TheRva00222A8BTarget TheGameState TheGameLogic, caller none.
#include "unicode_string.h"
class GameWindow;
class GameState { public: void *rva002DBC97Get(int saveType); };
#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameState *TheGameState;
extern GameLogic *TheGameLogic;
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
class AptPlayer { public: static int GetLevelIndex(GameWindow *window); };
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
void Rva00434337::rva00434337(int v)
{
	switch (v)
	{
	case 1:
		if (m_27C == 8)
			m_27C = 7;
		else if (m_27C == 0xB)
		{
			UnicodeString filename = GadgetTextEntryGetText(m_win290);
			void *extension = TheGameState->rva002DBC97Get(6);
			filename.concat((const unsigned short *)extension);
			TheGameLogic->rva0023D30F(1, 0, &filename);
		}
		break;
	case 3:
		if (m_27C == 9)
		{
			TheRva00222A8BTarget->invoke(reinterpret_cast<void *>(AptPlayer::GetLevelIndex((GameWindow *)this)), "closeDelayed", 1, "OnClosed", 0, 0, 0, 0);
			m_27C = 0xA;
			Rva00433D27Enable();
		}
		else if (m_27C == 0xC)
			m_27C = 0xD;
		else if (m_27C == 0x17 || m_27C == 0x16)
			m_27C = 1;
		break;
	}
}
