// cl: /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAVRva004E194E@@IV1@@_STL@@YAPAVRva004E194E@@PAV1@IABV1@ABU__false_type@0@@Z 0x005656E4 37B evidence: leaf caller 0x00565EC4; stride 0x14 via 20B opaque; _Construct 0x0052C3D7 rowed EH twin; precedent Rva00565685FillN same flags recipe.
class Rva004E194E
{
    char _m[20];
public:
    Rva004E194E(const Rva004E194E &that);
};
namespace _STL
{
struct __false_type {};
template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &)
{
    ForwardIter cur = first;
    for (; n > 0; --n, ++cur)
        _Construct(cur, x);
    return cur;
}
}
template Rva004E194E *_STL::__uninitialized_fill_n(Rva004E194E *, unsigned int, const Rva004E194E &, const _STL::__false_type &);
