// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva005694CD@Rva00569393@@QAEXXZ @0x005694CD 118B.
// Teardown: drain-notify via the rowed 0x00569393 cursor loop, fan out the
// +0x2C slots through rowed 0x005C815B, release each slot through the rowed
// destructor 0x005C8565 plus ::operator delete (rowed 0x0002FD60) and null it, clear
// every element +0x10, then clear the +0x40/+0x4C STLport vectors via rowed
// two-iterator erase 0x0031BD55. Honest address-derived names.
#include <vector>
// Keep vector<void*> begin/end inline without emitting this unit's COMDAT
// copies: retail's out-of-line ones are the /Od bodies (0x00023B90, 0x00023BA0).
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end() { return this->_M_finish; }
}

class HostClass005C815B
{
public:
	void method_005C815B();
};

class Rva005C8565
{
public:
	~Rva005C8565();
};

struct Rva005694CDElem
{
	char m_pad[0x10];
	unsigned char m_flag;	// +0x10
	char m_pad2[3];
};

class Rva00569393
{
public:
	void rva00569393(void *tag);
	void rva005694CD();
private:
	char m_pad[0x14];
	Rva005694CDElem *m_begin;	// +0x14
	Rva005694CDElem *m_end;	// +0x18
	char m_pad2[0x10];
	void *m_slots[4];	// +0x2C
	char m_pad3[0x40 - 0x3C];
	::_STL::vector<void *, ::_STL::allocator<void *> > m_40;	// +0x40
	::_STL::vector<void *, ::_STL::allocator<void *> > m_4C;	// +0x4C
};

void Rva00569393::rva005694CD()
{
	rva00569393((void *)1);
	HostClass005C815B **slot = (HostClass005C815B **)m_slots;
	int left = 4;
	do {
		if (*slot != 0)
			(*slot)->method_005C815B();
		++slot;
	} while (--left != 0);
	Rva005C8565 **slot2 = (Rva005C8565 **)m_slots;
	left = 4;
	do {
		Rva005C8565 *slotObject = *slot2;
		if (slotObject != 0) {
			slotObject->~Rva005C8565();
			::operator delete(slotObject);
			*slot2 = 0;
		}
		++slot2;
	} while (--left != 0);
	for (Rva005694CDElem *element = m_begin; element != m_end; ++element)
		element->m_flag = 0;
	::_STL::vector<void *, ::_STL::allocator<void *> > *v40 = &m_40;
	v40->erase(v40->begin(), v40->end());
	::_STL::vector<void *, ::_STL::allocator<void *> > *v4C = &m_4C;
	v4C->erase(v4C->begin(), v4C->end());
}
