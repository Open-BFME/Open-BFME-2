// cl: /MD
// ??0Rva0052C8AB@@QAE@ABV0@@Z 0x0052C8AB 68B evidence: Vector_base 0x00421D73 row E16; get_allocator 0x0021983A row AsciiString; uninit-copy 0x0052C2CA row Rva003A6360Record; caller 0x0052D555; sibling Rva005386F5Copy same recipe
struct BfmeE16 { float x, y, z, w; };
class Rva003A6360Record
{
	char _m[0x10];
public:
	Rva003A6360Record(const Rva003A6360Record &that);
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
};
template <class InputIter, class ForwardIter>
ForwardIter __uninitialized_copy(InputIter first, InputIter last, ForwardIter result, const __false_type &tag);
}
class Rva0052C8AB : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	Rva0052C8AB(const Rva0052C8AB &x);
};
Rva0052C8AB::Rva0052C8AB(const Rva0052C8AB &x)
	: _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >((x.m_finish - x.m_start), *(const _STL::allocator<BfmeE16> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	m_finish = (BfmeE16 *)_STL::__uninitialized_copy((Rva003A6360Record *)x.m_start, (Rva003A6360Record *)x.m_finish, (Rva003A6360Record *)m_start, _STL::__false_type());
}
