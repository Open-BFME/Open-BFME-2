// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0059EF62@Rva0059EF62@@QAEXIIABVAsciiString@@0I@Z at 0x0059EF62 (51B). Five-arg setter.
// Evidence: dword moves to +4/+8/+14 plus AsciiString assigns at +0x10/+0x0C via 0x366F0;
// ret 0x14; EBP frame; caller 0x59FC13.
#include "ascii_string.h"

class Rva0059EF62 {
	unsigned char m_pad[4];
	unsigned int m_04;
	unsigned int m_08;
	AsciiString m_0C;
	AsciiString m_10;
	unsigned int m_14;
public:
	void rva0059EF62(unsigned int a, unsigned int b, const AsciiString &c, const AsciiString &d, unsigned int e);
};

void Rva0059EF62::rva0059EF62(unsigned int a, unsigned int b, const AsciiString &c, const AsciiString &d, unsigned int e)
{
	m_08 = b;
	m_04 = a;
	m_10 = c;
	m_0C = d;
	m_14 = e;
}
