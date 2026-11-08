// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B17: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Owner identities are not recovered, and these declarations model no layout
// beyond the thunk-proven secondary base at +0x8 noted at Rva005E12D1 below
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x005E3677  0x005E362F  0x00C77BD0#0
//   0x005E5A66  0x00576FCE  0x00C6E3E8#0, 0x00C6E620#0, 0x00C6E8A8#0, 0x00C77D90#0
//   0x005E67E2  0x005E66A4  0x00C77E04#0
//   Rva005E80FD wrapper rehomed to its real lifetime unit.
//   0x005E8E64  0x005E8D71  0x00C77F88#0
//   Rva005E91A9 wrappers rehomed to their complete lifetime unit.
//   0x005E9F4D  0x005E9F3F  0x00C780A8#0
//   0x005EA68B  0x005E9F7B  0x00C75374#0, 0x00C77AD8#0, 0x00C781B8#0
//   0x005EA83E  0x005EA85A  0x00C781DC#0
//   0x005EB761  0x005EB753  0x00C7823C#0
//   0x005EE0D8  0x005EE05E  0x00C786A8#0
//   0x005F02C4  0x005F00FB  0x00C78A78#0
//   0x005F1757  0x005F1749  0x00C78EFC#0
//   0x005F41B7  0x005F4179  0x00C79448#0
//   0x005F4ECC  0x005F4EE8  0x00C794E4#0
//   0x005F5678  0x005F566A  0x00C7953C#0

struct EmitVtableTag;

class Rva005E362F
{
public:
	Rva005E362F(EmitVtableTag *);
public:
	virtual ~Rva005E362F();
};

// ?<Rva005E362F::Rva005E362F> absent-from-retail
Rva005E362F::Rva005E362F(EmitVtableTag *)
{
}

class Rva00576FCE
{
public:
	Rva00576FCE(EmitVtableTag *);
public:
	virtual ~Rva00576FCE();
};

// ?<Rva00576FCE::Rva00576FCE> absent-from-retail
Rva00576FCE::Rva00576FCE(EmitVtableTag *)
{
}

// Rva005E80FD now emits its deleting wrapper from its real MI lifetime unit.

// The secondary base at +0x8 of the five classes below: slot 0 of each
// class's ??_7...@@6BRva005E12D1@@@ table is a this-adjusting (sub ecx, 8)
// deleting-destructor thunk, target evidence for that base and offset.
class Rva005E12D1 { public: virtual ~Rva005E12D1(); };

// Primary base at +0 (vptr plus one word), named as its ??_7Rva005E8D71@@6BRva005E8D71Base@@@ table.
class Rva005E8D71Base { public: virtual ~Rva005E8D71Base() {} private: char m_unmodelled04[4]; };
class Rva005E8D71 : public Rva005E8D71Base, public Rva005E12D1
{
public:
	Rva005E8D71(EmitVtableTag *);
public:
	virtual ~Rva005E8D71();
};

// ?<Rva005E8D71::Rva005E8D71> absent-from-retail
Rva005E8D71::Rva005E8D71(EmitVtableTag *)
{
}

// Rva005E91A9 emits its native deleting wrapper and adjusting thunk
// from the complete lifetime unit Rva005E91A9Dtor.cpp.

class Rva005E9F3F
{
public:
	Rva005E9F3F(EmitVtableTag *);
public:
	virtual ~Rva005E9F3F();
	virtual void event1() = 0;
	virtual void event2() = 0;
	virtual void event3() = 0;
	virtual void event4() = 0;
};

// ?<Rva005E9F3F::Rva005E9F3F> absent-from-retail
Rva005E9F3F::Rva005E9F3F(EmitVtableTag *)
{
}

class Rva005E9F7B
{
public:
	Rva005E9F7B(EmitVtableTag *);
public:
	virtual ~Rva005E9F7B();
};

// ?<Rva005E9F7B::Rva005E9F7B> absent-from-retail
Rva005E9F7B::Rva005E9F7B(EmitVtableTag *)
{
}

// Rva005EA85A's stub and deleting-dtor row live in Rva005EA85ACtor.cpp (full
// 9-virtual view matching retail vftable 0x00C781DC slots 0-7); the duplicate
// stub here LNK2005-collided with it, so the class view and stub are removed
// from this TU, leaving a single vftable emitter tree-wide.

class Rva005EB753
{
public:
	Rva005EB753(EmitVtableTag *);
public:
	virtual ~Rva005EB753();
};

// ?<Rva005EB753::Rva005EB753> absent-from-retail
Rva005EB753::Rva005EB753(EmitVtableTag *)
{
}

class Rva005EE05E
{
public:
	Rva005EE05E(EmitVtableTag *);
public:
	virtual ~Rva005EE05E();
};

// ?<Rva005EE05E::Rva005EE05E> absent-from-retail
Rva005EE05E::Rva005EE05E(EmitVtableTag *)
{
}

class INI;

class MappedImageCache
{
public:
	MappedImageCache(EmitVtableTag *);
public:
	virtual ~MappedImageCache();
	virtual void rva005EFFA6(INI *ini);
};

// ?<MappedImageCache::MappedImageCache> absent-from-retail
MappedImageCache::MappedImageCache(EmitVtableTag *)
{
}

namespace StrategicHUD {
class RegionDetailsStructuresMovieClip
{
public:
 RegionDetailsStructuresMovieClip(EmitVtableTag *);
 virtual ~RegionDetailsStructuresMovieClip();
};
}

// ?<StrategicHUD::RegionDetailsStructuresMovieClip::RegionDetailsStructuresMovieClip> absent-from-retail
StrategicHUD::RegionDetailsStructuresMovieClip::RegionDetailsStructuresMovieClip(EmitVtableTag *)
{
}

class Rva005F4179
{
public:
	Rva005F4179(EmitVtableTag *);
public:
	virtual ~Rva005F4179();
};

// ?<Rva005F4179::Rva005F4179> absent-from-retail
Rva005F4179::Rva005F4179(EmitVtableTag *)
{
}

class Rva005F4EE8
{
public:
	Rva005F4EE8(EmitVtableTag *);
public:
	virtual ~Rva005F4EE8();
	virtual void notifyClosed();	// slot 1, rowed in Rva005F4DC4Create.cpp (0x005F4B48)
};

// ?<Rva005F4EE8::Rva005F4EE8> absent-from-retail
Rva005F4EE8::Rva005F4EE8(EmitVtableTag *)
{
}

class Rva005F566A
{
public:
	Rva005F566A(EmitVtableTag *);
public:
	virtual ~Rva005F566A();
};

// ?<Rva005F566A::Rva005F566A> absent-from-retail
Rva005F566A::Rva005F566A(EmitVtableTag *)
{
}

// The native Rva005F5819 / Rva005F5BF2 / Rva005F5EA6 deleting wrappers
// and -8 adjusting thunks are now emitted by their complete destructor
// units. Their synthetic partial views conflicted with the real base
// destructor definitions and are removed.
