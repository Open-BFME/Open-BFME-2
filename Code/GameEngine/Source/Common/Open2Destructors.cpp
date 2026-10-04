// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// Record destructors.  A record destructor's only visible work is
// destroying the members that HAVE a destructor, in reverse declaration order,
// so each class below carries only the AsciiStrings and the gaps between them
// -- that is all these bytes attest to, and inventing the rest would be
// inventing identity.
//
// The unwind state counts down alongside the calls (2, 1, 0, then -1), which
// is the same evidence: one destructible subobject per state.
//
// StringBase's destructor is private in the real header and the ledger holds
// the private mangling at 0x00887940, so it is spelled private here with
// AsciiString as its friend.

// A gap is layout, not data: it has no destructor, so it contributes nothing.
template <int N>
class Open2Gap
{
public:
	char m_bytes[ N ];
};

#include "string_base.h"

#include "ascii_string.h"

// -------------------------------------------------------------------------
// 0x0005F4B0 -- 103 bytes, 4 string member(s)
class Open2Dtor05F4B0
{
public:
	~Open2Dtor05F4B0();
	Open2Gap< 0x10 > m_pad0;
	AsciiString m_at10;
	AsciiString m_at14;
	AsciiString m_at18;
	AsciiString m_at1c;
};

// @??1Open2Dtor05F4B0@@QAE@XZ 0x0005F4B0
// ??1Open2Dtor05F4B0@@QAE@XZ present-unmatched
Open2Dtor05F4B0::~Open2Dtor05F4B0()
{
}

// -------------------------------------------------------------------------
// 0x0013A8E0 -- 180 bytes, 10 string member(s)
class Open2Dtor13A8E0
{
public:
	~Open2Dtor13A8E0();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	AsciiString m_at10;
	Open2Gap< 0x8 > m_pad0;
	AsciiString m_at1c;
	AsciiString m_at20;
	Open2Gap< 0x4 > m_pad1;
	AsciiString m_at28;
	Open2Gap< 0x10 > m_pad2;
	AsciiString m_at3c;
	Open2Gap< 0x4 > m_pad3;
	AsciiString m_at44;
};

// @??1Open2Dtor13A8E0@@QAE@XZ 0x0013A8E0
// ??1Open2Dtor13A8E0@@QAE@XZ present-unmatched
Open2Dtor13A8E0::~Open2Dtor13A8E0()
{
}

// -------------------------------------------------------------------------
// 0x0040B830 -- 118 bytes, 5 string member(s); BFME2 target layout places
// the final string at +0x94 (the target default-record constructor copies it
// from the global default block at base+0x94).
class Open2Dtor40B830
{
public:
	~Open2Dtor40B830();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	Open2Gap< 0x8 > m_pad0;
	AsciiString m_at14;
	Open2Gap< 0x7c > m_pad1;
	AsciiString m_at94;
};

// @??1Open2Dtor40B830@@QAE@XZ 0x0040B830
Open2Dtor40B830::~Open2Dtor40B830()
{
}

// -------------------------------------------------------------------------
// 0x004793C0 -- 102 bytes, 4 string member(s)
class Open2Dtor4793C0
{
public:
	~Open2Dtor4793C0();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
};

// @??1Open2Dtor4793C0@@QAE@XZ 0x004793C0
Open2Dtor4793C0::~Open2Dtor4793C0()
{
}

// -------------------------------------------------------------------------
// 0x005A7D90 -- 102 bytes, 4 string member(s)
class Open2Dtor5A7D90
{
public:
	~Open2Dtor5A7D90();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
};

// @??1Open2Dtor5A7D90@@QAE@XZ 0x005A7D90
// ??1Open2Dtor5A7D90@@QAE@XZ present-unmatched
Open2Dtor5A7D90::~Open2Dtor5A7D90()
{
}

// -------------------------------------------------------------------------
// 0x0069CF00 -- 141 bytes, 7 string member(s)
class Open2Dtor69CF00
{
public:
	~Open2Dtor69CF00();
	AsciiString m_at00;
	AsciiString m_at04;
	AsciiString m_at08;
	AsciiString m_at0c;
	AsciiString m_at10;
	AsciiString m_at14;
	Open2Gap< 0x5c > m_pad0;
	AsciiString m_at74;
};

// @??1Open2Dtor69CF00@@QAE@XZ 0x0069CF00
// ??1Open2Dtor69CF00@@QAE@XZ present-unmatched
Open2Dtor69CF00::~Open2Dtor69CF00()
{
}

// 0x002E096A..0x002E0A0A -- target-only layout, not the drift queue's
// Open2Dtor69CF00 identity. Eight calls to narrow releaseBuffer at 0x36410
// and two null-guarded calls to OpaqueRefCounted::Release_Ref at 0x50ED3
// accompany ten member cleanup states. The original record name is unknown.
// This referent declaration agrees with OpaqueRefOwnership.cpp.
class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();
	void Add_Ref();
	void Release_Ref();
private:
	long refs;
};

class Open2OwnedReference
{
public:
	__forceinline ~Open2OwnedReference()
	{
		if (referent)
			referent->Release_Ref();
	}
private:
	OpaqueRefCounted *referent;
};

class Rva002E096A
{
public:
	~Rva002E096A();
private:
	AsciiString m_at00;
	AsciiString m_at04;
	Open2Gap<0x18> m_pad08;
	AsciiString m_at20;
	AsciiString m_at24;
	AsciiString m_at28;
	AsciiString m_at2c;
	AsciiString m_at30;
	AsciiString m_at34;
	Open2OwnedReference m_at38;
	Open2OwnedReference m_at3c;
};

Rva002E096A::~Rva002E096A()
{
}
