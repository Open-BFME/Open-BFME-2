// cl: /MD
// ?rva000E3A8D@Rva000E3A8D@@QAEAAV1@ABV1@@Z 0x000E3A8D 180: vector assign for 4-byte ref holders.
// Evidence: callers at 0xE9CFB 0xEDF23 0xEF137 push member vectors; callees rowed allocate 0x5E25EF clear 0x8B4AF forward 0xE1D51 destroy 0x8AFDC copy 0x7E2FA.
struct Rva002B9062Element
{
	char m_pad[4];
	Rva002B9062Element(const Rva002B9062Element &that);
	~Rva002B9062Element();
};
struct Rva0008B4AFElement
{
	char m_pad[4];
};
class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &other);
private:
	void *m_ptr;
};
class Rva000E3A8D;
namespace _STL
{
struct __false_type
{
};
template <class Type> class allocator
{
public:
	Type *allocate(unsigned int n, const void *hint) const;
};
struct RvaAllocProxy
{
	allocator<Rva002B9062Element> m_alloc;
	Rva002B9062Element *m_data;
};
template <class Type, class Allocator> class vector
{
public:
	typedef Type *pointer;
	typedef unsigned int size_type;
protected:
	template <class ForwardIter> pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
private:
	pointer m_start;
	pointer m_finish;
	RvaAllocProxy m_endOfStorage;
	friend class ::Rva000E3A8D;
};
}
template <> class _STL::vector<Rva0008B4AFElement, _STL::allocator<Rva0008B4AFElement> >
{
protected:
	void _M_clear();
protected:
	Rva0008B4AFElement *_M_start;
	Rva0008B4AFElement *_M_finish;
	Rva0008B4AFElement *_M_end_of_storage;
	friend class ::Rva000E3A8D;
};
Rva00072A94 *__cdecl Rva000E1D51Forward(Rva00072A94 *first, Rva00072A94 *last, Rva00072A94 *dest, void *ignored);
void __cdecl Rva0008AFDCDestroy(void *first, void *last);
void **__cdecl Rva0007E2FACopy(void **first, void **last, void **result, const _STL::__false_type &tag);
class Rva000E3A8D
{
public:
	Rva000E3A8D &rva000E3A8D(const Rva000E3A8D &other);
private:
	Rva00072A94 *m_start;
	Rva00072A94 *m_finish;
	Rva00072A94 *m_end;
};
Rva000E3A8D &Rva000E3A8D::rva000E3A8D(const Rva000E3A8D &other)
{
	if (&other == this)
		return *this;
	unsigned int other_n = (unsigned int)(other.m_finish - other.m_start);
	unsigned int cap = (unsigned int)(m_end - m_start);
	_STL::__false_type tag;
	if (other_n > cap) {
		Rva002B9062Element *tmp = ((_STL::vector<Rva002B9062Element, _STL::allocator<Rva002B9062Element> > *)this)->_M_allocate_and_copy(other_n, (Rva002B9062Element *)other.m_start, (Rva002B9062Element *)other.m_finish);
		((_STL::vector<Rva0008B4AFElement, _STL::allocator<Rva0008B4AFElement> > *)this)->_M_clear();
		m_start = (Rva00072A94 *)tmp;
		m_end = m_start + other_n;
	} else if ((unsigned int)(m_finish - m_start) >= other_n) {
		Rva00072A94 *e = Rva000E1D51Forward(other.m_start, other.m_finish, m_start, (void *)&tag);
		Rva0008AFDCDestroy((void *)e, (void *)m_finish);
	} else {
		Rva000E1D51Forward(other.m_start, other.m_start + (m_finish - m_start), m_start, (void *)&tag);
		Rva0007E2FACopy((void **)(other.m_start + (m_finish - m_start)), (void **)other.m_finish, (void **)m_finish, tag);
	}
	m_finish = m_start + other_n;
	return *this;
}
