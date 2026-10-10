// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva001F8E45@Rva001F8E45@@QAEXPAX0@Z, retail 0x001F8E45, 78 bytes.
//
// Clears a ModuleData vector at this+0 then rebuilds it from the pointer
// vector at arg2+0x1cc, keeping entries whose byte at +0x1c is nonzero and
// mapping each through the virtual at +0x14 slot 0 with arg1. Evidence:
// callers 0x001FA529 (this+4) and jmp 0x001F9487; callees rowed voidptr
// erase 0x0031BD55 and ModuleData push_back 0x004DFCB0; loop keeps src base
// in esi and iter in edi with end reloaded from [esi+4].
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

class Rva001F8E45Iface
{
public:
	virtual const ModuleData* getData(void* arg);
};

struct Rva001F8E45Elem
{
	char m_pad0[0x14];
	Rva001F8E45Iface m_iface;
	char m_pad1[4];
	unsigned char m_flag;
};

class Rva001F8E45
{
public:
	void rva001F8E45(void* a1, void* a2);
private:
	_STL::vector<void*> m_vec;
};

void Rva001F8E45::rva001F8E45(void* a1, void* a2)
{
	_STL::vector<void*>& src = *(_STL::vector<void*>*)((char*)a2 + 0x1cc);
	m_vec.clear();
	for (void** it = (void**)src.begin(); it != (void**)src.end(); ++it) {
		Rva001F8E45Elem* e = (Rva001F8E45Elem*)*it;
		if (!e->m_flag)
			continue;
		const ModuleData* md = e->m_iface.getData(a1);
		((_STL::vector<const ModuleData*>&)m_vec).push_back(md);
	}
}
