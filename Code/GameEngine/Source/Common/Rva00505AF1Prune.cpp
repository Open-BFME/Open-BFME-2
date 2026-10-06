// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?rva00505AF1@Rva00505AF1@@QAEXXZ, retail 0x00505AF1, 201 bytes.
// Evidence: 4 voidptr vectors at +0x10 +0x28 +0x40 +0x58 pruned via byte at +0x28 virtual slot0(0) plus rowed delete 0x0002FD60 and rowed erase 0x001FF51F; caller 0x005069B7.
#include <vector>

class Rva00505AF1Elem
{
public:
	virtual void *rva(int);
	char m_pad[0x24];
	unsigned char m_28;
};

class Rva00505AF1
{
	char m_00[0x10];
	_STL::vector<Rva00505AF1Elem *> m_10;
	char m_1C[12];
	_STL::vector<Rva00505AF1Elem *> m_28;
	char m_34[12];
	_STL::vector<Rva00505AF1Elem *> m_40;
	char m_4C[12];
	_STL::vector<Rva00505AF1Elem *> m_58;
public:
	void rva00505AF1();
};

void Rva00505AF1::rva00505AF1()
{
	for (_STL::vector<Rva00505AF1Elem *>::iterator it = m_10.begin(); it != m_10.end(); ) {
		Rva00505AF1Elem *e = *it;
		if (e->m_28 != 0) {
			void *p = e->rva(0);
			::operator delete(p);
			it = (_STL::vector<Rva00505AF1Elem *>::iterator)(((_STL::vector<void *> *)&m_10)->erase((void **)it));
		} else {
			++it;
		}
	}
	for (_STL::vector<Rva00505AF1Elem *>::iterator it = m_28.begin(); it != m_28.end(); ) {
		Rva00505AF1Elem *e = *it;
		if (e->m_28 != 0) {
			void *p = e->rva(0);
			::operator delete(p);
			it = (_STL::vector<Rva00505AF1Elem *>::iterator)(((_STL::vector<void *> *)&m_28)->erase((void **)it));
		} else {
			++it;
		}
	}
	for (_STL::vector<Rva00505AF1Elem *>::iterator it = m_40.begin(); it != m_40.end(); ) {
		Rva00505AF1Elem *e = *it;
		if (e->m_28 != 0) {
			void *p = e->rva(0);
			::operator delete(p);
			it = (_STL::vector<Rva00505AF1Elem *>::iterator)(((_STL::vector<void *> *)&m_40)->erase((void **)it));
		} else {
			++it;
		}
	}
	for (_STL::vector<Rva00505AF1Elem *>::iterator it = m_58.begin(); it != m_58.end(); ) {
		Rva00505AF1Elem *e = *it;
		if (e->m_28 != 0) {
			void *p = e->rva(0);
			::operator delete(p);
			it = (_STL::vector<Rva00505AF1Elem *>::iterator)(((_STL::vector<void *> *)&m_58)->erase((void **)it));
		} else {
			++it;
		}
	}
}
