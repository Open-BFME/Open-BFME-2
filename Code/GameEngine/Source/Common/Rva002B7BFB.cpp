// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
// ?rva002B7BFB@Rva002B7BFB@@QAEXXZ @0x002B7BFB 121B. Unlock: outer vector at
// +0x8C holds holders with inner vector at +0x1B8 of Rva003193D1; each inner
// element runs rowed 0x003193D1; then clears vector at +0x10C via rowed erase
// 0x0031BD55. Evidence: same erase as vslot clear precedent; caller at
// 0x002BD379 unblocks 0x002BD36D; prev/next share /O1 family.
#include <vector>
class Rva003193D1
{
public:
	void rva003193D1();
};
struct Rva002B7BFBOuter
{
	char m_pad[0x1B8];
	_STL::vector<Rva003193D1 *> m_1B8;
};
class Rva002B7BFB
{
public:
	void rva002B7BFB();
private:
	char m_pad00[0x8C];
	_STL::vector<Rva002B7BFBOuter *> m_8C;
	char m_pad98[0x10C - 0x98];
	_STL::vector<void *> m_10C;
};
void Rva002B7BFB::rva002B7BFB()
{
	for (unsigned int i = 0; i < m_8C.size(); ++i) {
		_STL::vector<Rva003193D1 *> &inner = m_8C[i]->m_1B8;
		for (unsigned int j = 0; j < inner.size(); ++j)
			inner[j]->rva003193D1();
	}
	m_10C.clear();
}
