// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector base for the 12-byte ProductionPrerequisite
// record element. The count-taking _Vector_base (retail 0x005C8C37, 60B) is
// emitted here as a side product of the explicit instantiation, mirroring
// the BfmeVectorRecord000BDF17 allocate_copy TU that placed its own 60B
// _Vector_base by masked whole-text search. The allocator and the alloc
// proxy callees are both settled; the 12-byte stride (imul 0x0C) selects
// the PrereqUnitRec element spelling.
#include <vector>
struct PrereqUnitRec
{
	unsigned int m_data[3];
	~PrereqUnitRec() {}
};
template class _STL::vector<PrereqUnitRec, _STL::allocator<PrereqUnitRec> >;

// Reference the count-taking _Vector_base so the object emits it: retail
// 0x005C8C37 is the (count, allocator) base ctor, which nothing above calls.
void forcePrereqUnitRecVectorBase()
{
	_STL::vector<PrereqUnitRec, _STL::allocator<PrereqUnitRec> > counted(3);
}
