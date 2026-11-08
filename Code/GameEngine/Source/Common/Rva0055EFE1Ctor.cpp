// cl: /EHs-c-
// ??0Rva0055EFE1@@QAE@I@Z, retail 0x0055EFE1, 31 bytes.
//
// Derived of Rva00563FE1 (rowed 0x00563FE1 in T4VtableSetCtors.cpp) taking the
// same int: placement-constructs the base then re-stamps the same two vftables
// (+0x00 0x00C1D2C0, +0x08 0x00C1C780). Callers at 0x003A59D7 and 0x0055F22D.
// The class keeps an address-derived name; the tables use address-named
// aliases like the base. Base is opaque here so the call never inlines.

#include <new.h>

// Address-named alias: retail RVA 0x0081C780 is one __purecall slot.
// The emitted donor table is independently checked as four bytes with
// one __purecall relocation, whose matched body is at RVA 0x0003B810.
// This establishes table contents; it assigns no donor class to the caller.
extern "C" const void *const __identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")[];

extern "C" const void *const __identifier("??_7Rva005EA430@@6BV3Vt01111D90@@@")[];  // vftable 0x00C1D2C0

class Rva00563FE1
{
public:
	Rva00563FE1( unsigned int a );
};

class Rva0055EFE1
{
public:
	Rva0055EFE1( unsigned int a );
private:
	unsigned char m_storage[ 0x0c ];
};

Rva0055EFE1::Rva0055EFE1( unsigned int a )
{
	__assume( this != 0 );
	new( this ) Rva00563FE1( a );
	volatile unsigned int *slots = (unsigned int *)this;
	slots[ 0 ] = ((unsigned int)__identifier("??_7Rva005EA430@@6BV3Vt01111D90@@@"));
	slots[ 2 ] = ((unsigned int)__identifier("??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@"));
}
