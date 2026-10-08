// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00377064@Rva00377064@@QAEXHHH@Z @0x00377064 168B.
// Unlock lane: thiscall with three int args (ret 0xc); stores to GameLogic
// +0xa4/+0x110, moves GlobalData string +0xac0 to +0x0c when non-empty via
// rowed isEmpty/set/clear(releaseBuffer), stores arg to this +0x94, zeroes
// +0xa8, hides Shell unless +0x110==4, clears dword unless +0x114==3.
// Evidence: callers at 0x002B47F8 0x002B4877 (FUN_006b47c3) and 0x003779BB;
// callees all rowed/pinned (set 0x00203BCD, isEmpty 0x00001E2F, set 0x000366F0,
// releaseBuffer 0x00036410, hide pin 0x0035BF4C, clear 0x0023D2D8); prev/next
// flags copied from Rva0037ADB6Write.
#include "ascii_string.h"

class ScriptEngine;
extern class ScriptEngine *TheScriptEngine; // ?g_Va009FE16C@@3PAVScriptEngine@@A
class GameLogic;
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A
class GlobalData;
extern GlobalData *TheWritableGlobalData; // ?TheWritableGlobalData@@3PAVGlobalData@@A
struct GlobalA01E48;
extern class Shell *TheShell; // ?g_Va00A01E48@@3PAUGlobalA01E48@@A

class Rva00203BCDDwordSlot
{
public:
	void set(int value); // ?set@Rva00203BCDDwordSlot@@QAEXH@Z
};
class Rva0023D2D8DwordClearer
{
public:
	void clear(); // ?clear@Rva0023D2D8DwordClearer@@QAEXXZ
};
class Shell
{
public:
	void hide(bool flag); // ?hide@Shell@@QAEX_N@Z pin-only
};

class GameLogic
{
public:
	char m_pad00[0xa4];
	int m_a4; // +0xa4
	char m_padA8[0x110 - 0xa4 - 4];
	int m_110; // +0x110
	int m_114; // +0x114
};
class GlobalData
{
public:
	char m_pad00[0x0c];
	AsciiString m_0c; // +0x0c
	char m_padAfter0c[0x0ac0 - 0x0c - sizeof(AsciiString)];
	AsciiString m_ac0; // +0xac0
};

class Rva00377064
{
public:
	void rva00377064(int a, int b, int c);
private:
	char m_pad00[0x94];
	int m_94; // +0x94
	char m_pad98[0xa8 - 0x94 - 4];
	unsigned char m_a8; // +0xa8
};

void Rva00377064::rva00377064(int a, int b, int c)
{
	((Rva00203BCDDwordSlot *)TheScriptEngine)->set(1);
	TheGameLogic->m_a4 = b;
	TheGameLogic->m_110 = a;
	if (!TheWritableGlobalData->m_ac0.isEmpty()) {
		((StringBase<char> *)&TheWritableGlobalData->m_0c)->set(*(const StringBase<char> *)&TheWritableGlobalData->m_ac0);
		TheWritableGlobalData->m_ac0.clear();
	}
	m_94 = c;
	if (TheGameLogic->m_110 != 4)
		((Shell *)(*(GlobalA01E48 **)&TheShell))->hide(true);
	m_a8 = 0;
	if (TheGameLogic->m_114 == 3)
		((Rva0023D2D8DwordClearer *)TheGameLogic)->clear();
}
