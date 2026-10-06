// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva002B85EC@Rva002BA8F1Logic@@QAEXPAURva002B85ECFilter@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z retail 0x002B85EC 88 bytes.
// Filter member vector at +0x10c by element +0x54 == filter +0x14, appending
// matches to output vector via rowed push_back 0x004DFCB0. Evidence: caller
// 0x00577448 passes [logic+0x98] and stack vector with this=g_009FEF10
// (Rva002BA8F1Logic); callees rowed; neighbours are stlport WWLib TUs.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its vector bodies.
#pragma optimize("s", off)
#pragma optimize("t", on)
#include <stl/_algobase.h>
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

class ModuleData
{
public:
	unsigned char m_pad[0x54];
	unsigned int m_code;
};

struct Rva002B85ECFilter
{
	unsigned char m_pad[0x14];
	unsigned int m_key;
};

class Rva002BA8F1Logic
{
public:
	void rva002B85EC(Rva002B85ECFilter *filter, _STL::vector<const ModuleData *> *out);

private:
	unsigned char m_pad[0x10c];
	_STL::vector<const ModuleData *> m_vec;
};

void Rva002BA8F1Logic::rva002B85EC(Rva002B85ECFilter *filter, _STL::vector<const ModuleData *> *out)
{
	for (unsigned int i = 0; i < m_vec.size(); ++i) {
		const ModuleData *cand = m_vec[i];
		if (cand->m_code == filter->m_key)
			out->push_back(cand);
	}
}
