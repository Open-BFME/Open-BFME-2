// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0039EA9C@@QAE@XZ @0x0039EAB7 54B, dtor of the six-dword record whose
// ctor is rowed at 0x0039EA9C. Retail destroys StringBase<char> at +0x10 then
// +0x0C through rowed releaseBuffer 0x00036410 with EH states 0 then -1.
// Same callers as the ctor (0x0059A3BB 0x0059A6C6 0x005AA017). No vptr.
// Evidence: caller pairing with ctor, releaseBuffer rows, no vtable store.
#include "ascii_string.h"

class Rva0039EA9C
{
public:
	~Rva0039EA9C();
private:
	int m_00;
	int m_04;
	int m_08;
	AsciiString m_0c;
	AsciiString m_10;
	int m_14;
};
Rva0039EA9C::~Rva0039EA9C()
{
}
