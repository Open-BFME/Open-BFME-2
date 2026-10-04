// ?rva00289812@Rva00289ABD@@QAE_NPA_N@Z
// partial score=0.98 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Only mismatch: the two cdecl argument pops after TheInGameUI->message are
// split around the g_Va00DFECC8 store (59 c6.. 59) where retail pops both
// right after the cmp (59 59 c6..). Tried: plain if, hoisted local (mov al/test),
// both branch orders with duplicated stores.
#include "unicode_string.h"
class InGameUI
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void message(UnicodeString format, ...);
};
extern InGameUI *TheInGameUI;	// VA 0x00DFEDF0
class RifStore
{
public:
	virtual void v00(); virtual void v01();
	virtual bool rva001B5384Slot2();
};
// The ExperienceLevels store (vftable 0x00BFB8F4, class Rva00289ABD) clears
// its hash table at +0x10 (0x00289371) and a .bss "needs restart" byte before
// reloading; after a reload it latches its own .bss byte and +0x24, and
// passes a pending restart out through its argument.
class Rva00289371HashTable
{
public:
	void clear();
};

// g_Va00DFECC8: VA 0x00DFECC8 (.bss); retail initial byte 00.
bool g_Va00DFECC8;
// g_Va00DFECC9: VA 0x00DFECC9 (.bss); retail initial byte 00.
bool g_Va00DFECC9;

class Rva00289ABD : public RifStore
{
public:
	bool rva00289812(bool *needsRestart);
private:
	char m_unmodelled04[0x10 - 0x04];
	Rva00289371HashTable *m_table10;
	char m_unmodelled14[0x24 - 0x14];
	bool m_reloaded24;
};

bool Rva00289ABD::rva00289812(bool *needsRestart)
{
	Rva00289371HashTable *table = m_table10;
	g_Va00DFECC9 = false;
	table->clear();
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: ExperienceLevels reloaded. All units will need to be refreshed."));
		if (!g_Va00DFECC9)
		{
			g_Va00DFECC8 = true;
			m_reloaded24 = true;
		}
		else
		{
			g_Va00DFECC8 = true;
			m_reloaded24 = true;
			*needsRestart = true;
		}
	}
	return g_Va00DFECC8;
}
