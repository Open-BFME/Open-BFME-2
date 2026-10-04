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

extern "C" void __cdecl free(void *);

// Only the accessed payload prefix is modeled: native teardown 0x0007FAB3
// frees the owned pointer at +0, and 0x0004AA28 reads the count at +0x10.
// The donor's vector/cursor layout motivates this ownership relationship;
// the intervening bytes and original payload type are not asserted here.
struct BfmeWideResultPayload
{
    void *m_storage;
    unsigned char m_unmodelled[0x0c];
    int m_refCount;
    ~BfmeWideResultPayload();
};

struct BfmeWideResult
{
	void *m_value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &that);
	~BfmeWideResult();
};

#pragma optimize("s", on)
// ?BfmeWideResultPayload::~BfmeWideResultPayload present-unmatched
// This emitted 14-byte destructor is independently exact at 0x0007FAB3,
// already rowed as BasicStringCharDtor_dup. Its _free call is native 0x30830.
// The folded provider has the same thiscall ABI and destroys this storage;
// no additional row or progress is claimed for that already covered range.
BfmeWideResultPayload::~BfmeWideResultPayload()
{
    if (m_storage)
        free(m_storage);
}

BfmeWideResult::~BfmeWideResult()
{
    void *&payload = m_value;
    --static_cast<BfmeWideResultPayload *>(payload)->m_refCount;
    if (static_cast<BfmeWideResultPayload *>(payload)->m_refCount == 0)
        delete static_cast<BfmeWideResultPayload *>(payload);
}
#pragma optimize("", on)
