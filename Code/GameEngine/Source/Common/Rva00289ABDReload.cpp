// cl: /O1 /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// INI reload slots of the ExperienceLevels store (vftable 0x00BFB8F4, class
// Rva00289ABD; its constructor is 0x00289ABD):
//
//   slot 4, 0x00289812  clear the table at +0x10 (0x00289371) and the
//                       "needs restart" byte, then, when the shared slot 2
//                       (0x001B5384) reports a reload, put "RIF:
//                       ExperienceLevels reloaded..." on screen through
//                       TheInGameUI (slot 16, cdecl), latch the "reloaded"
//                       byte and +0x24, and pass a pending restart out
//                       through the argument; answer the latch.
//   slot 5, 0x00289874  once after a reload latched its byte: swap the
//                       tables at +0x0C and +0x10, clear the tree at +0x28
//                       (0x002889BB), clear the table now at +0x10, and
//                       answer true.
//
// Both bytes (VA 0x00DFECC8 "reloaded", 0x00DFECC9 "needs restart") are
// file-static: slot 4 loads +0x10 before it stores the restart byte and tests
// that byte before its two stores, which MSVC 7.1 schedules that way only for
// a static it can prove `this` does not alias. All their other readers and
// writers (0x00289874 and the parse body around 0x0028A429) sit beside these
// slots. Names are address-derived; the byte meanings are inferred from
// their uses.

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

// g_Va00DFECC8: VA 0x00DFECC8 (.bss); retail initial byte 00.
static bool g_Va00DFECC8;
// g_Va00DFECC9: VA 0x00DFECC9 (.bss); retail initial byte 00.
static bool g_Va00DFECC9;

class Rva00289371HashTable
{
public:
	void clear();	// 0x00289371
};

class Rva0028881C
{
public:
	void rva002889BB();	// tree clear
};

class Rva00289ABDBase
{
public:
	virtual void v00();
	virtual void v01();
	virtual bool rva001B5384Slot2();
};

class Rva00289ABD : public Rva00289ABDBase
{
public:
	bool rva00289812(bool *needsRestart);
	bool rva00289874();
private:
	char m_unmodelled04[0x0C - 0x04];
	Rva00289371HashTable *m_table0C;
	Rva00289371HashTable *m_table10;
	char m_unmodelled14[0x24 - 0x14];
	bool m_reloaded24;
	char m_unmodelled25[0x28 - 0x25];
	Rva0028881C m_tree28;
};

bool Rva00289ABD::rva00289812(bool *needsRestart)
{
	g_Va00DFECC9 = false;
	m_table10->clear();
	if (rva001B5384Slot2())
	{
		TheInGameUI->message(UnicodeString(L"RIF: ExperienceLevels reloaded. All units will need to be refreshed."));
		g_Va00DFECC8 = true;
		m_reloaded24 = true;
		if (g_Va00DFECC9)
			*needsRestart = true;
	}
	return g_Va00DFECC8;
}

bool Rva00289ABD::rva00289874()
{
	if (g_Va00DFECC8)
	{
		Rva00289371HashTable *old = m_table0C;
		m_table0C = m_table10;
		m_tree28.rva002889BB();
		m_table10 = old;
		old->clear();
		g_Va00DFECC8 = false;
		return true;
	}
	return false;
}
