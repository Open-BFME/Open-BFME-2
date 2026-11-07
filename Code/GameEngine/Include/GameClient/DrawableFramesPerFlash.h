// DRAWABLE_FRAMES_PER_FLASH, the one dynamically initialized constant of GameClient/Drawable.h.
//
// Target facts: 442 entries of retail's .CRT$XCU table (the first at 0x007AB7F0) are one
// 16-byte initializer, mov eax, [0x00DBA4E8]; cdq; sub eax, edx; sar eax, 1; mov [s], eax;
// ret, each into its own unit's .bss int. Drawable::updateDrawable divides the client frame
// by its unit's copy (0x00275A30 div [0x00DFEB98], then test edx, edx) and ScriptActions'
// flash actions divide a frame count by theirs (0x003BB5ED idiv [0x00E02D9C]). Zero Hour
// makes exactly those uses of DRAWABLE_FRAMES_PER_FLASH, which its Drawable.h defines as
// LOGICFRAMES_PER_SECOND / 2. BFME 2 divides the frame-rate variable at VA 0x00DBA4E8
// instead, so every unit that includes Drawable.h builds the constant at startup.
//
// The canonical Drawable.h includes this header where it defines the constant. A unit still
// built on Zero Hour's headers (PreRTS.h and Zero Hour's Thing) cannot take the canonical
// Drawable.h beside them, so it includes this header at the point retail's unit included
// Drawable.h: its object then builds the same copy, in the same place in its initializer
// run, without a second Thing or Drawable class.
#ifndef BFME2_DRAWABLE_FRAMES_PER_FLASH_H
#define BFME2_DRAWABLE_FRAMES_PER_FLASH_H

extern int BfmeClientFramesPerSecond;
const int DRAWABLE_FRAMES_PER_FLASH = BfmeClientFramesPerSecond / 2;

#endif // BFME2_DRAWABLE_FRAMES_PER_FLASH_H
