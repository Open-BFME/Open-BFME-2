// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Transferred unchanged from Open-BFME-1 5cae4bdff game/Libraries/Source/WWVegas/WWLib/stlport_ios_failure_ctor.cpp;
// bfme1_sweep ambiguous: byte-identical to 8 BFME2 placements; the one at 0x0001BBF0 is
// the only one whose call reads the BFME2 address of the donor's own callee.
// Addresses in the donor text are BFME1.

#include <ios>
#include <string>

namespace _STL {
ios_base::failure::failure(const string &message) : __Named_exception(message)
{
}
}
