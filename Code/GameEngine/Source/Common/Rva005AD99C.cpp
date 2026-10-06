// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005AD99C@Rva005AD99C@@QAEXABVAsciiString@@PAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@@Z, retail 0x005AD99C, 36 bytes.
// Outer loop over holder array at this+0..this+4; for each element forward
// the same (name, out) args to rowed inner 0x005DCE72 which filters ModuleData
// by name into the vector. Evidence: callee rowed, caller 0x0050704B.
// Honest address name; chain from 0x005DCE72.
#include <vector>
#include "ascii_string.h"

class ModuleData;
class Rva005DCE72
{
public:
	void rva005DCE72(const AsciiString &name, _STL::vector<const ModuleData *> *out);
};

class Rva005AD99C
{
public:
	void rva005AD99C(const AsciiString &name, _STL::vector<const ModuleData *> *out);
private:
	Rva005DCE72 **m_begin; // +0x0
	Rva005DCE72 **m_end; // +0x4
};

void Rva005AD99C::rva005AD99C(const AsciiString &name, _STL::vector<const ModuleData *> *out)
{
	for (Rva005DCE72 **it = m_begin; it != m_end; ++it)
		(*it)->rva005DCE72(name, out);
}
