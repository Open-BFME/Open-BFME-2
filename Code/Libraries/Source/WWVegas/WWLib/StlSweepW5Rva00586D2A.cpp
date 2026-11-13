// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Oi /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00586D2AElement { Rva00586D2AElement();Rva00586D2AElement(const Rva00586D2AElement&);~Rva00586D2AElement();Rva00586D2AElement&operator=(const Rva00586D2AElement&);char bytes[84]; bool operator<(const Rva00586D2AElement&)const; bool operator==(const Rva00586D2AElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template Rva00586D2AElement * _STL::__copy<Rva00586D2AElement *, Rva00586D2AElement *, int>(Rva00586D2AElement *, Rva00586D2AElement *, Rva00586D2AElement *, _STL::random_access_iterator_tag const &, int *);

// ICF twin of ??4BfmeAssignRecord84@@QAEAAU0@ABU0@@Z (0x00586BC9,
// stlport_assign_record84_00586BC9.cpp): the same 84-byte record assignment,
// so the copy loop above binds a definition. The member deque's assignment is
// the owner's external instantiation, declared here so this unit emits none.
#include <deque>
struct BfmeE12
{
	int m_00;
	int m_04;
	int m_08;
};
typedef _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > BfmeE12CopyIterator;
namespace _STL {
template <> deque<BfmeE12> &deque<BfmeE12>::operator=(const deque<BfmeE12> &);
template <> BfmeE12CopyIterator copy_backward<BfmeE12CopyIterator, BfmeE12CopyIterator>(
    BfmeE12CopyIterator, BfmeE12CopyIterator, BfmeE12CopyIterator);
}
#include "Ints12.h"
struct Rva00586D2AView
{
	int m_00;
	Ints12 m_04;
	Ints12 m_10;
	unsigned char m_1C;
	char m_pad1D[3];
	int m_20;
	int m_24;
	_STL::deque<BfmeE12> m_28;
	int m_50;
};

Rva00586D2AElement &Rva00586D2AElement::operator=(const Rva00586D2AElement &o)
{
	Rva00586D2AView *self = (Rva00586D2AView *)this;
	const Rva00586D2AView &other = *(const Rva00586D2AView *)&o;
	self->m_00 = other.m_00;
	self->m_04 = other.m_04;
	self->m_10 = other.m_10;
	self->m_1C = other.m_1C;
	self->m_20 = other.m_20;
	self->m_24 = other.m_24;
	self->m_28 = other.m_28;
	self->m_50 = other.m_50;
	return *this;
}
