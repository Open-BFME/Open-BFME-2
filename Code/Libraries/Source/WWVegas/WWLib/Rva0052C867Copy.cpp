// cl: /MD
// ??0Rva0052C867@@QAE@ABV0@@Z 0x0052C867 68B evidence: Vector_base 0x00421D73 row E16; get_allocator 0x0021983A row AsciiString; uninit-copy 0x0052C2A4 row Rva004E18A2; caller 0x0052D627; sibling Rva0052C8ABCopy same recipe
struct BfmeE16 { float x, y, z, w; };
class Rva004E18A2
{
	char _m[0x10];
public:
	Rva004E18A2(const Rva004E18A2 &that);
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
class Rva0052C867 : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	Rva0052C867(const Rva0052C867 &x);
};
Rva0052C867::Rva0052C867(const Rva0052C867 &x)
	: _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >((x.m_finish - x.m_start), *(const _STL::allocator<BfmeE16> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	m_finish = (BfmeE16 *)_STL::__uninitialized_copy((Rva004E18A2 *)x.m_start, (Rva004E18A2 *)x.m_finish, (Rva004E18A2 *)m_start, _STL::__false_type());
}
