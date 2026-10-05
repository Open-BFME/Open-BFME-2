// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ?rva005D3B26@Rva005D3B26@@QAEXXZ retail 0x005D3B26 116B
// Evidence: unlock twin of rowed 0x005D3B9A portrait; format row 0x00038150 releaseBuffer row 0x00036410; empty VA 0x007BAC1C manager VA 0x009FE4CC; pinned callee 0x002239E2; callers 0x005D3CF0 0x005D3D44
template <typename T> class StringBase;

class AsciiString;

#include "ascii_string.h"

class Image;

class Rva00222A8BTarget
{
public:
	void rva002239E2(const AsciiString &name, const Image *image);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

struct Rva005D2FD0Inner
{
	char m_pad8[8];
	char m_name[1];
};

class Rva005D3B26
{
public:
	void rva005D3B26();

	void *m_unused00;
	int m_level;
	Rva005D2FD0Inner *m_inner;
	char m_pad0C[0x14];
	const Image *m_image20;
};

void Rva005D3B26::rva005D3B26()
{
	if (TheRva00222A8BTarget == 0)
		return;
	if (m_image20 == 0)
		return;
	AsciiString tmp;
	const char *name = m_inner ? m_inner->m_name : "";
	tmp.format("_level%u.%s_Portrait", m_level, name);
	TheRva00222A8BTarget->rva002239E2(tmp, m_image20);
}
// ?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A: the global at VA 0xdfe4cc is ?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A.
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
