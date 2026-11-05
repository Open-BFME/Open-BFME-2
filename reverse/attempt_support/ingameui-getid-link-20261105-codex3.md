# InGameUI drawable ID getter binding

Inspected revision: `fa3a400d559cc842f17409b4900ddefaec916faf` (2026-11-05).
Scope: `InGameUICreateMouseoverHint.cpp` and `InGameUIXfer.cpp` under
`Code/GameEngine/Source/GameClient/`.

## Target facts

The real-link blocker register names both units as callers of undefined
`?getID@Drawable@@QBE?AW4DrawableID@@XZ`. Its pin supplies a target address,
not an object definition. The existing provider in
`Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp` defines
`?get@Rva0055A88BDwordField@@QBEHXZ` at that same RVA, `0x0055A88B`.
Retail bytes there are `8b 81 00 01 00 00 c3` (load dword at +0x100).

Retail independently proves both call destinations:

| Parent RVA / size | Call RVA | Retail bytes | Destination RVA |
| --- | --- | --- | --- |
| createMouseoverHint: 0x0029EBE2 / 1901 | 0x0029ECFD | e8 89 bb 2b 00 | 0x0055A88B |
| xfer: 0x002A6AC2 / 1515 | 0x002A6E0F | e8 77 3a 2b 00 | 0x0055A88B |

Each replacement binds that REL32 relocation to the existing provider through
its declaration-only call view. The mouseover assignment explicitly preserves
DrawableID; the transfer local already uses int. No recovered provider name or
new class layout is claimed. LaserUpdate and AnimationSoundClientBehavior
already use this binding; their source is a repair lead, not the target proof.

## Verification

- Normal scoped builds pass all 16 function rows in each unit (32 total),
  including their funclets; string, float and import-reference checks pass.
- Declared-unmatched checks before and after report all bodies matched.
- Both repaired objects reference the existing getter and no longer reference
  the missing Drawable::getID spelling. The provider object defines the new
  reference. Xfer's before/after external sets differ only by this reference:
  definitions, weak externals, alternates and /INCLUDE sets are unchanged.
- After fetching the published index, the combined link preview passes both
  units: 1,913 and 1,947 authored bytes, unchanged. Index: c95fcfcfcd,
  2026-11-05 05:17. This preview already accepted the old spelling and therefore
  does not establish a real-link improvement by itself.
- `git diff --check` passes. No pin, alias, ledger or header changes.

The next automated real link must confirm that both units stop listing this
missing getter. No census gain or full-game link is claimed. Other callers
remain outside this scope; InGameUISelectDrawable.cpp was held by another seat.
