// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
//
// ?rva004E063F@Rva004E063F@@QAEXXZ @0x004E063F 104B.
// EH-guarded factory: look up a blob through the 0xDFE1C8 host via rowed
// 0x0021311F keyed on the AsciiString at m_28+0x10, new a 0x44-byte
// Rva0052B278 with (lookup, this, &m_48), store at m_2C, then run its
// 0x0052B003 with (m_20 == -1). Retail 0x004E063F..0x004E06A7.
// The ctor (0x52B278) and the bool method (0x52B003) are unrowed: pinned
// here as honest address-derived candidates. The 0x44 size comes from the
// operator-new push; Rva0052B278 is padded to it. The global uses the proven
// Rva00DFE1C8 void* plus alternatename idiom, cast to the rowed host view.

#include "ascii_string.h"
#include <new>

extern void *Rva00DFE1C8;

class Rva0021311F
{
public:
	void *rva0021311F(const AsciiString *key);
};

class Rva0052B278
{
public:
	Rva0052B278(void *lookup, void *parent, void *extra);
	void rva0052B003(bool flag);

private:
	char m_pad[0x44];
};

class Rva004E063F
{
public:
	void rva004E063F();

private:
	char m_pad[0x20];
	int m_20;
	char m_pad24[0x28 - 0x24];
	void *m_28;
	Rva0052B278 *m_2C;
	char m_pad30[0x48 - 0x30];
	void *m_48;
};

// ?Rva00DFE1C8@@3PAXA: the global at VA 0xdfe1c8 is ?g_009FE1C8@@3PAVRva0021294A@@A.
#pragma comment(linker, "/alternatename:?Rva00DFE1C8@@3PAXA=?g_009FE1C8@@3PAVRva0021294A@@A")

// ?rva004E063F@Rva004E063F@@QAEXXZ
void Rva004E063F::rva004E063F()
{
	void *lookup = ((Rva0021311F *)Rva00DFE1C8)->rva0021311F((const AsciiString *)((char *)m_28 + 0x10));
	m_2C = new Rva0052B278(lookup, this, &m_48);
	m_2C->rva0052B003(m_20 == -1);
}
