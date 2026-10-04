// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??1Rva00309D9E@@UAE@XZ retail 0x00309D9E 60B.
// Dtor with vtable 0x00C082E8 slot0, two AsciiString members at +4 +8 destroyed
// via releaseBuffer, EH states 0/-1. Deleting dtor rowed 0x00309DDA in
// OpaqueScalarDeletingDtorsB06.cpp. Caller 0x00309DDD.
// Evidence: callees rowed releaseBuffer 0x00036410 twice, vtable store g_00C082E8.
#include "ascii_string.h"

class Rva00309D9E
{
public:
	virtual ~Rva00309D9E();
private:
	AsciiString m_04;
	AsciiString m_08;
};

Rva00309D9E::~Rva00309D9E()
{
}
