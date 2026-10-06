// cl: /MD
// ??0Rva005386F5@@QAE@ABV0@@Z @0x005386F5 68B
// Vector copy ctor via rowed Vector_base E16 size get_allocator AsciiString then Float4Record uninit-copy.
// Evidence: Vector_base 0x00421D73 row E16; get_allocator 0x0021983A row AsciiString; uninit-copy 0x005385F3 row Float4Record; caller 0x005388C2 holder copy; prev Rva005386B7Swap same layout.
struct BfmeE16 { float x, y, z, w; };
struct BfmeFloat4Record00469C61 { float x, y, z, w; };
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
class Rva005386F5 : public _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >
{
public:
	Rva005386F5(const Rva005386F5 &x);
};
Rva005386F5::Rva005386F5(const Rva005386F5 &x)
	: _STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> >((x.m_finish - x.m_start), *(const _STL::allocator<BfmeE16> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	m_finish = (BfmeE16 *)_STL::__uninitialized_copy((BfmeFloat4Record00469C61 *)x.m_start, (BfmeFloat4Record00469C61 *)x.m_finish, (BfmeFloat4Record00469C61 *)m_start, _STL::__false_type());
}
