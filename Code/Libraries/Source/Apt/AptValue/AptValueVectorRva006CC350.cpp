// cl: /MD
// ?rva006CC350@AptValueVector@@QAEPAV1@I@Z, retail 0x006CC350 (35B).
// AptValueVector deleting-dtor shape: calls free-array dtor then sized pool
// free. Evidence: calls rowed rva006E6D50 at 0x006E6D50; flag bit0 test with
// ret-4 and return-this; pool freeBlock at 0x006DB270 size 0x10; chain from
// 0x006E6D50 landing; no callers.
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8
class AptValue;
class AptValueVector {
    int mCapacity;
    int mCurrentNum;
    AptValue **mpValues;
    int mHighWaterNum;
public:
    void rva006E6D50();
    AptValueVector *rva006CC350(unsigned int flag);
};
AptValueVector *AptValueVector::rva006CC350(unsigned int flag)
{
    rva006E6D50();
    if (flag & 1)
        g_pChainBlockAllocator->freeBlock(this, 0x10);
    return this;
}
