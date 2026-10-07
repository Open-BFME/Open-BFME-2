// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /MD
// ?rva0059E861@Rva0059E861@@QAE_NABVAsciiString@@@Z @0x0059E861 17B
// Evidence: leaf called from 0x0059E9B5; callee Faction 0x00441E4D; pushes arg and this+4; neighbours 0x0059E848 and 0x0059E872.
#include "ascii_string.h"

bool Rva00441E4DFaction(void *p, const AsciiString &s);

class Rva0059E861
{
public:
	bool rva0059E861(const AsciiString &s);
private:
	char m_pad00[4];
	void *m_04;
};

bool Rva0059E861::rva0059E861(const AsciiString &s)
{
	return Rva00441E4DFaction(m_04, s);
}
