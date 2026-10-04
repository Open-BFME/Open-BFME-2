// ?rva005A0C6E@Rva005A083C@@QAEXPBDHPAVGameWindow@@@Z
// partial score=0.99 date=2026-10-05
// cl: /Ireference/shims/bfmelist /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005A083C@Rva005A083C@@QAEXXZ, retail 0x005A083C 140B. Unlock: builds 2-int list from +0x498/+0x49C when both non-null then WindowManager 0xB4/0xB0.
// Evidence: callees list base/push_front/push_back/dup/dtor rowed in stlport_list_int_o1; TheWindowManager global; caller 0x005A0D56.
#include <list>

class GameWindowManager
{
public:
	virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
	virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
	virtual void _v8(); virtual void _v9(); virtual void _v10(); virtual void _v11();
	virtual void _v12(); virtual void _v13(); virtual void _v14(); virtual void _v15();
	virtual void _v16(); virtual void _v17(); virtual void _v18(); virtual void _v19();
	virtual void _v20(); virtual void _v21(); virtual void _v22(); virtual void _v23();
	virtual void _v24(); virtual void _v25(); virtual void _v26(); virtual void _v27();
	virtual void _v28(); virtual void _v29(); virtual void _v30(); virtual void _v31();
	virtual void _v32(); virtual void _v33(); virtual void _v34(); virtual void _v35();
	virtual void _v36(); virtual void _v37(); virtual void _v38(); virtual void _v39();
	virtual void _v40(); virtual void _v41(); virtual void _v42(); virtual void _v43();
	virtual void slotB0(_STL::list<int> lst);
	virtual void slotB4();
};
extern GameWindowManager *TheWindowManager;

class GameWindow;
class WinInstanceData;
class BfmeKeyLC;
typedef void (__cdecl *GameWinTooltipFunc)(GameWindow *window, WinInstanceData *data, unsigned int flags);
void __cdecl GadgetListBoxReset(GameWindow *window);
void __cdecl Rva0032060D(GameWindow *window, int value);
void __cdecl bfmeGo924F(BfmeKeyLC *k, unsigned short w);
extern "C" int __cdecl strcmp(const char *a, const char *b);
void __cdecl Rva005A08C8Tooltip(GameWindow *window, WinInstanceData *data, unsigned int flags);

class GameWindow
{
public:
	void *winGetUserData();
	void winSetUserData(void *data);
	int winSetTooltipFunc(GameWinTooltipFunc tooltip);
	unsigned int winSetStatus(unsigned int status);
};

struct Rva005A0C6EUserData
{
	char m_pad[0x12];
	unsigned char m_12;
};

class Rva005A083C
{
public:
	void rva005A083C();
	void rva005A0C6E(const char *a1, int a2, GameWindow *a3);
private:
	char m_pad[0x48C];
	GameWindow *m_48C;
	GameWindow *m_490;
	GameWindow *m_494;
	int m_498;
	int m_49C;
};




void Rva005A083C::rva005A0C6E(const char *a1, int a2, GameWindow *a3)
{
	if (a3 == 0)
		return;
	if (strcmp(a1, "GameList") == 0) {
		GadgetListBoxReset(a3);
		m_48C = a3;
		Rva005A0C6EUserData *ud = (Rva005A0C6EUserData *)a3->winGetUserData();
		ud->m_12 = 1;
		a3->winSetUserData(ud);
		a3->winSetTooltipFunc(Rva005A08C8Tooltip);
		return;
	}
	if (strcmp(a1, "Lobbies") == 0) {
		m_490 = a3;
		return;
	}
	if (strcmp(a1, "GameInfo") == 0) {
		GadgetListBoxReset(a3);
		m_494 = a3;
		return;
	}
	if (strcmp(a1, "GameName") == 0) {
		m_498 = (int)a3;
		bfmeGo924F((BfmeKeyLC *)a3, 0x14);
		a3->winSetStatus(2);
		rva005A083C();
	} else {
		if (strcmp(a1, "GamePassword") != 0)
			return;
		m_49C = (int)a3;
		Rva0032060D(a3, 5);
		bfmeGo924F((BfmeKeyLC *)a3, 0x14);
		a3->winSetStatus(2);
		rva005A083C();
	}
}
