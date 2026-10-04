// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8A9F@Rva002B8A9F@@QAEXPAVModuleData@@@Z @0x002B8A9F 33B.
// Push-once ModuleData* into vector at +0x118 if byte at [p+0x75] clear
// then set it, via rowed push_back 0x004DFCB0. Callers in 0x002BA3DA etc.
#include <vector>

class ModuleData
{
public:
	char m_pad[0x75];
	unsigned char m_flag75;
};

class Rva002B8A9F
{
public:
	void rva002B8A9F(ModuleData *p);
private:
	char m_pad[0x118];
	_STL::vector<const ModuleData *> m_118;
};

void Rva002B8A9F::rva002B8A9F(ModuleData *p)
{
	if (p->m_flag75)
		return;
	p->m_flag75 = 1;
	m_118.push_back(p);
}
