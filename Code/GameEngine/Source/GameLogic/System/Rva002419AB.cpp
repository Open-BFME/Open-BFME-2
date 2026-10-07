// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

#include "ascii_string.h"

// This 16-byte object is allocated by the target at 0x00240D8C. Its helper
// initializes a vtable-like word at +0 and an AsciiString at +8; the object
// identity is unresolved, so the type and constructor name use the helper RVA.
class Rva0023FC98
{
private:
	void *m_vtable;

public:
	Rva0023FC98(const AsciiString *value);
	int m_referenceCount;

private:
	char m_unknown_08[8];
};

class Rva002419ABOwner
{
private:
	Rva0023FC98 *m_value;

public:
	void *rva00240D8C(const AsciiString *value);
	void *rva002419AB(AsciiString value, int option);
};

// ?rva00240D8C@Rva002419ABOwner@@QAEPAXPBVAsciiString@@@Z @ 0x00240D8C (73B):
// Ghidra boundary; caller 0x002419AB passes its local AsciiString by address.
// Retail allocates 16 bytes, initializes the object through 0x0023FC98, stores
// the pointer at this+0, increments its +4 count, and returns this. The object
// and operation remain address-derived.
void *Rva002419ABOwner::rva00240D8C(const AsciiString *value)
{
	m_value = new Rva0023FC98(value);
	if (m_value != 0)
		++m_value->m_referenceCount;
	return this;
}

// ?rva002419AB@Rva002419ABOwner@@QAEPAXVAsciiString@@H@Z @ 0x002419AB (55B):
// target passes its by-value string to 0x00240D8C and destroys it at 0x00036410.
// The second 4B argument is unused in retail. Owner and operation remain
// address-derived.
void *Rva002419ABOwner::rva002419AB(AsciiString value, int option)
{
	(void)option;
	rva00240D8C(&value);
	return this;
}
