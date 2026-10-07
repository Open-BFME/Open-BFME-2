// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
// ?rva005F1D06@Rva005F1D06@@QAEHPAD@Z @0x005F1D06 37B evidence: gap between dtor rows in Rva005F1CE8Dtor.cpp base write 0x005F1B75 plus pair write at +0x10 caller 0x005F1D7C
#include "ascii_string.h"
struct Rva002226E5TextPlusString
{
	int length() const;
	int write(char *dst);
	char m_pad[8];
};
struct AsciiStringRef
{
	class AsciiString *m_string;
	int m_len;
	int write(char *dst);
};
struct Rva005F1B75 : Rva002226E5TextPlusString
{
	int length() const;
	int write(char *dst);
	AsciiStringRef m_third;
};
class Rva000B3F84Pair
{
public:
	int write(char *dst);
	char m_pad[4];
	int m_extra;
};
class Rva005F1D06 : public Rva005F1B75
{
public:
	int rva005F1D06(char *dst);
	AsciiString rva005F1D47();
private:
	Rva000B3F84Pair m_10;
};
int Rva005F1D06::rva005F1D06(char *dst)
{
	int n = Rva005F1B75::write(dst);
	return n + m_10.write(dst + n);
}
AsciiString Rva005F1D06::rva005F1D47()
{
	AsciiString tmp;
	int extra = m_10.m_extra;
	int total = Rva005F1B75::length() + extra;
	char *buf = ((StringBase<char> &)tmp).getBufferForRead(total);
	rva005F1D06(buf);
	return tmp;
}
