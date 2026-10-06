// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva0059F2EB@Rva0059F2EB@@QAEXVAsciiString@@@Z @ 0x0059F2EB (55B).
// Thiscall by-value AsciiString assign to member at this-4 via pin-only
// operator= 0x000366F0, param destroyed via rowed releaseBuffer 0x00036410
// with EH states 0/-1. Callers 0x005A2B24/0x005A2CDF/0x005AF5D9.
#include "ascii_string.h"

class Rva0059F2EB
{
public:
	void rva0059F2EB(const AsciiString arg);

private:
	char m_pad[0x1000];
};

void Rva0059F2EB::rva0059F2EB(const AsciiString arg)
{
	AsciiString &slot = *(AsciiString *)((char *)this + 0xFFC);
	slot = arg;
}
