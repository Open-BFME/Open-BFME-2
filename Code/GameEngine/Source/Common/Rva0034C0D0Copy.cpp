// cl: /MD
// ??0Rva0034C0D0@@QAE@ABV0@@Z @0x0034C0D0 71B
// Vector copy ctor via rowed Vector_base PrereqUnitRec then get_allocator AsciiString then Coord3D uninit-copy.
// Evidence: Vector_base 0x005C8C37 row PrereqUnitRec; get_allocator 0x0021983A row AsciiString; uninit-copy 0x00346C2D row Coord3D; caller 0x00354B44.
struct PrereqUnitRec
{
	unsigned int m_data[3];
};
struct Coord3D
{
	float x, y, z;
	Coord3D(const Coord3D &that);
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
class Rva0034C0D0 : public _STL::_Vector_base<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >
{
public:
	Rva0034C0D0(const Rva0034C0D0 &x);
};

Rva0034C0D0::Rva0034C0D0(const Rva0034C0D0 &x)
	: _STL::_Vector_base<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >((x.m_finish - x.m_start), *(const _STL::allocator<PrereqUnitRec> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	m_finish = (PrereqUnitRec *)_STL::__uninitialized_copy((Coord3D *)x.m_start, (Coord3D *)x.m_finish, (Coord3D *)m_start, _STL::__false_type());
}
