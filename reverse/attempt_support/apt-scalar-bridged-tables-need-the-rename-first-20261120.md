# Three bridged Apt scalar tables cannot be re-based under their Rva names

Tables 0x008EA4C0, 0x008EA560 and 0x008EA600 (`??_7Rva006D8510@@6B@`,
`??_7Rva006D86F0@@6B@`, `??_7Rva006D88B0@@6B@`) sit in
`reverse/vtable_bridge_queue.tsv` as `bridged` / `bridge-retirement`. Their
destructors all live in `Code/GameEngine/Source/Common/Rva006DE350Derived.cpp`,
the same unit whose other two classes were repaired today
(`vtable-008ed808-apt-int-value-20261114.md`).

**That repair does not transfer to these three.** The reason is specific and
measured, not a judgement about effort.

## They are AptValue tables, with two more overrides

`tools/vftable_map.py --va 0x00CEA4C0 / 0x00CEA560 / 0x00CEA600`: all three have
15 slots and agree with `AptValue`'s own table except at slots **2, 9, 12, 13**
and 14:

| slot | AptValue | 0x008EA4C0 | 0x008EA560 | 0x008EA600 |
| ---: | --- | --- | --- | --- |
| 2 `ForceDelete` | 0x006CBCD0 | 0x006D8670 | 0x006D8810 | 0x006D8A20 |
| 9 `DeleteThis` | 0x006CBCF0 | 0x006D8670 | 0x006D8810 | 0x006D8A20 |
| 12 `IsGarbageCollected` | pure | 0x0073B660 | 0x0073B660 | 0x0073B660 |
| 13 `RegisterReferences` | pure | 0x0069E440 | 0x0069E440 | 0x0069E440 |
| 14 deleting dtor | — | 0x006D84E0 | 0x006D86C0 | 0x006D8880 |

Slots 2 and 9 share one address per class, so each class's `ForceDelete` and
`DeleteThis` are one retail body serving two slots.

## Why the opaque re-base is impossible

Slots 12 and 13 are the easy pair and are exactly what was landed today for
0x008ED808 and 0x008ED844: `return false;` and `{}`, no external reference, so
they can be written under any class name and rowed as ICF twins.

Slots 2 and 9 cannot. That body is already rowed three times in
`Code/GameEngine/Source/Common/VslotSmallBodiesP.cpp` (15 bytes each) and it
pushes `this` onto a per-class free list:

    void Rva006D8670::rva006D8670()
    {
        m_next = (Rva006D8670 *)g_aptIntegerFreeList;
        g_aptIntegerFreeList = (AptInteger *)this;
    }

Those globals are declared with class types, and MSVC puts the class name in
the decorated name. Built and read off the object:

    ?g_aptIntegerFreeList@@3PAVAptInteger@@A
    ?g_aptFloatFreeList@@3PAVAptFloat@@A
    ?g_aptBooleanFreeList@@3PAVAptBoolean@@A

A TU can only bind those symbols by spelling the pointee `AptInteger`,
`AptFloat`, `AptBoolean`. Declaring the same global as `Rva006D8510 *` yields
`?g_aptIntegerFreeList@@3PAVRva006D8510@@A`, a different symbol; `void *` gives
`?g_aptIntegerFreeList@@3PAXA`, also different. So an override of slot 2 or 9
written in a class named `Rva006D8510` cannot reach the free list the body
needs. **The rename has to come first.**

This is the general boundary the two repairs today sit on either side of: a
bridged table whose own overrides are self-contained can be cleared by a link
seat under the placeholder name; one whose overrides touch a class-typed global
or member cannot, and belongs to the naming lane.

## The rename already has its evidence

Each table ties to one class through its own rowed slot-2/9 body and that
body's global, with the installer agreeing:

| table | slots 2/9 body | its free list | installer on the table |
| --- | --- | --- | --- |
| 0x008EA4C0 (`Rva006D8510`) | `?rva006D8670@Rva006D8670@@QAEXXZ` | `g_aptIntegerFreeList` | `?Create@AptInteger@@SAPAVAptValue@@H@Z` |
| 0x008EA560 (`Rva006D86F0`) | `?rva006D8810@Rva006D8670@@QAEXXZ` | `g_aptFloatFreeList` | `?ClearPool@AptFloat@@SAXXZ` |
| 0x008EA600 (`Rva006D88B0`) | `?rva006D8A20@Rva006D8670@@QAEXXZ` | `g_aptBooleanFreeList` | `?Create@AptBoolean@@SAPAVAptValue@@_N@Z` |

`VslotSmallBodiesP.cpp` states the same mapping in its own comment ("The
AptInteger, AptFloat and AptBoolean free lists (heads at VA 0x00E18020,
0x00E18024 and 0x00E18028), popped by their Create bodies and drained by
AptScalarClearPoolsBFME2.cpp"). The three rowed bodies' notes independently
place the slots: "vtable slots at VA 0x00CEA4C8/0x00CEA4E4" is slots 2 and 9 of
0x00CEA4C0, and likewise for the other two.

Caveat, not resolved here: `vftable_map` also lists
`?rva006D7D00@@YAPAVAptString@@PAVRva006DD6C0@@@Z` among 0x00CEA4C0's installers
and `??3AptActionQueueC@@SAXPAXI@Z` among 0x00CEA560's. Those are not accounted
for by the free-list tie and should be understood before the rename lands.

## What a naming seat should do

1. `rename.py` the three classes to `AptInteger`, `AptFloat`, `AptBoolean`,
   carrying their destructor rows (`??1Rva006D8510@@UAE@XZ` 0x006D8510,
   `??1Rva006D86F0@@UAE@XZ` 0x006D86F0, `??1Rva006D88B0@@UAE@XZ` 0x006D88B0),
   their deleting destructors (0x006D84E0, 0x006D86C0, 0x006D8880) and the three
   `Rva006D8670` member bodies.
2. Then re-base each on `Code/Libraries/Source/Apt/AptValue.h` in both of its
   units, exactly as 0x008ED808 and 0x008ED844 were done today: layout is
   `AptValue` (8 bytes) plus the free-list link at +8, keeping `sizeof` 0xC.
3. Then row slots 2, 9, 12 and 13 with `add_match.py --icf-owner`. Slots 2 and 9
   land at the same address as two ICF twins of the existing
   `Rva006D8670` body; 12 and 13 take `?Rva0073B660False@@YA_NPAXH@Z` and the
   shared one-byte RET as owners.

Measured today, so it need not be re-derived: deriving one of these classes from
`AptValue` leaves the 11-byte destructor and the 35-byte deleting destructor
byte-identical, and the two units' `??_G` and `??_7` COMDAT copies come out with
identical digests.

## Reproducing

    python3 tools/vftable_map.py --va 0x00CEA4C0   # and 0x00CEA560, 0x00CEA600
    ./build.sh Code/GameEngine/Source/Common/VslotSmallBodiesP.cpp
    # then read the FreeList symbols out of its object: all three carry the
    # class name in the decorated global
