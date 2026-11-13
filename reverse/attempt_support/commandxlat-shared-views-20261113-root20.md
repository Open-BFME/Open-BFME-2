# Shared CommandXlat consumer declarations

Inspected at `5f3deb924b5`; game source changes are limited to CommandXlat.cpp and one explicit dependency in GameClientDrawableTOC.cpp. No shared header, function row, pin, compiler flag or runtime algorithm changes.

CommandXlat used the older `Common/UnicodeString.h` shim plus a local inline destructor. GameInfo and RecorderClass's shared headers include the canonical Unicode header and therefore collided with that older declaration. Selecting the existing `unicode_string.h` through the source's existing first include path and removing the redundant destructor resolves this integration. Ordinary `header_adopt_lane.adopt` then removes both private GameInfo and RecorderClass bodies.

The active GameInfo dispatch remains through TranslateGameInfo slot 19; retail GameInfo table RVA `0x008193C8` slot 19 targets the admitted `isMultiPlayer` provider `0x003FF3B5`. The removed private slot-11 declaration was unused. Neither GameInfo nor GameSlot is constructed or destroyed in this consumer, and no additional table is emitted.

Before and after, `./build.sh` passes **147/147 function rows** across the three inspected sources. Strict reusable provider preparation also passes; it leaves the census/index/status unchanged and does not check whole-link closure. Every one of the **408 previous COMDAT fingerprints** is unchanged: common fire-weapon 9, DrawableTOC 327, CommandXlat 72. The undefined-symbol sets remain unchanged.

CommandXlat emits two additional canonical template helpers. Independent COFF review found both COMDAT selection ANY, no runtime code/data incoming references, no weak bindings, and exactly one debug reference each:

- `StringBase<unsigned short>::~StringBase`: 5-byte jump with one REL32 to releaseBuffer at RVA `0x00036E70`; matches the existing FireWeaponUpdate object and retail destructor shape at `0x005B804E`.
- `StringBase<unsigned short>::validate`: 1-byte RET, no relocations; matches its existing provider and retail empty body at `0x000B3FD0`.

The old and new literal constructors have identical 18 bytes and relocation to the unsigned-short StringBase constructor, confirming the active wchar_t spelling is compatible. Canonical inheritance adds no virtual table. No new ledger alias or row is needed.

Owning acceptance retires five queue rows: the two new consumer adoptions, two already-shared CommandXlat classes (BfmeSelectionState and Rva0031D5F8), and SubsystemInterface in DrawableTOC. The latter already arrived through MessageStream.h; its direct dependency is now explicit **after** MessageStream.h, preserving the existing subsystem-slot configuration. This is one dependency clarification, not another removed private view. UnicodeString itself passes acceptance with no queue row to retire. UserPreferences and foreign-held FreelistPool remain queued.

The selected CommandTranslator header remains incomplete for the native 0x30-byte polymorphic class. All other queued pairs in the three files were inspected; refused trials were restored. Their prerequisites are recorded separately. Function coverage and authoritative bridge counts do not change.

Latest observed completed authoritative run 43449493373 at c9d82e95: **38 unresolved, 0 duplicates, no image; 468 initializer bridges and 3,331 vtable bridges / 50,310 slots**. These declarations supply no new image or runtime result.

[Machine evidence](commandxlat-shared-views-20261113-root20.json).
