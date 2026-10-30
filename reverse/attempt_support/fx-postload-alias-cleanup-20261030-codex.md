# FX particle post-load callback alias cleanup

Inspected base: `a5c01ba2ba`; 2026-10-30, seat yasinschroeder-codex.
Source: `Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`.

## Target facts and change

Retail exports 1302 and 1303 name
`FXParticleSystem::DefaultAlphaModuleInfo::LoadPostProcess()` and
`FXParticleSystem::DefaultColorModuleInfo::LoadPostProcess()` respectively,
both at RVA `0x000B3FD0`. The complete native body is `C3` (RET).
The source previously declared each callback as `v1` and used an
`/alternatename` to the existing Coord2D empty destructor at that address.
There were no other source or pin references to those placeholder names.

The declarations now use the exported names, with empty out-of-line C++
bodies alongside the three existing named post-load callbacks in the same
file. `add_match.py --icf-owner '??1Coord2D@@QAE@XZ'` admitted both complete
one-byte bodies, with the Coord2D unit as fold proof. They share the already
owned address: no new native coverage, pin, source path, class layout or
transfer slot is claimed. Two `/alternatename` hatch keys are retired.
No external donor source was used.

## Verification

- Before: normal build passes 368/368 function checks, one data row,
  17 string literals and 10 floating-point literals. Ordinary preview
  against census index `85f6b7f40c` retains LINKS, 5,649 -> 5,649 bytes.
- Both admissions pass the normal source build. The final source passes
  370/370 function checks, its data/string/float checks, and the
  declared-unmatched check (371 ledger rows including existing aliases).
- Raw COFF comparison retains all 680 prior COMDATs. Of these, 678 keep
  identical bytes and relocation names; the remaining two are the
  DefaultAlpha/DefaultColor vftables. Their bytes and sizes are identical,
  with only each +4 relocation changed from `v1` to `LoadPostProcess`.
  Both names still resolve to native B3FD0. The only added COMDATs are
  the two one-byte callbacks. No definition disappears.
- Strict preparation passes 370/370 function checks and the data, string
  and float checks, producing a reusable current receipt. The staged hatch
  check credits alternatename total 2,893 -> 2,891; check_csv passes 99,011
  function rows, 9,415 symbols and 2,235 data rows.
- Ordinary after-preview reports LINKS, 5,649 -> 5,650 authored bytes.
  That overlapping folded body adds zero unique native bytes and is not
  a census linking gain.

Local normal-build, admission, preview, strict-preparation and raw object
comparison artifacts are under `build/fx-postload*`.

## Remaining Snapshot prerequisite

This is a bounded prerequisite to the existing blocked Snapshot adoption,
not acceptance of that header-queue entry. The private one-slot Snapshot
view and existing shorter info vftables remain. Before retrying adoption,
reconcile the nine exported DoXfer providers, signatures and complete
four-slot tables described in
[the previous attempt](fxparticle-snapshot-header-20261027-codexb4.md).
The two post-load providers repaired here are no longer missing; the
other seven post-load providers still need recovery. Keep the Snapshot
header-queue row until the owning acceptance tool passes.

## Outgoing audit boundary

The staged-tree batch audit exits 2, INCONCLUSIVE. Its index `85f6b7f40c`
predates outgoing base `a5c01ba2ba`, and the affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a
current receipt. No whole-consumer loss/selection clearance is claimed.
Carry that consumer, the changed FXParticleSystem provider and its two
vtable references into the next scheduled census. No measurement runner
was launched. The bounded current-object comparison and ordinary preview
above remain the verified scope.
