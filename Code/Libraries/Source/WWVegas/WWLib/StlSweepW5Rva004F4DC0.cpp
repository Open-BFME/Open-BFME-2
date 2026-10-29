// STLport 4.5.3 pointer-range __copy over ProductionPrerequisite::PrereqUnitRec.
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// 0x004F4DC0 (50B) walks 12-byte records and calls the record's implicit
// operator= (0x002CEFAA: copies unit and flags, then StringBase<char>::set on
// the name at +8) for each one. Its callers are vector<PrereqUnitRec>::erase
// (0x004F50E2, through the __copy_ptrs forwarder 0x002CF594) and the record
// vector's operator=. The record is Zero Hour's
// ProductionPrerequisite::PrereqUnitRec {unit, flags, name}; this unit emits
// the copy loop and the record's operator=.
#include <vector>
#include "ascii_string.h"

class ThingTemplate;

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		const ThingTemplate *unit;
		int flags;
		AsciiString name;
	};
};

template ProductionPrerequisite::PrereqUnitRec *_STL::__copy<ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, int>(
	ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *,
	const _STL::random_access_iterator_tag &, int *);
