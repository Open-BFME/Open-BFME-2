// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?RemoveExternHandler@Rva002244CA@@QAEHPBVAsciiString@@@Z @0x002244CA 8B
// Tail-jmp forwarder adding 0x20 then calling rowed erase 0x00223736.
// Evidence: chain lane add ecx 0x20 jmp to rowed ?rva00223736@Rva00223591; 8 callers.
#include "ascii_string.h"

#include "../../Include/GameClient/Rva00223591.h"

class Rva002244CA
{
public:
	int RemoveExternHandler(const AsciiString *key);
private:
	char m_pad[0x20];
	Rva00223591 m_table;
};

int Rva002244CA::RemoveExternHandler(const AsciiString *key)
{
	return m_table.rva00223736(key);
}
