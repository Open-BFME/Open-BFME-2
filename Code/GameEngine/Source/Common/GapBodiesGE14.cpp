// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source/Common
// Small GameEngine bodies from .text gaps no Ghidra function covers
// (fourteenth batch; see GapBodiesGE01.cpp). Retail bytes establish every
// shape; owning classes are not recovered unless named, so each keeps an
// address-derived name and a view of only the members it touches. Callees and
// globals use the ledger's existing spellings.
#include "ascii_string.h"

// --- 0x00525479 (13B): the first record's rowed comparison against the
// second (this unused).
#include "Rva00525119.h"

class Rva00525479
{
public:
	int rva00525479(Rva00525119 *a, Rva00525119 *b);
};

int Rva00525479::rva00525479(Rva00525119 *a, Rva00525119 *b)
{
	return a->rva00525119(b);
}

// --- 0x00525489 / 0x005254A7 (30B each): vtables 0x00C6ECB4 / 0x00C67E80
// over a cleared word and a copied pair.
struct GapPair
{
	int a;
	int b;
};

#define GAP_VTABLE_PAIR_CTOR(NAME) \
	class NAME \
	{ \
	public: \
		NAME(const GapPair &pair); \
		virtual ~NAME() {} \
	private: \
		int m_04; \
		int m_08; \
		int m_0C; \
	}; \
	NAME::NAME(const GapPair &pair) : m_04(0), m_08(pair.a), m_0C(pair.b) \
	{ \
	}

GAP_VTABLE_PAIR_CTOR(Rva00525489)
GAP_VTABLE_PAIR_CTOR(Rva005254A7)

// --- 0x003B9CDF..0x003B9D23: command-line flag parsers on GlobalData
// (+0x1110 cleared, +0x87 / +0x88 set, +0x86 cleared) and the rowed
// 0x004128E8 flag.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva003B9CDFGlobalData
{
	char m_pad[0x86];
	bool m_liveCampaignMode;
	bool m_hideLivingWorldRegions;
	bool m_livingWorldTurbo;
	char m_pad89[0x1110 - 0x89];
	bool m_1110;
};

void Rva004128E8SetFlag();									// 0x004128E8

int Rva003B9CDF(char *args[], int)
{
	if (TheWritableGlobalData)
		((Rva003B9CDFGlobalData *)TheWritableGlobalData)->m_1110 = false;
	return 1;
}

int parseHideLivingWorldRegions(char *args[], int)
{
	((Rva003B9CDFGlobalData *)TheWritableGlobalData)->m_hideLivingWorldRegions = true;
	return 1;
}

int Rva003B9D03(char *args[], int)
{
	((Rva003B9CDFGlobalData *)TheWritableGlobalData)->m_liveCampaignMode = false;
	return 1;
}

int parseLivingWorldTurbo(char *args[], int)
{
	((Rva003B9CDFGlobalData *)TheWritableGlobalData)->m_livingWorldTurbo = true;
	return 1;
}

int Rva003B9D23(char *args[], int)
{
	Rva004128E8SetFlag();
	return 1;
}

// --- 0x003B9A20 / 0x003B9A9C / 0x003B9D6F (9B each): more handlers of this
// family that raise one byte global and return 1. Their option strings are
// not referenced from the image; the globals are the existing providers:
// ShaderOverbrightEnabled (VA 0x00DB5F84, ShaderClassApply.cpp), the save
// flag Rva002DBC97Get.cpp reads as BfmeSaveTransferOption, and
// g_natTransportContextEnabled (VA 0x00E02D8C, NATUpdateBfme.cpp).
extern bool ShaderOverbrightEnabled;
extern bool BfmeSaveTransferOption;
extern bool g_natTransportContextEnabled;

int Rva003B9A20(char *args[], int)
{
	ShaderOverbrightEnabled = true;
	return 1;
}

int Rva003B9A9C(char *args[], int)
{
	BfmeSaveTransferOption = true;
	return 1;
}

int Rva003B9D6F(char *args[], int)
{
	g_natTransportContextEnabled = true;
	return 1;
}

// --- 0x00391FC4 (77B): four zero floats, an emptied name (+0x14), a -1 id
// and a cleared flag.
// The 0x00392092 array initializer pairs this ctor with the folded destructor
// 0x004D9A3C at stride 0x1C, so it owns that destructor's address-derived class.
class Rva004D9A3C
{
public:
	Rva004D9A3C();
private:
	float m_00;
	float m_04;
	float m_08;
	float m_0C;
	bool m_10;
	AsciiString m_name;										// +0x14
	int m_18;
};

Rva004D9A3C::Rva004D9A3C()
{
	m_00 = 0.0f;
	m_04 = 0.0f;
	m_08 = 0.0f;
	m_0C = 0.0f;
	m_name.clear();
	m_18 = -1;
	m_10 = false;
}

// --- 0x00406D95 (14B): the rowed ControlBar lookup with 1.
class CommandSet;

class ControlBar
{
public:
	CommandSet *rva0031E8D5(const AsciiString &name, int flag);	// 0x0031E8D5
	CommandSet *rva00406D95(const AsciiString &name);
};

CommandSet *ControlBar::rva00406D95(const AsciiString &name)
{
	return rva0031E8D5(name, 1);
}

// --- 0x003F7209 (78B): vtable 0x00C370D4 over the argument and 9999 / 0
// defaults.
struct GapWordBase04
{
	int m_04;
	GapWordBase04(int a) : m_04(a) {}
};

class Rva003F7209 : public GapWordBase04
{
public:
	Rva003F7209(int a);
	virtual ~Rva003F7209() {}
private:
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	float m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	float m_2C;
	int m_30;
	float m_34;
};

Rva003F7209::Rva003F7209(int a) : GapWordBase04(a), m_08(9999.0f), m_0C(9999.0f), m_10(9999.0f), m_14(9999.0f), m_18(9999.0f),
	m_1C(0), m_20(0), m_24(0), m_28(0), m_2C(9999.0f), m_30(0), m_34(9999.0f)
{
}

// --- 0x00319A52 (78B): "Small" / "Medium" / "Large" select 1 / 2 / 3
// (rowed 0x00318BC6).
class Rva00318BC6Owner
{
public:
	void rva00318BC6(int size);								// 0x00318BC6
	void rva00319A52(const AsciiString &name);
};

void Rva00318BC6Owner::rva00319A52(const AsciiString &name)
{
	const StringBase<char> &text = *(const StringBase<char> *)&name;
	if (!text.compare("Small"))
		rva00318BC6(1);
	else if (!text.compare("Medium"))
		rva00318BC6(2);
	else if (!text.compare("Large"))
		rva00318BC6(3);
}

// --- 0x003681DC (17B): false while +0x4B8 bit 0 is set, else the rowed
// 0x002645FF.
class Rva002645FF
{
public:
	bool rva002645FF();										// 0x002645FF
	bool rva003681DC();
private:
	char m_pad[0x4B8];
	unsigned char m_4B8;
};

bool Rva002645FF::rva003681DC()
{
	if (m_4B8 & 1)
		return false;
	return rva002645FF();
}

// --- 0x004CFC81 (80B): frames until the pending deadline (+0x1205C) while
// the queue (+0x12028 / +0x1202C) is non-empty, else frames since the
// earliest of the eight active (+0x04) slots' times (+0x12060).
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva004CFC81Logic
{
	char m_pad[0x40];
	unsigned int m_frame;
};

class Rva004CFC81
{
public:
	unsigned int rva004CFC81() const;
private:
	int m_00;
	int m_active[8];										// +0x04
	char m_pad24[0x12028 - 0x24];
	int m_queueBegin;										// +0x12028
	int m_queueEnd;											// +0x1202C
	char m_pad12030[0x1205C - 0x12030];
	unsigned int m_deadline;								// +0x1205C
	unsigned int m_times[8];								// +0x12060
};

unsigned int Rva004CFC81::rva004CFC81() const
{
	if (m_queueBegin != m_queueEnd)
		return m_deadline - ((Rva004CFC81Logic *)TheGameLogic)->m_frame;
	unsigned int earliest = 0x7fffffff;
	for (int i = 0; i < 8; ++i)
		if (m_active[i] && earliest >= m_times[i])
			earliest = m_times[i];
	return ((Rva004CFC81Logic *)TheGameLogic)->m_frame - earliest;
}
