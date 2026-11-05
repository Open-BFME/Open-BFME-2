# Save/load and Lua sound Drawable ID binding

Inspected revision: `3c11d5a83dea905b6f65fe0a021dbae49232ea3b` (2026-11-05).
Scope: ObjectDoXfer.cpp, LuaScriptEngine.cpp and W3DGhostObjectScene.cpp.

## Target facts

The real-link blocker register lists each unit referencing undefined
`?getID@Drawable@@QBE?AW4DrawableID@@XZ`; each original compiled object
independently references that exact name. The existing provider is
`?get@Rva0055A88BDwordField@@QBEHXZ`, rowed at RVA `0x0055A88B` in
`Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp`. Its object defines
that name; retail's complete seven-byte body is `8b 81 00 01 00 00 c3`,
returning the dword at this +0x100.

Each caller independently proves that destination:

| Parent RVA / size | Call RVA | Retail bytes | Destination RVA |
| --- | --- | --- | --- |
| Object::xfer: 0x00297684 / 3414 | 0x002979A7 | e8 df 2e 2c 00 | 0x0055A88B |
| CurDrawablePlaySound: 0x0033382F / 233 | 0x003338BF | e8 c7 6f 22 00 | 0x0055A88B |
| W3DGhostObject::xfer: 0x00063F78 / 694 | 0x00063FD5 | e8 b1 68 4f 00 | 0x0055A88B |

## Repair

Call the existing provider through a declaration-only view and cast its return
to DrawableID, preserving the consumer's ID domain and audio overload. Remove
the unused local Drawable::getID declarations in the ghost and Lua units.
ObjectDoXfer's shared header is unchanged. No recovered provider identity,
donor path or additional layout is asserted. Other callers remain outside scope.

## Verification

- Normal scoped builds before and after pass all 266 function rows and two
  data rows across these three units, including EH handlers and funclets.
  String, float and import reference checks pass.
- Declared-unmatched checks pass before and after; the Lua unit's existing
  accepted unclaimed definition is unchanged.
- Each compiled object's undefined external set removes only
  `?getID@Drawable@@QBE?AW4DrawableID@@XZ` and adds only
  `?get@Rva0055A88BDwordField@@QBEHXZ`. External definitions, weak externals,
  alternate names and /INCLUDE sets are unchanged.
- After fetching the published index, all three previews LINKS: ObjectDoXfer
  3,418 authored bytes, LuaScriptEngine 16,516 and W3DGhostObjectScene 3,908.
  Index: c95fcfcfcd, 2026-11-05 05:17. These unchanged census figures are
  previews; only the next automated real link can confirm blocker removal.
- `git diff --check` passes. No ledger, pin, alias or header edits.

The next automated real link must confirm these three units stop listing the
undefined getter. No full-link success or census improvement is claimed.

## Publication reconciliation

Publishing rebased onto `babe36570d`. Upstream commits `2825058d58` and
`3f56eb6465` had independently bound these same three callers to the same
provider and removed the unused declarations. Conflict resolution keeps those
upstream sources exactly, including their declaration formatting; this outgoing
commit retains independent retail-call and verification evidence only. It
claims no additional source repair or linking gain beyond upstream's work.
The mouseover/UI-transfer and terrain/audio-loop repairs in the earlier local
commits overlap those upstream repairs too; their resolutions keep upstream's
sources and preserve the evidence. The next automated real-link result remains
the confirmation step for the shared cause.
