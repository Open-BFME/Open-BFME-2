// Target facts (addresses are RVAs unless marked VA): Rva006DB270 is a plain class with no virtual functions or base calls in its complete retail initialization and teardown.
// 0x006CC3C6 allocates 0x1C bytes, 0x006CC3FC calls constructor 0x006DAEB0, and 0x006CC410 stores its result at VA 0x00E176E8. Shutdown reloads that same receiver at 0x006CE03E, calls teardown 0x006DAFA0 at 0x006CE04D and frees 0x1C bytes at 0x006CE052.
// Constructor 0x006DAEB0 stores dwords at +0x08 (0x006DAEC9), +0x0C (0x006DAEF2), +0x10 (0x006DAEE6), +0x14 (0x006DAEF5) and +0x18 (0x006DAEF8). Its allocator results become +0x00 at 0x006DAF06 and +0x04 at 0x006DAF16; neither is a vptr. It writes config bytes +0x10/+0x11/+0x12 at 0x006DAF50/0x006DAF59/0x006DAF5F.
// freeBlock (ledger 0x006DB270, 207 bytes) reads byte +0x13 at 0x006DB2B2, compares unsigned +0x0C at 0x006DB2BE, walks pools from +0x04 at 0x006DB2D4, decrements +0x14 at 0x006DB315 and calls 0x006DB090 with the unchanged receiver at 0x006DB333. That callee indexes the free-list array at +0x00 (0x006DB0C2), increments +0x18 (0x006DB0D3) and reads config dword +0x10 and bytes +0x11/+0x12 (0x006DB0D8/0x006DB0ED/0x006DB101).
// 0x006DB1CF uses +0x08 as an allocation size. Teardown 0x006DAFA0 frees the array at +0x00 using +0x0C + 4, then walks the pool list at +0x04, without a table store or virtual dispatch. Constructor and teardown have different ledger owner names, Rva006DAEB0 and Rva006DAFA0Walk; no constructor or destructor row is named Rva006DB270. Only freeBlock's spelling is established for this class, so it remains an out-of-line declaration; field names below are neutral offset labels.

#pragma once

struct _DOGMA_MemPool;

class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);

private:
    void **field00;
    _DOGMA_MemPool *field04;
    int field08;
    unsigned int field0C;
    union {
        unsigned int field10;
        struct {
            unsigned char byte10;
            unsigned char byte11;
            unsigned char byte12;
            unsigned char byte13;
        };
    };
    int field14;
    int field18;
};
