// ?reserve@?$vector@URva004DA181Element@@V?$allocator@URva004DA181Element@@@_STL@@@_STL@@QAEXI@Z @0x004DA039 126B: STLport vector reserve for 340-byte element. Capacity and size via idiv 0x154; reuses rowed POD allocate_and_copy 0x004D9C1C and POD allocate 0x004D94B3 plus rowed Rva _M_clear 0x004DA01B. Caller 0x004DA426. Evidence: same shape as template reserve; retail calls POD helpers per packet.
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
struct BfmePod340 {
	int a[85];
};

struct Rva004DA181Element {
	char opaque[336];
	Rva004DA181Element(const Rva004DA181Element &);
	Rva004DA181Element &operator=(const Rva004DA181Element &);
	virtual ~Rva004DA181Element();
};

namespace _STL {
template <class T>
class allocator {
public:
	T *allocate(unsigned int n, const void *hint) const;
};

template <class T, class A>
class vector {
public:
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef unsigned int size_type;
	pointer m_start;
	pointer m_finish;
	struct Proxy : public allocator<T> {
		T *m_data;
	} m_end;
	void reserve(size_type n);
protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
	void _M_clear();
	template <class U, class V> friend class vector;
};
}

void _STL::vector<Rva004DA181Element, _STL::allocator<Rva004DA181Element> >::reserve(size_type n)
{
	size_type cap = size_type(m_end.m_data - m_start);
	if (cap < n) {
		size_type old_size = size_type(m_finish - m_start);
		pointer tmp;
		if (m_start) {
			tmp = (pointer)((vector<BfmePod340, allocator<BfmePod340> > *)this)->_M_allocate_and_copy(
				n, (const BfmePod340 *)m_start, (const BfmePod340 *)m_finish);
			_M_clear();
		} else {
			tmp = (pointer)reinterpret_cast<const allocator<BfmePod340> &>((const allocator<Rva004DA181Element> &)m_end).allocate(n, 0);
		}
		m_start = tmp;
		m_finish = tmp + old_size;
		m_end.m_data = tmp + n;
	}
}
