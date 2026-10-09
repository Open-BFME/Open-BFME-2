// cl: /O1 /Oy- /G7 /MD
// Native5414C2..5414E535B is the lookup wrapper used by the LookAt track.
// The66-byte provider5413B0 compares key0 and ignores its one-byte comparator.
// Its ABI declaration uses the existing provider spelling; precise source
// comparator/wrapper identity is unknown, so retain an address-derived name.
// Value initialization follows independently verified sibling540301.
struct BfmePod28 { int key; char frame[24]; };
// Native sibling54150A uses the same comparator/tag ABI and a20-byte record;
// its separate66-byte provider5413F2 independently establishes stride and key0.
struct BfmePod20 { int key; char frame[16]; };
namespace _STL {
template<class T> struct less {};
template<class F,class T,class C,class D>
F __lower_bound(F,F,const T &,C,D *);
}
BfmePod28 *rva005414C2(BfmePod28 *first,BfmePod28 *last,const BfmePod28 &key)
{
    return _STL::__lower_bound(first,last,key,_STL::less<BfmePod28>(),(int *)0);
}
BfmePod20 *rva0054150A(BfmePod20 *first,BfmePod20 *last,const BfmePod20 &key)
{
    return _STL::__lower_bound(first,last,key,_STL::less<BfmePod20>(),(int *)0);
}

