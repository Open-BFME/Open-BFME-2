// ProductionPrerequisite::PrereqUnitRec's implicit operator=.
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// 0x002CEFAA (35B) copies the record's unit and flags words, then assigns the
// AsciiString at +8 through StringBase<char>::set (0x000366F0). Its only caller
// is the record copy loop __copy<PrereqUnitRec *> (0x004F4DC0), so the record
// is Zero Hour's ProductionPrerequisite::PrereqUnitRec {unit, flags, name}.
// The compiler emits the implicit operator= where a copy loop uses it; this
// unit instantiates that loop (rowed in StlSweepW5Rva004F4DC0.cpp, the same
// select-any body) to emit it.
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
