// ?rva002B8AC0@Rva002B8AC0@@QAEXPBVModuleData@@@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Oy-
// stlport
// ?rva002B8AC0@Rva002B8AC0@@QAEXPBVModuleData@@@Z @0x002B8AC0 42B.
// Push ModuleData* into vector at +0xCC or +0xD8 based on byte at [p+8]
// via rowed push_back 0x004DFCB0. Callers in 0x00211396 0x00565148 etc.
#include <vector>

class ModuleData
{
public:
	unsigned char m_pad[8];
	unsigned char m_flag8;
};

class Rva002B8AC0
{
public:
	void rva002B8AC0(const ModuleData *p);
private:
	char m_pad[0xCC];
	_STL::vector<const ModuleData *> m_cc;
	_STL::vector<const ModuleData *> m_d8;
};

// ?rva002B8AC0@Rva002B8AC0@@QAEXPBVModuleData@@@Z present-unmatched
void Rva002B8AC0::rva002B8AC0(const ModuleData *p)
{
	if (p->m_flag8)
		m_d8.push_back(p);
	else
		m_cc.push_back(p);
}
