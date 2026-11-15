#pragma once

// Keep the existing Line3D compiler-helper setup and RefCount inclusion
// together when tu_skeleton composes the retail translation unit. The native
// vector constructor iterator at 0x00001423 and RefCount bodies use /O1.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("s", on)
#include "refcount.h"
#pragma optimize("", on)
