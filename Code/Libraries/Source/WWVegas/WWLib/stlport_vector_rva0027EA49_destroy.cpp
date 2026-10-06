// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva0027EA49@@@_STL@@YAXPAURva0027EA49@@0@Z, retail 0x00281AD4, 25 bytes.
// Range destroy for 8-byte Rva0027EA49 holder (int at +0 plus TargetRef pointer at +4
// whose dtor is rowed at 0x0027EA49): strides 8 calling that dtor. Same 25B loop shape
// as rowed Rva0048130E _Destroy at 0x00481595. Emitted via explicit _Destroy instantiation
// over the rowed dtor; callers are vector dtors at 0x002830D5 and 0x00308C13.
#include <vector>
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva0027EA49
{
	~Rva0027EA49();
	int m_00;
	TargetRef00217D4C *m_04;
};

template void _STL::_Destroy<Rva0027EA49 *>(Rva0027EA49 *, Rva0027EA49 *);

// vector dtor (retail 0x002830D5): byte-identical explicit member
// instantiation calling the _Destroy above and _free.
template _STL::vector<Rva0027EA49>::~vector();
