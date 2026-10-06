// cl: /MD
// ??0Rva002B55AE@@QAE@ABV0@@Z @0x002B55AE 68B
// Vector copy ctor via rowed Vector_base(size get_allocator) then 4-arg uninit-copy with empty tag.
// Evidence: Vector_base 0x004F62A4 row ScienceType; get_allocator 0x0021983A ICF ScienceType twin;
// Rva copy 0x003F74CF ICF 4-arg Holder pin; caller 0x002B90FC member +0xC 12B vector in 103B EH ctor.
enum ScienceType { SCIENCE_NONE = 0 };
class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other) throw();
private:
	void *m_ptr;
};
namespace _STL {
template <class T> class allocator
{
public:
	allocator();
	allocator(const allocator &other);
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
class Rva002B55AE : public _STL::_Vector_base<ScienceType, _STL::allocator<ScienceType> >
{
public:
	Rva002B55AE(const Rva002B55AE &x);
};
Rva002B55AE::Rva002B55AE(const Rva002B55AE &x)
	: _STL::_Vector_base<ScienceType, _STL::allocator<ScienceType> >((x.m_finish - x.m_start), ((const _STL::vector<ScienceType, _STL::allocator<ScienceType> > &)x).get_allocator())
{
	m_finish = (ScienceType *)_STL::__uninitialized_copy((Rva004F6093Holder *)x.m_start, (Rva004F6093Holder *)x.m_finish, (Rva004F6093Holder *)m_start, _STL::__false_type());
}
