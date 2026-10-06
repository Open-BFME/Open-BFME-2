// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0?$list@UBfmeStringRecord002B4DC1@@V?$allocator@UBfmeStringRecord002B4DC1@@@_STL@@@_STL@@QAE@I@Z @ 0x002B8FF3 (106B).
// list<BfmeStringRecord002B4DC1> fill ctor size_type only; List_base via folded Coord3D row 0x00280A8D,
// fill insert via rowed 0x002B815B, wide temp teardown via 0x00036E70. Evidence: callees rowed, shape matches
// list<UnicodeString> fill ctor precedent 0x0043C072.
#include <list>

template <typename T> class StringBase
{
	friend struct BfmeStringRecord002B4DC1;
private:
	void releaseBuffer();
	void *m_data;
};

struct BfmeStringRecord002B4DC1
{
	StringBase<unsigned short> m_head;
	int m_a;
	int m_b;
	BfmeStringRecord002B4DC1() { m_head.m_data = 0; m_a = 0; m_b = 3; }
	~BfmeStringRecord002B4DC1() { m_head.releaseBuffer(); }
};

template _STL::list<BfmeStringRecord002B4DC1, _STL::allocator<BfmeStringRecord002B4DC1> >::list(unsigned int);
