// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
// ?rva00279677@Rva00279677@@QAEXXZ @0x00279677 65B
// Vector clear at +0x36c: deletes each element via first virtual (int 0) then operator delete, then erases range.
// Evidence: callees rowed ??3@YAXPAX@Z erase vector<void*>; prev/next OpaqueScalarDeletingDtorsB05; caller 0x00530241.
// Neighbour flags /O1 /DNDEBUG /MD copied.
#include <vector>

class RvaVecElem
{
public:
	virtual void *func0(int arg);
};

class Rva00279677
{
public:
	void rva00279677();
private:
	char m_pad[0x36c];
	_STL::vector<void *> m_vec;
};

void Rva00279677::rva00279677()
{
	for (void **it = m_vec.begin(); it != m_vec.end(); ++it) {
		void *p = *it;
		RvaVecElem *e = (RvaVecElem *)p;
		void *q = e ? e->func0(0) : (void *)0;
		::operator delete(q);
	}
	_STL::vector<void *> &v = m_vec;
	v.erase(v.begin(), v.end());
}
