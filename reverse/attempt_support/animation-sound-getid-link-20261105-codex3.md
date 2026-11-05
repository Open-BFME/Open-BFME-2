# AnimationSoundClientBehavior getter binding

Inspected revision: `d992ebcd3c383a995426c411eeff217ce214c620` (2026-11-05).
Scope: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`.

## Target facts

- `reverse/exit_link_blockers.tsv` lists this unit referencing the undefined
  `?getID@Drawable@@QBE?AW4DrawableID@@XZ`. The original compiled object
  independently references that exact name.
- The retail `updateAnimationSounds` row starts at RVA `0x004CA328`, size 811.
  Its call at RVA `0x004CA5C0` has bytes `e8 c6 02 09 00` and targets
  RVA `0x0055A88B`.
- That address already has one matched row,
  `?get@Rva0055A88BDwordField@@QBEHXZ`, in
  `Code/GameEngine/Source/Common/DispDwordFieldGetters.cpp`. Its compiled body
  and retail both contain `8b 81 00 01 00 00 c3`: load the dword at +0x100
  and return. Its provider object defines that exact symbol.
- The existing `Drawable::getID` pin names the same RVA but supplies no object
  definition. The census preview accepts this caller before the repair, so
  that preview alone does not clear the real-link blocker.

## Repair and limits

Declare the existing getter's ABI view beside this unit's other getter view,
call it through a pointer cast and cast the return to `DrawableID` to preserve
the audio-event constructor overload. Remove the unused `Drawable::getID`
declaration. `LaserUpdate.cpp` already uses this provider spelling for drawable
IDs; the target call above independently proves the address here. No donor
name or recovered class layout is asserted, and no pin, alias or ledger row
is added or removed.

The compiled object's external definitions, weak externals, alternatename
directives and /INCLUDE set are unchanged. Its external-reference set removes
only `?getID@Drawable@@QBE?AW4DrawableID@@XZ` and adds only
`?get@Rva0055A88BDwordField@@QBEHXZ`. The latter relocation is REL32 at
offset `0x299` of `updateAnimationSounds`, the retail call above.

## Verification

- `./build.sh Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`:
  functions 31/31 matched; one data row verified; seven funclet rows verified;
  string, float and import-reference checks pass.
- `find_declared_unmatched.py` before and after: all defined functions already
  matched (32 rows reported, two existing unclaimed definitions accepted).
- `link_check.py` after fetching the index: LINKS, 2,316 authored bytes unchanged;
  census index `c95fcfcfcd`, 2026-11-05 05:17. This is a preview, not a new census.
- `git diff --check`: passes.

The repaired object no longer needs the missing name. Other units listed for
the same getter in `exit_link_blockers.tsv` remain outside this claimed scope.
Next: independently claim and verify those callers against their retail call
sites, or recover the provider identity for the family. The next automated
real link must confirm this unit stops appearing; no full-link or census gain
is claimed here.
