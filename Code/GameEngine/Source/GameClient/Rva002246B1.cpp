// cl: /Ireference/shims/bfme2_ascii /MD
// ?RemoveCustomRender@Rva002246B1@@QAEHPBVAsciiString@@@Z @0x002246B1 8B
// Tail-jmp wrapper over table at +0x34 via rowed erase 0x00223736.
// Evidence: chain lane calls rowed 0x00223736; retail add ecx 0x34 plus jmp.
#include "ascii_string.h"

#include "../../Include/GameClient/Rva00223591.h"

class Rva002246B1
{
public:
	int RemoveCustomRender(const AsciiString *key);
private:
	char m_pad[0x34];
	Rva00223591 m_table;
};

int Rva002246B1::RemoveCustomRender(const AsciiString *key)
{
	return m_table.rva00223736(key);
}
