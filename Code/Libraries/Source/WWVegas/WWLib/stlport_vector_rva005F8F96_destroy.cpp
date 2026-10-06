// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$_Destroy@PAURva005F8F96@@@_STL@@YAXPAURva005F8F96@@0@Z, retail 0x00153470, 25 bytes.
// Range destroy for 8-byte Rva005F8F96 holder (TargetRef pointer at +0 whose dtor
// is rowed at 0x005F8F96 plus int at +4): strides 8 calling that dtor. Same 25B loop
// shape as rowed Rva0027EA49 _Destroy at 0x00281AD4. Emitted via explicit _Destroy
// instantiation over the rowed dtor; callers are at 0x00153704 0x00153744 0x00153843.
#include <vector>
struct TargetRef00217D4C { virtual void *destroy(unsigned int flags); int references; };
struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
	int m_04;
};

template void _STL::_Destroy<Rva005F8F96 *>(Rva005F8F96 *, Rva005F8F96 *);
