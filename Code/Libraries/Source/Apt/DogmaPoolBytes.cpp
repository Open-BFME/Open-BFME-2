// cl: /MD
// APT0.19.03 Xbox final PDB/MAP names DOGMA_PoolManager::GetTotalBytesUsed.
// Target Apt.cpp shutdown6CDF60 calls this body for both pool globals at
// 6CDFD2/6CE02C and prints the result as "Total Bytes Used". The same non-GC
// pool receiver is destroyed at6CE04D by6DAFA0, whose assertions name
// DogmaAllocator.cpp. This corroborates the donor owner and operation.
// Target proves head+4, next+0 and subtraction of dwords+4/+8; member names
// and unsigned types are from donor TPI2DD3/2DB8. Only accessed prefixes used.
struct _DOGMA_MemPool {
    _DOGMA_MemPool *mpNextPool;
    unsigned int mnPoolSize, mnPoolFree;
};
class DOGMA_PoolManager {
    unsigned char unaccessed[4];
    _DOGMA_MemPool *mpFirstPool;
public:
    unsigned int GetTotalBytesUsed();
};
unsigned int DOGMA_PoolManager::GetTotalBytesUsed()
{
    unsigned int used=0;
    _DOGMA_MemPool *pool=mpFirstPool;
    do {
        used+=pool->mnPoolSize-pool->mnPoolFree;
        pool=pool->mpNextPool;
    } while(pool);
    return used;
}
