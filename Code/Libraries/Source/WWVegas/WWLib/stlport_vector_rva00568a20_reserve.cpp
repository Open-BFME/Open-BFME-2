// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?reserve@?$vector@VRva00568A20@@V?$allocator@VRva00568A20@@@_STL@@@_STL@@QAEXI@Z @0x00569E1D 116B.
// STLport 4.5.3 vector<Rva00568A20>::reserve. Capacity and size via idiv 0xC stride.
// Reuses rowed helpers: _M_allocate_and_copy PBV at 0x00568D68 and _M_clear BfmePoolRef10
// at 0x00569DFF plus BfmeE12 allocate at 0x00395928 as ICF twins for the 12-byte element.
// Caller at 0x0056A54F makes 0x0056A4AA ready. Flags from stlport_vector_stringrecord_111acf
// sibling which lands the same 116B reserve shape under /O1 /G7 no-EH.
struct BfmePoolHolder88;
class BfmePoolRef10
{
	BfmePoolHolder88 *m_target;
public:
	BfmePoolRef10(const BfmePoolRef10 &other);
	~BfmePoolRef10();
};
class Rva00568A20
{
public:
	Rva00568A20(const Rva00568A20 &other);
	~Rva00568A20();
private:
	BfmePoolRef10 m_pool;
	int m_word;
	unsigned char m_flag;
};
struct BfmeE12
{
	int a[3];
};
namespace _STL
{
template <class T>
class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
template <class T, class A>
class vector
{
public:
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef unsigned int size_type;
	pointer m_start;
	pointer m_finish;
	struct Proxy : public allocator<T>
	{
		T *m_data;
	} m_end;
	void reserve(size_type n);
protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
};
}
namespace _STL
{
template <>
class vector<BfmePoolRef10, allocator<BfmePoolRef10> >
{
public:
	typedef BfmePoolRef10 *pointer;
	pointer m_start;
	pointer m_finish;
	struct ProxyB : public allocator<BfmePoolRef10>
	{
		pointer m_data;
	} m_end;
protected:
	void _M_clear();
	friend class vector<Rva00568A20, allocator<Rva00568A20> >;
};
}
void _STL::vector<Rva00568A20, _STL::allocator<Rva00568A20> >::reserve(size_type n)
{
	size_type cap = size_type(m_end.m_data - m_start);
	if (cap < n) {
		size_type old_size = size_type(m_finish - m_start);
		pointer tmp;
		if (m_start) {
			tmp = _M_allocate_and_copy(n, (const_pointer)m_start, (const_pointer)m_finish);
			((vector<BfmePoolRef10, allocator<BfmePoolRef10> > *)this)->_M_clear();
		} else {
			tmp = (pointer)reinterpret_cast<const allocator<BfmeE12> &>((const allocator<Rva00568A20> &)m_end).allocate(n, 0);
		}
		m_start = tmp;
		m_finish = tmp + old_size;
		m_end.m_data = tmp + n;
	}
}
