// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (eighth
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered unless named, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.

class Object;
class Overridable;

// --- 0x002D50E5 / 0x002D50F8 / 0x002D510B (19B each): constructors from an
// int through the rowed pointer constructors of their bases.
#define GAP_INT_FORWARD_CTOR(NAME, BASE) \
	class BASE \
	{ \
	public: \
		BASE(const int *value); \
	}; \
	class NAME : public BASE \
	{ \
	public: \
		NAME(int value); \
	}; \
	NAME::NAME(int value) : BASE(&value) \
	{ \
	}

GAP_INT_FORWARD_CTOR(Rva002D50E5, Rva002D4594)
GAP_INT_FORWARD_CTOR(Rva002D50F8, Rva002D45C9)
GAP_INT_FORWARD_CTOR(Rva002D510B, Rva002D45FE)

// --- 0x003673DC (17B) / 0x003673ED (20B) / 0x00367401 (20B): setters of the
// +0x540 value and the +0x544 / +0x560 points.
struct Rva003673EDPoint
{
	float x;
	float y;
	float z;
};

class Rva003673DC
{
public:
	void rva003673DC(float value);
	void rva003673ED(const Rva003673EDPoint *pos);
	void rva00367401(const Rva003673EDPoint *pos);
private:
	char m_pad[0x540];
	float m_540;
	Rva003673EDPoint m_544;
	char m_pad550[0x560 - 0x550];
	Rva003673EDPoint m_560;
};

void Rva003673DC::rva003673DC(float value)
{
	m_540 = value;
}

void Rva003673DC::rva003673ED(const Rva003673EDPoint *pos)
{
	m_544 = *pos;
}

void Rva003673DC::rva00367401(const Rva003673EDPoint *pos)
{
	m_560 = *pos;
}

// --- 0x003674BD (13B): vtable 0x00C172A8 over a cleared word; 0x003674CA
// (29B): vtable 0x00BF8FE4 with an int and a flag; 0x003674E7 (15B): the
// team with the +0x40 id (rowed TeamFactory::findTeamByID).
struct GapZeroBase04
{
	int m_04;
	GapZeroBase04() : m_04(0) {}
};

class Rva003674BD : public GapZeroBase04
{
public:
	Rva003674BD();
	virtual ~Rva003674BD() {}
};

Rva003674BD::Rva003674BD()
{
}

class Rva003674CA
{
public:
	Rva003674CA(int value, bool flag);
	virtual ~Rva003674CA() {}
private:
	int m_04;
	int m_08;
	bool m_0C;
};

Rva003674CA::Rva003674CA(int value, bool flag) : m_04(0), m_08(value), m_0C(flag)
{
}

class Team;
class TeamFactory
{
public:
	Team *findTeamByID(unsigned int id);					// 0x0039F761
};
extern TeamFactory *TheTeamFactory;

class Rva003674E7
{
public:
	Team *getTeam() const;
private:
	char m_pad[0x40];
	unsigned int m_teamID;									// +0x40
};

Team *Rva003674E7::getTeam() const
{
	return TheTeamFactory->findTeamByID(m_teamID);
}

// --- 0x003B960E / 0x003B9622 / 0x003B9636: command-line flag parsers
// setting GlobalData +0x9AD, +0x9AE or clearing +0x2C.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva003B960EGlobalData
{
	char m_pad[0x2C];
	bool m_windowed;
	char m_pad2D[0x9AD - 0x2D];
	bool m_9AD;
	bool m_9AE;
};

int Rva003B960E(char *args[], int)
{
	if (TheWritableGlobalData)
		((Rva003B960EGlobalData *)TheWritableGlobalData)->m_9AD = true;
	return 1;
}

int Rva003B9622(char *args[], int)
{
	if (TheWritableGlobalData)
		((Rva003B960EGlobalData *)TheWritableGlobalData)->m_9AE = true;
	return 1;
}

int parseNoWin(char *args[], int)
{
	if (TheWritableGlobalData)
		((Rva003B960EGlobalData *)TheWritableGlobalData)->m_windowed = false;
	return 1;
}

// --- 0x00584ECA (14B, cdecl): deque iterator distance (rowed
// _Deque_iterator_base<BfmeE12>::_M_subtract); 0x00584ED8 / 0x00584EEC: the
// +0x18 word of the indexed 0x1C-byte record in the (+0x04 object's) +0x188
// table.
struct BfmeE12
{
	int a;
	int b;
	int c;
};

namespace _STL {
template <class T> struct _Deque_iterator_base
{
	int _M_subtract(const _Deque_iterator_base<T> &that) const;
	T *_M_cur;
	T *_M_first;
	T *_M_last;
	T **_M_node;
};
}

int Rva00584ECA(const _STL::_Deque_iterator_base<BfmeE12> *first, const _STL::_Deque_iterator_base<BfmeE12> *last)
{
	return last->_M_subtract(*first);
}

struct Rva00584ED8Record
{
	char m_pad[0x18];
	int m_18;
};

class Rva00584ED8
{
public:
	int rva00584ED8(int index) const;
	char m_pad[0x188];
	Rva00584ED8Record *m_records;							// +0x188
};

int Rva00584ED8::rva00584ED8(int index) const
{
	return m_records[index].m_18;
}

class Rva00584EEC
{
public:
	int rva00584EEC(int index) const;
private:
	int m_00;
	Rva00584ED8 *m_04;
};

int Rva00584EEC::rva00584EEC(int index) const
{
	return m_04->m_records[index].m_18;
}

// --- 0x0043DDBE (21B, cdecl): the open setup screen's +0x58 interface
// answer (virtual slot 21), -1 without a screen; 0x0043DDD3 (7B): forward
// through +0x00 to the rowed 0x0043DA65; 0x0043DDDA (12B): its +0x08 word.
class Rva0043DDBEInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20();
	virtual int s21();
};

struct Rva0043DDBEScreen
{
	char m_pad[0x58];
	Rva0043DDBEInterface *m_58;
};
extern int g_Va00E0333C;

int Rva0043DDBE()
{
	Rva0043DDBEScreen *screen = (Rva0043DDBEScreen *)g_Va00E0333C;
	if (!screen)
		return -1;
	return screen->m_58->s21();
}

class Rva0043DA65
{
public:
	int rva0043DA65();										// 0x0043DA65
	char m_pad[8];
	int m_08;
};

class Rva0043DDD3
{
public:
	int rva0043DDD3();
	void rva0043DDDA(int value);
private:
	Rva0043DA65 *m_00;
};

int Rva0043DDD3::rva0043DDD3()
{
	return m_00->rva0043DA65();
}

void Rva0043DDD3::rva0043DDDA(int value)
{
	m_00->m_08 = value;
}

// --- 0x004FC91D (13B): raise the out value to +0x10 (first two arguments
// unused); 0x004FC92D (42B): the logic's +0xFC less the region's +0x134.
class Rva0020E89C;
class Rva0020EAF6View
{
public:
	Rva0020E89C *rva0020EAF6(int id);						// 0x0020EAF6
};

struct Rva004FC92DLogic
{
	char m_pad[0xB0];
	Rva0020EAF6View *m_regionManager;						// +0xB0
	char m_padB4[0xFC - 0xB4];
	int m_FC;
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva004FC91D
{
public:
	void rva004FC91D(int a, int b, int *out) const;
	int rva004FC92D(int regionID) const;
private:
	char m_pad[0x10];
	int m_10;
};

void Rva004FC91D::rva004FC91D(int, int, int *out) const
{
	if (*out < m_10)
		*out = m_10;
}

int Rva004FC91D::rva004FC92D(int regionID) const
{
	Rva0020E89C *region = ((Rva004FC92DLogic *)TheLivingWorldLogic)->m_regionManager->rva0020EAF6(regionID);
	return ((Rva004FC92DLogic *)TheLivingWorldLogic)->m_FC - *(const int *)((const char *)region + 0x134);
}

// --- 0x0041C295 (21B) / 0x0041C2AC / 0x0041C2B5 / 0x0041C2BE / 0x0041C2C7
// (9B each): final-override reads: a +0x18 mask bit, the +0x50 value, the
// +0x60 and +0x78 members, the +0x7C value.
#include "../../Include/Common/Overridable.h"

struct Rva0041C295Data
{
	char m_pad[0x18];
	unsigned int m_18;
	char m_pad1C[0x50 - 0x1C];
	float m_50;
	char m_pad54[0x60 - 0x54];
	char m_60[0x78 - 0x60];
	char m_78[4];
	float m_7C;
};

class Rva0041C295 : public Overridable
{
public:
	bool rva0041C295(int bit) const;
	float rva0041C2AC() const;
	const void *rva0041C2B5() const;
	const void *rva0041C2BE() const;
	float rva0041C2C7() const;
};

bool Rva0041C295::rva0041C295(int bit) const
{
	return (((const Rva0041C295Data *)friend_getFinalOverride())->m_18 & (1 << bit)) ? true : false;
}

float Rva0041C295::rva0041C2AC() const
{
	return ((const Rva0041C295Data *)friend_getFinalOverride())->m_50;
}

const void *Rva0041C295::rva0041C2B5() const
{
	return ((const Rva0041C295Data *)friend_getFinalOverride())->m_60;
}

const void *Rva0041C295::rva0041C2BE() const
{
	return ((const Rva0041C295Data *)friend_getFinalOverride())->m_78;
}

float Rva0041C295::rva0041C2C7() const
{
	return ((const Rva0041C295Data *)friend_getFinalOverride())->m_7C;
}

// --- 0x005EE9E5 (59B, cdecl): two (int, float, int, float) records equal.
struct Rva005EE9E5Record
{
	int a;
	float b;
	int c;
	float d;
};

int Rva005EE9E5(const Rva005EE9E5Record *x, const Rva005EE9E5Record *y)
{
	if (x->a == y->a && x->b == y->b && x->c == y->c && x->d == y->d)
		return 1;
	return 0;
}

// --- 0x00260F50 (39B): the +0x08 filter accepts the object (rowed
// 0x004D6BCD) and its +0x438 bit 0 is set.
class Rva004D6BCD
{
public:
	bool rva004D6BCD(const Object *obj) const;				// 0x004D6BCD
};

struct Rva00260F50Object
{
	char m_pad[0x438];
	unsigned char m_438;
};

class Rva00260F50
{
public:
	int rva00260F50(const Object *obj) const;
private:
	char m_pad[8];
	Rva004D6BCD *m_filter;
};

int Rva00260F50::rva00260F50(const Object *obj) const
{
	if (m_filter && m_filter->rva004D6BCD(obj) && !(((const Rva00260F50Object *)obj)->m_438 & 1))
		return 1;
	return 0;
}

// --- 0x004216EC (18B): a (-1, 0.0, 0) record; 0x004216FE (26B): whether the
// value exceeds the record's +0x04; 0x00421718 / 0x00421720 (8B each): set
// and clear the deque-search flag (g_00DC84F5).
struct Rva004216EC
{
	Rva004216EC();
	int m_00;
	float m_04;
	int m_08;
};

Rva004216EC::Rva004216EC() : m_00(-1), m_04(0.0f), m_08(0)
{
}

class Rva004216FE
{
public:
	int rva004216FE(const Rva004216EC *record, float value);
};

int Rva004216FE::rva004216FE(const Rva004216EC *record, float value)
{
	if (value > record->m_04)
		return 1;
	return 0;
}

extern unsigned char g_00DC84F5;

void Rva00421718()
{
	g_00DC84F5 = 1;
}

void Rva00421720()
{
	g_00DC84F5 = 0;
}
