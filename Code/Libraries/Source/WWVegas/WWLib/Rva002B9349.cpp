// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva002B9349@Rva002B9349@@QAEXHH@Z @0x002B9349 61B.
// Flat-map insert-or-assign over vector<BfmeE8> at +0x10: linear search
// for key then store value, else push_back the pair.
// Evidence: leaf lane; callee rowed push_back 0x00539A2E; caller at
// 0x002BE6E4; same search-plus-push shape as retail.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct BfmeE8 {
	int a, b;
};

class Rva002B9349
{
public:
	void rva002B9349(int key, int value);
private:
	char m_pad00[0x10];
	_STL::vector<BfmeE8> m_vec10;
};

void Rva002B9349::rva002B9349(int key, int value)
{
	BfmeE8 *finish = m_vec10.end();
	BfmeE8 *first = m_vec10.begin();
	for (; first != finish; ++first) {
		if (first->a == key) {
			first->b = value;
			return;
		}
	}
	BfmeE8 e;
	e.b = value;
	e.a = key;
	m_vec10.push_back(e);
}
