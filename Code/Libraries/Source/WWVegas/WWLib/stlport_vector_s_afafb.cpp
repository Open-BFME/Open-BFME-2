// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000AFAFB@@QAE@I@Z @0x000AFAFB 51B
// Evidence: chain lane, calls 0x000AF183 which you just landed plus fill_n 0x000AD8C9, ret 4, same shape as vector<short> ctor 0x00513DD0.
namespace _STL
{
template <class _Tp>
class allocator;
template <>
class allocator<int>
{
public:
};
template <class _Out, class _Size, class _Val>
_Out fill_n(_Out first, _Size n, const _Val &val);
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
protected:
	short *m_start;
	short *m_finish;
	_STL::_STLP_alloc_proxy<unsigned int, int, _STL::allocator<int> > m_end;
};

class Rva000AFAFB : public Rva000AF183
{
public:
	Rva000AFAFB(unsigned int n);
};

Rva000AFAFB::Rva000AFAFB(unsigned int n)
	: Rva000AF183(n, *(const _STL::allocator<int> *)((const char *)&n + 3))
{
	short *s = m_start;
	m_finish = _STL::fill_n(s, n, short());
}
