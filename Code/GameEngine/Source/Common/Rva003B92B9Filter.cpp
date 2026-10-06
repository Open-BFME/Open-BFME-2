// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003B92B9@Rva003B8BAA@@QAEXPAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z @0x003B92B9 84B.
// Filter member vector at +0x14 by Rva003B8B2A check, collecting matching
// entries into output vector<const ModuleData*> via rowed reserve 0x002B712E
// plus rowed push_back 0x004DFCB0. Evidence: same class/offsets as sibling
// Rva003B930D filter (Rva003B8BAA +0x14 vector<Rva*>); same check callee
// 0x003B8B2A with test al al; dest rows are ModuleData-const vector; retail
// pushes edi (address of source slot) so source and dest element types match.
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

class Rva003B8B2A
{
	char m_pad00[0x1C];
	int m_field1C;
	int m_field20;
	char m_pad24[0x4C - 0x24];
	unsigned char m_flag4C;
public:
	int rva003B8B2A();
};

class ModuleData;

class Rva003B8BAA
{
	char m_pad[0x14];
	_STL::vector<const ModuleData *> m_vec14;
public:
	void rva003B92B9(_STL::vector<const ModuleData *> *out);
};

void Rva003B8BAA::rva003B92B9(_STL::vector<const ModuleData *> *out)
{
	out->reserve(m_vec14.size());
	for (unsigned int i = 0; i < m_vec14.size(); ++i)
	{
		const ModuleData * &slot = m_vec14[i];
		if ((unsigned char)((Rva003B8B2A *)slot)->rva003B8B2A())
			out->push_back(slot);
	}
}
