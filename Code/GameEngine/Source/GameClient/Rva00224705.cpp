// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00224705@Rva00224705@@QAEHPBVAsciiString@@@Z @0x00224705 11B
// Tail-jmp wrapper over table at +0xb8 via rowed erase 0x00223736.
// Evidence: chain lane calls rowed 0x00223736; retail add ecx 0xb8 plus jmp.
#include "ascii_string.h"

class Rva00223591
{
public:
	int rva00223736(const AsciiString *key);
};

class Rva00224705
{
public:
	int rva00224705(const AsciiString *key);
private:
	char m_pad[0xb8];
	Rva00223591 m_table;
};

int Rva00224705::rva00224705(const AsciiString *key)
{
	return m_table.rva00223736(key);
}
