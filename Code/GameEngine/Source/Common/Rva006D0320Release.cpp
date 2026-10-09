// cl: /DNDEBUG /MD
// ?rva006D0320@Rva006D0280@@QAEPAV1@_N@Z @ 0x006D0320 35B
// Honest address name: __thiscall conditional pool free beside Rva008951B0Find.
// Target evidence: 35B retail, pinned teardown 0x6D0280 plus pinned freeBlock
// 0x6DB270 with pool VA 0xE176E8 and size 0x1C, ret 4 bool arg, returns this.
// Prev/next share /DNDEBUG /MD shape.
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006D0280
{
public:
    ~Rva006D0280();
    Rva006D0280 *rva006D0320(unsigned char doFree);
};
Rva006D0280 *Rva006D0280::rva006D0320(unsigned char doFree)
{
    this->~Rva006D0280();
    if (doFree & 1)
        g_pChainBlockAllocator->freeBlock(this, 0x1C);
    return this;
}
