// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva004E5A78@@QAE@XZ @0x004E5A78 (118B)
// Destructor over vector<void*>: deletes each element via Rva004E5821 cleanup
// plus operator delete, then erases the range; storage freed by vector dtor.
// Evidence: unlock lane, callees rowed, callers 0x004E5AEE deleting dtor and
// 0x004E5CB0 deleter both call here.
#include "IngameNoticeDisplayVector.h"

class DisplayString;
class Rva004E5821
{
public:
	void rva004E5821();
	void *rva004E58F5(unsigned int flags);
private:
	int m_00; // +0x00
	DisplayString *m_04; // +0x04
};

// Not vector<void *>: retail's unwind action for the member jumps to the
// 14-byte free-first-pointer body 0x0007FAB3, not vector<void *>'s /Od
// destructor 0x00027370; only the shared range erase uses that spelling.
class Rva004E5A78
{
public:
	~Rva004E5A78();
	_STL::vector<Rva004E5821 *> m_vec; // +0x00
};

Rva004E5A78::~Rva004E5A78()
{
	for (unsigned int i = 0; i < m_vec.size(); ++i) {
		Rva004E5821 *p = m_vec[i];
		if (p != 0) {
			p->rva004E5821();
			::operator delete(p);
		}
	}
	_STL::vector<void *> &erased = reinterpret_cast<_STL::vector<void *> &>(m_vec);
	erased.erase(erased.begin(), erased.end());
}
