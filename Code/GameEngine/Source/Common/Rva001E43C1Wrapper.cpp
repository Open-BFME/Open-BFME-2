// cl: /DNDEBUG /MD /EHsc
// Object::isUsingAirborneLocomotor (0x0028B81E) is rowed in
// ObjectIsUsingAirborneLocomotor.cpp; this unit holds only the 0x001E43C1
// flag-setter wrapper below, so it carries no second definition of it.

#include "../../Include/GameLogic/LocomotorClass.h"

// Native 0x001E43C1..0x001E43CF is a complete thiscall entry between the
// preceding RET8 and the independently rowed matrix copy. It forwards its
// one consumed bool with index four (Zero Hour's
// NO_SLOW_DOWN_AS_APPROACHING_DEST) to the existing setFlag body 0x001E3459,
// preserving ECX. No callers establish this wrapper's original class or
// method name. BFME1 f98983a7 assetstatus.cpp supplied the constant-argument
// wrapper shape under O1/SSE2/G6; its Report_Missing_HAnim name and string
// argument do not apply to the target's independently verified callee.
class Rva001E43C1
{
public:
	void rva001E43C1(bool enabled);
};

void Rva001E43C1::rva001E43C1(bool enabled)
{
	reinterpret_cast<Locomotor *>(this)->setNoSlowDownAsApproachingDest(enabled);
}
