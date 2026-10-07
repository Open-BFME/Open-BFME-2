// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Two more ShareBufferClass 4-byte-element 3-arg constructor instantiations
// recovered from the ??0?$ShareBufferClass@K@@QAE@HPBDH@Z recipe at 0x00169950.
// Same operand-masked shape: SEH prologue, refcount = 1, unaligned or aligned
// _bfmeArrayNew (0x0002FDE0), then store the raw/aligned pointers. Only the
// vtable pointer and the SEH scope table address differ, and both are DIR32
// relocation sites. The element type is unknown, so it is address-derived and
// a 4-byte POD; the *4 scale and the code shape are what the ledger proves.
#pragma optimize("gsy", on)
// Emit the shared compiler iterator under this TU's existing retail context.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }

#include "refcount.h"
#pragma optimize("", on)
#include "rendobj.h"
#include "sharebuf.h"

struct Rva0015AC00Elem { int m_x; };
struct Rva0015AD60Elem { int m_x; };

template ShareBufferClass<Rva0015AC00Elem>::ShareBufferClass(int count, const char* msg, int alignment);
template ShareBufferClass<Rva0015AD60Elem>::ShareBufferClass(int count, const char* msg, int alignment);
