# Win32Mouse init canonical base adoption

Inspected revision: `3a287f4eb93f65497091bc33218d87a4e6c7304b`.
Scope: `Code/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse_reset.cpp`,
`?init@Win32Mouse@@UAEXXZ`, RVA `0x000419F5`, complete 17-byte body.

Target facts: the existing row calls `Mouse::init` at RVA `0x001EE4DC`
and writes byte 1 at `this + 0x4F9C`. Canonical `Mouse.h` places that byte
inside its opaque `field4F14` array; its base extent is already `0x5010`.
The mechanical adoption retained a derived padding array and therefore failed
the byte check. Removing the private Mouse declaration and derived storage,
then writing `field4F14[0x4F9C - 0x4F14]`, preserves the native offset.
The shared header, symbols, pins and ledger remain unchanged.

Donor fact: the committed Zero Hour reference's
`GeneralsMD/Code/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse.cpp`
implements `Win32Mouse::init` as `Mouse::init()` followed by
`m_inputMovesAbsolute = TRUE`. This explains the existing function identity;
no new BFME2 member name or donor layout is asserted.

Verification:

- `find_declared_unmatched.py` before and after: all defined functions matched.
- `./build.sh Code/GameEngineDevice/Source/Win32Device/GameClient/Win32Mouse_reset.cpp`:
  1/1 matched; string, float and import checks pass.
- `header_adopt_lane.py accept --class Mouse` for this source: PASS;
  tool retired exactly its one `reverse/header_queue.tsv` row.
- `link_check.py` for this source: LINKS, LINKED 17 -> 17 bytes, against
  census `2026-11-04 07:28` at `a62ac1c10b`; current dependency cache.
- No source-specific data, identity or hatch register keys were found.

This retires one header-debt row and preserves this unit's linking prediction.
No new census measurement, TU consolidation or broader Mouse clearance is claimed.
