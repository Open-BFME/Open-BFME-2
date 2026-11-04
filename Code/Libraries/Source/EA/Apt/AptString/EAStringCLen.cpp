// cl: /DNDEBUG /MD /EHsc
// ?rva006D5EC0@EAStringC@@QAEHXZ, retail 0x006D5EC0, 15 bytes.
// Leaf: returns rowed 0x006D4D80 of the UTF-8 payload at m_pData+8.
// Evidence: caller Rva006D7A60Finish uses int return for negative-start fixup
// and rowed EAStringC Mid at 0x006D5F30 proves the payload layout.

int __cdecl rva006d4d80(const char *s);

#include "../../../Apt/EAStringC.h"

int EAStringC::rva006D5EC0()
{
	return rva006d4d80(reinterpret_cast<char *>(data) + 8);
}
