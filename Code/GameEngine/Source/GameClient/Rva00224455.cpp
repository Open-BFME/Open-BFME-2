// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00224455@Rva00224455@@QAEHPBVAsciiString@@@Z @0x00224455 8B
// Tail-jmp forwarder adding 0xC then calling rowed erase 0x00223736.
// Evidence: chain lane add ecx 0xC jmp to rowed ?rva00223736@Rva00223591; 11 callers.
#include "ascii_string.h"

class Rva00223591
{
public:
	int rva00223736(const AsciiString *key);
};

class Rva00224455
{
public:
	int rva00224455(const AsciiString *key);
private:
	char m_pad[0xc];
	Rva00223591 m_table;
};

int Rva00224455::rva00224455(const AsciiString *key)
{
	return m_table.rva00223736(key);
}
