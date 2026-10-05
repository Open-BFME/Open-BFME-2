// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005DCE72@Rva005DCE72@@QAEXABVAsciiString@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z, retail 0x005DCE72, 59 bytes.
// Loop over ModuleData* array at this+4..this+8; for each element compare
// AsciiString at +0xC with arg1 via rowed StringBase::compare 0x000069D6,
// on match push the element into vector arg2 via rowed push_back 0x004DFCB0.
// Evidence: callees rowed, caller 0x005AD99C passes through. Honest address name.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>
#include "ascii_string.h"

class ModuleData
{
public:
	char m_pad0[0xC];
	AsciiString m_name; // +0xC
};

class Rva005DCE72
{
public:
	void rva005DCE72(const AsciiString &name, _STL::vector<const ModuleData *> *out);
private:
	char m_pad0[4];
	const ModuleData **m_begin; // +0x4
	const ModuleData **m_end; // +0x8
};

void Rva005DCE72::rva005DCE72(const AsciiString &name, _STL::vector<const ModuleData *> *out)
{
	for (const ModuleData **it = m_begin; it != m_end; ++it)
	{
		const ModuleData *md = *it;
		if (md->m_name.compare(name) == 0)
			out->push_back(md);
	}
}
