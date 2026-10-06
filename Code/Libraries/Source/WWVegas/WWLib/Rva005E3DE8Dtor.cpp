// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva005E3DE8@@QAE@XZ @0x005E3DE8 53B.
// Non-virtual dtor: inline AsciiString member at +8 torn down via releaseBuffer
// with EH state 0 then member at +0 destroyed via 0x0022167C. No vptr store.
// Evidence: unlock lane plus caller 0x005E3EF1 deleting dtor plus callee releaseBuffer 0x00036410 plus pin ??1Rva0022167C plus precedent Rva0057A4E7Dtor.
#include "ascii_string.h"

class Rva0022167C
{
public:
	~Rva0022167C();
private:
	char m_bytes[8];
};

class Rva005E3DE8
{
public:
	~Rva005E3DE8();
private:
	Rva0022167C m_at00;
	AsciiString m_at08;
};

Rva005E3DE8::~Rva005E3DE8()
{
}
