// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva00573B23@@QAE@XZ @0x00573A9B 45B
// Ctor for Rva00573B23 (vtable 0x0086E270): calls rowed base ??0Rva0055B0CC@@QAE@XZ then zeroes AsciiString +0x2c and Coord +0x30 plus float +0x3c via SSE.
// Evidence: call 0x0055B048 then mov [esi] 0x00C6E270 then and [esi+2c] 0 then 4x movss xmm0; layout from Rva00573A35Xfer.cpp and Rva00573B23Dtor.cpp; unblocks 0x005AAA34 0x005AC294 0x005AB843 0x005AA90D.
#include "ascii_string.h"

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
private:
	char m_pad04[0x28];
};

class Rva00573B23 : public Rva0055B0CC
{
public:
	Rva00573B23();
private:
	AsciiString m_2c;
	Coord3DBase m_30;
	float m_3c;
};

Rva00573B23::Rva00573B23()
{
	m_30.x = 0.0f;
	m_30.y = 0.0f;
	m_30.z = 0.0f;
	m_3c = 0.0f;
}
