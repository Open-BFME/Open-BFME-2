// ?rva004DFB7E@Rva004DFB7E@@QAE_NPAX@Z
// partial score=0.95 date=2026-10-10
// ?rva004DFB7E@Rva004DFB7E@@QAE_NPAX@Z
// partial score=0.95 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include "ascii_string.h"
#include <vector>

class Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};
extern Rva002A8F24 *g_00DFEEF8;

struct Rva004DFB7EBase
{
	char m_pad00[0x98];
	_STL::vector<AsciiString> m_98;
};

struct Rva002A8AB1Record
{
	char m_pad00[0x160];
	Rva004DFB7EBase *m_160;
};

struct Rva004DFB7EInner
{
	char m_pad00[0x64];
	AsciiString m_64;
};

struct Rva004DFB7EArg
{
	char m_pad00[0x4];
	Rva004DFB7EInner *m_04;
};

class Rva004DFB7E
{
public:
	bool rva004DFB7E(void *p);
private:
	char m_pad00[0x28];
	void *m_28;
};

bool Rva004DFB7E::rva004DFB7E(void *p)
{
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(m_28);
	if (rec != 0)
	for (register unsigned int i = 0; i < rec->m_160->m_98.size(); ++i)
	{
		Rva004DFB7EArg *a = (Rva004DFB7EArg *)p;
		if (((const StringBase<char> *)&rec->m_160->m_98[i])->compare(*(const StringBase<char> *)&a->m_04->m_64) == 0)
			return true;
	}
	return false;
}
