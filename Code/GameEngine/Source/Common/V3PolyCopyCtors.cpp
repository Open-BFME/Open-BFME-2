// cl: /DNDEBUG /MD /EHsc
// Complete-lifetime copy/holder owners. Deferred lifetime views remain in
// V3PolyDeferredCopyCtors.cpp; function bodies and class layouts are unchanged.

typedef int Int;
typedef short Short;

// ----------------------------------- vptr + two ints (retail 0x003AE11B)
// B2 body-address name: no B1 class has exactly this shape.
class Rva003AE11B
{
public:
	Rva003AE11B(const Rva003AE11B &other);
	virtual ~Rva003AE11B();

	Int m_field04;
	Int m_field08;
};

Rva003AE11B::Rva003AE11B(const Rva003AE11B &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
}

// ------------------------- vptr + one int (retail 0x004AB7EB)
// B2 body-address name: same 21-byte shape as 0x003AE07D with a different
// vtable so a different class. Retail caller 0x004ABB0A re-installs this
// same vptr right after the call.
class Rva004AB7EB
{
public:
	Rva004AB7EB(const Rva004AB7EB &other);
	virtual ~Rva004AB7EB();

	Int m_field04;
};

Rva004AB7EB::Rva004AB7EB(const Rva004AB7EB &other)
{
	m_field04 = other.m_field04;
}

// ------------------------- vptr + one int (retail 0x004C9F61)
// B2 body-address name: same 21-byte shape with a different vtable so a
// different class. Retail caller 0x004C9FC8 installs derived vptr 0xC07E54
// right after the call so this is the base-class copy.
class Rva004C9F61
{
public:
	Rva004C9F61(const Rva004C9F61 &other);
	virtual ~Rva004C9F61();

	Int m_field04;
};

Rva004C9F61::Rva004C9F61(const Rva004C9F61 &other)
{
	m_field04 = other.m_field04;
}

// -------------------- vptr + two scalar words + a byte (retail 0x0028C6D6)
// B2 body-address name: same 33-byte shape as 0x003AE315 with a different
// vtable so a different class. Retail caller 0x0028F6B0 is itself a ret-4
// copy-ctor tail so this is the base-class copy.
// The shared header also covers the default constructor at 0x00262093 and
// the real virtual transfer slot at 0x004D70D5. These stores cannot throw.
#include "../../Include/Common/Rva0028C6D6.h"

Rva0028C6D6::Rva0028C6D6(const Rva0028C6D6 &other) throw()
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
}

// -------------------- vptr + one int + two bytes (retail 0x003ADE98)
// B2 body-address name: +0x08 and +0x09 are byte members (8A51/8850 and
// 8A49/8848). Retail caller 0x003ADE78 installs adjacent-vtable parts
// after the call so this is the subobject copy.
// Its destructor is inline and empty: the deleting dtor 0x004A10FD in the
// vtable 0x00C1D1F4 stored below calls 0x0049B47C, the shared one-store dtor
// that only restores the Snapshot vtable 0x00BBB554, which is also all the
// derived destructor 0x003ADFB2 does for this base. The Snapshot base itself is
// not modelled in this view.
class Rva003ADE98
{
public:
	Rva003ADE98(const Rva003ADE98 &other);
	virtual ~Rva003ADE98() {}

	Int m_field04;
	char m_field08;
	char m_field09;
};

Rva003ADE98::Rva003ADE98(const Rva003ADE98 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field09 = other.m_field09;
}

// ------------------------------------------ vptr + ten ints (retail 0x003ADF61)
// B2 body-address name: straight ten-dword run +0x04..+0x28. Four retail
// E8 callers all sit in 0x003AE1xx copy tails. Its destructor is inline and
// empty: the deleting dtor 0x004A10FD in its vtable 0x00C1D264 calls
// 0x0049B47C, which only restores the Snapshot vtable 0x00BBB554.
class Rva003ADF61
{
public:
	Rva003ADF61(const Rva003ADF61 &other);
	virtual ~Rva003ADF61() {}

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
};

Rva003ADF61::Rva003ADF61(const Rva003ADF61 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field24 = other.m_field24;
	m_field28 = other.m_field28;
}

// ------------------------------------------ vptr + ten ints (retail 0x004F5FD8)
// B2 body-address name: same ten-dword run as 0x003ADF61 with a different
// vtable so a different class. Two retail E8 callers.
class Rva004F5FD8
{
public:
	Rva004F5FD8(const Rva004F5FD8 &other);
	virtual ~Rva004F5FD8() {}

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
};

Rva004F5FD8::Rva004F5FD8(const Rva004F5FD8 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field24 = other.m_field24;
	m_field28 = other.m_field28;
}

// ------------------------------------------- vptr + six ints (retail 0x0020E449)
// B2 body-address name: straight six-dword run +0x04..+0x18. Two retail E8
// callers at 0x0020F399 and 0x004FF2B4.
class Rva0020E449
{
public:
	Rva0020E449(const Rva0020E449 &other);
	virtual ~Rva0020E449();

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
};

Rva0020E449::Rva0020E449(const Rva0020E449 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
}

// PerTurnStats's copy constructor (retail 0x004EE1A9) is the implicit one
// LivingWorldScoreKeeper.cpp emits.

// -------------------------- vptr + two words (retail 0x005DBCD1)
// B2 body-address name: two word members at +0x04/+0x06 with 66-prefix
// moves. Five retail E8 callers.
class Rva005DBCD1
{
public:
	Rva005DBCD1(const Rva005DBCD1 &other);
	virtual ~Rva005DBCD1() {}

	Short m_field04;
	Short m_field06;
};

Rva005DBCD1::Rva005DBCD1(const Rva005DBCD1 &other)
{
	m_field04 = other.m_field04;
	m_field06 = other.m_field06;
}

// --------------------- vptr + two ints + three words (retail 0x0039B893)
// B2 body-address name: dwords at +0x04/+0x08 then words at +0x0C/+0x0E/+0x10
// with 66-prefix moves. Six retail E8 callers.
class Rva0039B893
{
public:
	Rva0039B893(const Rva0039B893 &other);
	Rva0039B893 &operator=(const Rva0039B893 &other);
	virtual ~Rva0039B893();

	Int m_field04;
	Int m_field08;
	Short m_field0C;
	Short m_field0E;
	Short m_field10;
};

Rva0039B893::Rva0039B893(const Rva0039B893 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field0E = other.m_field0E;
	m_field10 = other.m_field10;
}

// --------------------- vptr-skip assign of same layout (retail 0x0039B900)
// ??4Rva0039B893@@QAEAAV0@ABV0@@Z @0x0039B900 45B: same two ints plus three
// words as the 0x0039B893 copy ctor above with no vptr store (6B smaller).
// Evidence: three callers 0x0039B92D/0x0039BA68/0x0039BAA0 looping with 0x14
// stride; class identity from the shared copy-ctor layout.
Rva0039B893 &Rva0039B893::operator=(const Rva0039B893 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field0E = other.m_field0E;
	m_field10 = other.m_field10;
	return *this;
}

// ------------------------- vptr + held pointer (retail 0x00575383)
// B2 body-address name: same holder shape as 0x005CB22A with a different
// vtable so a different class. Three retail E8 callers.
#include "../../Include/Common/Rva00575383.h"

Rva00575383::Rva00575383(void *held)
{
	m_field04 = held;
}

// ------------------------- vptr + held pointer (retail 0x005D6FCC)
// B2 body-address name: same holder shape with a different vtable so a
// different class. Four retail E8 callers.
class Rva005D6FCC
{
public:
	Rva005D6FCC(void *held);
	virtual ~Rva005D6FCC() {}

	void *m_field04;
};

Rva005D6FCC::Rva005D6FCC(void *held)
{
	m_field04 = held;
}

// ------------------------- vptr + held pointer (retail 0x005DAA36)
// B2 body-address name: same holder shape with a different vtable so a
// different class. Three retail E8 callers.
#include "../../Include/Common/Rva005DAA36.h"

Rva005DAA36::Rva005DAA36(void *held)
{
	m_field04 = held;
}

// ------------------------- vptr + held pointer (retail 0x005E67FE)
// B2 body-address name: same holder shape with a different vtable so a
// different class. Four retail E8 callers.
class Rva005E67FE
{
public:
	Rva005E67FE(void *held);
	virtual ~Rva005E67FE();

	void *m_field04;
};

Rva005E67FE::Rva005E67FE(void *held)
{
	m_field04 = held;
}

// Native5E6810 resets only this holder base vptr. Canonical provider for
// the owning wrapper cleanups; rehomes the old integer-setter row (zero gain).
Rva005E67FE::~Rva005E67FE() {}

// ----------------- vptr + converted int from +0x74 (retail 0x005DCC4B)
// B2 body-address name: the single member takes arg+0x74, not arg+0x04, so
// this converts from a larger source whose only observed member is the int
// at +0x74. The source layout is inferred from that one load. Retail caller
// 0x005AD6CA passes the source pointer by value then installs its own vptr.
#include "../../Include/Common/Rva005DCC4BSource.h"

class Rva005DCC4B
{
public:
	Rva005DCC4B(const Rva005DCC4BSource *source);
	virtual ~Rva005DCC4B();

	Int m_field04;
};

Rva005DCC4B::Rva005DCC4B(const Rva005DCC4BSource *source)
{
	m_field04 = source->m_field74;
}

// Empty virtual destructor: restores this vtable (0x00C1C780, the one the
// constructor installs) and returns; retail ICF-folds it into 0x005FED52 with
// every other vptr-only destructor. AINavyUnitBattleShip's destructor
// 0x005AD6EA tail-calls it.
Rva005DCC4B::~Rva005DCC4B()
{
}

