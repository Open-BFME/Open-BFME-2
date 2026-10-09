// cl: /O1 /G7 /Oy- /MD
// stlport
// Native4F904F..4F907740B guards empty subranges and forwards them to the
// existing whole131B STLport __inplace_merge_aux. Native183B4F922C initializes
// and copies a one-byte stateless comparator, rather than supplying a fourth
// integer. Rva004F9185Cmp is the existing sort family's opaque stateless view;
// the legacy merge provider's less<Rva004F8C16Element> is an ABI carrier with
// the same empty representation. Neither spelling asserts an original name.
#include <functional>
struct Rva004F8C16Element;
struct Rva004F9185Cmp {};
namespace _STL {
template<class Iterator,class Value,class Distance,class Compare>
void __inplace_merge_aux(Iterator,Iterator,Iterator,Value *,Distance *,Compare);
}
void rva004F904F(Rva004F8C16Element *first,Rva004F8C16Element *middle,Rva004F8C16Element *last,Rva004F9185Cmp cmp)
{
 if(first==middle || middle==last)return;
 _STL::__inplace_merge_aux(first,middle,last,(Rva004F8C16Element *)0,(int *)0,*reinterpret_cast<const _STL::less<Rva004F8C16Element> *>(&cmp));
}
