// cl: /O2 /MD
// ?Rva006F12F0Free@@YAXPAXH@Z 0x006F12F0 22B: chain pool free forwarder,
// recovered from the ?Rva006D8680Free@@YAXPAXH@Z recipe at 0x006D8680.
// Same operand-masked shape: load the block and size arguments, then thiscall
// the allocator's freeBlock through the pool pointer global at 0x00E176F4.
// Only the pool global (a DIR32 operand) and the REL32 callee differ: retail
// calls 0x006D2A60, which the template pins at 0x006DB270 for its sibling.
// Evidence: callee Ghidra extent 253B at 0x006D2A60; prev/next share /O1 /MD.
class Rva006D2A60
{
public:
    void freeBlock(void *block, int size);
};
extern Rva006D2A60 *g_bfmeChainBlockAllocatorAtE176F4;
void __cdecl Rva006F12F0Free(void *block, int size)
{
    g_bfmeChainBlockAllocatorAtE176F4->freeBlock(block, size);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_bfmeChainBlockAllocatorAtE176F4@@3PAVRva006D2A60@@A=?g_pChainBlockAllocatorF4@@3PAVRva006D2A60@@A")
