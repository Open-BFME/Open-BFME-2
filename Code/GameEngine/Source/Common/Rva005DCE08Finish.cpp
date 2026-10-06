// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??1Rva005DCE08@@QAE@XZ @0x005DCE08 (90 bytes).
// Non-virtual destructor of an object holding a _STL::vector<Rva005DCE08Elem*>
// at +0x04 (4-byte scalar member ahead of it). Retail walks begin..end and
// releases each element through the rowed global operator delete 0x002FD60 with
// the adjusted pointer from the element's virtual slot 0; the vector's own
// destructor then frees the buffer through the rowed free 0x00030830. The
// EH frame is the vector member's destructor state (and [ebp-0x10] is `this`).
// Evidence: callers 0x005AD948 and 0x005ADA66 are deleting-destructor shapes;
// the member's begin/end/free is the STLport _Vector_base layout proven by the
// adjacent landed Rva005DCDD9 ctor (same +0x04 vector) and Rva0042643D dtor.
// Identity is address-derived; no target evidence names the class.
#include <vector>

class Rva005DCE08Elem
{
public:
	virtual void *v00(int v);
};

class Rva005DCE08
{
public:
	~Rva005DCE08();
private:
	char m_pad00[4];
	_STL::vector<Rva005DCE08Elem *> m_vec; // +0x04
};

Rva005DCE08::~Rva005DCE08()
{
	for (Rva005DCE08Elem **p = m_vec.begin(); p != m_vec.end(); ++p)
		::operator delete(*p ? (*p)->v00(0) : 0);
}
