// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x002CF594 (29B) is STLport's __copy_ptrs forwarder (const __false_type& tag)
// over ProductionPrerequisite::PrereqUnitRec: vector<PrereqUnitRec>::erase
// (0x004F50E2) calls it, and its REL32 lands on 0x004F4DC0, rowed as
// __copy<PrereqUnitRec *> in StlSweepW5Rva004F4DC0.cpp. The callee is only
// declared here, so this unit emits the forwarder alone.
#include <algorithm>

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec;
};

namespace _STL {
template <> ProductionPrerequisite::PrereqUnitRec *__copy<ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, int>(
	ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *,
	const random_access_iterator_tag &, int *);
}

template ProductionPrerequisite::PrereqUnitRec *_STL::__copy_ptrs<ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *>(
	ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, const _STL::__false_type &);
