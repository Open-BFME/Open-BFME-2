// cl: /MD
// ?Rva006D8680Free@@YAXPAXH@Z 0x006D8680 22B: chain pool free forwarder via g_pChainBlockAllocator.
// Evidence: chain lane callee rowed freeBlock 0x006DB270; pool VA 0x00A176E8 extern name in use; prev/next share /O1 /MD.
class Rva006DB270
{
public:
    void freeBlock(void *block, int size);
};
extern Rva006DB270 *g_pChainBlockAllocator;
void __cdecl Rva006D8680Free(void *block, int size)
{
    g_pChainBlockAllocator->freeBlock(block, size);
}
