// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva005118F3Show@@YAXH_N@Z, retail 0x005118F3 157B. Chain over just-landed
// rva005AFD43 SetText 0x005AFD43. Free cdecl helper switching active tab:
// stores new index to g_Va00E046BC, fires ShowActiveTab via TheRva00222A8BTarget
// invoke, clears old entry text to EmptyString and sets new entry text from
// g_Va00E048C0, then optionally clears vector via Rva00381C2DClear.
// Evidence: globals g_Va00E046BC g_Va00E046B8 g_Va00E048C0, string
// ShowActiveTab, TheEmptyString, callers 0x004464DC 0x00511B98 0x00517CAF.
#include "unicode_string.h"

class GameWindow;
class Rva005AFD43
{
public:
	void rva005AFD43(GameWindow *g, const UnicodeString &s);
};

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0,
		void *a1, void *a2, void *a3, void *a4);
};

struct Rva00511730State
{
	char m_pad00[0x274];
	void *m_274;
	unsigned char m_flag278;
	char m_pad279[3];
	int m_field27C;
	Rva005AFD43 **m_array280;
	char m_pad284[0x298 - 0x284];
	GameWindow * volatile m_window298;
	unsigned char m_flag29C;
};

extern int g_Va00E046BC;
extern Rva00511730State *g_Va00E046B8;
extern UnicodeString g_Va00E048C0;
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
void __cdecl Rva00381C2DClear(unsigned int idx);

void __cdecl Rva005118F3Show(int index, bool clear)
{
	if (g_Va00E046BC != index) {
		int old = g_Va00E046BC;
		g_Va00E046BC = index;
		if (g_Va00E046B8 != 0) {
			(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke(g_Va00E046B8->m_274, "ShowActiveTab", 0, 0, 0, 0, 0, 0);
			g_Va00E046B8->m_flag29C = 1;
			Rva005AFD43 *oldWin = g_Va00E046B8->m_array280[old];
			Rva005AFD43 *newWin = g_Va00E046B8->m_array280[g_Va00E046BC];
			if (oldWin != 0) {
				oldWin->rva005AFD43(0, UnicodeString::TheEmptyString);
			}
			if (newWin != 0) {
				newWin->rva005AFD43(g_Va00E046B8->m_window298, g_Va00E048C0);
			}
		}
	}
	if (clear) {
		Rva00381C2DClear(index);
	}
}
