// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva004E5A78@@QAE@XZ @0x004E5A78 (118B)
// Destructor over vector<void*>: deletes each element via Rva004E5821 cleanup
// plus operator delete, then erases the range; storage freed by vector dtor.
// Evidence: unlock lane, callees rowed, callers 0x004E5AEE deleting dtor and
// 0x004E5CB0 deleter both call here.
#include <vector>

class Rva004E5821
{
public:
	void rva004E5821();
};

class Rva004E5A78
{
public:
	_STL::vector<void *> m_vec;
	~Rva004E5A78();
};

Rva004E5A78::~Rva004E5A78()
{
	for (unsigned int i = 0; i < m_vec.size(); ++i) {
		Rva004E5821 *p = (Rva004E5821 *)m_vec[i];
		if (p != 0) {
			p->rva004E5821();
			::operator delete(p);
		}
	}
	m_vec.erase(m_vec.begin(), m_vec.end());
}
