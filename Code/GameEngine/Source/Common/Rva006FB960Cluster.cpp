// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Four Apt-neighbourhood bodies around 0x006FB960..0x006FC130, in the
// BfmePicker1284.cpp page of Code/GameEngine/Source/Common.
//
// 0x006FB960 / 0x006FB9C0 (29B): constructors of two BfmeAptValue006DCD20
//   subclasses.  Each calls the rowed base ctor 0x006DCCC0 with its folded type
//   constant (4 and 8), stores the int argument at +8 and installs its own
//   vtable (0x00CED808 / 0x00CED844, masked DIR32).
// 0x006FBBE0 (43B): linked-list lookup; walks +0x1C next pointers and calls the
//   rowed hash lookup ?lookup@Rva0070B380 0x0070B380 on the embedded table at +8.
//   The sibling 0x006FBE80, which wraps this over a global plus a +0x28 list,
//   is banked as a 60/66 partial (see reverse/re_attempts.log).
// 0x006FC130 (95B): subclass ctor built on a private Rva006FC130Base view of
//   Rva006D6360 (vtable 0x00CEA228; base type 0x1E,
//   AptNativeHash at +8 sized 8) plus a non-polymorphic bits base at +0x1C,
//   then its own vtable.  The EH frame comes from the AptNativeHash member's
//   destructor being in scope while the base ctor runs.
//
// Class identities beyond the rowed base/tab callees are unproven; the classes
// are address-named after their body RVAs.

// The real AptValue: retail's base vtable 0x00CEAED0 (and the unchanged copies
// 0x00CED808 / 0x00CED844 the two small subclasses install) holds the rowed
// AddRef (0x006DCAC0), Release (0x006DCB20) and ForceDelete (0x006CBCD0) in
// slots 0-2.
class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	virtual void ForceDelete();
};

class BfmeAptValue006DCD20 : public AptValue
{
public:
	BfmeAptValue006DCD20(int type);
	virtual ~BfmeAptValue006DCD20();
	unsigned int m_flags;
};

class Rva006FB960 : public BfmeAptValue006DCD20
{
public:
	Rva006FB960(int value);

private:
	int m_value;	// +0x08
};

Rva006FB960::Rva006FB960(int value) : BfmeAptValue006DCD20(4)
{
	m_value = value;
}

class Rva006FB9C0 : public BfmeAptValue006DCD20
{
public:
	Rva006FB9C0(int value);

private:
	int m_value;	// +0x08
};

Rva006FB9C0::Rva006FB9C0(int value) : BfmeAptValue006DCD20(8)
{
	m_value = value;
}

class BfmeN1034;
class EAStringC;

// The rowed hash lookup 0x0070B380 (?lookup@Rva0070B380); the key is passed
// as the reference it takes.
class Rva0070B380
{
public:
	void *lookup(const EAStringC &key);

private:
	char m_pad[0x14];	// embedded table occupies +0x08..+0x1B
};

struct Rva006FBBE0
{
	BfmeN1034 *find(int key);

	char m_pad00[8];
	Rva0070B380 m_table;		// +0x08
	Rva006FBBE0 *m_next;		// +0x1C
};

BfmeN1034 *Rva006FBBE0::find(int key)
{
	Rva006FBBE0 *node = this;
	while (node != 0) {
		BfmeN1034 *found = (BfmeN1034 *)node->m_table.lookup(*(const EAStringC *)key);
		if (found != 0)
			return found;
		node = node->m_next;
	}
	return 0;
}

#include "../../../Libraries/Source/Apt/AptNativeHash.h"

class Rva006FC130Base : public BfmeAptValue006DCD20
{
public:
	AptNativeHash m_hash;	// 0x14 bytes, so the bits base lands at +0x1C

	__declspec(dllimport) __forceinline Rva006FC130Base(int type, int size) : BfmeAptValue006DCD20(type), m_hash(size) {}
	virtual ~Rva006FC130Base() {}
};

class Rva006DBits
{
protected:
	unsigned int m_bits;

public:
	Rva006DBits()
	{
		*(unsigned char *)&m_bits = 0;
		m_bits &= 0xFFFFFCFF;
	}
};

class Rva006FC130 : public Rva006FC130Base, public Rva006DBits
{
public:
	Rva006FC130();
};

Rva006FC130::Rva006FC130() : Rva006FC130Base(0x1e, 8), Rva006DBits()
{
}

// WB175E910 calls the same scope lookup on a global first, then this+28.
// PC inlines only the global path. Donor+2C is not the native member layout.
class AptFrameStack;
// The global is VA 0x00E1835C, AptScriptFunctionBase::spFrameStack, which
// AptScriptFunction.cpp defines and the interpreter sets (Rva006FBED0Cluster.cpp
// declares it the same way).
extern "C" AptFrameStack *__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A");
struct Rva006FBE80 {
 BfmeN1034 *find2(int);
 char padding[0x28];
 Rva006FBBE0 *scope;
};
BfmeN1034 *Rva006FBE80::find2(int key) {
 if(!__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A")) return scope ? scope->find(key) : 0;
 return ((Rva006FBBE0 *)__identifier("?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A"))->find(key);
}
