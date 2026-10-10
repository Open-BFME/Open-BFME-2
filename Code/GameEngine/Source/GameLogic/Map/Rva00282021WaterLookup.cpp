// cl: /O1 /MD /Gy /Ireference/shims/bfme2_ascii
// Semantic lead: Open-BFME-1 4367fc698990427e26cc1c399989d074d8ee9bbe,
// game/GameEngine/Source/GameLogic/Map/TerrainLogicNameLookups.cpp,
// TerrainLogic::getWaterHandleByName. Its linked-list layout is not used here.
// Target: Ghidra boundary 0x00282021..0x002820A0 (127B), including the cold
// return at 0x0028209C. Calls StringBase<char>::compare at 0x69B1 (Water Grid)
// and 0x69D6 (entry name). The owner+0x50, store+0x14/+0x18, 8B slot stride,
// slot+4 entry and entry+0x20 name come from target accesses. Unknown bytes
// are padding views; original class, method, slot key and handle types unknown.
// The reference argument and opaque pointer result describe the witnessed ABI,
// not the donor's by-value signature. Cursor constructors shape return storage;
// no original cursor class identity or out-of-line constructor is asserted.
#include "string_base.h"

struct Rva00282021Entry {
    char unknown00[0x20];
    StringBase<char> name;
};
struct Rva00282021Slot {
    char unknown00[4];
    Rva00282021Entry *value;
};
struct Rva00282021Store;
struct Rva00282021Cursor {
    Rva00282021Cursor(Rva00282021Store *s, int i) : store(s), index(i) {}
    Rva00282021Cursor(const Rva00282021Cursor &x) : store(x.store), index(x.index) {}
    Rva00282021Store *store;
    int index;
};
struct Rva00282021Store {
    Rva00282021Cursor begin() { return Rva00282021Cursor(this, 0); }
    Rva00282021Cursor end() { return Rva00282021Cursor(this, last - first); }
    char unknown00[0x14];
    Rva00282021Slot *first;
    Rva00282021Slot *last;
};
// ?rva0007E394CursorEqual present-unmatched
// Target 0x7E394 compares only two DWORDs (29B, no relocations). The full
// bytes match this 8B cursor view; original template identity remains unknown.
// Its range is already covered by ?dup_0007e394 in stlport_pod_hash_bodies.cpp,
// so this byte-identical typed copy adds no row or recovered-byte credit.
extern "C" __declspec(noinline) bool __cdecl rva0007E394CursorEqual(
    const Rva00282021Cursor &a, const Rva00282021Cursor &b)
{
    return a.store == b.store && a.index == b.index;
}

// Target data at VA 0x00DBB710 starts as DWORD 1. The water-height body at
// 0x0027D85B also compares against this sentinel; reuse its existing extern.
void *g_Va00DBB710 = reinterpret_cast<void *>(1);
class Rva00282021WaterLookup {
public:
    void *rva00282021(const StringBase<char> &name);
private:
    char unknown00[0x50];
    Rva00282021Store *store;
};

void *Rva00282021WaterLookup::rva00282021(const StringBase<char> &name)
{
    if (name.compare("Water Grid") == 0)
        return g_Va00DBB710;
    for (Rva00282021Cursor cur = store->begin();
        !rva0007E394CursorEqual(cur, store->end()); ++cur.index) {
        Rva00282021Entry *entry = cur.store->first[cur.index].value;
        if (entry->name.compare(name) == 0)
            return entry;
    }
    return 0;
}
