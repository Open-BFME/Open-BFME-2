// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// String-slot cluster around 0x000B82F9. Members carry a flag byte, a raw
// name pointer and AsciiString slots; destruction of by-value AsciiString
// parameters emits the shared releaseBuffer worker (0x00036410) through the
// shim destructor, and slot fills go through StringBase::set (0x000366F0)
// via AsciiString::operator= (the operator= inline schedules the member-add
// ahead of the argument push where a direct set call does not).
// Class and member names are address-derived; sibling probes 0xB82F9/0xB83A7
// are banked (epilog load-order wall) with the wider layout, and rejoin here
// when that lever is found.

#include "ascii_string.h"

class Rva000B8F5A
{
public:
	void rva000B8F5A(char *a, AsciiString b);

private:
	char m_pad00[0x94];
	bool m_94;
	char m_pad95[0x98 - 0x95];
	char *m_98;
	char m_pad9C[0xA8 - 0x9C];
	AsciiString m_A8;
	char m_padAC[0x258 - 0xAC];
};

// ?rva000B8F5A@Rva000B8F5A@@QAEXPADVAsciiString@@@Z @0x000B8F5A 71B
void Rva000B8F5A::rva000B8F5A(char *a, AsciiString b)
{
	m_98 = a;
	m_94 = false;
	m_A8 = b;
}
