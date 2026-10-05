// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?rva0021C970@Rva0021BCA7@@QAEPBVAsciiString@@HI@Z 0x0021C970 54B
// Evidence: unlock lane; callees rva0021BC0D rowed rva0021BCA7 rowed; callers 0x21CB06; returns AsciiString at +4 or TheEmptyString; global g_00DFE354 out; this has map at +0x24 like Rva0021BCA7.
#include "ascii_string.h"

class Rva0021BC0D
{
public:
	unsigned char rva0021BC0D(int key, void **out);
};

class Rva0021BCA7
{
public:
	void *rva0021BCA7(int key, unsigned int index);
	const AsciiString *rva0021C970(int key, unsigned int index);
};

extern void *g_00DFE354;

const AsciiString *Rva0021BCA7::rva0021C970(int key, unsigned int index)
{
	if (!((Rva0021BC0D *)this)->rva0021BC0D(key, (void **)&g_00DFE354))
		return &AsciiString::TheEmptyString;
	void *p = rva0021BCA7(key, index);
	if (p)
		return (const AsciiString *)((const char *)p + 4);
	return &AsciiString::TheEmptyString;
}
