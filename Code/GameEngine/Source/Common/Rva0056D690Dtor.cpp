// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ??1Rva0056D690@@UAE@XZ retail 0x0056D690 62 bytes.
// Virtual dtor: vptr 0x0086DAC4, AsciiString at +0x26C via shared header,
// base Rva005C9659 rowed via pin 0x005C9659.
// Evidence: deleting dtor 0x0056D74F calls here; vtable 0x00C6DAC4;
// callees releaseBuffer 0x00036410 base pin 0x005C9659; prev/next flags.
#include "ascii_string.h"

class Rva005C9659
{
public:
	virtual ~Rva005C9659();
};

class Rva0056D690 : public Rva005C9659
{
public:
	virtual ~Rva0056D690();
private:
	unsigned char m_pad[0x26C - 4];
	AsciiString m_26C;
};

Rva0056D690::~Rva0056D690()
{
}
