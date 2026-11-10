// Reference: pristine STLport4.5.3. Address-derived opaque record ABI.
// Target boundary and literal pointer stride establish storage width only; no application identity inferred.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>



// The 28-byte element is retail's record under other address-derived labels:
// its placement copy ctor is rowed at 0x003F5F89 (??0EvaMessageInfo, matched in
// Code/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogicRemovePlayer.cpp)
// and its destructor at 0x003F60C8 (??1BfmeStringRecord00111ACF,
// VectorMemberRecordDtors.cpp; this unit's row at 0x003F6B24 is the ICF twin of
// that record's 0x003F6B24 _M_insert_overflow). The vector helpers below keep
// this unit's own Rva003F6B24Record spelling for the ledger row, but the two
// special calls they reach must bind to those rowed owners instead of the
// undefined ??$_Construct@URva003F6B24Record / ??1Rva003F6B24Record: the
// _Construct specialization reproduces retail's null-guarded placement copy at
// 0x003F62C8 (byte-identical) through the rowed copy ctor, and the destructor
// is a view of the rowed dtor.
struct EvaMessageInfo { public: EvaMessageInfo(const EvaMessageInfo&); };
class BfmeStringRecord00111ACF { public: ~BfmeStringRecord00111ACF(); };

struct Rva003F6B24Record { Rva003F6B24Record(); Rva003F6B24Record(const Rva003F6B24Record&); ~Rva003F6B24Record() { ((BfmeStringRecord00111ACF *)this)->BfmeStringRecord00111ACF::~BfmeStringRecord00111ACF(); } Rva003F6B24Record&operator=(const Rva003F6B24Record&); private: char bytes[28]; };
namespace _STL {template<> inline void _Construct<Rva003F6B24Record,Rva003F6B24Record>(Rva003F6B24Record*p,const Rva003F6B24Record&v){ _STLP_PLACEMENT_NEW ((void*)p) EvaMessageInfo(*(const EvaMessageInfo*)&v); }}
template void _STL::vector<Rva003F6B24Record>::_M_insert_overflow(Rva003F6B24Record*,const Rva003F6B24Record&,const _STL::__false_type&,unsigned int,bool);
