// cl: /Ireference/shims/bfme2_ascii /MD
// ??1Rva002004FD@@QAE@XZ @0x002004FD 9B: dtor zeroes +0x14 then releases StringBase; retail and [ecx+0x14],0 then jmp releaseBuffer 0x00036410. Evidence: deleting-dtor caller 0x0031F83A calls this as ??1; same idiom as Rva0031F831Dtor (+8); and-mem-zero needs /O1.
#include "ascii_string.h"

class Rva002004FD
{
public:
	~Rva002004FD();
private:
	AsciiString m_str;
	char m_pad[16];
	int m_14;
};

Rva002004FD::~Rva002004FD()
{
	m_14 = 0;
}
