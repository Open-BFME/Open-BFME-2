// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no Ghidra function covers (third
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings.
struct Coord3D;
class Object;

// --- 0x002FDB67 / 0x002FDB7D / 0x00525136 / 0x0052514C (22B each): vtable
// constructors over a cleared +0x04 that store their argument at +0x08.
#include "../../Include/Common/BfmeAccessorMacros.h"

// vtables VA 0x00C071B4, 0x00C071C0, 0x00C67E60, 0x00C67E70
GAP_VTABLE_ARG_CTOR(Rva002FDB67)
GAP_VTABLE_ARG_CTOR(Rva002FDB7D)
GAP_VTABLE_ARG_CTOR(Rva00525136)
GAP_VTABLE_ARG_CTOR(Rva0052514C)

// --- 0x00318DC0 (27B) / 0x00318DDB (17B): a callback record (code pointer
// at +0x00, two arguments) - assignment of the arguments and the invoke on a
// receiver; 0x005DBD10 (25B) / 0x005DBD29 (20B): the two-word / three-argument
// variant.
class __single_inheritance GapReceiver;
typedef void (GapReceiver::*GapCallback2)(int, int);
typedef void (GapReceiver::*GapCallback3)(int, int, int);

class Rva00318DC0
{
public:
	Rva00318DC0 &operator=(const Rva00318DC0 &that);
	void invoke(GapReceiver *receiver);
private:
	GapCallback2 m_callback;
	int m_a;
	int m_b;
	int m_0C;
};

Rva00318DC0 &Rva00318DC0::operator=(const Rva00318DC0 &that)
{
	m_a = that.m_a;
	m_b = that.m_b;
	m_0C = that.m_0C;
	return *this;
}

void Rva00318DC0::invoke(GapReceiver *receiver)
{
	(receiver->*m_callback)(m_a, m_b);
}

// --- 0x004A6BE7 (44B): through the +0x18 owner's object (+0x14) and its
// +0x258 interface (virtual slot 95), virtual slot 13 with 0; returns 0.
// --- 0x00583A07 (11B): set the +0x04 object's +0x120 flag.
struct Rva00583A07Target
{
	char m_pad[0x120];
	bool m_120;
};

class Rva00583A07
{
public:
	void rva00583A07();
private:
	Rva00583A07Target *m_00;
	Rva00583A07Target *m_04;
};

void Rva00583A07::rva00583A07()
{
	m_04->m_120 = true;
}

// --- 0x005F273B / 0x005F2744 / 0x005F274F / 0x005F275B: bits 0..3 of the
// +0x04 object's +0x58 flags.
struct Rva005F273BFlags
{
	char m_pad[0x58];
	unsigned char m_bit0 : 1;
	unsigned char m_bit1 : 1;
	unsigned char m_bit2 : 1;
	unsigned char m_bit3 : 1;
};

class Rva005F273B
{
public:
	bool rva005F273B() const;
	bool rva005F2744() const;
	bool rva005F274F() const;
	bool rva005F275B() const;
private:
	int m_00;
	Rva005F273BFlags *m_04;
};

bool Rva005F273B::rva005F273B() const { return m_04->m_bit0; }
bool Rva005F273B::rva005F2744() const { return m_04->m_bit1; }
bool Rva005F273B::rva005F274F() const { return m_04->m_bit2; }
bool Rva005F273B::rva005F275B() const { return m_04->m_bit3; }

// --- 0x004A9B51 / 0x004A9B60 / 0x004A9B6F (15B each): null-preserving
// pointers to the +0x3E4 / +0x3E8 / +0x3EC subobjects.
class Rva004A9B51Sub
{
public:
	int m_00;
};

class Rva004A9B51
{
public:
	Rva004A9B51Sub *rva004A9B51();
	Rva004A9B51Sub *rva004A9B60();
	Rva004A9B51Sub *rva004A9B6F();
private:
	char m_pad[0x3E4];
	Rva004A9B51Sub m_3E4;
	Rva004A9B51Sub m_3E8;
	Rva004A9B51Sub m_3EC;
};

Rva004A9B51Sub *Rva004A9B51::rva004A9B51() { return this ? &m_3E4 : 0; }
Rva004A9B51Sub *Rva004A9B51::rva004A9B60() { return this ? &m_3E8 : 0; }
Rva004A9B51Sub *Rva004A9B51::rva004A9B6F() { return this ? &m_3EC : 0; }

// --- 0x0052AC16 / 0x0052AC29 (19B each): assign a by-value delegate
// description through the rowed assignments; return this.
#include "../../Include/Common/DelegateDesc.h"

class Rva0052A786
{
public:
	Rva0052A786 &rva0052A786(const DelegateDesc *desc);	// 0x0052A786
	Rva0052A786 &rva0052AC16(DelegateDesc desc);
};

Rva0052A786 &Rva0052A786::rva0052AC16(DelegateDesc desc)
{
	rva0052A786(&desc);
	return *this;
}

class Rva0052A7C1
{
public:
	Rva0052A7C1 &rva0052A7C1(const DelegateDesc *desc);	// 0x0052A7C1
	Rva0052A7C1 &rva0052AC29(DelegateDesc desc);
};

Rva0052A7C1 &Rva0052A7C1::rva0052AC29(DelegateDesc desc)
{
	rva0052A7C1(&desc);
	return *this;
}

// --- 0x0028864F (46B): whether this override's final override has a higher
// +0x18 value than the other's. The +0x18 int belongs to a derived template
// class that is not recovered; this view names only that member.
#include "../../Include/Common/Overridable.h"

struct Rva0028864FOverride : public Overridable
{
	char m_pad10[8];
	int m_18;	// +0x18
};

bool Overridable::rva0028864F(const Overridable *other) const
{
	const Rva0028864FOverride *mine = (const Rva0028864FOverride *)friend_getFinalOverride();
	const Rva0028864FOverride *theirs = (const Rva0028864FOverride *)other->friend_getFinalOverride();
	if (mine && theirs)
		return mine->m_18 > theirs->m_18;
	return false;
}

// --- 0x00525AAC (19B): by-value DelegateDesc wrapper over the rowed binder
// 0x00525916 on the same object (shape of rva0052AC16 above).
class Rva00525916
{
public:
	Rva00525916 &rva00525916(const DelegateDesc *desc);	// 0x00525916
	Rva00525916 &rva00525AAC(DelegateDesc desc);
};

Rva00525916 &Rva00525916::rva00525AAC(DelegateDesc desc)
{
	rva00525916(&desc);
	return *this;
}

// --- 0x00518756 (19B): constructor taking a 16-byte functor binding by value
// and handing its address to the rowed holder base constructor 0x0057BC63.
#include "../../Include/GameClient/FunctorBinding.h"

class Rva0057BC63FunctorHolder
{
public:
	Rva0057BC63FunctorHolder(const FunctorBinding &binding);	// 0x0057BC63
	void *m_ptr;
};

class Rva00518756 : public Rva0057BC63FunctorHolder
{
public:
	Rva00518756(FunctorBinding binding);
};

Rva00518756::Rva00518756(FunctorBinding binding) : Rva0057BC63FunctorHolder(binding)
{
}
