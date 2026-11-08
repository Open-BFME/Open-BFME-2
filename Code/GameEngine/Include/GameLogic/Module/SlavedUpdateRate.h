// SLAVED_UPDATE_RATE, the dynamically initialized frame count BFME 2's slaved-update header
// gives every unit that includes it.
//
// Target facts: three entries of retail's .CRT$XCU table are one 17-byte initializer that
// stores the logic frame rate (0x00DBA4E4) divided by 4 into the unit's own .bss int:
// SlavedUpdate's (0x007B1A27, the interval its update reloads, BfmeSlavedUpdateIntervalFrames
// in SlavedUpdateRepair.cpp), and two never read, in the runs of ModuleFactory (0x007ADD72)
// and SlowDeathBehavior (0x007B0BA0).
// Donor facts (Zero Hour): GameLogic/Module/SlavedUpdate.h defines
// `const Int SLAVED_UPDATE_RATE = LOGICFRAMES_PER_SECOND/4;`, and exactly three units include
// it: SlavedUpdate.cpp, SlowDeathBehavior.cpp and ModuleFactory.cpp.
// The name is the donor's (inferred, not a BFME 2 fact); the BFME 2 header that defines it is
// not recovered. A unit that builds the rate includes this header where retail's run puts it.
#ifndef BFME2_SLAVED_UPDATE_RATE_H
#define BFME2_SLAVED_UPDATE_RATE_H

extern int BfmeLogicFramesPerSecond;
const int SLAVED_UPDATE_RATE = BfmeLogicFramesPerSecond / 4;

#endif // BFME2_SLAVED_UPDATE_RATE_H
