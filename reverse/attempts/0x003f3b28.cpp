// ?rva003F3B28@Rva003F3AB5@@QAEXI@Z
// partial score=0.89201 date=2026-10-08
// cl: /O1 /G7 /Oy- /MD /EHsc /D_CRTIMP=
struct BfmeE16 {float x,y,z,w;};
namespace _STL {
template<class T>class allocator {public:allocator(){}};
template<class T,class A>class _Vector_base {public:_Vector_base(const A&)throw();T*begin,*end,*capacity;};
}
typedef _STL::allocator<BfmeE16> HeaderAllocator;
struct DynamicPortalLink:public _STL::_Vector_base<BfmeE16,HeaderAllocator> {
 __forceinline DynamicPortalLink(const HeaderAllocator &a=HeaderAllocator())throw():_STL::_Vector_base<BfmeE16,HeaderAllocator>(a){}
 DynamicPortalLink(const DynamicPortalLink&);
 ~DynamicPortalLink()throw();
};
class Rva003F3AB5 {public:void rva003F3AB5(unsigned,DynamicPortalLink);void rva003F3B28(unsigned);};
void Rva003F3AB5::rva003F3B28(unsigned n){rva003F3AB5(n,DynamicPortalLink());}
