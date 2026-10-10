// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002129A1@Rva002129A1@@QAEXPBVModuleData@@@Z, retail 0x002129A1 19B.
// Vector push_back wrapper: appends a ModuleData pointer to the
// vector<ModuleData const *> at this+0x258 through the rowed push_back
// 0x004DFCB0. Caller at 0x003FC6AD (0x003FC58C family). Evidence: ret-4
// thiscall; lea arg plus add ecx-0x258 plus call shape.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class ModuleData;

class Rva002129A1
{
public:
	void rva002129A1(const ModuleData *data);

private:
	unsigned char m_pad[0x258];
	_STL::vector<const ModuleData *> m_vec;
};

void Rva002129A1::rva002129A1(const ModuleData *data)
{
	m_vec.push_back(data);
}
