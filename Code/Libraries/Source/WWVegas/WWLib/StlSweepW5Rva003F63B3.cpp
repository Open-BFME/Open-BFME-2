// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva003F63B3Element {Rva003F63B3Element();Rva003F63B3Element(const Rva003F63B3Element&);Rva003F63B3Element&operator=(const Rva003F63B3Element&);~Rva003F63B3Element(){}char bytes[28]; bool operator==(const Rva003F63B3Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva003F63B3Element * _STL::__copy_backward<Rva003F63B3Element *, Rva003F63B3Element *, int>(Rva003F63B3Element *, Rva003F63B3Element *, Rva003F63B3Element *, _STL::random_access_iterator_tag const &, int *);

// ICF twin of ??4BfmeAssignRecord28@@QAEAAU0@ABU0@@Z (0x003F6388,
// StlSweepBfmeAssignRecord28.cpp): the same 28-byte record assignment, so the
// copy loop above binds a definition. The member vectors' assignments stay
// out of line, as in the owner unit.
struct Rva003F5FD0Record { Rva003F5FD0Record(); Rva003F5FD0Record(const Rva003F5FD0Record&); ~Rva003F5FD0Record(); Rva003F5FD0Record& operator=(const Rva003F5FD0Record&); char bytes[48]; };
#include "Rva0021C21BElement.h"
namespace _STL {
template<> vector<Rva003F5FD0Record, allocator<Rva003F5FD0Record> > &vector<Rva003F5FD0Record, allocator<Rva003F5FD0Record> >::operator=(const vector<Rva003F5FD0Record, allocator<Rva003F5FD0Record> > &);
template<> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &);
}

struct Rva003F63B3View
{
	unsigned int field;
	_STL::vector<Rva003F5FD0Record, _STL::allocator<Rva003F5FD0Record> > records;
	_STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > elements;
};

Rva003F63B3Element &Rva003F63B3Element::operator=(const Rva003F63B3Element &other)
{
	Rva003F63B3View *self = (Rva003F63B3View *)this;
	const Rva003F63B3View &o = *(const Rva003F63B3View *)&other;
	self->field = o.field;
	self->records = o.records;
	self->elements = o.elements;
	return *this;
}
