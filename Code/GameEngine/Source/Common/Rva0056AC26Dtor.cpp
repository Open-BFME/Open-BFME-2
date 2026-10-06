// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ??1Rva0056AC26@@UAE@XZ, retail 0x0056AC26 (84B): destructor of the opaque
// base several BFME 2 registry entries derive from (Rva0056AC26Derived.cpp,
// Rva0056B218Dtor.cpp, ...). Layout from this body: two polymorphic bases,
// the first (vftable 0x00BC6F20) with a word at +4 and the second (vftable
// 0x00C37298) at +8, a UnicodeString at +0xC and the owning registry at
// +0x10. Retail stores this class's vftables (0x00C6D058 / 0x00C6D01C), asks
// the owner to forget it (0x003F88A7, pinned), releases the string, and the
// inline base destructors restore their vftables. Names stay address-derived.

#include "unicode_string.h"

class Rva0056AC26;

class Rva0056AC26Owner
{
public:
	void rva003F88A7(Rva0056AC26 *entry);
};

class Rva0056AC26Base1
{
public:
	virtual ~Rva0056AC26Base1() {}

private:
	int m_04;
};

class Rva0056AC26Base2
{
public:
	virtual ~Rva0056AC26Base2() {}
};

class Rva0056AC26 : public Rva0056AC26Base1, public Rva0056AC26Base2
{
public:
	virtual ~Rva0056AC26();

private:
	UnicodeString m_text;        // +0x0C
	Rva0056AC26Owner *m_owner;   // +0x10
};

Rva0056AC26::~Rva0056AC26()
{
	m_owner->rva003F88A7(this);
}
