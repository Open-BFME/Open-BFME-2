// cl: /O2 /Ob1
// Handle teardown lead: complete clean BFME1
// game/GameEngine/Source/GameLogic/Object/Update/CommandButtonHuntUpdateScanClosestTarget.cpp
// at 7c4d488c5bc928bb8eaf37171ae5700b4e33937f, compiled /O1 against the
// verified 6583b3c1ff21db4a561285717028fdafc780b7db headers. Original result
// and payload class names remain recovery names, rather than target RTTI facts.
// Native 0x0004AA28 is a complete 34-byte Ghidra entry ending in plain RET;
// existing result-handle callers independently use this same teardown endpoint.
// It decrements the payload word at +0x10, then destroys and scalar-deletes
// the payload at zero. The signedness of that count is carried from the donor.
// /Ob1 permits the compiler's deleting-dtor wrapper to inline; /Ob0 emitted a
// different call. The handle declaration agrees with the existing forwarding
// unit: one void* word and the same ctor/copy/dtor signatures. That unit's
// independent unrowed maker dependency is outside this teardown recovery.

#include <stdlib.h>

// Only the accessed payload words are modeled: native teardown 0x0007FAB3
// frees the owned pointer at +0, and 0x0004AA28 reads the count at +0x10.
// As in the donor (a vector, cursor and count), the payload's destructor is
// implicit: it is a select-any copy here, like PartitionManagerGetObjectsInRange.cpp's.
// The intervening bytes and original payload type are not asserted here.
struct BfmeWideResultStorage
{
    void *m_storage;
    unsigned char m_unmodelled[0x08];
    ~BfmeWideResultStorage()
    {
        if (m_storage)
            free(m_storage);
    }
};

struct BfmeWideResultPayload
{
    BfmeWideResultStorage m_items;
    void *m_cursor;
    int m_refCount;
};

#include "PartitionRangeQueryCallView.h"

// The emitted payload destructor is independently exact at 0x0007FAB3,
// already rowed as BasicStringCharDtor_dup; its _free call is native 0x30830.
BfmeWideResult::~BfmeWideResult()
{
    void *&payload = m_value;
    --static_cast<BfmeWideResultPayload *>(payload)->m_refCount;
    if (static_cast<BfmeWideResultPayload *>(payload)->m_refCount == 0)
        delete static_cast<BfmeWideResultPayload *>(payload);
}
