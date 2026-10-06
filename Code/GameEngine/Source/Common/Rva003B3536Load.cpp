// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva003B3536@Rva003B3536@@QAEXAAVDataChunkInput@@PAX@Z @0x003B3536 123B
// DataChunkInput field loader: two readByte bools then readInt then readByte
// bool then counted-string reader readAsciiString with StringBase set into +0xC.
// Evidence: unlock lane callees all rowed readByte 0x306E9A readInt 0x306E78
// readAsciiString 0x30750A StringBase set 0x366F0 releaseBuffer 0x36410 plus
// caller 0x3B79F1 layout bool+0 bool+1 int+4 bool+8 AsciiString+0xC ret 8.
#include "ascii_string.h"

class DataChunkInput
{
public:
	unsigned char readByte();
	int readInt();
	AsciiString readAsciiString();
};

class Rva003B3536
{
public:
	Rva003B3536(const Rva003B3536 &other);
	void rva003B3536(DataChunkInput &input, void *info);

private:
	bool m_a; // +0
	bool m_b; // +1
	int m_c; // +4
	bool m_d; // +8
	AsciiString m_e; // +0xC
};

Rva003B3536::Rva003B3536(const Rva003B3536 &other)
	: m_a(other.m_a)
	, m_b(other.m_b)
	, m_c(other.m_c)
	, m_d(other.m_d)
	, m_e(other.m_e)
{
}

void Rva003B3536::rva003B3536(DataChunkInput &input, void *info)
{
	m_a = input.readByte() != 0;
	m_b = input.readByte() != 0;
	m_c = input.readInt();
	m_d = input.readByte() != 0;
	m_e = input.readAsciiString();
}
