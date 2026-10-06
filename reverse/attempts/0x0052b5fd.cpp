// ?rva0052B5FD@Rva0052B5FD@@QAEXABVAsciiString@@@Z
// partial score=0.98 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva0052B5FD@Rva0052B5FD@@QAEXABVAsciiString@@@Z, RVA 0x0052B5FD size 55.
// Leaf lane: new(0x18) plus rowed ctor 0x005C49EF with EH null guard.
// Evidence: callee rows for new 0x0002FDA0 and ctor; caller at 0x0052B661;
// neighbours Rva0052B024Loop and RvaLookupFieldOrZeroFamily share /O1.
#include "ascii_string.h"
class Rva005C4A91
{
public:
	Rva005C4A91(const AsciiString &s);
private:
	char m_pad[0x18];
};
class Rva0052B5FD
{
public:
	void rva0052B5FD(const AsciiString &s);
};
// ?rva0052B5FD@Rva0052B5FD@@QAEXABVAsciiString@@@Z present-unmatched
void Rva0052B5FD::rva0052B5FD(const AsciiString &s)
{
	Rva005C4A91 *p = new Rva005C4A91(s);
	(void)p;
}
