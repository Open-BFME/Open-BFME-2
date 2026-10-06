// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport _Construct<T, T> (placement copy through T's copy constructor, EH
// framed, with the null test placement new emits) for four records whose
// copy constructors are rowed:
//   0x0038350D Rva003829E5  -> copy ctor 0x00382C2D
//   0x0038353A Rva00382BF0  -> copy ctor 0x00382BF0
//   0x004398AB Rva004395EC  -> copy ctor 0x0043964D
//   0x004BA219 Rva004BA1D0  -> copy ctor 0x004BA1D0
// Each 45B body was banked as a hand-written `if (p) new (p) T(v)` free
// function one byte order away: retail stores the EH state before the null
// test, which is what the vendored _Construct (the precedent is the rowed
// _Construct<Rva003371B1> 0x00337313) emits and the explicit if does not.
// The struct/class keyword of each record follows its copy-constructor row.
#include <memory>
class Rva003829E5
{
public:
	Rva003829E5(const Rva003829E5 &other);
};
struct Rva00382BF0
{
	Rva00382BF0(const Rva00382BF0 &other);
};
struct Rva004395EC
{
	Rva004395EC(const Rva004395EC &other);
};
class Rva004BA1D0
{
public:
	Rva004BA1D0(const Rva004BA1D0 &other);
};
template void _STL::_Construct<Rva003829E5, Rva003829E5>(Rva003829E5 *, const Rva003829E5 &);
template void _STL::_Construct<Rva00382BF0, Rva00382BF0>(Rva00382BF0 *, const Rva00382BF0 &);
template void _STL::_Construct<Rva004395EC, Rva004395EC>(Rva004395EC *, const Rva004395EC &);
template void _STL::_Construct<Rva004BA1D0, Rva004BA1D0>(Rva004BA1D0 *, const Rva004BA1D0 &);
