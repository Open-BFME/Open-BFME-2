// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00214A8A@Rva00214A8A@@QAEXXZ @0x00214A8A 61B
// Vector clear with element deletion: iterates void* vector at +0xC deleting
// each non-null Rva002146F7 via its pinned dtor then erases the range.
// Evidence: callees dtor 0x004043FF pinned delete 0x0002FD60 erase 0x0031BD55
// rowed; callers 0x002305B7; container offset 0xC.
#include <vector>

class Rva002146F7
{
public:
	~Rva002146F7();
};

class Rva00214A8A
{
public:
	void rva00214A8A();
	char m_pad00[0x0c];
	_STL::vector<void *> m_vec;
};

void Rva00214A8A::rva00214A8A()
{
	for (_STL::vector<void *>::iterator it = m_vec.begin(); it != m_vec.end(); ++it)
		delete (Rva002146F7 *)*it;
	m_vec.clear();
}
