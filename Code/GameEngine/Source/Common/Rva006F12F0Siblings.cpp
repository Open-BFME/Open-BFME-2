// cl: /MD
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
extern class Rva006D2A60 *g_pChainBlockAllocatorF4;
void __cdecl Rva006F12F0Free(void *block, int size)
{
    g_pChainBlockAllocatorF4->freeBlock(block, size);
}
