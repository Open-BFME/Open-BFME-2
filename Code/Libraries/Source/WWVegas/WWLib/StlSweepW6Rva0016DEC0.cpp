// STLport 4.5.3 reference member instantiation. Native 0x0016DEC0 is
// the iterator-result wrapper of the existing three-integer-key find at
// 0x0016D6A0. The full 21B wrapper and 108B helper verify independently.
// Gen_p12pod is the existing provider identity; the original application
// key and outer container names are not recovered here.
// cl: /O2 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

struct Gen_p12pod { int a[3]; };
inline bool compare_tail(const Gen_p12pod &a, const Gen_p12pod &b)
{
    const int a1 = a.a[1];
    return b.a[1] > a1 || (!(b.a[1] < a1) && a.a[2] < b.a[2]);
}
inline bool operator<(const Gen_p12pod &a, const Gen_p12pod &b)
{
    const int a0 = a.a[0];
    return b.a[0] > a0 || (!(b.a[0] < a0) && compare_tail(a, b));
}
namespace _STL {
typedef pair<const Gen_p12pod, int> GenP12Value;
typedef _Rb_tree<Gen_p12pod, GenP12Value, _Select1st<GenP12Value>,
    less<Gen_p12pod>, allocator<GenP12Value> > GenP12Tree;
template GenP12Tree::const_iterator GenP12Tree::find<Gen_p12pod>(const Gen_p12pod &) const;
}
