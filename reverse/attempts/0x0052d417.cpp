// ??0Rva0052D417@@QAE@ABV0@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /EHsc /MD
// ??0Rva0052D417@@QAE@ABV0@@Z @0x0052D417 96B: vector copy ctor via rowed Vector_base PrereqUnitRec 0x005C8C37 then get_allocator AsciiString 0x0021983A then uninit-copy Rva005668E9Element 0x0052D3F1; caller 0x0052D669.
struct PrereqUnitRec
{
	unsigned int m_data[3];
};
struct Rva005668E9Element
{
	int a[3];
	Rva005668E9Element(const Rva005668E9Element &that);
};
class AsciiString;
namespace _STL {
template <class T> class allocator
{
public:
	allocator();
	allocator(const allocator &other);
	template <class U> allocator(const allocator<U> &) {}
	T *allocate(unsigned int n, const void *hint) const;
};
struct __false_type { __false_type() {} };
template <class T, class Alloc> class vector
{
public:
	allocator<T> get_allocator() const;
private:
	T *m_start;
	T *m_finish;
	T *m_end;
};
template <class T, class Alloc> class _Vector_base
{
protected:
	T *m_start;
	T *m_finish;
	T *m_end;
public:
	_Vector_base(unsigned int n, const allocator<T> &a);
	~_Vector_base();
};
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &tag);
}
class Rva0052D417 : public _STL::_Vector_base<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >
{
public:
	Rva0052D417(const Rva0052D417 &x);
};

Rva0052D417::Rva0052D417(const Rva0052D417 &x)
	: _STL::_Vector_base<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >((x.m_finish - x.m_start), *(const _STL::allocator<PrereqUnitRec> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	m_finish = (PrereqUnitRec *)_STL::__uninitialized_copy((const Rva005668E9Element *)x.m_start, (const Rva005668E9Element *)x.m_finish, (Rva005668E9Element *)m_start, _STL::__false_type());
}
