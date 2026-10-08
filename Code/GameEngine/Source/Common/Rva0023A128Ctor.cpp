// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva0023A128@@QAE@PAX0H@Z @0x0023A128 130B.
// Constructor of an object registered on two lists through the rowed append
// 0x005A0B4C: itself (first base at +0) on the holder passed as a1, and its
// second base at +4 on the list at +0x4C of the singleton TheLivingWorldLogic. Retail's
// unwind map: states 0 and 1 destroy the two base subobjects (+0 and +4,
// both through the folded 7-byte vptr setter 0x00238D97); state 2 the
// Rva0042D8D4 at +0x14 (rowed ctor 0x0042D8D4); states 3-4 the two zeroed
// members at +0x18/+0x1C, whose destructor is out of line (0x0023932B). The
// +4 slot first takes the second base's vtable and then this class's second
// vtable. m_08/m_0C are this class's own members (addressed from the object,
// not the base). Replaces the banked 0.92 attempt, which stored vtable
// addresses as data behind an empty base.
//
// Target evidence for the rest of the class:
// - Its one creator (0x0023A95F) passes itself as a0, the holder global
//   g_00DFEF18 as a1 and the global 0x00E03210 as a2, and parks the object in
//   its owning pointer at +0x13C (rowed reset 0x0023A053, whose pointee
//   destructor is 0x00239D7A).
// - The two vtables (VA 0x00BED6C0 and 0x00BED6B8) have two slots each and
//   no destructor slot, so the destructor 0x00239D7A is not virtual; both
//   bases restore the same table 0x00BED658, whose two slots are the shared
//   3-byte ret 4 at 0x0047A69C. Two bases with identical two-slot tables is
//   a structural inference from those bytes.
// - First table: slot 0 (0x0023A1AA) drops this object through the
//   creator's +0x13C owning pointer (rowed clear 0x0023A039); slot 1
//   (0x00239B7E) resets the +0x10 object (rowed 0x0042CC1B) and refreshes the
//   two items. Second table: slot 0 (0x00239B94) is the same refresh compiled
//   for the +4 base (this - 4); slot 1 keeps the base's empty body.
// - The refresh 0x00239457 keeps an item in the +0x18 owning pointer while
//   the holder's +0x18 byte is set, its +0x19 byte clear and TheGameLogic's
//   +0x114 mode is not 3, and one in +0x1C under the same holder test when
//   the rowed GameLogic predicate 0x0023C6A4 holds; otherwise it drops them
//   (rowed 0x0023932B). The items are 4-byte objects built by 0x0042C76B
//   (holder, +0x10 object, &m_14) and 0x0042C8D1 (holder, +0x10 object), both
//   deleted through the rowed destructor 0x0042C1B7; treating both builders
//   as constructors of that one class is a structural inference.

#include "GameLogicObjectLookupView.h"

class LivingWorldLogic;
LivingWorldLogic *TheLivingWorldLogic;
// Retail initializer in GameEngine::init (0x0022E2E4) names this singleton.
// Matched DIR32 references bind it to RVA 0x009FEF10; the retail slot is zero.
// BFME 1 donor ba7ddda7 defines the same named singleton, without proving its target layout.

extern GameLogic *TheGameLogic;

struct Rva002BA8F1Listener;
class CreateAHeroData;
// The list's erase (0x002B7250) is rowed under its own address-named class.
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *who);
};
class Rva005A0B4CList : public Rva002B7250
{
public:
	void append(Rva002BA8F1Listener *p);
private:
	char m_pad[12];
};
// The holder global g_00DFEF18 (Rva002D3627Check.cpp's view).
class Rva002D3627Host
{
public:
	char pad[4];
	Rva005A0B4CList list; // +0x04
	char pad10[0x18 - 0x10];
	unsigned char m_18;
	unsigned char m_19;
};
class Rva002BA8F1Logic
{
public:
	char pad[0x4c];
	Rva005A0B4CList list;
};

// GameLogic's mode view (Rva0023C6A4Check.cpp).
class Rva0023C6A4
{
public:
	bool rva0023C6A4();

	char m_pad[0x114];
	int m_unk114; // +0x114
};

class Rva0042CBB6
{
public:
	void rva0042CC1B();
};

class Rva0042D8D4
{
public:
	Rva0042D8D4();
	~Rva0042D8D4();
private:
	int m_0;
};
class Rva0042C1B7Item
{
public:
	Rva0042C1B7Item(Rva002D3627Host *holder, Rva0042CBB6 *source, Rva0042D8D4 *state); // 0x0042C76B
	Rva0042C1B7Item(Rva002D3627Host *holder, Rva0042CBB6 *source); // 0x0042C8D1
	~Rva0042C1B7Item();
private:
	void *m_impl;
};
class Rva0023932BPtr
{
public:
	void rva0023932B(); // delete and null
	void rva00239345(Rva0042C1B7Item *item); // replace
	Rva0042C1B7Item *get() const { return m_ptr; }
protected:
	Rva0042C1B7Item *m_ptr;
};
class Rva0023932BMember : public Rva0023932BPtr
{
public:
	Rva0023932BMember() { m_ptr = 0; }
	~Rva0023932BMember() { rva0023932B(); }
};
class Rva0023A128Listener
{
public:
	Rva0023A128Listener() {}
	~Rva0023A128Listener() {}
	virtual void rva0023A1AA(int);
	virtual void rva00239B7E(int);
};
class Rva0023A128Link
{
public:
	Rva0023A128Link() {}
	~Rva0023A128Link() {}
	virtual void rva00239B94(int);
	virtual void v01(int);
};
class Rva0023A039
{
public:
	void clear();
private:
	void *m_ptr;
};
struct Rva0023A128Owner
{
	char pad[0x13C];
	Rva0023A039 m_13C; // +0x13C
};
class Rva0023A128 : public Rva0023A128Listener, public Rva0023A128Link
{
public:
	Rva0023A128(void *a0, void *a1, int a2);
	~Rva0023A128();
	virtual void rva0023A1AA(int);
	virtual void rva00239B7E(int);
	virtual void rva00239B94(int);
	void rva00239457();
private:
	Rva0023A128Owner *m_08;
	Rva002D3627Host *m_0C;
	Rva0042CBB6 *m_10;
	Rva0042D8D4 m_14;
	Rva0023932BMember m_18;
	Rva0023932BMember m_1C;
};
Rva0023A128::Rva0023A128(void *a0, void *a1, int a2)
	: m_08((Rva0023A128Owner *)a0), m_0C((Rva002D3627Host *)a1), m_10((Rva0042CBB6 *)a2)
{
	m_0C->list.append((Rva002BA8F1Listener *)static_cast<Rva0023A128Listener *>(this));
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->list.append((Rva002BA8F1Listener *)static_cast<Rva0023A128Link *>(this));
}

// Retail 0x00239D7A, 127 bytes.
Rva0023A128::~Rva0023A128()
{
	m_0C->list.rva002B7250((CreateAHeroData *)static_cast<Rva0023A128Listener *>(this));
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->list.rva002B7250((CreateAHeroData *)static_cast<Rva0023A128Link *>(this));
}

// Retail 0x00239457, 226 bytes.
void Rva0023A128::rva00239457()
{
	unsigned char enabled = m_0C->m_18;
	if (enabled && !m_0C->m_19 && ((Rva0023C6A4 *)TheGameLogic)->m_unk114 != 3)
	{
		if (!m_18.get())
			m_18.rva00239345(new Rva0042C1B7Item(m_0C, m_10, &m_14));
	}
	else
		m_18.rva0023932B();

	if (m_0C->m_18 && !m_0C->m_19 && ((Rva0023C6A4 *)TheGameLogic)->rva0023C6A4())
	{
		if (!m_1C.get())
			m_1C.rva00239345(new Rva0042C1B7Item(m_0C, m_10));
	}
	else
		m_1C.rva0023932B();
}

// Retail 0x0023A1AA, 17 bytes.
void Rva0023A128::rva0023A1AA(int)
{
	m_08->m_13C.clear();
}

// Retail 0x00239B7E, 22 bytes.
void Rva0023A128::rva00239B7E(int)
{
	m_10->rva0042CC1B();
	rva00239457();
}

// Retail 0x00239B94, 23 bytes.
void Rva0023A128::rva00239B94(int)
{
	m_10->rva0042CC1B();
	rva00239457();
}
