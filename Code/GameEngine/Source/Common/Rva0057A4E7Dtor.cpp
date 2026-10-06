// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ??1Rva0057A4E7@@QAE@XZ @0x0057A4E7 53B.
// Non-virtual dtor: inline AsciiString member at +8 torn down via releaseBuffer
// with EH state 0 then member at +0 destroyed via 0x0022167C. No vptr store.
// Evidence: unlock lane plus caller 0x0057AAD5 deleting dtor plus callee releaseBuffer 0x00036410 plus pin ??1Rva0022167C plus precedent Rva005CB3BEDtor.
#include "ascii_string.h"

class Rva0022167C
{
public:
	~Rva0022167C();
private:
	char m_bytes[8];
};

class Rva0057A4E7
{
public:
	~Rva0057A4E7();
private:
	Rva0022167C m_at00;
	AsciiString m_at08;
};

Rva0057A4E7::~Rva0057A4E7()
{
}
