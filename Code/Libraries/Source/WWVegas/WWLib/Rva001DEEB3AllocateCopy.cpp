// cl: /DNDEBUG /MD
// ?rva001DEEB3@Rva001DEEB3@@QAEPAVBfmePod48@@IPAURva001DF3F1Element@@1@Z @0x001DEEB3 45B: allocate plus uninitialized_copy 0x001DEDD4; allocator at +8; callers 0x001DEFC8 unblocks 0x001DEF89.
struct BfmePod48
{
	char _m[0x30];
};
struct Rva001DF3F1Element
{
	Rva001DF3F1Element(const Rva001DF3F1Element &that);
	char _m[0x30];
};
namespace _STL
{
struct __false_type {};
template <class T>
class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
template <class I, class F>
F __uninitialized_copy(I first, I last, F dest, const __false_type &);
}
class Rva001DEEB3
{
public:
	void *rva001DEEB3(unsigned int n, Rva001DF3F1Element *first, Rva001DF3F1Element *last);
private:
	char m_pad[8];
	_STL::allocator<BfmePod48> m_alloc;
};

void *Rva001DEEB3::rva001DEEB3(unsigned int n, Rva001DF3F1Element *first, Rva001DF3F1Element *last)
{
	BfmePod48 *p = m_alloc.allocate(n, 0);
	char dummy;
	_STL::__uninitialized_copy(first, last, (Rva001DF3F1Element *)p, *(const _STL::__false_type *)&dummy);
	return p;
}
