// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ??4?$vector@URva005F8F96@@V?$allocator@URva005F8F96@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z, retail 0x001537d8, 180 bytes. Banked partial (score 0.98) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Vector assign 3-path sar 3 stride 8 via allocate_and_copy 0x153489 plus clear 0x15373C plus copy 0x1534B6 plus Destroy 0x153470 plus uninit_copy 0x153425.
// Evidence: cmp ebx esi je then sar 3 capacity check jbe then allocate_and_copy plus clear plus copy plus Destroy plus copy plus uninit_copy then finish update; caller 0x1539D8 loops 6 vectors; callees rowed.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
struct Rva005F8F96
{
	~Rva005F8F96();
	TargetRef00217D4C *m_00;
	int m_04;
};
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};
struct Rva00153252
{
	TreeHintRef00217D4C m_00;
	int m_04;
};
class Rva00468520;
struct Tag
{
	Tag() {}
};
struct BfmeE8
{
	int a;
	int b;
};
Rva00153252 *Rva001534B6Copy(Rva00153252 *first, Rva00153252 *last, Rva00153252 *result, const Tag &tag);
void _DestroyRva005F8F96(Rva005F8F96 *first, Rva005F8F96 *last);
Rva00468520 *Rva00153425Copy(Rva00468520 *first, Rva00468520 *last, Rva00468520 *result, const Tag &tag);
namespace _STL
{
template <class T> class allocator
{
public:
	T *allocate(unsigned int n, const void *hint) const;
};
template <class T, class Alloc> class vector
{
	template <class U, class A> friend class vector;
public:
	typedef T *pointer;
	typedef const T *const_pointer;
	typedef unsigned int size_type;
	vector &operator=(const vector &x);
	pointer begin() { return m_start; }
	const_pointer begin() const { return m_start; }
	pointer end() { return m_finish; }
	const_pointer end() const { return m_finish; }
	size_type size() const { return size_type(m_finish - m_start); }
	size_type capacity() const { return size_type(m_endOfStorage - m_start); }
protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
	void _M_clear();
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};
template <class ForwardIter> void _Destroy(ForwardIter first, ForwardIter last);
}
inline _STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> > &_STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> >::operator=(const vector &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		if (xsize > capacity())
		{
			BfmeE8 *tmpB = reinterpret_cast<_STL::vector<BfmeE8, _STL::allocator<BfmeE8> > *>(this)->_M_allocate_and_copy<Rva00468520 *>(xsize, (Rva00468520 *)x.begin(), (Rva00468520 *)x.end());
			pointer tmp = (pointer)tmpB;
			_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			Rva00153252 *new_finish = Rva001534B6Copy((Rva00153252 *)x.begin(), (Rva00153252 *)x.end(), (Rva00153252 *)m_start, Tag());
			_STL::_Destroy((Rva005F8F96 *)new_finish, (Rva005F8F96 *)m_finish);
		}
		else
		{
			Rva001534B6Copy((Rva00153252 *)x.begin(), (Rva00153252 *)(x.begin() + size()), (Rva00153252 *)m_start, Tag());
			Rva00153425Copy((Rva00468520 *)(x.begin() + size()), (Rva00468520 *)x.end(), (Rva00468520 *)m_finish, Tag());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}
template _STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> > &_STL::vector<Rva005F8F96, _STL::allocator<Rva005F8F96> >::operator=(const vector &);
