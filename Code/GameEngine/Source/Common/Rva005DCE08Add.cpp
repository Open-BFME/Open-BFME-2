// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva005DCE62@Rva005DCE08@@QAEXPAVRva00573E7C@@@Z @0x005DCE62 (16 bytes).
// Adds one order pointer to the vector at this+0x04 via the rowed
// vector<const ModuleData*>::push_back 0x004DFCB0. Layout proven by the
// neighbouring Rva005DCE08 dtor (same +0x04 vector) and the caller
// 0x005AE084 in Rva005ADA40::rva005ADE1D which passes an Rva00573E7C*.
// Identity is address-derived; pin names the class and signature.
#include <vector>

class ModuleData;
class Rva00573E7C;

class Rva005DCE08
{
public:
	void rva005DCE62(Rva00573E7C *order);
private:
	char m_pad00[4];
	_STL::vector<const ModuleData *> m_vec; // +0x04
};

void Rva005DCE08::rva005DCE62(Rva00573E7C *order)
{
	m_vec.push_back(*(const ModuleData **)&order);
}
