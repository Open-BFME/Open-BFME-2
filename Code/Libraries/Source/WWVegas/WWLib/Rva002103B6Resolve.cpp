// cl: /Ireference/shims/bfme2_ascii /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002103B6@Rva002103B6@@QAEXPAVRva00210390@@@Z @0x002103B6 119B: clear Science vector at +0x2C, reserve src count at +0x20, resolve each AsciiString via rowed 0x00210390.
// Evidence: retail erase 0x00532803 on [edi]/[edi+4], reserve 0x002A1410 of (0x24-0x20)>>2, loop lea+push into rowed 0x00210390 with this=[ebp+8], [eax+0x12C] or -1 into push_back 0x002E01C6; caller 0x00210714.
#include <vector>

#include "ascii_string.h"

class Rva00210390
{
public:
	void *rva00210390(const AsciiString *key);
};

enum ScienceType
{
	SCIENCE_INVALID = -1
};

struct Rva002103B6Node
{
	char m_pad[0x12C];
	ScienceType m_science;
};

class Rva002103B6
{
public:
	void rva002103B6(Rva00210390 *lookup);
private:
	char m_pad00[0x20];
	_STL::vector<AsciiString> m_src20;
	_STL::vector<ScienceType> m_dst2C;
};

void Rva002103B6::rva002103B6(Rva00210390 *lookup)
{
	_STL::vector<ScienceType> &dst = m_dst2C;
	dst.erase(dst.begin(), dst.end());
	dst.reserve(m_src20.size());
	for (unsigned int i = 0; i < m_src20.size(); ++i) {
		void *node = lookup->rva00210390(&m_src20[i]);
		int v;
		if (node)
			v = ((Rva002103B6Node *)node)->m_science;
		else
			v = -1;
		dst.push_back((ScienceType)v);
	}
}
