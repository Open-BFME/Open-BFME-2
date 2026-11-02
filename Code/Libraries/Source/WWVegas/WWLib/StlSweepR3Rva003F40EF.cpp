// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// cl: /O1 /G6 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// 0x003F40EF is _STL::swap<ArmySummary>: the 104-byte temporary is built by the
// ArmySummary copy constructor (0x0040E96D), both assignments call
// ArmySummary::operator= (0x0040EAED) and the temporary is torn down by the
// virtual destructor ~ArmySummary (0x0040E499), all rowed under those names.
// Its one caller, LivingWorldBattle::BattlePlayer::SwapArmies (0x003F427D),
// swaps two elements of the battle player's army-summary vector.
#include <algorithm>

// Only the members swap reaches are declared, so this unit emits nothing else
// of the class; the 0x64 bytes after the vptr give the retail 0x68 temporary.
#include "../../../../GameEngine/Include/GameLogic/ArmySummary.h"

template void _STL::swap(ArmySummary &, ArmySummary &);
