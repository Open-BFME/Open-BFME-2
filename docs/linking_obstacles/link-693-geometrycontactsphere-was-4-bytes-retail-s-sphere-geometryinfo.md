# LINK-693: GeometryContactSphere was 4 bytes; retail's sphere GeometryInfo is 0x5C, and attacking crashed

**Status: Fixed 2026-11-18.** Same defect class as
[globals constructed into storage smaller than retail's object](globals-constructed-into-storage-smaller-than-retail-2026-11-04.md)
and [LINK-678](link-678-g-aptdateinterpreter-was-72-bytes-retail-s-interpreter-is-0x6c.md).

## Symptom

In a skirmish, right-click attacking an enemy with a ranged unit froze the game (window minimised, sound
looping). It reproduced in the plain build linked from master. The freeze was a crash: the game's
`DebugExceptionhandler` turned the fault into `abort()`, the CRT "Runtime Error!" box took focus, and the
window procedure then deadlocked on the Miles audio mutex while handling activation.

## Evidence (minidump `crash-attack-30776.dmp`, plain image, map base 0x02000000)

- The original `EXCEPTION_RECORD` on the main thread's stack is an access violation writing address 0x7 at
  image RVA 0x8297C8: `inc dword ptr [eax]` in the narrow `StringBase` copy constructor (retail 0x000365F0,
  in our map under `BfmeTailF5::copyFrom`). Its CONTEXT has eax=7 and ecx=0x04B0EB9C. A second access
  violation (RVA 0x41E691) is later on the stack, raised inside the exception handling. It is not the cause.
- The call chain is `AIAttackFireWeaponState::update` → `Object::fireCurrentWeapon` →
  `Weapon::privateFireWeapon` → `WeaponTemplate::fireWeaponTemplate` → `adjustTargetPositionOnVictim` →
  `Object::getWorldspaceBestContactPoint` → `GeometryInfo::getBestContactPoint` →
  `GeometryInfo::CollidesWith`+0x1C8. Retail's CollidesWith calls the same copy constructor at the same
  offset (0x006BED48 → 0x000365F0), so the binding is right and the data is wrong.
- `getBestContactPoint` tests each contact point against the static sphere `GeometryContactSphere` (retail RVA
  0x00A0C150, built by the rowed initializer 0x007B6640 with placement new). `Rva007B6610.cpp` defined it
  as `unsigned GeometryContactSphere;`, 4 bytes. In the map `bfmeObjDAE` (the Apt `EAStringC[178]` table) was
  8 bytes later. The dump shows the sphere's shape vector begin/end (+0x2C/+0x30) as 0x04B0EB80/0x04B0EB98.
  Those are two of `bfmeObjDAE`'s string pointers, inside the Apt property-name pool (`_highquality`,
  `_left`...). So CollidesWith walked string bytes as 36-byte `GeometryShape` records. The record's name
  `AsciiString` was the word 7, and copying it faulted.
- Retail reserves 0x00A0C150..0x00A0C1B4 (0x64 bytes; the next ledger global is `_g_rva006C4E30Guard` at
  0x00A0C1B4). `Geometry.h` checks `sizeof(GeometryInfo) == 0x5C`.

## Repair

Following the register's rule for a data-rowed name: `GeometryContactSphere` is now
`unsigned GeometryContactSphere[sizeof(GeometryInfo) / sizeof(unsigned)]` (92 bytes) in `Rva007B6610.cpp`. The three
units that name it (`GeometryInfoCollidesWith.cpp`, `Rva007B6A00AtexitThunks.cpp`,
`Rva007B6A00AtexitThunks_Rva007B7786.cpp`) declare it `extern unsigned GeometryContactSphere[];`. The data row
becomes `?GeometryContactSphere@@3PAIA`, 92 bytes. Every use takes `&GeometryContactSphere`, so the matched
bodies are unchanged apart from the relocation's symbol name. `reverse/data_ledger.csv` is generated and is not
edited here.

Not verified at runtime by this seat: the fix still needs a skirmish attack test.
