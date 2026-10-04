// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva005F18C1@@QAE@XZ @0x005F18C1 93B: dtor with AsciiString at +0x04 plus Rva0052413E at +0x08 plus Rva005242D7 at +0x14 plus two UnicodeString at +0x20 and +0x24.
// Evidence: calls rowed releaseBuffer narrow 0x00036410 plus rowed dtors 0x0052413E and 0x005242D7 plus rowed releaseBuffer wide 0x00036E70 twice; callers 0x005F1B5C and 0x005F1B9C.
#include "ascii_string.h"
#include "unicode_string.h"
class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[12];
};
class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};
class Rva005F18C1
{
public:
	~Rva005F18C1();
private:
	int m_00;
	AsciiString m_04;
	Rva0052413E m_08;
	Rva005242D7 m_14;
	UnicodeString m_20;
	UnicodeString m_24;
};

Rva005F18C1::~Rva005F18C1()
{
}
