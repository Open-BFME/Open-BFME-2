// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000AF183@@QAE@IABV?$allocator@H@_STL@@@Z @0x000AF183 58B
// Evidence: unlock lane, _Vector_base<short> shape via proxy 0x0014F3C4 and allocate 0x000AD722, caller 0x000AFAFB, ret 8.
namespace _STL
{
template <class _Tp>
class allocator;
template <>
class allocator<short>
{
public:
	short *allocate(unsigned int n, const void *hint) const;
};
template <>
class allocator<int>
{
public:
};
template <class _Value, class _Tp, class _Alloc>
class _STLP_alloc_proxy : public _Alloc
{
public:
	_Value _M_data;
	_STLP_alloc_proxy(const _Alloc &a, _Value p);
};
}

class Rva000AF183
{
public:
	Rva000AF183(unsigned int n, const _STL::allocator<int> &a);
private:
	short *m_start;
	short *m_finish;
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_end;
};

Rva000AF183::Rva000AF183(unsigned int n, const _STL::allocator<int> &a)
	: m_start(0), m_finish(0), m_end(a, 0)
{
	m_start = ((const _STL::allocator<short> &)m_end).allocate(n, 0);
	m_finish = m_start;
	m_end._M_data = (unsigned int)(m_start + n);
}
