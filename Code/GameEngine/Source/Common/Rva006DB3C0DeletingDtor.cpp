// cl: /MD
// ??_GRva0070A840@@QAEPAXI@Z @0x006DB3C0 35B evidence calls pinned ??1Rva0070A840 plus pool free via g_pChainBlockAllocator size 0x14 matching retail push
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8
class Rva0070A840
{
public:
    ~Rva0070A840();
    static void operator delete(void *p, unsigned int size)
    {
        g_pChainBlockAllocator->freeBlock(p, size);
    }
    char m_pad[0x14];
};
void deleteRva0070A840(Rva0070A840 *p)
{
    delete p;
}
