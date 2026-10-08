// cl: /O1 /GX /DNDEBUG /MD /Ireference/shims/moduledata
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
//   0x0040E81E  0x0040E499  0x00C394F0#0
//   0x0041456E  0x00414520  0x00C3A08C#0
//   0x00415E6E  0x00415CAB  0x00C3A288#0
//   0x00419E1C  0x00419E38  0x00C3AD60#0, 0x00C6AB40#0
//   0x0041A7DB  0x0041A644  0x00C3AD70#0
//   0x0041B7D9  0x0041B790  0x00C3ADD8#0
//   0x0041F25E  0x0041F042  0x00C3AF78#0
//   0x0041F9D2  0x0041F94A  0x00C3B8C8#0
//   0x0041FC9B  0x0041FB13  0x00C3B914#0
//   0x00426A3F  0x00426745  0x00C3C408#0
//   0x0042C677  0x0042C5C3  0x00C3C6E4#1
//   0x0042C977  0x0042C833  0x00C3C6EC#1
//   0x00432151  0x00431FB5  0x00C3C9AC#4
//   0x00436197  0x00435DE7  0x00C3CDC8#0
//   0x0043AE0C  0x0043A351  0x00C3D478#0
//   0x0043AE28  0x0043A396  0x00C3D50C#0
//   0x0043B709  0x0043B660  0x00C3D5F0#0
//   0x0043D3BE  0x0043D1C9  0x00C3D7F8#0
//   0x00444067  0x0052163E  0x00C3DFA8#0, 0x00C67840#0
//   0x00488D1F  0x00488D3B  0x00C4B510#0

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

class Rva0040E499
{
public:
	Rva0040E499(EmitVtableTag *);
public:
	virtual ~Rva0040E499();
};

// ?<Rva0040E499::Rva0040E499> absent-from-retail
Rva0040E499::Rva0040E499(EmitVtableTag *)
{
}

class Rva00414520
{
public:
	Rva00414520(EmitVtableTag *);
public:
	virtual ~Rva00414520();
};

// ?<Rva00414520::Rva00414520> absent-from-retail
Rva00414520::Rva00414520(EmitVtableTag *)
{
}

class Rva00415CAB
{
public:
	Rva00415CAB(EmitVtableTag *);
public:
	virtual ~Rva00415CAB();
};

// ?<Rva00415CAB::Rva00415CAB> absent-from-retail
Rva00415CAB::Rva00415CAB(EmitVtableTag *)
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

class Rva0041A644
{
public:
	Rva0041A644(EmitVtableTag *);
public:
	virtual ~Rva0041A644();
};

// ?<Rva0041A644::Rva0041A644> absent-from-retail
Rva0041A644::Rva0041A644(EmitVtableTag *)
{
}

class Rva0041B790
{
public:
	Rva0041B790(EmitVtableTag *);
public:
	virtual ~Rva0041B790();
};

// ?<Rva0041B790::Rva0041B790> absent-from-retail
Rva0041B790::Rva0041B790(EmitVtableTag *)
{
}

class Rva0041F042
{
public:
	Rva0041F042(EmitVtableTag *);
public:
	virtual ~Rva0041F042();
};

// ?<Rva0041F042::Rva0041F042> absent-from-retail
Rva0041F042::Rva0041F042(EmitVtableTag *)
{
}

class Rva0041F94A
{
public:
	Rva0041F94A(EmitVtableTag *);
public:
	virtual ~Rva0041F94A();
};

// ?<Rva0041F94A::Rva0041F94A> absent-from-retail
Rva0041F94A::Rva0041F94A(EmitVtableTag *)
{
}

class Rva00426745
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

class Rva0042C5C3
{
public:
	Rva0042C5C3(EmitVtableTag *);
public:
	virtual ~Rva0042C5C3();
};

// ?<Rva0042C5C3::Rva0042C5C3> absent-from-retail
Rva0042C5C3::Rva0042C5C3(EmitVtableTag *)
{
}

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

class Rva00431FB5
{
public:
	Rva00431FB5(EmitVtableTag *);
public:
	virtual ~Rva00431FB5();
};

// ?<Rva00431FB5::Rva00431FB5> absent-from-retail
Rva00431FB5::Rva00431FB5(EmitVtableTag *)
{
}

class Rva00435DE7
{
public:
	Rva00435DE7(EmitVtableTag *);
public:
	virtual ~Rva00435DE7();
};

// ?<Rva00435DE7::Rva00435DE7> absent-from-retail
Rva00435DE7::Rva00435DE7(EmitVtableTag *)
{
}

class Rva00355D66
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
};

class Rva0043A351 : public Rva00355D66
{
public:
	Rva0043A351(EmitVtableTag *);
public:
	virtual ~Rva0043A351();
};

// ?<Rva0043A351::Rva0043A351> absent-from-retail
Rva0043A351::Rva0043A351(EmitVtableTag *)
{
}

class Rva0043A396
{
public:
	Rva0043A396(EmitVtableTag *);
public:
	virtual ~Rva0043A396();
};

// ?<Rva0043A396::Rva0043A396> absent-from-retail
Rva0043A396::Rva0043A396(EmitVtableTag *)
{
}

// Target facts: Rva0043B660 constructs a member at +4 through the rowed
// set constructor 0x0043B69C and destroys it through
// 0x0043B4B4. The set element spelling/layout is carried from the verified
// STLport transfer and remains donor inference.
struct Rva0043B69CElement {
	Rva0043B69CElement();
	Rva0043B69CElement(const Rva0043B69CElement &);
	~Rva0043B69CElement();
	Rva0043B69CElement &operator=(const Rva0043B69CElement &);
	char bytes[8];
};
bool operator<(const Rva0043B69CElement &, const Rva0043B69CElement &);

class Rva0043B4B4
{
public:
	~Rva0043B4B4();
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
	Rva0043B4B4 m_member04;
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

class Rva0043D1C9
{
public:
	Rva0043D1C9(EmitVtableTag *);
public:
	virtual ~Rva0043D1C9();
};

// ?<Rva0043D1C9::Rva0043D1C9> absent-from-retail
Rva0043D1C9::Rva0043D1C9(EmitVtableTag *)
{
}

class Rva0052163E
{
public:
	Rva0052163E(EmitVtableTag *);
public:
	virtual ~Rva0052163E();
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
