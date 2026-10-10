// cl: /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003F2739@Rva003F2739@@QAEXW4ScienceType@@@Z, retail 0x003F2739 19B.
// Pushes a ScienceType value into the vector at this+0x164 via rowed
// push_back 0x002E01C6. Evidence: retail lea eax,[esp+4]/push/add ecx,0x164
// with ret 4 shows a __thiscall method taking ScienceType by value;
// neighbours LivingWorldRegionConnectionRva003F287F.cpp give TU and flags;
// caller 0x00319645 pushes [esi+0x20].
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

enum ScienceType
{
	SCIENCE_DUMMY = 0
};

class Rva003F2739
{
public:
	void rva003F2739(ScienceType v);

private:
	char _pad[0x164];
	_STL::vector<ScienceType> m_vec; // +0x164
};

void Rva003F2739::rva003F2739(ScienceType v)
{
	m_vec.push_back(v);
}
