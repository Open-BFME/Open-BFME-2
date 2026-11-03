// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// ??1?$vector@URva0007BB16Record@@V?$allocator@URva0007BB16Record@@@_STL@@@_STL@@QAE@XZ @0x0007C5D5 63B:
// STLport 4.5.3 vector<Rva0007BB16Record>::~vector over the 0x24-byte
// two-string record (same definition as stlport_vector_rva0007bb16_destroy.cpp
// and Code/GameEngine/Source/Common/StringRecordDtors.cpp). Retail destroys
// the range through the rowed _Destroy at 0x0007C2D7 then frees via 0x00030830
// (EH states 0/-1); called by 16 parents including 0x0007DBEC and 0x00152496.
#include <vector>

#include "ascii_string.h"

#include "Rva0007BB16Record.h"

template _STL::vector<Rva0007BB16Record>::~vector();
