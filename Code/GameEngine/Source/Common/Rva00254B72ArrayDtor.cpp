// cl: /O1 /MD /EHsc /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Complete native254B72..254B8216B helper, called by the ThingTemplate
// constructor for array cleanup. The eh-vector destructor arguments prove
// stride8, count56, and callback4C9F38; they are not stride56/count8.
// Callback owner Rva002390CB establishes the eight-byte two-word record,
// whose second word owns a reference. The application element type and
// original containing class name remain unknown.
class OpaqueRefCounted;
#include "../../Include/Common/Rva002390CB.h"
class Rva00254B72 {Rva002390CB records[56];public:~Rva00254B72();};
__declspec(noinline) inline Rva00254B72::~Rva00254B72(){}
// Select-any: another unit compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva00254B72Dtor absent-from-retail
void bfmeAnchorRva00254B72Dtor(Rva00254B72 *p) { p->~Rva00254B72(); }
