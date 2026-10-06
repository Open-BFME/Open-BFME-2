// cl: /Ireference/shims/bfmelist /Oy /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /EHs-c-
// stlport
// ?rva0029D3FB@Rva0029D3FB@@QAEXXZ @0x0029D3FB 83B.
// List clearer like Rva0029D30A at +0x8A0 but at +0x8CC: circular
// _STL::list<int> holding holder pointers as ints; each holder carries the
// payload object pointer at +0, null-checked, slot00(0) on it, then operator
// delete the result plus the holder, then erase. Evidence: rowed
// list<int>::erase 0x00438539, rowed operator delete 0x0002FD60, callers
// 0x002A5C25 0x002A6102, prev/next.
#include <list>

class Rva0029D3FBPayload
{
public:
	virtual void *slot00(int flag);
};

struct Rva0029D3FBHolder
{
	Rva0029D3FBPayload *ptr;
};

class Rva0029D3FB
{
public:
	void rva0029D3FB();
	unsigned char m_pad[0x8CC];
	_STL::list<int> m_8CC; // +0x8CC
};

void __cdecl operator delete(void *p);

void Rva0029D3FB::rva0029D3FB()
{
	_STL::list<int>::iterator it = m_8CC.begin();
	while (it != m_8CC.end()) {
		int v = *it;
		Rva0029D3FBHolder *h = (Rva0029D3FBHolder *)v;
		if (h != 0) {
			void *q;
			if (h->ptr != 0)
				q = h->ptr->slot00(0);
			else
				q = 0;
			::operator delete(q);
			::operator delete(h);
		}
		it = m_8CC.erase(it);
	}
}
