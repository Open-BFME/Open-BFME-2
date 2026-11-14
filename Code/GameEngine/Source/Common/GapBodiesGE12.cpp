// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (twelfth
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.

#include <ctype.h>
#include <stdlib.h>

// --- 0x0030BE5D (57B): a non-zero 2D offset goes to the +0x68 strip (rowed
// QuadStrip2D 0x005382F4), then virtual slot 10.
struct BfmeE8
{
	float x;
	float y;
};

#include "../../Include/Common/QuadStrip2D.h"

class Rva0030BE5D
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9();
	virtual void s10();
	void translate(const BfmeE8 *offset);
private:
	char m_pad[0x68 - 4];
	QuadStrip2D m_strip;									// +0x68
};

void Rva0030BE5D::translate(const BfmeE8 *offset)
{
	if (offset->x != 0.0f || offset->y != 0.0f)
	{
		m_strip.rva005382F4(*offset);
		s10();
	}
}

// --- 0x00431FF2 (70B): consume the two pending flags (+0x04, +0x05); a
// message of type 23..24 with the first or 27..28 with the second is handled
// (1), anything else goes to the +0x08 handler (virtual slot 2).
struct Rva00431FF2Message
{
	char m_pad[0x10];
	int m_type;
};

class Rva00431FF2Handler
{
public:
	virtual void s0(); virtual void s1();
	virtual int s2(Rva00431FF2Message *msg);
};

class Rva00431FF2
{
public:
	int translateGameMessage(Rva00431FF2Message *msg);
private:
	int m_00;
	bool m_04;
	bool m_eatNextRightClick;
	char m_pad06[2];
	Rva00431FF2Handler *m_handler;							// +0x08
};

int Rva00431FF2::translateGameMessage(Rva00431FF2Message *msg)
{
	bool first = m_04;
	bool second = m_eatNextRightClick;
	m_04 = false;
	m_eatNextRightClick = false;
	switch (msg->m_type)
	{
	case 23:
	case 24:
		if (first)
			return 1;
		break;
	case 27:
	case 28:
		if (second)
			return 1;
		break;
	}
	return m_handler->s2(msg);
}

// --- 0x00524F61 (9B): vtable 0x00C67E3C only; 0x00524F6A (13B): the +0x10
// object's +0x18 word.
class Rva0052634F_Base
{
public:
	Rva0052634F_Base();
	virtual ~Rva0052634F_Base() {}
};

Rva0052634F_Base::Rva0052634F_Base()
{
}

struct Rva00524F6AData
{
	char m_pad[0x18];
	int m_18;
};

class Rva00524F6A
{
public:
	void rva00524F6A(int value);
private:
	char m_pad[0x10];
	Rva00524F6AData *m_10;
};

void Rva00524F6A::rva00524F6A(int value)
{
	m_10->m_18 = value;
}

// --- 0x005FD4AA..0x005FD4DD: the indexed 0x18-byte record (from +0x24 of
// the +0x04 object): its +0x00 and +0x04 members, its +0x08 and +0x0C words.
struct Rva005FD4AARecord
{
	int m_00;
	int m_04;
	int m_commandPoints;
	int m_maxCommandPoints;
	int m_10;
	int m_14;
};

struct Rva005FD4AATable
{
	char m_pad[0x24];
	Rva005FD4AARecord m_records[1];
};

class Rva005FD4AA
{
public:
	int *getRegionName(int index) const;
	int *getArmyName(int index) const;
	int getCommandPoints(int index) const;
	int getMaxCommandPoints(int index) const;
private:
	int m_00;
	Rva005FD4AATable *m_04;
};

int *Rva005FD4AA::getRegionName(int index) const
{
	return &m_04->m_records[index].m_00;
}

int *Rva005FD4AA::getArmyName(int index) const
{
	return &m_04->m_records[index].m_04;
}

int Rva005FD4AA::getCommandPoints(int index) const
{
	return m_04->m_records[index].m_commandPoints;
}

int Rva005FD4AA::getMaxCommandPoints(int index) const
{
	return m_04->m_records[index].m_maxCommandPoints;
}

// --- 0x005FDE81 (70B): a numeric string naming one of the +0x28 vector's
// 12-byte entries selects it (virtual slot 4).
struct PlayerTab
{
	char m_data[12];
};

// The battle-prompt player tabs movie clip (AptBattlePromptTabsConstructor.cpp:
// its ctor 0x005FE640 binds "_level%u.<prefix>_OnTabClicked" to this body, and
// its 12-byte tab vector is at +0x28).
class Rva005FE750
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(unsigned int index);
	void OnTabClicked(const char *text);
private:
	char m_pad[0x28 - 4];
	PlayerTab *m_begin;
	PlayerTab *m_end;
};

void Rva005FE750::OnTabClicked(const char *text)
{
	if (text && isdigit(*text))
	{
		int index = atoi(text);
		if (index >= 0 && (unsigned int)index < (unsigned int)(m_end - m_begin))
			s4(index);
	}
}
