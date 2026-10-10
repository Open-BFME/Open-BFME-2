// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva003B1546@@UAE@XZ @0x003B1546 (144B):
// Virtual dtor with vtable 0x00C1ED1C over vector<void*> at +0x0C plus int
// at +0x18 plus GameEngineDeletingBase base (size 0x0C). Drains the vector
// element by element through virtual slot 0 with arg 0 plus global operator
// delete (same idiom as Rva00317BBB intrusive-list dtor), then clears the
// vector through rowed erase 0x0031BD55, zeroes +0x18, frees the buffer
// through the vector dtor (_free 0x00030830), then base dtor 0x001B4E74.
// Caller 0x003B17F3 is the ??_G. Evidence: unlock lane, all callees rowed.
#include <vector>

void __cdecl operator delete(void *p);

class AsciiStringMember {
public:
	~AsciiStringMember();
};

// Base dtor at 0x001B4E74 by its row name ??1SubsystemInterface@@UAE@XZ (SubsystemInterface.cpp).
class SubsystemInterface {
public:
	virtual ~SubsystemInterface();
private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

struct Rva003B1546Elem {
	virtual void *destroy(int flags);
};

class Rva003B1546 : public SubsystemInterface {
public:
	virtual ~Rva003B1546();
private:
	_STL::vector<void *, _STL::allocator<void *> > m_vec;
	int m_18;
};

Rva003B1546::~Rva003B1546()
{
	for (unsigned i = 0; i < m_vec.size(); ++i) {
		Rva003B1546Elem *p = (Rva003B1546Elem *)m_vec[i];
		void *mem;
		if (p != 0)
			mem = p->destroy(0);
		else
			mem = 0;
		::operator delete(mem);
	}
	_STL::vector<void *, _STL::allocator<void *> > *pv = &m_vec;
	pv->erase(pv->begin(), pv->end());
	m_18 = 0;
}
