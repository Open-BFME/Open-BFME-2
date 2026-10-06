// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0020DB91@Rva0020DB91@@QAEPAXABVAsciiString@@@Z 0x0020DB91 46B scan ptr array with StringBase compareNoCase
// Evidence: retail iterates [ecx+0x10] to [ecx+0x14] step 4 calling 0x00006A00 compareNoCase on [esi]+0x18; callers 0x0020DC8F 0x00568709
#include "ascii_string.h"

struct Rva0020DB91Item
{
	char m_pad[24];
	AsciiString m_str;
};

class Rva0020DB91
{
public:
	void *rva0020DB91(const AsciiString &arg);
private:
	char m_pad00[16];
	Rva0020DB91Item **m_begin10;
	Rva0020DB91Item **m_end14;
};

void *Rva0020DB91::rva0020DB91(const AsciiString &arg)
{
	for (Rva0020DB91Item **it = m_begin10; it != m_end14; ++it) {
		if ((*it)->m_str.compareNoCase(arg) == 0)
			return *it;
	}
	return 0;
}
