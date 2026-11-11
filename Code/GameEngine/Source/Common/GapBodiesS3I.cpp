// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Table-reached bodies from .text gaps no ledger row covers (seat-3 batch I;
// see GapBodiesS3A.cpp). Retail bytes establish every shape; owning classes
// are not recovered unless a callee names them, so each keeps an
// address-derived name and a view of only the members it touches.

// --- 0x005D8929 (41B): whether the object's AI (+0x258) victim is a
// structure (kind-of bit 7 of its template word +0x108).
class Object;

#include "../../Include/GameLogic/Module/AIUpdate.h"

struct Rva005D8929TemplateView
{
	char m_pad[0x108];
	unsigned int m_kindOf;									// +0x108
};

class Object
{
public:
	int m_00;
	Rva005D8929TemplateView *m_template;					// +0x04
	char m_pad008[0x258 - 8];
	AIUpdateInterface *m_ai;								// +0x258
};

class Rva005D8929
{
public:
	virtual bool rva005D8929(Object *obj);
};

bool Rva005D8929::rva005D8929(Object *obj)
{
	Object *victim = obj->m_ai->getCurrentVictim();
	if (victim)
		return (bool)((victim->m_template->m_kindOf >> 7) & 1);
	return false;
}

// --- 0x006D6C90 (41B): return this Apt string to the free list
// (g_AptStringFreeList, linked through +0x0C) and release the +0x08 string
// when the rowed 0x006D3860 check (0x21) says so.
class Rva0089E1E0
{
public:
	unsigned char cmp(int value);							// 0x006D3860
};

#include "../../../Libraries/Source/Apt/EAStringC.h"

class Rva006D6D20;
extern Rva006D6D20 *g_AptStringFreeList;

class Rva006D6D20
{
public:
	virtual void ForceDelete();
private:
	int m_04;
	EAStringC m_string;										// +0x08
	Rva006D6D20 *m_nextFree;								// +0x0C
};

void Rva006D6D20::ForceDelete()
{
	m_nextFree = g_AptStringFreeList;
	g_AptStringFreeList = this;
	if (((Rva0089E1E0 *)&m_string)->cmp(0x21))
		m_string.rva006D3470();
}

// --- 0x005C4CE7 (52B): when the requested state differs from bit 2 of the
// +0xB8 bit-field word, set (4, 0, 4) or clear (0, 4, 0) it through the rowed
// 0x005C4B56; the second argument is unused.
class Rva005C4B56
{
public:
	void rva005C4B56(int set, int clear, int mask);			// 0x005C4B56
};

class Rva005C4CE7
{
public:
	virtual void rva005C4CE7(bool on, int unused);
private:
	char m_pad04[0xB8 - 4];
	unsigned int m_flag0 : 1;								// +0xB8 bit 0
	unsigned int m_flag1 : 1;
	unsigned int m_flag2 : 1;								// +0xB8 bit 2
};

void Rva005C4CE7::rva005C4CE7(bool on, int)
{
	if (m_flag2 != on)
	{
		int setBits;
		int clearBits;
		int mask;
		if (on)
		{
			setBits = 4;
			mask = 4;
			clearBits = 0;
		}
		else
		{
			mask = 0;
			setBits = 0;
			clearBits = 4;
		}
		((Rva005C4B56 *)this)->rva005C4B56(setBits, clearBits, mask);
	}
}

// --- 0x005DB045 (47B): forward to the rowed ExperienceTracker 0x0039B16F
// with a clear fourth flag and a 1.0 scale, then run the rowed 0x005DB004.
#include "../../Include/GameLogic/ExperienceTracker.h"

#include "../../Include/Common/Rva005DB004.h"

class Rva005DB045
{
public:
	virtual void rva005DB045(float value, bool a, bool b, bool d);
};

void Rva005DB045::rva005DB045(float value, bool a, bool b, bool d)
{
	((ExperienceTracker *)this)->rva0039B16F(value, a, b, false, d, 1.0f);
	((Rva005DB004 *)this)->rva005DB004();
}
