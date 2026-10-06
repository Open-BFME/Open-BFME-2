// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0020FD7F@Rva0020FD7F@@QAEXPAURva0020FD7FFilter@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z @0x0020FD7F 96B via voidptr-erase plus ModuleData filter push
// Evidence: retail clears out vector via rowed voidptr erase 0x0031BD55 then loops holder vector at (this+8)+0x2c comparing element+0x13c to filter+0x14 and push_back via rowed 0x004DFCB0; caller 0x002B7DE6; neighbours share /O1; Rva002B85ECFilter precedent for filter shape.
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

class ModuleData
{
public:
	unsigned char m_pad[0x13c];
	unsigned int m_code;
};

struct Rva0020FD7FFilter
{
	unsigned char m_pad[0x14];
	unsigned int m_key;
};

struct Rva0020FD7FHolder
{
	unsigned char m_pad[0x2c];
	_STL::vector<const ModuleData *> m_vec;
};

class Rva0020FD7F
{
public:
	void rva0020FD7F(Rva0020FD7FFilter *filter, _STL::vector<const ModuleData *> *out);
private:
	char m_pad[8];
	Rva0020FD7FHolder *m_holder;
};

void Rva0020FD7F::rva0020FD7F(Rva0020FD7FFilter *filter, _STL::vector<const ModuleData *> *out)
{
	((_STL::vector<void *> *)out)->erase(((_STL::vector<void *> *)out)->begin(), ((_STL::vector<void *> *)out)->end());
	Rva0020FD7FHolder *holder = m_holder;
	_STL::vector<const ModuleData *> &vec = holder->m_vec;
	for (unsigned int i = 0; i < vec.size(); ++i) {
		const ModuleData *cand = vec[i];
		if (cand->m_code == filter->m_key)
			out->push_back(cand);
	}
}
