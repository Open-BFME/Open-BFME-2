// cl: /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003F209C@Rva003F209C@@QAEXXZ, retail 0x003F209C 20B.
// Clears the ScienceType vector at this+0x164 via rowed erase 0x00532803.
// Evidence: retail push [ecx+0x168]/add ecx 0x164/push [ecx]/call erase
// shows __thiscall clear of vector at +0x164; same layout as Rva003F2739Push;
// callees all rowed; callers 0x0020EE44 and 0x003F20E8.
#include <vector>

enum ScienceType
{
	SCIENCE_DUMMY = 0
};

class Rva003F209C
{
public:
	void rva003F209C();

private:
	char _pad[0x164];
	_STL::vector<ScienceType> m_vec; // +0x164
};

void Rva003F209C::rva003F209C()
{
	m_vec.clear();
}
