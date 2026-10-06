// cl: /Ireference/shims/bfme2_ascii /GX /MD
// ??1Rva0010F83E@@UAE@XZ, retail 0x0010F83E, 53 bytes.
// EH dtor: AsciiString member at +0x10 via rowed releaseBuffer 0x00036410
// then base Rva001164F5 via pinned 0x001164F5. Novtable suppresses the
// derived vptr store retail lacks, matching the Taint precedent.
// Evidence: callees rowed/pinned 0x00036410 plus 0x001164F5 plus EH_prolog;
// caller 0x0010F825 in OpaqueScalarDeletingDtorsB01; vtable none (novtable).
#include "ascii_string.h"

class Rva001164F5
{
public:
	virtual ~Rva001164F5();
};

class __declspec(novtable) Rva0010F83E : public Rva001164F5
{
public:
	virtual ~Rva0010F83E();
private:
	unsigned char m_pad[0x10 - 4];
	AsciiString m_s10;
};

Rva0010F83E::~Rva0010F83E()
{
}
