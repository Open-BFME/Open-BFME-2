// ?rva002D511E@Rva002D4688@@QAE?AVAsciiString@@XZ
// partial score=0.95 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD
// ?rva002D511E@Rva002D4688@@QAE?AVAsciiString@@XZ
// Materializer for Rva002D4688. Layout follows its rowed writer at +0 and
// +0x10; length reads sum the two nested title fields and trailing pair.
// Caller 0x002D56DB. Uses rowed string buffer, writer, copy, and release calls.
#include "ascii_string.h"

struct Rva000B3F84Pair
{
	const char *m_ptr;
	int m_len;
	int write(char *dst);
};

struct WinMainTitlePair : Rva000B3F84Pair
{
	Rva000B3F84Pair m_secondPair;
	int write(char *dst);
};

class Rva002D4688
{
public:
	int rva002D4688(char *buffer);
	AsciiString rva002D511E();

private:
	WinMainTitlePair m_00;
	Rva000B3F84Pair m_10;
};

AsciiString Rva002D4688::rva002D511E()
{
	AsciiString tmp;
	int third = m_10.m_len;
	int first = m_00.m_len;
	int second = m_00.m_secondPair.m_len;
	int len = (first + second) + third;
	char *buf = ((StringBase<char> *)&tmp)->getBufferForRead(len);
	rva002D4688(buf);
	return tmp;
}
