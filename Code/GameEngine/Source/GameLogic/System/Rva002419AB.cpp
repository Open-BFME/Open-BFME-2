// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc

#include "ascii_string.h"

class Rva002419ABOwner
{
public:
	void *rva00240D8C(const AsciiString *value);
	void *rva002419AB(AsciiString value, int option);
};

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
