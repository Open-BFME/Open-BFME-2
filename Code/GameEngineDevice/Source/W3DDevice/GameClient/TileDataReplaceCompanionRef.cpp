// cl: /O1 /MD /EHsc
// Native11178B-1117B4; called by WorldHeightMap tile reader ABEA0 after
// TileData constructor111850. Incoming reference is retained before the old
// reference is released. The caller releases its temporary reference after
// this call. No original method name or complete TileData layout is asserted.
// Semantic guide: ZH refcount.h REF_PTR_SET; target independently proves
// pointee virtualslot0 and reference count4; receiver's companion pointer2AB4.
class Rva0011178BRetained {
public:
    virtual void deleteLastReference()=0;
    int refs;
    // ?Rva0011178BRetained::retain present-unmatched
    __forceinline void retain() { ++refs; }
    // ?Rva0011178BRetained::release present-unmatched
    __forceinline void release() { if(--refs==0)deleteLastReference(); }
};
// This ABI view declares only the fields and method touched by the native body.
class TileData {
    unsigned char untouched[0x2AB4];
    Rva0011178BRetained *companion;
public:
    void rva0011178B(TileData *value);
};
// ?TileData::rva0011178B present-unmatched
void TileData::rva0011178B(TileData *value)
{
    Rva0011178BRetained *incoming=reinterpret_cast<Rva0011178BRetained *>(value);
    if(incoming)incoming->retain();
    Rva0011178BRetained *&slot=companion;
    if(slot)slot->release();
    slot=incoming;
}
