// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva000E016A@Rva000E016A@@QAEPAUBfmeE12@@IPAUCoord3D@@0@Z @0x000E016A 45B
// Evidence: unlock thiscall ret 0xc 3 args; allocator at +8 via rowed allocate<BfmeE12> 0x00395928; uninitialized_copy<Coord3D> rowed 0x00346C2D; callers 0x002CD0DB 0x003514E2 0x00390763; LINK BONUS via 0x0035149F.
struct BfmeE12
{
	char m_data[12];
};
#include "../../../Libraries/Include/Lib/Coord3D.h"
namespace _STL
{
struct __false_type { __false_type() {} };
template <class T>
class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &);
}
class Rva000E016A
{
public:
	BfmeE12 *rva000E016A(unsigned int n, Coord3D *first, Coord3D *last);
private:
	char m_pad[8];
	_STL::allocator<BfmeE12> m_alloc08;
};

BfmeE12 *Rva000E016A::rva000E016A(unsigned int n, Coord3D *first, Coord3D *last)
{
	BfmeE12 *buf = m_alloc08.allocate(n, 0);
	_STL::__uninitialized_copy(first, last, (Coord3D *)buf, _STL::__false_type());
	return buf;
}
