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

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>

// The +4 member is spelled with its StringBase<char> pointers, not
// vector<void *>: retail's unwind action jumps to the 14-byte
// free-first-pointer body 0x0007FAB3, not vector<void *>'s /Od destructor
// 0x00027370. The clear still reaches the shared vector<void *> range erase.
namespace _STL {
template <> __declspec(dllimport) __forceinline void **vector<void *>::begin() { return _M_start; }
template <> __declspec(dllimport) __forceinline void **vector<void *>::end() { return _M_finish; }
}

class Rva00496F30
{
public:
	~Rva00496F30();
private:
	int m_00; // +0x00
	_STL::vector<StringBase<char> *> m_vec; // +0x04
};

Rva00496F30::~Rva00496F30()
{
	for (_STL::size_t i = 0; i < m_vec.size(); i++) {
		StringBase<char> *p = m_vec[i];
		if (p) {
			((AsciiString *)p)->~AsciiString();
			::operator delete(p);
		}
	}
	_STL::vector<void *> &cleared = reinterpret_cast<_STL::vector<void *> &>(m_vec);
	cleared.erase(cleared.begin(), cleared.end());
}
