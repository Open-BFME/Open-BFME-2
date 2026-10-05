// cl: /Ireference/shims/bfme2_ascii /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@UAnimSet@GenericObjectCreationNugget@@V?$allocator@UAnimSet@GenericObjectCreationNugget@@@_STL@@@_STL@@IAEXPAUAnimSet@GenericObjectCreationNugget@@ABU34@ABU__false_type@2@I_N@Z,
// retail 0x001F326F, 183 bytes. Dedicated TU.
//
// STLport 4.5.3 vector<GenericObjectCreationNugget::AnimSet>::_M_insert_overflow,
// the growth path of the push_back that ObjectCreationList.cpp already matches
// at 0x001F3326 (called by parseAnimSet at 0x001F335D for the AnimationSet
// field). BFME1 lands the same function from the same header at 0x00755CA0
// (284 bytes; reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/
// AnimSetVectorInsert.cpp) via an insert anchor; here the shape is recovered
// by explicit member instantiation.
//
// It cannot come from ObjectCreationList.cpp itself: that TU compiles the
// identical template body at 184 bytes with this in esi, len-total in edi and
// a lea-chain for len*12, while retail homes this in edi, len-total in esi
// and scales with imul esi,esi,0xc. /G7 (P4 scheduler) emits the imul and the
// retail homing; /G6 and the default blend keep the lea form (IMUL law, also
// used by the sibling AsciiStringVectorInsertOverflow.cpp TU, whose /G7
// /arch:SSE recipe this TU copies).
//
// /Ireference/shims/bfmealloc keeps allocator<AnimSet>::allocate a two-argument
// out-of-line call (push 0 / push len / call 0x00395928, pinned); stock headers
// fold it into the one-argument proxy and drop two bytes. The reduced
// AsciiString below is BFME's releaseBuffer string (protected releaseBuffer at
// 0x00036410, copy ctor at 0x000365F0, both pinned): with it _M_clear stays a
// 30-byte out-of-line call as in ObjectCreationList.cpp, where a trivial dtor
// would inline it. _Construct<AnimSet> is declared, not defined, so the copies
// call ObjectCreationList.cpp's body at 0x001F06B9. Explicit member (not
// whole-class) instantiation keeps push_back and the other members owned by
// ObjectCreationList.cpp; the helper cascade this emits (_M_clear, _M_set,
// size, allocator pair, destroy chain, max, dtor pair) is byte-identical to
// that TU's and folds.
//
// Access note: retail's AnimSet is a private nested struct; access is not
// encoded in the mangled name, so the public replica below mangles identically.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "ascii_string.h"

class GenericObjectCreationNugget
{
public:
	struct AnimSet
	{
		AsciiString m_animInitial;
		AsciiString m_animFlying;
		AsciiString m_animFinal;
		AnimSet(const AnimSet &other);
	};
};

namespace _STL
{
template <> void _Construct<GenericObjectCreationNugget::AnimSet, GenericObjectCreationNugget::AnimSet>(
	GenericObjectCreationNugget::AnimSet *, const GenericObjectCreationNugget::AnimSet &);
}

template void _STL::vector<GenericObjectCreationNugget::AnimSet>::_M_insert_overflow(
	GenericObjectCreationNugget::AnimSet *,
	const GenericObjectCreationNugget::AnimSet &,
	const _STL::__false_type &,
	unsigned int,
	bool);
