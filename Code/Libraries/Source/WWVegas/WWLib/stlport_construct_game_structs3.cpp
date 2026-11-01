// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// Fifth batch of STLport _Construct<T> placement-copy helpers, same-shape
// siblings of the rowed _Construct<AsciiString> at 0x0002C485 (45 bytes; see
// stlport_construct_asciistring.cpp). Each body is the null-guarded
// placement-new copy over a single element: the copy delegates out-of-line
// to T's own copy ctor (rowed or pinned), and __EH_prolog resolves via its
// matched row. Each T is declared minimally (declared-only copy ctor,
// matching the struct/class-ness of its copy ctor); no member is ever
// touched, so the emitted code is identical apart from the callee. Ledger
// uses the actual _Construct<T> compiler names. The helper pattern is carried
// from STLport; original application identity of the opaque record is unknown.

#include <memory>

#include "../../../../GameEngine/Include/GameLogic/Bfme2BuildListInfo.h"

struct BfmeOpaqueOwnedRecord1432
{
public:
	BfmeOpaqueOwnedRecord1432(const BfmeOpaqueOwnedRecord1432 &other);

private:
	char m_body[1432];
};

template void _STL::_Construct<BuildListInfo, BuildListInfo>(BuildListInfo *, const BuildListInfo &);
template void _STL::_Construct<BfmeOpaqueOwnedRecord1432, BfmeOpaqueOwnedRecord1432>(BfmeOpaqueOwnedRecord1432 *, const BfmeOpaqueOwnedRecord1432 &);
