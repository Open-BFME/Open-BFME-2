// ??BRva0002C9C2@@QAE?AVAsciiString@@XZ
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
//
// Rva0002C9C2 materializer, retail 0x0002CB02, 98 bytes: size via rowed
// Rva005D0507 length helper (layout-compatible AsciiString pair at +0/+8)
// then fill via own rowed write plus shared getBufferForRead, return copy
// with releaseBuffer via tmp dtor. Evidence: RegistryAsciiPath.cpp names
// unclaimed operator at 0x0002CB02 plus same 98B shape as Rva0020F58E
// operator at 0x0020F712; LINK BONUS via 0x0002CBCC; prev proves flags.
#include "ascii_string.h"

class Rva005D0507
{
public:
	int rva005D0507();
};

class Rva0002C9C2
{
public:
	int write(char *dst);
	operator AsciiString();
};

Rva0002C9C2::operator AsciiString()
{
	AsciiString tmp;
	int len = ((Rva005D0507 *)this)->rva005D0507();
	char *buf = ((StringBase<char> *)&tmp)->getBufferForRead(len);
	write(buf);
	return tmp;
}
