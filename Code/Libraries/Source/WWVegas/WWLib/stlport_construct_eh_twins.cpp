// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
//
// STLport _Construct<T> placement copies with an EH frame, 45 bytes each, for
// three address-named classes whose copy constructors are rowed:
//
//   0x004157E1  T = Rva0041579E  (copy ctor 0x0041579E, Rva0041573FCopy.cpp)
//   0x0052C1D6  T = Rva002E0A0A  (copy ctor 0x002E0A0A, Rva002E0A0ACopyCtor.cpp)
//   0x0052C3D7  T = Rva004E194E  (copy ctor 0x0052BE96, Rva004E194ECopyCtor.cpp)
//
// Each is an EH-framed twin of the rowed _Construct<GenericObjectCreationNugget::AnimSet>
// (0x001F06B9, ObjectCreationList.cpp), identical except for its copy call and
// its own __ehhandler; the copy call names T. StlportConstructEhSiblings.cpp's
// two _Construct rows have this shape.
#include <memory>
#include <new>
#include "ascii_string.h"
class Rva0041579E
{
public:
	Rva0041579E(const Rva0041579E &other);
};
class Rva002E0A0A {
    char opaque[36];
public:
    Rva002E0A0A(const Rva002E0A0A &);
    Rva002E0A0A &operator=(const Rva002E0A0A &);
    virtual ~Rva002E0A0A();
};
namespace _STL {
template <> void _Construct<Rva002E0A0A, Rva002E0A0A>(
    Rva002E0A0A *, const Rva002E0A0A &);
}
class Rva004E194E
{
public:
	virtual ~Rva004E194E();
	Rva004E194E(const Rva004E194E &other);
private:
	int m_04;
	int m_08;
	AsciiString m_0C;
	unsigned char m_10;
};

namespace _STL
{
template <class _T1, class _T2>
void _Construct(_T1 *, const _T2 &);
template <> void _Construct<Rva004E194E, Rva004E194E>(Rva004E194E *, const Rva004E194E &);
}
template void _STL::_Construct<Rva0041579E, Rva0041579E>(Rva0041579E *, const Rva0041579E &);
// Out-of-line definitions: the unit's loops call these two rather than inlining them.
namespace _STL { template <> void _Construct<Rva002E0A0A, Rva002E0A0A>(Rva002E0A0A *p, const Rva002E0A0A &v) { new (p) Rva002E0A0A(v); } }
namespace _STL { template <> void _Construct<Rva004E194E, Rva004E194E>(Rva004E194E *p, const Rva004E194E &v) { new (p) Rva004E194E(v); } }
