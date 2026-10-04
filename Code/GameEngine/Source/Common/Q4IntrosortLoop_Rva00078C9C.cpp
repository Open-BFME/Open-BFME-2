// cl: -GX- /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
#include <algorithm>

// STLport's __lg<int> is emitted by the donor TU Q4IntrosortLoop.cpp (its
// _STL::sort instantiations call it). The donor's macro-generated q4Sort*
// callers are omitted here; an explicit instantiation forces the same body.
template int _STL::__lg<int>(int);
