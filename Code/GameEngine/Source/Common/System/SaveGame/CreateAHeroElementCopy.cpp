// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB

// Twelve-byte CreateAHeroData array element. Its retail default constructor
// zeros an AsciiString and two scalar words; assignment preserves string
// ownership through StringBase::set at 0x366F0. Field meanings are unknown.
#include "ascii_string.h"
#include "../../../../Include/Common/BfmeHeroElement005C39DE.h"
// The genuine reset caller in CreateAHeroDataResetElements.cpp emits the
// existing default constructor and folded member teardown naturally. Their
// ledger rows live there; this unit owns only the assignment body.
BfmeHeroElement005C39DE &BfmeHeroElement005C39DE::operator=(const BfmeHeroElement005C39DE &o) { if (this != &o) { text=o.text; word4=o.word4; word8=o.word8; } return *this; }
