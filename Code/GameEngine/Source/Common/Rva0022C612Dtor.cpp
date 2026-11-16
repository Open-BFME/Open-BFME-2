// cl: /EHs /MD
// ??1Rva00226883@@QAE@XZ @0x0022C612 (56B):
// Non-virtual dtor of Rva00226883: calls clear rva0022999F at 0x22999F
// then destroys header member whose inline dtor null-checks and frees
// m_00Head via rowed free at 0x30830. Same 56B EH shape as rowed
// ??1BfmeSubEBD@@QAE@XZ at 0x00384DEB in BfmeConv802.cpp (/O1 /EHs /MD)
// and STLport tree dtors; /EHs preserves the cleanup-state transition
// that /EHsc drops for extern C free. Layout from Rva00226883.h
// (header +0x00 flag +0x04 no vtable). Callers 0x0047482C 0x0053AEDD
// 0x005EB907 0x005EB913 plus thunk 0x0022CA3B. No new pins.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Rva00226883.h"

Rva00226883::~Rva00226883()
{
	rva0022999F();
}

// Native0x0022CA3B..0x0022CA40 tail JMP to sole rowed nonvirtual dtor
// at0x0022C612. Unadjusted receiver no stack args RET0; original wrapper
// name enclosing type and lifetime role remain unknown.
struct Rva0022CA3BCleanupForward { void cleanup(); };
void Rva0022CA3BCleanupForward::cleanup()
{
    reinterpret_cast<Rva00226883*>(this)->~Rva00226883();
}
