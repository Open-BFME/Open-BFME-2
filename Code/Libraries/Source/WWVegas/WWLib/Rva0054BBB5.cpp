// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// SimpleObjectIterator::insert (WorldBuilder name, SimpleObjectIterator.cpp line 62: deque push_back of the pair); 0x0054B414 (deque clear) is on the same class.
// stlport
//
// was ?rva0054BBB5@Rva0054BBB5@@QAEXHM@Z, retail 0x0054BBB5, 37 bytes.
// Packs (int, float) into BfmeE8 temp and deque push_back at this+0x14.
// Evidence: prev 0x0054B850 deque push_back rowed, retail movss plus
// lea [ebp-8] plus add ecx 0x14 plus ret 8, 15 callers.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <deque>

struct BfmeE8
{
	int a;
	float b;
};

// The existing cleanup provider names only the established eight-byte record
// width. Its external declaration preserves the native potentially-throwing
// member cleanup, including the base destructor's exceptional path.
struct BfmeTrivialDequeElement8 { unsigned char opaque[8]; };
namespace _STL {
template<> deque<BfmeTrivialDequeElement8,allocator<BfmeTrivialDequeElement8> >::~deque();
}

// Native tables C6A68C and C6A698 share the empty base destructor and two
// iterator slots. Keep the existing base owner spelling rather than guessing
// a new name. Its layout is four bytes; the derived cursor occupies +4..+14.
class Rva00549C74 {
public:
	virtual ~Rva00549C74() {}
	virtual int first() = 0;
	virtual int next() = 0;
};

class SimpleObjectIterator : public Rva00549C74
{
public:
	virtual ~SimpleObjectIterator();
	virtual int first();
	virtual int next();
	void insert(int a, float b);
	void rva0054B414();

private:
	_STL::deque<BfmeTrivialDequeElement8>::iterator m_cursor;
	_STL::deque<BfmeTrivialDequeElement8> m_deque;
};

// Native 54B81A..54B850: the deque cleanup at +14 and the base-vtable
// restoration independently establish the two destructor stages. The named
// insert, constructor call sites and the three-slot vtable establish this
// class; Zero Hour's ObjectIter.h supplies the empty-base destructor lead.
SimpleObjectIterator::~SimpleObjectIterator() {}

void SimpleObjectIterator::insert(int a, float b)
{
	BfmeE8 tmp;
	tmp.a = a;
	tmp.b = b;
	// Preserve the existing provider's typed ABI view over the proven 8-byte
	// deque storage. The original record type remains unrecovered.
	reinterpret_cast<_STL::deque<BfmeE8> &>(m_deque).push_back(tmp);
}

void SimpleObjectIterator::rva0054B414()
{
	return reinterpret_cast<_STL::deque<BfmeE8> &>(m_deque).clear();
}

// Existing native +4/+24 cursor/finish view, with integer result and optional
// numeric output. The original element identity is not established.
struct Rva0054A82C { int rva0054A82C(int *); };

// Vtable slot 1 at C6A69C; native 54B804..54B81A resets the sixteen-byte
// cursor from deque.begin(), then requests the next item without a numeric out.
int SimpleObjectIterator::first() {
	m_cursor = m_deque.begin();
	return reinterpret_cast<Rva0054A82C *>(this)->rva0054A82C(0);
}

// Vtable slot 2 at C6A6A0; native 54B7FC..54B804 delegates without resetting.
int SimpleObjectIterator::next() {
	return reinterpret_cast<Rva0054A82C *>(this)->rva0054A82C(0);
}
