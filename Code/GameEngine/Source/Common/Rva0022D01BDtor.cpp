// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0022D01B@@QAE@XZ @0x0022D01B 68B: dtor over two Rva002294A3 trees at +0 and +C plus AsciiString at +0x18. Evidence: unlock packet calls rowed 0x0022C917 twice plus rowed releaseBuffer 0x00036410 with states 1-0--1 and reverse destroy order.
#include "ascii_string.h"
class Rva002294A3
{
public:
	~Rva002294A3();
private:
	char m_pad[8];
};
class Rva0022D01B
{
public:
	~Rva0022D01B();
private:
	Rva002294A3 m_a;
	int m_pad8;
	Rva002294A3 m_b;
	int m_pad14;
	AsciiString m_str;
};
Rva0022D01B::~Rva0022D01B()
{
}
