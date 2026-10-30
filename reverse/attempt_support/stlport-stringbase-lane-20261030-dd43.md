# Private StringBase copies: what remains after dd-43 (2026-10-30)

Lane: fleet priority 2, remove a unit's private `template <typename T> class StringBase`
and use the frozen `reference/shims/bfme2_ascii/string_base.h` under
`/DBFME_STRINGBASE_PUBLIC_DTOR` (dd-24/dd-31/dd-33/dd-40 method). 25 files converted in
this pass; every one byte-verifies and commits with 0 new shadow code-identity findings.

## Method that works

1. Replace the private block with

   ```
   // The canonical frozen StringBase replaces the private copy; its switch makes
   // the member dtor reachable and keeps the teardown an out-of-line call to the
   // rowed releaseBuffer (0x00036410 narrow, 0x00036E70 wide).
   #define BFME_STRINGBASE_PUBLIC_DTOR
   #include "string_base.h"
   ```

2. Add `/Ireference/shims/bfme2_ascii` to the `// cl:` line.
3. `./build.sh <file>`; the row count must stay the same.

The narrow teardown stays a call to 0x00036410 and the wide one to 0x00036E70. Files whose
dtor has EH funclets still match: build.py re-binds the renumbered `$L` labels through the
parent EH data (e.g. `$L407 -> $L703 at 0x00781D2B`).

## The one shadow finding this lane still hits

```
code identity: binding: <source> | $Lnnn | ??1?$StringBase@D@@QAE@XZ | 0x0048BA39 | wrong
```

`allowed_symbols.py --source <file>` reports it as `wrong/extent: 1`. It appeared on 3 of the
25 attempted files and those commits were dropped:

- `GameNetwork/Rva004D65DCDtor.cpp` (5 rows)
- `GameClient/Rva0029B816Dtor.cpp` (4 rows)
- `Common/Rva004703E0Finish.cpp` (3 rows)

All three have a `StringBase<char>` member and an EH funclet. `LifeEventModuleInfoDtor.cpp`,
`RenderObjectDrawModuleInfoDtor.cpp`, `ParticleSystemFXNuggetDtor.cpp` and nine others also
have EH funclets and StringBase<char> members and do **not** report it, so the trigger is not
simply "EH plus a char member". A seat that can rebind the funclet name (or show the binding
is a tool false positive) recovers these three from the recipe above.

## Walls, by kind (files still carrying a private copy)

Default-ctor access (C2248 on `string_base.h(120)`; the shim keeps `StringBase()` private and
only friends `AsciiString`/`UnicodeString`). Every one of these constructs or implicitly
constructs a member in its own TU:

- `Common/Rva0020D583Dtor.cpp` (5 members, implicit ctor instantiated)
- `Common/OpaqueScalarDeletingDtorsB19.cpp`
- `Common/Rva005CCC07Dtor.cpp`
- `GameLogic/Object/Upgrade/BaseUpgrade.cpp`
- `GameNetwork/NetCommandMsgCtor.cpp` (32 rows; `Rva004D6134` default-constructs `m_1c`)
- `GameLogic/Object/Rva003FD789Ctor.cpp`, `GameLogic/Object/Rva003FD7CEParse.cpp`,
  `Common/Rva002E0906Ctor.cpp`, `Common/Rva00417F7CInit.cpp`,
  `Libraries/Source/WWVegas/WWLib/Rva0002C4FDCtor.cpp`,
  `Libraries/Source/WWVegas/WWLib/Rva004FAC21Ctor.cpp`,
  `Libraries/Source/WWVegas/WWLib/Rva004FAC4F.cpp`,
  `Libraries/Source/WWVegas/WWLib/Rva004FA830Ctor.cpp`,
  `GameLogic/Object/Rva001FA8DDParse.cpp`, `GameNetwork/GameSpyOverlay_RaiseGSMessageBox_YAXXZ.cpp`

A public-default-ctor switch on the shim (a reference change, maintainer decision) would clear
this whole group; dd-40 reached the same conclusion from `StrategicInGameUI.cpp`.

`typedef StringBase<char> AsciiString;` in the unit (C2371 at the typedef): the shim's
`friend class AsciiString;` declares the name as a class, so the file's typedef conflicts.
`Common/Rva0045EF90Dtor.cpp`, `Common/Rva007401F6Dtor.cpp`, `Common/BaseUpgrade.cpp`.

Private copy ctor / friendship used by the unit (`friend class ...` plus a private
`StringBase(const StringBase&)`): `GameLogic/Object/Rva0033BEF5Make.cpp`,
`Common/Rva000BB491Copy.cpp`, `GameDevice/.../W3DFloorDraw_doDrawModule.cpp` (by-value
StringBase parameter), `Bfme/Rva005E8908Dtor.cpp` (public pinned copy ctor 0x00037050),
`GameDevice/.../W3DSupplyDrawBoneStatus.cpp` (custom `StringHeader` view),
`Common/RvaTreeValueEraseFamily.cpp` (friend-only declaration, 64 rows),
`Common/Win32Mouse.cpp` (friend plus inline `str()` over `m_data->data`),
`GameDevice/.../W3DDisplay.cpp` (33 rows, public default ctor plus `set`/`concat`).

Layout placeholders, not real copies: `Common/Rva004D9A3CVectorDeletingDtor.cpp` uses
`char m_pad[8]` to hold a 28-byte element; the shim's 4-byte object shrinks the class
(`push 0x1c` becomes `push 0x18`). Leave it.

Already shipped by dd-40 and not touched here: `Rva00448089Dtor.cpp`, `Rva005396E6Dtor.cpp`,
`Rva004D60CADtor.cpp`, `Rva004D6208Dtor.cpp`, `Rva00216094Dtor.cpp`, `Rva003F9FE6*`,
`Rva00413B16ElementCopy.cpp`. Dropped by dd-40 for findings and left alone:
`Rva003560ED` (landed by another seat), `Rva003B1101`, `Rva00469D86`, `Rva0040AFF3`,
`Rva0048C200`, `Rva00238B90`, `Rva001DBC77`.

Rows whose body IS a StringBase member (`StringBase*` sources, `string_base_clear.cpp`,
`stlport_*` shards): never convert.
