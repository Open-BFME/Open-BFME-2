// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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
// its own __ehhandler; the copy call names T. Flags as in
// StlportConstructEhSiblings.cpp, whose two _Construct rows have this shape.
#include <memory>
class Rva0041579E
{
public:
	Rva0041579E(const Rva0041579E &other);
};
class Rva002E0A0A
{
public:
	Rva002E0A0A(const Rva002E0A0A &other);
};
class Rva004E194E
{
public:
	Rva004E194E(const Rva004E194E &other);
};
template void _STL::_Construct<Rva0041579E, Rva0041579E>(Rva0041579E *, const Rva0041579E &);
template void _STL::_Construct<Rva002E0A0A, Rva002E0A0A>(Rva002E0A0A *, const Rva002E0A0A &);
template void _STL::_Construct<Rva004E194E, Rva004E194E>(Rva004E194E *, const Rva004E194E &);
