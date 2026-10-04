// cl: -DNDEBUG -DWIN32 -MD -EHs-c- -D_STLP_USE_STATIC_LIB /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// The donor BitFlagsParseToken.cpp reaches _STL::bitset<86>::_Unchecked_reset
// through its parseToken loop (the $0FG identifier: F=5 G=6 -> 0x56 = 86).
// Only that specialization is emitted here; an explicit class instantiation
// forces the same body without the donor's seven macro-generated parseToken
// classes.
#include <bitset>

template class _STL::bitset<86>;
