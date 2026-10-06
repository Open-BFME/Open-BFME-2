// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva004EC1CE@Rva004EC1CE@@QAEXABVAsciiString@@@Z @ 0x004EC1CE, 11 bytes.
// Tail-jmp wrapper add ecx,0x148 then jmp StringBase<char>::set.
// Evidence: single add ecx,0x148 plus jmp to rowed 0x000366F0 set; tail pattern
// per recipe; same 0x130-0x148 family as Rva004EC276; caller 0x002A9555.
#include "ascii_string.h"

class Rva004EC1CE
{
public:
	void rva004EC1CE(const AsciiString &s);
private:
	char m_pad[0x148];
	AsciiString m_str;
};

void Rva004EC1CE::rva004EC1CE(const AsciiString &s)
{
	return ((StringBase<char> &)m_str).set((const StringBase<char> &)s);
}
