// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// BFME1 donor: reference/open-bfme-1/game/GameEngine/Include/GameNetwork/IPEnumeration.h
// BFME2's node has no MemoryPoolObject base: target allocation is 12 bytes and
// the following address-backed members are AsciiString, IP, and next pointer.

class AsciiString;
#include "ascii_string.h"

class EnumeratedIP
{
public:
	EnumeratedIP();

private:
	AsciiString m_IPstring;
	unsigned int m_IP;
	EnumeratedIP *m_next;
};

// ??0EnumeratedIP@@QAE@XZ
EnumeratedIP::EnumeratedIP()
{
	m_IPstring = "";
	m_next = 0;
	m_IP = 0;
}
