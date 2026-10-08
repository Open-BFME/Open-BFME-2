// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva004B031E@Rva004B031E@@QAEPAXXZ, retail 0x004B031E, 21 bytes.
// Honest-address thiscall with no stack args returning void*: loads
// AsciiString at [this+4]+0xD0 and looks it up through global g_009FF000
// slot rva002D06CA. Evidence: rowed callee 0x002D06CA, extern name in use
// g_009FF000 (?g_009FF000@@3PAVRva002D06CA@@A), callers 0x004B052E/0x004B0570
// test eax (non-void return), neighbours ModuleUpdateDtors / SpecialDisguise.
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

struct Rva004B031EInner
{
	char m_pad[0xD0];
	AsciiString m_key;
};

class Rva004B031E
{
public:
	void *rva004B031E();
private:
	char m_pad0[4];
	Rva004B031EInner *m_ptr;
};

void *Rva004B031E::rva004B031E()
{
	AsciiString *key = &m_ptr->m_key;
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA(key);
}
