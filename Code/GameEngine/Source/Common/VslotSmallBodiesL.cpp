// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch L: guarded forwards to already rowed functions. As
// in VslotSmallBodiesA-K, each class and method is address-derived unless the
// ledger already names it, and models only what its body touches; the
// comment above each gives the .rdata slot address(es) that reference it.
// Meanings are not recovered.

typedef int Int;
typedef bool Bool;

namespace _STL
{
template <class T> class allocator;
template <class T, class A = allocator<T> > class list
{
public:
	void push_back(const T &value);
private:
	void *m_node;
};
}

// slot at VA 0x00C37080: LivingWorldBattle's traversal visitor (the class
// whose inlined construction ~LivingWorldBattle stores, Rva003F6A91Dtor.cpp),
// slot 0 of its two-slot table (slot 1 is the folded deleting destructor at
// 0x003F4261). Hands the battle, viewed as its CreateAHeroData base at +0x04
// (NULL stays NULL), to the rowed 0x002B7250 on the entry's +0x08 member;
// answers true. Same shape as Rva005FED52::invoke (vtable 0x00C37064).
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *data);
};
struct Rva003F55B6Head
{
	Int m_00;
};
class CreateAHeroData
{
	Int m_00;
};
class Rva003F55B6Entry : public Rva003F55B6Head, public CreateAHeroData
{
};
struct Rva003F55B6Arg
{
	char m_pad00[0x08];
	Rva002B7250 m_08;
};
class Rva003F498ACallback
{
public:
	virtual bool invoke(int) = 0;
	~Rva003F498ACallback() {}
};
class Rva003F424F : public Rva003F498ACallback
{
public:
	virtual bool invoke(int entry);
	virtual ~Rva003F424F() {}
private:
	Rva003F55B6Entry *m_owner;
};
bool Rva003F424F::invoke(int entry)
{
	reinterpret_cast<Rva003F55B6Arg *>(entry)->m_08.rva002B7250(m_owner);
	return true;
}

// slots at VA 0x00C644C4, 0x00C64544 and 0x00C645AC: forward both arguments
// to a rowed method of the +0x134 (resp. +0x128) object when it is set.
class Rva001E11F8
{
public:
	void rva001E11F8(Int a, Int b);
};
class Rva002CA9CA
{
public:
	void rva002CAC6E(Int a, Int b);
};
class ObjectCreationList
{
public:
	void rva001F0410(void *a, void *b);
};
class Rva00508F0C
{
public:
	void rva00508F0C(Int a, Int b);
private:
	char m_pad00[0x134];
	Rva001E11F8 *m_134;
};
void Rva00508F0C::rva00508F0C(Int a, Int b)
{
	if (m_134)
		m_134->rva001E11F8(a, b);
}
class Rva00509367
{
public:
	void rva00509367(Int a, Int b);
private:
	char m_pad00[0x128];
	Rva002CA9CA *m_128;
};
void Rva00509367::rva00509367(Int a, Int b)
{
	if (m_128)
		m_128->rva002CAC6E(a, b);
}
class Rva0050959C
{
public:
	void rva0050959C(void *a, void *b);
private:
	char m_pad00[0x128];
	ObjectCreationList *m_128;
};
void Rva0050959C::rva0050959C(void *a, void *b)
{
	if (m_128)
		m_128->rva001F0410(a, b);
}

// slot at VA 0x00C66420: for argument 1, runs the rowed 0x0044BD79 on the
// +0x08 member when its first word is set.
class BfmeA1042N
{
public:
	void bfmeGo1042D();
	Int m_00;
};
class Rva00517364
{
public:
	void rva00517364(Int which);
private:
	char m_pad00[0x08];
	BfmeA1042N m_08;
};

// slots at VA 0x00C1AEC4, 0x00C6B90C, 0x00C6E27C and more: appends the
// argument to the int list at +0x14 (rowed list<int>::push_back).
class AIBuildable
{
public:
	void addNeed(Int value);
private:
	char m_pad00[0x14];
	_STL::list<Int> m_14;
};
void AIBuildable::addNeed(Int value)
{
	m_14.push_back(value);
}

// slots at VA 0x00C1C350, 0x00C1C3A4, 0x00C1C3E4 and more: the +0x08 field of
// the +0x04 system, or of the rowed 0x001FCBD7 factory's result without one.
class ParticleSystem
{
public:
	char m_pad00[0x08];
	Int m_08;
};
ParticleSystem *Make001FCBD7();
class Rva0055C44F
{
public:
	Int rva0055C44F();
private:
	char m_pad00[0x04];
	ParticleSystem *m_system;
};
Int Rva0055C44F::rva0055C44F()
{
	ParticleSystem *system = m_system;
	if (!system)
		system = Make001FCBD7();
	return system->m_08;
}

// Installed table output words. Original owner, base relationship and
// aggregate/return convention remain unknown. Native word operations only.
class Rva004647D8 {public:void *rva004647D8(void *output);};
void *Rva004647D8::rva004647D8(void *output) {unsigned int address=reinterpret_cast<unsigned int>(this);unsigned int *words=static_cast<unsigned int *>(output);words[0]=(address-0x20u)!=0u ? address : 0u;words[1]=address+0x34u;return output;}
