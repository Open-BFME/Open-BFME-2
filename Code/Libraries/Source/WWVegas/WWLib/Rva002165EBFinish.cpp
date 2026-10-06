// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??$_Construct@U?$pair@$$CBVAsciiString@@VGen_003A8BE0@@@_STL@@U12@@_STL@@YAXPAU?$pair@$$CBVAsciiString@@VGen_003A8BE0@@@0@ABU10@@Z
// @ 0x002165EB (45B).  STLport placement-copy for one
// pair<const AsciiString, Gen_003A8BE0> element: null-guarded placement new
// delegating out-of-line to the rowed pair copy constructor 0x002161DE.
// Caller 0x00216779 allocates 0x14 bytes, zeroes +0 and constructs the pair at
// +4.  Byte-identical twin of the matched Rva0045EF90Object instantiation at
// 0x0041072F in stlport_pair_asciistring_twins.cpp.  The vendored header emits
// the EH state store and the dst spill BEFORE the null test; the hand-written
// `if (p) new (p) T(v)` free-function attempt banked one byte away because it
// sank both into the taken branch.  The explicit instantiation is what
// reproduces retail's eager schedule.
#include "ascii_string.h"
#include <utility>
#include <memory>

class Gen_003A8BE0
{
public:
	Gen_003A8BE0(const Gen_003A8BE0 &other);
	~Gen_003A8BE0();
};

template void _STL::_Construct<_STL::pair<const AsciiString, Gen_003A8BE0>, _STL::pair<const AsciiString, Gen_003A8BE0> >(_STL::pair<const AsciiString, Gen_003A8BE0> *, const _STL::pair<const AsciiString, Gen_003A8BE0> &);
