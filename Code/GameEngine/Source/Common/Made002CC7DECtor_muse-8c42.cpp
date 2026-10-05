// cl: /O1 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??0Made002CC7DE@@QAE@XZ @0x0050968B 32B
// Derived of Rva00507823 base 0x0050775B (vtable 0x00864010) overwrites vtable 0x00864588
// zeroes +0x12C then +0x128. Caller parseWeaponOCLNugget 0x002CC803. Sibling Made002CC5E1
// (DamageNugget 0x00507C2D) proves base size 0x128 and derived layout.
// The implicit dtor 0x005096C7 (emitted with the vtable, so no vptr store)
// tears +0x12C down through the AsciiString dtor 0x00036410 before the base
// dtor 0x00507823, which is what makes +0x12C a string; it is zeroed by its
// own default ctor first and +0x128 by the body after. Slot 0 is ??_G 0x005096AB.
#include "ascii_string.h"

class Rva00507823
{
public:
	Rva00507823();
	virtual ~Rva00507823();
private:
	unsigned char m_pad[0x128 - 4];
};

class Made002CC7DE : public Rva00507823
{
public:
	Made002CC7DE();
private:
	const void *m_128; // +0x128
	AsciiString m_12C; // +0x12C
};

Made002CC7DE::Made002CC7DE()
{
	m_128 = 0;
}
