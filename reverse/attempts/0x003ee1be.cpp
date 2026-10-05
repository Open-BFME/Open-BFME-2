// ??1Rva003EE1BE@@UAE@XZ
// partial score=0.9 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
// ??1Rva003EE1BE@@UAE@XZ, RVA 0x003EE1BE size 126.
// Leaf lane dtor with vtable 0x0083613C slot 0 in OpaqueScalarDeletingDtorsB07.
// Evidence: deleting-dtor caller at 0x003EE3E5 in same batch file; base dtor
// row 0x001E3624; array begin/end at +0x1C/+0x20 freed via game _free 0x30830;
// element dtor pin 0x0056A061 plus operator-delete row 0x2FD60; AsciiString at
// +0x18 via shared releaseBuffer row 0x36410; neighbours share /O1 /DNDEBUG.
#include "ascii_string.h"
extern "C" void __cdecl free(void *p);
class Rva001E3624
{
public:
	virtual ~Rva001E3624();
private:
	Rva001E3624 *m_next;
};
class Rva0056A061
{
public:
	~Rva0056A061();
};
class Rva003EE1BE : public Rva001E3624
{
public:
	virtual ~Rva003EE1BE();
private:
	char m_pad08[0x10];
	AsciiString m_str18;
	Rva0056A061 **m_begin;
	Rva0056A061 **m_end;
};
// ??1Rva003EE1BE@@UAE@XZ present-unmatched
Rva003EE1BE::~Rva003EE1BE()
{
	for (Rva0056A061 **p = m_begin; p != m_end; ++p)
		delete *p;
	if (m_begin)
		free(m_begin);
}
