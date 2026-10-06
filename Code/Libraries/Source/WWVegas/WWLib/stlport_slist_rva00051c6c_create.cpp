// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00054E8BCreate@@YGPAURva00054E8BNode@@ABVRva00051C6C@@@Z @0x00054E8B 37B.
// slist node create: allocate 12 via rowed byte allocator plus zero next plus rowed _Construct.
// Evidence: unlock lane plus callees 0x000307F0 plus 0x00053FA4 plus caller 0x000556E7 plus size 12 with data at +4 matching Rva00051C6C 8B layout.
#include <memory>
class Rva00051C6C
{
public:
	Rva00051C6C(const Rva00051C6C &other);
};
namespace _STL {
template <typename T1, typename T2> void _Construct(T1 *, const T2 &) throw();
}
struct Rva00054E8BNode
{
	int m_next;
	Rva00051C6C m_data;
};
struct Rva00054E8BNode *__stdcall Rva00054E8BCreate(const Rva00051C6C &x)
{
	struct Rva00054E8BNode *p = (struct Rva00054E8BNode *)_STL::allocator<char>::allocate(12, 0);
	p->m_next = 0;
	_STL::_Construct(&p->m_data, x);
	return p;
}
