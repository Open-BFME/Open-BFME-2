// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva005092B2@Rva005092B2@@QAEXXZ @0x005092B2 34B: resolve helper over base
// Rva00507823 slot 8 plus WeaponStore findWeaponTemplate by +0x130 name into
// +0x128 slot. No callers rowed; address sits between Made002CC711Ctor and
// Made002CC774Parse.

#include "ascii_string.h"


class WeaponTemplate
{
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
};

extern WeaponStore *TheWeaponStore;

class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
	virtual void rva00507877();

private:
	char m_pad[0x128 - 4];
};

class Rva005092B2 : public Rva00507823
{
public:
	void rva005092B2();

private:
	const WeaponTemplate *m_128;
	char m_pad12C[4];
	AsciiString m_130;
};

void Rva005092B2::rva005092B2()
{
	Rva00507823::rva00507877();
	m_128 = TheWeaponStore->findWeaponTemplate(m_130);
}
