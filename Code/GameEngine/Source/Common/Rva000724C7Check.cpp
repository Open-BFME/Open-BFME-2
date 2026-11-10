// cl: /MD
// ?rva000724C7@Rva000724AE@@QAEHXZ, RVA 0x000724C7, 16B. Non-null check on
// +0x08/+0x0c pointers: returns 1 if either is non-null else 0. Evidence:
// sits between 0x000724AE and 0x000724D7 of the same class Rva000724AE,
// same // cl: /O1 /MD; caller at 0x0007256B.
#include "../../Include/Common/Rva000724AE.h"
bool Rva000724AE::rva000724C7()
{
	return m_08 != 0 || m_0c != 0;
}

// ?rva00072566@Rva00072566@@UAE_NXZ, RVA 0x00072566, 29B: virtual check that
// every entry of the one-element 0x14-byte array at +0x2C passes rva000724C7.
// Retail keeps ECX/EDX live across the call because the callee above is
// visible in this unit (cl knows it clobbers only EAX). Names address-derived.
class Rva00072566
{
public:
	virtual bool rva00072566();
private:
	char m_pad04[0x2C - 4];
	Rva000724AE m_entries[1];	// +0x2C
};
bool Rva00072566::rva00072566()
{
	for (int i = 0; i < 1; ++i)
		if (!m_entries[i].rva000724C7())
			return false;
	return true;
}
