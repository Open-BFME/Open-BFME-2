// cl: /DNDEBUG /MD
// stlport
//
// ??$_Construct@VBfmeStringTailRecord156@@V1@@_STL@@YAXPAVBfmeStringTailRecord156@@ABV1@@Z
// Retail 0x001D9A4F, 18 bytes. Ghidra extent is 18 bytes; retail disassembly
// is the null-guarded placement-copy wrapper ending in ret. Its callers are
// the byte-matched TailRecord156 vector fill/overflow paths (0x001D9A87 and
// 0x001D9FAC; the pin is recorded in reverse/symbols.csv).
// The target call at 0x001D9A5B is 0x001D9975. Upstream STLport's _Construct
// implementation is reference/open-bfme-1/inputs/vendor/stlport/stl/_construct.h:80-86;
// this unit instantiates that template from <memory>. The null guard is the
// one cl emits for the throw() placement new, confirmed by the retail bytes
// and the same emitted shape in Rva0046267AConstruct.cpp. This TU keeps
// the copy constructor out-of-line. Target 0x001D9975 is matched separately in
// stlport_construct_tailrecord156_copy.cpp. No matching named donor was found.

#include <memory>

#include "../../../../GameEngine/Include/Common/Rva0036CA00Str.h"

class BfmeStringTailRecord156
{
    Rva0036CA00Str m_string;
    int m_value;
public:
	BfmeStringTailRecord156(const BfmeStringTailRecord156 &) throw();
	~BfmeStringTailRecord156() throw();
};


template void _STL::_Construct<BfmeStringTailRecord156, BfmeStringTailRecord156>(
	BfmeStringTailRecord156 *, const BfmeStringTailRecord156 &);
