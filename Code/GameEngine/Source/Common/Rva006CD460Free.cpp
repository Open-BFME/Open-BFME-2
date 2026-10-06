// cl: /MD
// ?Rva006CD460Free@@YAXPAX@Z @0x006CD460 27B evidence array-free via pool freeBlock with stored size at p-4 plus 4
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8
void __cdecl Rva006CD460Free(void *p)
{
    int stored = ((int *)p)[-1];
    void *base = (char *)p - 4;
    g_pChainBlockAllocator->freeBlock(base, stored + 4);
}
