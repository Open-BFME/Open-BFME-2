// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva00496F30@@QAE@XZ retail 0x00496F30 117B.
// Unlock body: landing it makes 0x0049703A/28 and 0x00497056/249 ready.
// Callers at 0x0049703D and 0x004970E0. No vptr store so non-virtual dtor.
// Layout: int at +0 plus _STL::vector<void *> at +4 holding StringBase<char>*
// elements. Body loops the vector by index deleting each element through the
// rowed StringBase releaseBuffer at 0x00036410 plus rowed operator delete at
// 0x0002FD60 then clears through rowed voidptr erase at 0x0031BD55 and frees
// through rowed _free at 0x00030830. Flags: /O1 for rep-free loop shape plus
// /EHs for the extern-C free state store plus static STLport so erase and
// free stay E8 to rows instead of IAT.

#include <vector>

template <typename T>
class StringBase
{
	void releaseBuffer();
	friend class Rva00496F30;
public:
	~StringBase();
	T *m_data;
};

class Rva00496F30
{
public:
	~Rva00496F30();
private:
	int m_00;
	_STL::vector<void *> m_vec;
};

Rva00496F30::~Rva00496F30()
{
	for (_STL::size_t i = 0; i < m_vec.size(); i++) {
		StringBase<char> *p = (StringBase<char> *)m_vec[i];
		if (p) {
			p->releaseBuffer();
			::operator delete(p);
		}
	}
	m_vec.clear();
}
