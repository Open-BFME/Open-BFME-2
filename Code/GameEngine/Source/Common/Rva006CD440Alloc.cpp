// cl: /MD
// ?Rva006CD440Alloc@@YAPAXH@Z @0x006CD440 27B evidence chain pool alloc size+4 store size header via allocBlock pin 0x006DB160 plus g_pChainBlockAllocator callers 0x006E5028 0x006E6286 0x006E62A0 plus Free sibling 0x006CD460
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
class Rva006DB160
{
public:
    void *allocBlock(int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8
void *__cdecl Rva006CD440Alloc(int size)
{
    void *base = ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(size + 4);
    *(int *)base = size;
    return (char *)base + 4;
}
