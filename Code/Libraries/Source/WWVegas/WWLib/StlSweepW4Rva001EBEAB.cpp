// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// Retail's operation calls these rows for its element, spelled under separate placeholder
// names. The local element forwards to them, so the rows' own bodies run.
#include "../../../../GameEngine/Include/GameLogic/CarryoverUnit.h"
struct BfmeAssignRecord172
{
public:
	BfmeAssignRecord172(const BfmeAssignRecord172 &);
	~BfmeAssignRecord172();
	BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &);
	int a[43]; // +0x00
};
struct Rva001EBEABElement
{
public:
	Rva001EBEABElement();
	Rva001EBEABElement(const Rva001EBEABElement&other) { new (this) CarryoverUnit(*(const CarryoverUnit *)&other); }
	~Rva001EBEABElement() { ((CarryoverUnit *)this)->CarryoverUnit::~CarryoverUnit(); }
	Rva001EBEABElement&operator=(const Rva001EBEABElement&other) { ((BfmeAssignRecord172 *)this)->operator=(*(const BfmeAssignRecord172 *)&other); return *this; }
	bool operator<(const Rva001EBEABElement&)const;
	bool operator==(const Rva001EBEABElement&)const;
	char bytes[172]; // +0x00
};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva001EBEABElement, _STL::allocator<Rva001EBEABElement> >::_M_fill_insert(Rva001EBEABElement *, unsigned int, Rva001EBEABElement const &);
