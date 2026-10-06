// cl: /MD
// ??0Rva0051ED0A@@QAE@ABV0@@Z @0x0051ED0A 71B vector copy ctor via rowed Vector_base PrereqUnitRec get_allocator AsciiString uninit-copy nested PrereqUnitRec
// Evidence: caller 0x0051F87B member at +0x20; stride 0x0C; callees 0x0021983A row AsciiString 0x005C8C37 row PrereqUnitRec 0x004EE1E2 row nested uninit-copy; precedent Rva005386F5Copy.cpp
struct PrereqUnitRec
{
	unsigned int m_data[3];
};
class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned int m_data[3];
	};
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
class Rva0051ED0A : public _STL::_Vector_base<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >
{
public:
	Rva0051ED0A(const Rva0051ED0A &x);
};
Rva0051ED0A::Rva0051ED0A(const Rva0051ED0A &x)
	: _STL::_Vector_base<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >((x.m_finish - x.m_start), *(const _STL::allocator<PrereqUnitRec> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
	m_finish = (PrereqUnitRec *)_STL::__uninitialized_copy((ProductionPrerequisite::PrereqUnitRec *)x.m_start, (ProductionPrerequisite::PrereqUnitRec *)x.m_finish, (ProductionPrerequisite::PrereqUnitRec *)m_start, _STL::__false_type());
}
