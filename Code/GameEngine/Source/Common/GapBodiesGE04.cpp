// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/GameEngine/Include
// Small GameEngine bodies from .text gaps no Ghidra function covers (fourth
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.
#include <string.h>

template <class T> class StringBase;
class AsciiString;

// --- 0x004FD87A (46B): the named check (rowed 0x004FD6F9) of the +0x14 name
// of the region the region manager (TheLivingWorldLogic +0xB0) finds by id.
class Rva0020E89C;

class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int id);						// 0x0020EAF6
};

struct Rva004FD87ALogic
{
	char m_pad[0xB0];
	Rva0020EAF6View *m_regionManager;						// +0xB0
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva004FD6F9
{
public:
	bool rva004FD6F9(const StringBase<char> &name);			// 0x004FD6F9
	bool rva004FD87A(int regionID);
};

bool Rva004FD6F9::rva004FD87A(int regionID)
{
	Rva0020E89C *region = ((Rva004FD87ALogic *)TheLivingWorldLogic)->m_regionManager->rva0020EAF6(regionID);
	if (!region)
		return false;
	return rva004FD6F9(*(const StringBase<char> *)((char *)region + 0x14));
}

// --- 0x00232654 (12B) / 0x00232660 (16B) / 0x00232670 (19B): byte-indexed
// 8-byte records from +0x1C: the +4 word, the +1 flag and the +2 short.
struct Rva00232654Record
{
	char m_00;
	unsigned char m_status;
	unsigned short m_02;
	int m_04;
};

class Rva00232654
{
public:
	int getKeySequenceData(unsigned char index) const;
	void rva00232660(unsigned char index, unsigned char flag);
	void setKeyStateData(unsigned char index, unsigned char value);
private:
	char m_pad[0x1C];
	Rva00232654Record m_records[1];
};

int Rva00232654::getKeySequenceData(unsigned char index) const
{
	return m_records[index].m_04;
}

void Rva00232654::rva00232660(unsigned char index, unsigned char flag)
{
	m_records[index].m_status = flag;
}

void Rva00232654::setKeyStateData(unsigned char index, unsigned char value)
{
	m_records[index].m_02 = value;
}

// --- 0x0026FC6F (28B): bit test of the +0x380 mask; 0x0026FC8B (19B): the
// sum of +0xAC, +0xB0 and +0xB4.
class Rva0026FC6F
{
public:
	int rva0026FC6F(int bit) const;
	int rva0026FC8B() const;
private:
	char m_pad[0xAC];
	int m_AC;
	int m_B0;
	int m_B4;
	char m_padB8[0x380 - 0xB8];
	int m_380;
};

int Rva0026FC6F::rva0026FC6F(int bit) const
{
	return (m_380 & (1 << bit)) != 0;
}

int Rva0026FC6F::rva0026FC8B() const
{
	return m_B4 + m_B0 + m_AC;
}

// --- 0x002AC290 (47B): copy bytes from the +0x04 object's name text.
struct Rva002AC290Name
{
	char *m_data;
	const char *str() const { return m_data ? m_data + 8 : ""; }
};

class Rva002AC290
{
public:
	void rva002AC290(void *dest, int offset, unsigned int count);
private:
	int m_00;
	Rva002AC290Name **m_04;
};

void Rva002AC290::rva002AC290(void *dest, int offset, unsigned int count)
{
	memcpy(dest, (*m_04)->str() + offset, count);
}

// --- 0x0033F9CA (8B) / 0x0033F9D2 (10B): the +0x04 object's byte field
// (rowed getter) and its +0x161 flag; 0x0033F9DC (27B): vtable 0x00C11A5C
// constructor over a cleared +0x04 with an int and a flag.
class Rva002C940EByteField
{
public:
	unsigned char get() const;								// 0x002C940E
	char m_pad[0x161];
	unsigned char m_161;
};

class Rva0033F9CA
{
public:
	unsigned char rva0033F9CA() const;
	unsigned char rva0033F9D2() const;
private:
	int m_00;
	Rva002C940EByteField *m_04;
};

unsigned char Rva0033F9CA::rva0033F9CA() const
{
	return m_04->get();
}

unsigned char Rva0033F9CA::rva0033F9D2() const
{
	return m_04->m_161;
}

class Rva0033F9DC
{
public:
	Rva0033F9DC(int value, bool flag);
	virtual ~Rva0033F9DC() {}
private:
	int m_04;
	int m_08;
	bool m_0C;
};

Rva0033F9DC::Rva0033F9DC(int value, bool flag) : m_04(0), m_08(value), m_0C(flag)
{
}

// --- 0x003B956E (20B) / 0x003B9582 (27B): command-line flag parsers (as
// CommandLineNoAudio.cpp's) setting GlobalData +0xDD0, or the BFME2 flag 4
// and clearing GlobalData +0x99D.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
extern unsigned int BFME2CommandFlags;

struct Rva003B956EGlobalData
{
	char m_pad[0x99D];
	bool m_musicOn;
	char m_pad99E[0xDD0 - 0x99E];
	bool m_useHelpTextSystem;
};

int Rva003B956E(char *args[], int)
{
	if (TheWritableGlobalData)
		((Rva003B956EGlobalData *)TheWritableGlobalData)->m_useHelpTextSystem = true;
	return 1;
}

int parseNoMusic(char *args[], int)
{
	BFME2CommandFlags |= 4;
	if (TheWritableGlobalData)
		((Rva003B956EGlobalData *)TheWritableGlobalData)->m_musicOn = false;
	return 1;
}

// --- 0x0048893C (47B): through the +0x18 owner's object (+0x14) and its
// +0x258 interface (virtual slot 93), virtual slot 10 with -1 then slot 24.
class Rva0048893CTarget
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9();
	virtual void s10(int value);
	virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
	virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
	virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
	virtual void s23();
	virtual void s24();
};

class Rva0048893CSource
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
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
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
	virtual void s92();
	virtual Rva0048893CTarget *s93();
};

struct Rva0048893CObject
{
	char m_pad[0x258];
	Rva0048893CSource *m_258;
};

struct Rva0048893COwner
{
	char m_pad[0x14];
	Rva0048893CObject *m_14;
};

class DozerActionState
{
public:
	virtual void onExit(int unused);
private:
	char m_pad[0x18 - 4];
	Rva0048893COwner *m_18;
};

void DozerActionState::onExit(int)
{
	Rva0048893CSource *source = m_18->m_14->m_258;
	if (source)
	{
		Rva0048893CTarget *target = source->s93();
		target->s10(-1);
		target->s24();
	}
}

// --- 0x0023DB93 (20B) / 0x0023DBA7 (28B): the +0x00 short and whether the
// +0x06 short is zero, of the indexed 16-byte record in the +0xF50 table.
struct Rva0023DB93Record
{
	short m_00;
	short m_02;
	short m_04;
	short m_06;
	int m_08;
	int m_0C;
};

class Rva0023DB93
{
public:
	int rva0023DB93(int index) const;
	bool rva0023DBA7(int index) const;
private:
	char m_pad[0xF50];
	Rva0023DB93Record *m_records;
};

int Rva0023DB93::rva0023DB93(int index) const
{
	return m_records[index].m_00;
}

bool Rva0023DB93::rva0023DBA7(int index) const
{
	return m_records[index].m_06 == 0;
}

// --- 0x0025C7F9 (48B): hand a non-null string to TheDisplayStringManager's
// free (virtual slot 15), then clear the +0xC8 / +0xCC floats.
class DisplayStringManager
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void freeDisplayString(void *string);
};
extern DisplayStringManager *TheDisplayStringManager;

class Rva0025C7F9
{
public:
	void rva0025C7F9(void *string);
private:
	char m_pad[0xC8];
	float m_C8;
	float m_CC;
};

void Rva0025C7F9::rva0025C7F9(void *string)
{
	if (string)
		TheDisplayStringManager->freeDisplayString(string);
	m_C8 = 0.0f;
	m_CC = 0.0f;
}

// --- 0x002C02A0..0x002C02CF / 0x002C052F..0x002C055E (16B each): the
// enabled / disabled / hilite image of draw slot 4 or 3 of a window.
class Image;

class GameWindow
{
public:
	int winSetEnabledImage(int index, const Image *image);	// 0x003143B9
	int winSetDisabledImage(int index, const Image *image);	// 0x00314421
	int winSetHiliteImage(int index, const Image *image);	// 0x0031448F
};

int Rva002C02A0(GameWindow *window, const Image *image) { return window->winSetEnabledImage(4, image); }
int Rva002C02B0(GameWindow *window, const Image *image) { return window->winSetDisabledImage(4, image); }
int Rva002C02C0(GameWindow *window, const Image *image) { return window->winSetHiliteImage(4, image); }
int Rva002C052F(GameWindow *window, const Image *image) { return window->winSetEnabledImage(3, image); }
int Rva002C053F(GameWindow *window, const Image *image) { return window->winSetDisabledImage(3, image); }
int Rva002C054F(GameWindow *window, const Image *image) { return window->winSetHiliteImage(3, image); }

// --- 0x002D2D4A (25B): reset a record
// (flag cleared, three -2 ids, a zero float).
class Rva002D2D4A
{
public:
	void rva002D2D4A();
private:
	int m_00;
	int m_04;
	bool m_08;
	int m_0C;
	int m_10;
	int m_14;
	float m_18;
};

void Rva002D2D4A::rva002D2D4A()
{
	m_08 = false;
	m_0C = -2;
	m_10 = -2;
	m_14 = -2;
	m_18 = 0.0f;
}

// --- 0x002EAD84 / 0x002EAD9C (24B each): return a node to the free list of
// the 0x00DBD4B0 / 0x00DBD4C8 pool.
struct _Rva002EB416Node
{
	void *_m_link;
};
extern _Rva002EB416Node *g_Va00DBD4B8;

#include "Common/Rva002E8548Pool.h"

void __stdcall Rva002EAD84(void *node, unsigned int)
{
	if (node)
	{
		*(_Rva002EB416Node **)node = g_Va00DBD4B8;
		g_Va00DBD4B8 = (_Rva002EB416Node *)node;
	}
}

void __stdcall Rva002EAD9C(void *node, unsigned int)
{
	if (node)
	{
		*(void **)node = g_Va00DBD4C8.m_head;
		g_Va00DBD4C8.m_head = node;
	}
}
