// ?rva002D511E@Rva002D4688@@QAE?AVAsciiString@@XZ
// partial score=0.93 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD
// ?rva002D511E@Rva002D4688@@QAE?AVAsciiString@@XZ @ 0x002D511E (106B).
// Materializer for Rva002D4688 (layout from Rva002D4688.cpp): sizes an
// AsciiString as m_00.m_len + m_00.m_secondPair.m_len + m_10.m_len, fills it
// via rowed rva002D4688 0x002D4688, returns copy via StringBase copy
// 0x000365F0 with releaseBuffer 0x00036410. Same EH shape as rowed
// ??BRva0002C9C2@@QAE?AVAsciiString@@XZ 0x0002CB02; caller 0x002D56DB.
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
	int first = m_00.m_len;
	int second = m_00.m_secondPair.m_len;
	int third = m_10.m_len;
	int len = second + first + third;
	char *buf = ((StringBase<char> *)&tmp)->getBufferForRead(len);
	rva002D4688(buf);
	return tmp;
}
