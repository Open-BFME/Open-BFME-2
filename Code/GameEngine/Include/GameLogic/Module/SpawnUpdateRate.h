// SPAWN_UPDATE_RATE, the dynamically initialized frame count BFME 2's spawn-behavior header
// gives every unit that includes it.
//
// Target facts: twelve entries of retail's .CRT$XCU table are one 16-byte initializer,
// mov eax, [0x00DBA4E4]; cdq; sub eax, edx; sar eax, 1; mov [s], eax; ret (the logic frame
// rate halved into the unit's own .bss int), and each one directly follows its unit's
// Drawable.h copy (DRAWABLE_FRAMES_PER_FLASH) in .text$yc and in .bss. W3DDisplay's
// (0x007ABC6F, read by updateAverageFPS) is that unit's own START_CUMU_FRAME. SpawnBehavior's
// is the frame wait its update reloads (0x00E035C8, built by 0x007B0C0F after the unit's
// Drawable.h copy 0x007B0BFF). The other ten are never read, so they are a header's
// constant, not a unit's.
// Donor facts (Zero Hour): GameLogic/Module/SpawnBehavior.h defines
// `const Int SPAWN_UPDATE_RATE = LOGICFRAMES_PER_SECOND/2;`, and ActionManager.cpp includes
// Drawable.h and then SpawnBehavior.h, the order retail's ActionManager unit builds them in.
// Inference (the name is the donor's, not a BFME 2 fact): BFME 2's spawn-behavior header
// reaches Drawable.h before it defines the rate, so a unit that includes it builds the
// Drawable.h copy (if it has none yet) and then this one.
//
// A unit that builds the rate includes this header right after its Drawable.h include.
#ifndef BFME2_SPAWN_UPDATE_RATE_H
#define BFME2_SPAWN_UPDATE_RATE_H

extern int BfmeLogicFramesPerSecond;
const int SPAWN_UPDATE_RATE = BfmeLogicFramesPerSecond / 2;

#endif // BFME2_SPAWN_UPDATE_RATE_H
