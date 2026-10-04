// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

// DualIndexedDispatchThunk::dispatch is the donor DualIndexedDispatchThunk.cpp
// body; the donor's sibling dispatchSix is omitted. Retail 0x00388D61 calls the
// pinned dispatchIndexedValue (0x00699630) twice, at index 1 and index 2, each
// with count 2 over the value at this+0x54.
extern int DualIndexedDispatchFirst;
extern int DualIndexedDispatchSecond;

extern void __cdecl dispatchIndexedValue(
    void *target,
    int index,
    void *value,
    int count,
    int *first,
    int *second);

struct DualIndexedDispatchThunk
{
    unsigned char padding[0x54];
    void *value;

    void dispatch(void *target);
};

void DualIndexedDispatchThunk::dispatch(void *target)
{
    dispatchIndexedValue(target, 1, value, 2, &DualIndexedDispatchFirst, &DualIndexedDispatchSecond);
    dispatchIndexedValue(target, 2, value, 2, &DualIndexedDispatchFirst, &DualIndexedDispatchSecond);
}
