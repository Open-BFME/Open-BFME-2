// ?rva00215479@Rva00215479@@QAEHABVAsciiString@@@Z
// partial score=0.9 date=2026-10-06
// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?rva00215479@Rva00215479@@QAEHABVAsciiString@@@Z 0x00215479 69B find-index by AsciiString compare over 16B records
// Evidence: retail loops over [esi+0xc]/[esi+0x10] as begin/end of 16B entries (sar 4), calls
// ?compare@?$StringBase@D@@QBEHABV1@@Z per entry, returns index or -1 (ret 4, __thiscall, 1 stack arg).
// Callers 0x00215B14 and 0x0032FC70 (both unclaimed) pass one AsciiString-like ref.
#include "ascii_string.h"

class Rva00215479
{
public:
	int rva00215479(const AsciiString &needle);
private:
	char m_pad[0xc];
	char *m_begin;
	char *m_end;
};

// ?rva00215479@Rva00215479@@QAEHABVAsciiString@@@Z present-unmatched
int Rva00215479::rva00215479(const AsciiString &needle)
{
	for (unsigned int i = 0; i < (unsigned int)((m_end - m_begin) >> 4); ++i)
	{
		if (((AsciiString *)(m_begin + i * 16))->compare(needle) == 0)
			return (int)i;
	}
	return -1;
}
