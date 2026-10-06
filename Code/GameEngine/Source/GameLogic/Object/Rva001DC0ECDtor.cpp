// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1Rva001DC0EC@@QAE@XZ @0x001DC0EC 120B. Dtor: deletes Rva001DBC77 items
// out of list<int> at +0 via erase loop then AsciiString at +0xC then the
// list base. Evidence: deleting-dtor caller 0x001DC1E1 item dtor row
// 0x001DBC77 erase row 0x00438539 releaseBuffer row 0x00036410 and
// list-base dtor row 0x004EC395. Honest address name.
#include <list>

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva001DBC77
{
public:
	~Rva001DBC77();
};

void __cdecl operator delete(void *p);

class Rva001DC0EC
{
public:
	~Rva001DC0EC();
private:
	_STL::list<int, _STL::allocator<int> > m_list;
	char m_pad04[8];
	StringBase<char> m_string;
};

Rva001DC0EC::~Rva001DC0EC()
{
	_STL::list<int, _STL::allocator<int> >::iterator it = m_list.begin();
	while (it._M_node != m_list.end()._M_node) {
		Rva001DBC77 *p = (Rva001DBC77 *)*it;
		if (p != 0)
			delete p;
		it = m_list.erase(it);
	}
}
