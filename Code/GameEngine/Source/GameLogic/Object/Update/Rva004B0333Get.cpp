// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva004B0333@Rva004B0333@@QAEPAXXZ, retail 0x004B0333, 21 bytes.
// Honest-address thiscall with no stack args returning void*: loads
// AsciiString at [this+4]+0xD4 and looks it up through global g_009FF000
// slot rva002D06CA. Evidence: rowed callee 0x002D06CA, extern name in use
// g_009FF000 (?g_009FF000@@3PAVRva002D06CA@@A), sibling 0x004B031E same
// recipe at +0xD0, caller 0x00291242, neighbours Rva004B031E / SpecialDisguise.
#include "ascii_string.h"

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

struct Rva004B0333Inner
{
	char m_pad[0xD4];
	AsciiString m_key;
};

class Rva004B0333
{
public:
	void *rva004B0333();
private:
	char m_pad0[4];
	Rva004B0333Inner *m_ptr;
};

void *Rva004B0333::rva004B0333()
{
	AsciiString *key = &m_ptr->m_key;
	return ((Rva002D06CA *)TheThingFactory)->rva002D06CA(key);
}
