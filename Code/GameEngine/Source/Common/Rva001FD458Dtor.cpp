// cl: /DNDEBUG /MD /EHs
// ??1Rva001FD458@@QAE@XZ @0x001FD6F4 56B.
// Tree destructor for the Rva001FD458 node family: clears via the rowed
// rva001FD659, then the inline header-handle member dtor frees the sentinel
// via free 0x00030830 with a null guard. Same 56B clear-plus-free shape as
// the rowed ??1Rva001FD42B@@QAE@XZ 0x001FD6BC (Rva001FD42BDtor.cpp precedent:
// a throwing free under /EHs emits retail's unwind state store).
// Callers at 0x001FE25F 0x002B1372 and jmp at 0x001FD863; unblocks 0x002B11A7.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport. /EHs lets free throw,
// preserving retail's unwind states.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "RTS/PlayerTemplateTreeView.h"

Rva001FD458::~Rva001FD458()
{
	rva001FD659();
}
