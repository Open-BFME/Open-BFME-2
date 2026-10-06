// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva004EC166@Rva004EC166@@QAEXABVAsciiString@@@Z @ 0x004EC166, 8 bytes.
// Tail-jmp wrapper add ecx,8 then jmp StringBase<char>::set.
// Evidence: single add ecx,8 plus jmp to rowed 0x000366F0 set; same family as
// Rva004EC1CE (offset 0x148); caller 0x0043342A.
#include "ascii_string.h"

class Rva004EC166
{
public:
	void rva004EC166(const AsciiString &s);
private:
	char m_pad[8];
	AsciiString m_str;
};

void Rva004EC166::rva004EC166(const AsciiString &s)
{
	return ((StringBase<char> &)m_str).set((const StringBase<char> &)s);
}
