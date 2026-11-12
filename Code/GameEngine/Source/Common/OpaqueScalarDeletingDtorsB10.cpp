// cl: /O1 /GX /DNDEBUG /MD /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
//
// Opaque scalar deleting destructors, batch B10: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Rva0043B660 is the exception: its default constructor at 0x0043B6D7 is now
// recovered in this TU and initializes the +4 tree member.
// Other than the explicitly evidenced Rva0043B660 member view below, owner
// identities remain unresolved and these declarations carry no layout claim
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x00415E6E  0x00415CAB  0x00C3A288#0
//   0x00419E1C  0x00419E38  0x00C3AD60#0, 0x00C6AB40#0
//   0x0041A7DB  0x0041A644  0x00C3AD70#0
//   0x0041B7D9  0x0041B790  0x00C3ADD8#0
//   0x0041F25E  0x0041F042  0x00C3AF78#0
//   0x0041F9D2  0x0041F94A  0x00C3B8C8#0
//   0x0041FC9B  0x0041FB13  0x00C3B914#0
//   0x00426A3F  0x00426745  0x00C3C408#0  (rowed in BfmeStringRecord00426A5B.cpp; the class stays
//               here for its +0xC thunk 0x0042673D)
//   0x0042C977  0x0042C833  0x00C3C6EC#1
//   0x00432151  0x00431FB5  0x00C3C9AC#4
//   0x00436197  0x00435DE7  0x00C3CDC8#0
//   0x0043AE0C  0x0043A351  0x00C3D478#0
//   0x0043B709  0x0043B660  0x00C3D5F0#0
//   0x0043D3BE  0x0043D1C9  0x00C3D7F8#0
//   0x00444067  0x0052163E  0x00C3DFA8#0, 0x00C67840#0
//   0x00488D1F  0x00488D3B  0x00C4B510#0

typedef bool Bool;
#include "subsystem_interface.h"
// The former 40E81E placeholder is retired separately: native C394F0
// belongs to the independently proven ArmySummary class, whose proper
// home already emits the complete 28-byte deleting wrapper.

#include "Common/Snapshot.h"

namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class T, class Compare = less<T>, class Alloc = allocator<T> >
class set
{
public:
	set();

private:
	void *m_header;
	unsigned int m_count;
};
}

struct EmitVtableTag;

class Rva0022A809Subsystem : public SubsystemInterface
{
public:
	Rva0022A809Subsystem(EmitVtableTag *);
public:
	virtual ~Rva0022A809Subsystem();
};

// ?<Rva0022A809Subsystem::Rva0022A809Subsystem> absent-from-retail
Rva0022A809Subsystem::Rva0022A809Subsystem(EmitVtableTag *)
{
}

class Rva00419E38
{
public:
	Rva00419E38(EmitVtableTag *);
public:
	virtual ~Rva00419E38();
};

// ?<Rva00419E38::Rva00419E38> absent-from-retail
Rva00419E38::Rva00419E38(EmitVtableTag *)
{
}

// Rva0041B790's two tables (data ledger): GameEngineDeletingBase at +0 and Snapshot at +0xC, whose
// slot 0 is a this-adjusting (sub ecx, 0xC) deleting-destructor thunk.
// Both bases are the native 12-byte SubsystemInterface: ctor 1B4E63,
// dtor 1B4E74 and vtable BD77A0. Use its existing shared declaration.
class Rva0041B790 : public SubsystemInterface, public Snapshot
{
public:
	Rva0041B790(EmitVtableTag *);
public:
	virtual ~Rva0041B790();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
};

// ?<Rva0041B790::Rva0041B790> absent-from-retail
Rva0041B790::Rva0041B790(EmitVtableTag *)
{
}

// Slot view as Rva0041F042OwnerDtor.cpp's (vtable 0x00C3AF78: 14 slots, a
// SubsystemInterface whose lifetime, init, postProcessLoad, reset and update
// it overrides), so both units emit one vtable.
class Rva0041F042 : public SubsystemInterface
{
public:
	Rva0041F042(EmitVtableTag *);
public:
	virtual ~Rva0041F042();
	virtual void init() = 0;
	virtual void postProcessLoad() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;
};

// ?<Rva0041F042::Rva0041F042> absent-from-retail
Rva0041F042::Rva0041F042(EmitVtableTag *)
{
}

class Rva0041F94A : public SubsystemInterface
{
public:
	Rva0041F94A(EmitVtableTag *);
public:
	virtual ~Rva0041F94A();
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
};

// ?<Rva0041F94A::Rva0041F94A> absent-from-retail
Rva0041F94A::Rva0041F94A(EmitVtableTag *)
{
}

// Rva00426745's two tables (data ledger): SubsystemInterface at +0 and Rva00426745SnapshotBase at +0xC, whose
// slot 0 is a this-adjusting (sub ecx, 0xC) deleting-destructor thunk.
// Native base constructor 0x001B4E63 has its measured 17-byte provider in
// subsystem/SubsystemInterface.cpp. Declare it rather than emitting the
// implicit constructor for this bounded 12-byte deleting-destructor view.

class Rva00426745SnapshotBase { public: virtual ~Rva00426745SnapshotBase() {} };
class Rva00426745 : public SubsystemInterface, public Rva00426745SnapshotBase
{
public:
	Rva00426745(EmitVtableTag *);
public:
	virtual ~Rva00426745();
};

// ?<Rva00426745::Rva00426745> absent-from-retail
Rva00426745::Rva00426745(EmitVtableTag *)
{
}

// Native42C677 is now emitted by the complete Rva0042C5C3 owner and its
// proven two-slot primary table in Rva0042C5C3Dtor.cpp.

class Rva0042C833
{
public:
	Rva0042C833(EmitVtableTag *);
public:
	virtual ~Rva0042C833();
};

// ?<Rva0042C833::Rva0042C833> absent-from-retail
Rva0042C833::Rva0042C833(EmitVtableTag *)
{
}

// Vtable 0x00C3C9B8 holds the translator slot before the deleting dtor
// (Rva00431FB5Destructor.cpp's base view).
class Rva00431FB5
{
public:
	Rva00431FB5(EmitVtableTag *);
public:
	virtual void translate() = 0;
	virtual ~Rva00431FB5();
};

// ?<Rva00431FB5::Rva00431FB5> absent-from-retail
Rva00431FB5::Rva00431FB5(EmitVtableTag *)
{
}

// The screen destructors share the GameWindow and secondary-base prefix.
// Their rowed base destructor fixes the secondary vptr at +0x218.
class GameWindow
{
public:
	GameWindow();
protected:
	virtual ~GameWindow();
private:
	char m_unmodelled[0x214];
};

#include "../../Include/GameClient/Rva005248D0.h"

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString m_filename270;
};

class AptSaveLoad : public _bfme_AptGameWindow
{
public:
	AptSaveLoad(EmitVtableTag *);
public:
	virtual ~AptSaveLoad();
};

// ?<AptSaveLoad::AptSaveLoad> absent-from-retail
AptSaveLoad::AptSaveLoad(EmitVtableTag *) : _bfme_AptGameWindow(0)
{
}

class Rva00355D66
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
};

class Rva0043A278 : public Rva00355D66
{
public:
	Rva0043A278(EmitVtableTag *);
public:
	virtual ~Rva0043A278();
};

// ?<Rva0043A278::Rva0043A278> absent-from-retail
Rva0043A278::Rva0043A278(EmitVtableTag *)
{
}

// Target facts: Rva0043B660 constructs a member at +4 through the rowed
// set constructor 0x0043B69C and destroys it through
// 0x0043B4B4, the destructor rowed as Rva0043B2E2's in RvaTreeDtorFamily.cpp
// (named after its owner's erase 0x0043B2E2). The set element spelling/layout
// is carried from the verified STLport transfer and remains donor inference.
struct Rva0043B69CElement {
	Rva0043B69CElement();
	Rva0043B69CElement(const Rva0043B69CElement &);
	~Rva0043B69CElement();
	Rva0043B69CElement &operator=(const Rva0043B69CElement &);
	char bytes[8];
};
bool operator<(const Rva0043B69CElement &, const Rva0043B69CElement &);

class Rva0043B2E2
{
public:
	~Rva0043B2E2();
private:
	_STL::set<Rva0043B69CElement> m_tree;
};

class Rva0043B660 : public Snapshot
{
public:
	Rva0043B660();
public:
	virtual ~Rva0043B660();
private:
	Rva0043B2E2 m_member04;
};

// Target evidence: this vptr is the same one used by the rowed deleting
// destructor at 0x0043B709; the direct +4 constructor call and matching +4
// destructor call place this set member in Rva0043B660.
Rva0043B660::Rva0043B660()
{
}

// The target installs the derived vtable then destroys the +4 subobject. Its
// base-vtable store is supported by target bytes at 0x0043B68C.
Rva0043B660::~Rva0043B660()
{
}

class AptSpellStore : public _bfme_AptGameWindow
{
public:
	AptSpellStore(EmitVtableTag *);
public:
	virtual ~AptSpellStore();
};

// ?<AptSpellStore::AptSpellStore> absent-from-retail
AptSpellStore::AptSpellStore(EmitVtableTag *) : _bfme_AptGameWindow(0)
{
}

// Vtable 0x00C67840: the deleting dtor, then the input-route base's rowed
// link/unlink slots 0x0031455E / 0x00314581 (BfmeThreeHundredFortyTwo.cpp's
// view), then the input slot.
class Rva0031455E
{
public:
	Rva0031455E();
	virtual ~Rva0031455E();
	virtual void Rva0031455ELink(Rva0031455E *);
	virtual void Rva00314581Unlink();
private:
	void *next;
	void *window;
};

class Rva0052163E : public Rva0031455E
{
public:
	Rva0052163E(EmitVtableTag *);
public:
	virtual ~Rva0052163E();
	virtual int input(unsigned int msg, unsigned int data1, unsigned int data2) = 0;
};

// ?<Rva0052163E::Rva0052163E> absent-from-retail
Rva0052163E::Rva0052163E(EmitVtableTag *)
{
}

class Rva00488D3B
{
public:
	Rva00488D3B(EmitVtableTag *);
public:
	virtual ~Rva00488D3B();
};

// ?<Rva00488D3B::Rva00488D3B> absent-from-retail
Rva00488D3B::Rva00488D3B(EmitVtableTag *)
{
}
