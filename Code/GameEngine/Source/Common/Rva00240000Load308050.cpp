// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?rva00308050@Rva00240000@@QAE_NVAsciiString@@@Z, retail 0x00308050 (90B,
// ret 4), a member of the 0x00240000-constructed stream (see
// Rva00240000Ctor.cpp for the vtable and the +4 byte vector).
//
// Loads the named file into the +4 vector through the unrowed loader
// 0x00307EDC (cdecl: the by-value name's address then the vector). On
// success the read cursor (+0x14), the +0x18 word and the end (+0x1C) are
// set from the vector's start and its byte length; the by-value name is
// released on exit. Returns whether the load succeeded.
//
// Evidence (target): the loader call and its two pops, the vector words read
// at [edi] and [edi+4], the start/end arithmetic and the three stores at
// +0x18, +0x14 and +0x1C. Field names stay offset-derived.
#include "ascii_string.h"

struct Rva00240000ByteVector
{
	char *begin() const { return m_start; }
	unsigned int size() const { return m_finish - m_start; }
	char *m_start;
	char *m_finish;
	char *m_end;
};

bool rva00307EDC(AsciiString *path, Rva00240000ByteVector *data);

class Rva00240000
{
public:
	bool rva00308050(AsciiString path);

private:
	const void *m_00;
	Rva00240000ByteVector m_04;
	const void *m_10;
	char *m_14;
	char *m_18;
	char *m_1C;
};

bool Rva00240000::rva00308050(AsciiString path)
{
	bool loaded = false;
	if (rva00307EDC(&path, &m_04))
	{
		char *end = m_04.begin() + m_04.size();
		m_14 = m_18 = m_04.begin();
		m_1C = end;
		loaded = true;
	}
	return loaded;
}
