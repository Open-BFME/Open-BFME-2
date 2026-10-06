// cl: /Ireference/shims/bfmelist /Oy /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /EHs-c-
// stlport
//
// ?rva0029D30A@Rva0029D30A@@QAEXXZ @0x0029D30A 72B.
// InGameUI-adjacent list clearer: circular _STL::list<int> at +0x8A0 holding
// object pointers as ints (payload at node +8); erase each node, call slot 0
// on the payload with 0, then operator delete the result. Evidence: rowed
// list<int>::erase 0x00438539, rowed operator delete 0x0002FD60, prev/next.

#include <list>

class Rva0029D30APayload
{
public:
	virtual void *slot00(int flag);
};

class Rva0029D30A
{
public:
	void rva0029D30A();
	unsigned char m_pad[0x8A0];
	_STL::list<int> m_8A0; // +0x8A0
};

void __cdecl operator delete(void *p);

void Rva0029D30A::rva0029D30A()
{
	_STL::list<int>::iterator it = m_8A0.begin();
	while (it != m_8A0.end()) {
		int v = *it;
		it = m_8A0.erase(it);
		Rva0029D30APayload *p = (Rva0029D30APayload *)v;
		void *q;
		if (p)
			q = p->slot00(0);
		else
			q = 0;
		::operator delete(q);
	}
}
