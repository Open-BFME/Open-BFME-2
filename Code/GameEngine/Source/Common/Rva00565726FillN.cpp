// cl: /DNDEBUG /MD
// ??$__uninitialized_fill_n@PAVRva004E18A2@@IV1@@_STL@@YAPAVRva004E18A2@@PAV1@IABV1@ABU__false_type@0@@Z 0x00565726 37B evidence: chain via 0x0052BD16 just landed; stride 0x10 via 16B opaque; caller 0x00565F78; precedent Rva00565685FillN same flags recipe.
class Rva004E18A2
{
    char _m[16];
public:
    Rva004E18A2(const Rva004E18A2 &that);
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
template Rva004E18A2 *_STL::__uninitialized_fill_n(Rva004E18A2 *, unsigned int, const Rva004E18A2 &, const _STL::__false_type &);
