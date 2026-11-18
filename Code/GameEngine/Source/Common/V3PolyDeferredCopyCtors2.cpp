// cl: /DNDEBUG /MD /EHsc
// Copy constructors split from V3PolyDeferredCopyCtors.cpp. Neither class has a
// virtual destructor: each copy ctor installs a one-slot retail vftable whose
// slot is the record's transfer method, not a deleting destructor (target
// facts). 0x0028C62B stores 0x007F91FC, the table the default ctor 0x00263653
// stores (slot 0x004D6FC4), so both are Rva00263653's. 0x0028F68F stores
// 0x007F9200, the table the default ctor 0x00263895 stores (slot 0x004D6F86),
// so both are Rva00263895Member's. Its +0x04 member is the 0x0028C62B class
// and its +0x6C member the 0x0028C6D6 class, which matches the default ctor's
// layout.

#include "../../Include/Common/ScalarTypes.h"

#include "../../Include/Common/Rva0028C6D6.h"

// ----------------- vptr + twenty-three ints + three bytes (retail 0x0028C62B)
// B2 body-address name: seven dwords +0x04..+0x1C then bytes +0x20/+0x21 then
// ten dwords +0x24..+0x48 then byte +0x4C then six dwords +0x50..+0x64.
// Sits directly before 0x0028C6D6 and the retail caller 0x0028F6A4 builds
// both subobjects in one tail.
class Rva00263653
{
public:
	Rva00263653(const Rva00263653 &other);
	virtual void rva004D6FC4(void *context);

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	char m_field20;
	char m_field21;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
	Int m_field38;
	Int m_field3C;
	Int m_field40;
	Int m_field44;
	Int m_field48;
	char m_field4C;
	Int m_field50;
	Int m_field54;
	Int m_field58;
	Int m_field5C;
	Int m_field60;
	Int m_field64;
};

Rva00263653::Rva00263653(const Rva00263653 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field21 = other.m_field21;
	m_field24 = other.m_field24;
	m_field28 = other.m_field28;
	m_field2C = other.m_field2C;
	m_field30 = other.m_field30;
	m_field34 = other.m_field34;
	m_field38 = other.m_field38;
	m_field3C = other.m_field3C;
	m_field40 = other.m_field40;
	m_field44 = other.m_field44;
	m_field48 = other.m_field48;
	m_field4C = other.m_field4C;
	m_field50 = other.m_field50;
	m_field54 = other.m_field54;
	m_field58 = other.m_field58;
	m_field5C = other.m_field5C;
	m_field60 = other.m_field60;
	m_field64 = other.m_field64;
}

// ---- vptr + two member subobject copies (retail 0x0028F68F)
// B2 body-address name: member at +0x04 copies with the rowed 171B body and
// member at +0x6C with the rowed 33B body. Both member copies are pure
// stores, so the compiler proves nothrow and stays frameless with two
// outlined calls, exactly like retail. (The E8 sites sit 21/33 bytes in;
// the row names the C9-C3 boundary, not the call sites.)
class Rva00263895Member
{
public:
	Rva00263895Member(const Rva00263895Member &other);
	virtual void rva004D6F86(void *arg);

	Rva00263653 m_member04;
	Rva0028C6D6 m_member6C;
};

Rva00263895Member::Rva00263895Member(const Rva00263895Member &other)
	: m_member04(other.m_member04)
	, m_member6C(other.m_member6C)
{
}
