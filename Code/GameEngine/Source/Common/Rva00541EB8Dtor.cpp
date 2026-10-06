// cl: /EHs /MD
// stlport
// ??1Rva00541EB8@@UAE@XZ @0x00541EB8 74B outer dtor.
// Retail stores vtable 0x00869514 destroys two BfmeNarrowRecord0041A5D2 at
// +0x24 and +0x44 via twin 0x00541E77 then base ??1Rva0053FB33@@UAE@XZ.
// Member starts are32 bytes apart; the recovered record is28 bytes.
// Explicit four-byte gap preserves native +0x44 without a private32-byte class.
// Same chain shape as rowed ??1Rva0054080A@@UAE@XZ via inner plus base.
// Evidence: vtable store plus two twin calls plus base call plus caller 0x0054218E.
#include "BfmeNarrowRecord0041A5D2.h"

class Rva0053FB33
{
public:
	virtual ~Rva0053FB33();
private:
	unsigned char m_pad[0x24 - 4];
};

class Rva00541EB8 : public Rva0053FB33
{
public:
	virtual ~Rva00541EB8();
private:
	BfmeNarrowRecord0041A5D2 m_24;
	unsigned char m_gap40[4];
	BfmeNarrowRecord0041A5D2 m_44;
};

Rva00541EB8::~Rva00541EB8()
{
}
