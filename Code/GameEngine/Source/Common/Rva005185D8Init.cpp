// cl: /Ireference/shims/bfme2_ascii /MD
#include "ascii_string.h"
// ?Rva005185D8Init@@YAX_N000@Z @0x005185D8 128B
// Options.apt push plus 4 flag bytes into struct at g_Va00A04908 +0x280-0x284 plus show background mode 1.
// Evidence: callers 0x00444337 0x00516EC8 0x0051AFE3 add esp 0x10 plus ret 4 (4 args __cdecl); callees StringBase 0x00037BA0 Shell push 0x0035C74A rva002233A6 0x002233A6 all rowed; string Options.apt 0x00802988; globals g_Va00A04908 g_Va00A01E48 TheRva00222A8BTarget; precedent Rva00434160Init same Shell push pattern.
extern int g_Va00A04908;
extern int g_00E04914;
struct GlobalA01E48;
extern class Shell *TheShell;
class Shell
{
public:
	void push(AsciiString s, bool flag);
};
class Rva00222A8BTarget
{
public:
	void rva002233A6(int mode);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
struct State005185D8
{
	char m_pad[0x280];
	unsigned char m_280;
	unsigned char m_281;
	unsigned char m_282;
	unsigned char m_283;
	unsigned char m_284;
};
struct State0051E262
{
	char m_pad[0x280];
	int m_280; // +0x280
	char m_pad284[4];
	int m_288; // +0x288
	void rva0051DE3D();
};
void Rva005185D8Init(bool a1, bool a2, bool a3, bool a4)
{
	if (g_Va00A04908 != 0)
		return;
	((Shell *)(*(GlobalA01E48 **)&TheShell))->push(AsciiString("Options.apt"), false);
	if (g_Va00A04908 != 0)
	{
		((State005185D8 *)g_Va00A04908)->m_280 = a2;
		((State005185D8 *)g_Va00A04908)->m_283 = a1;
		((State005185D8 *)g_Va00A04908)->m_284 = a4;
		((State005185D8 *)g_Va00A04908)->m_281 = a3;
		((State005185D8 *)g_Va00A04908)->m_282 = a2;
	}
	(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva002233A6(1);
}

// ?Rva0051E262Init@@YA_NHH@Z @0x0051E262 85B
// ScoreScreen.apt push plus two ints at +0x280/+0x288 plus the 0x51DE3D
// tail; same Shell-push idiom as Rva005185D8Init above. Always returns
// true; early-out when the score screen state already exists.
bool Rva0051E262Init(int a1, int a2)
{
	if (g_00E04914 != 0)
		return true;
	((Shell *)(*(GlobalA01E48 **)&TheShell))->push(AsciiString("ScoreScreen.apt"), false);
	((State0051E262 *)g_00E04914)->m_280 = a1;
	((State0051E262 *)g_00E04914)->m_288 = a2;
	((State0051E262 *)g_00E04914)->rva0051DE3D();
	return true;
}
