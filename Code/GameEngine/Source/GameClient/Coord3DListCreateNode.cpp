// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME2's coordinate lists use the STLport node layout: two links followed by
// three Real values. The shared Construct body and allocator<char> call are
// independently pinned by the retail node body.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
typedef float Real;
struct Coord3D { Real x, y, z; };
namespace _STL {
template <> void _Construct(Coord3D *p, const Coord3D &val);
template _List_node<Coord3D> *list<Coord3D>::_M_create_node(const Coord3D &);
}
