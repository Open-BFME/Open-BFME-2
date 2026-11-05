# InGameUI callers use the recovered Drawable ID accessor

Inspected revision: `bff9d97674a0`, 2026-11-05. Scope: claimed
`InGameUI.cpp`, `InGameUISelectDrawable.cpp` and `InGameUIXfer.cpp`.
`InGameUICreateMouseoverHint.cpp` was peer-held and remains untouched.

## Evidence and change

The default picker still serves the missing `Drawable::getID` blocker from
LINK-534. Current source already contains its real out-of-line provider:
commit `85b46a09f3` defines and rows the seven-byte accessor in `Drawable.cpp`
at `0x0055A88B`, ICF-folded with the opaque disp32 dword getter. Its
[scoped byte check](provider-build.log) passes. This is an existing repaired
provider, not a new recovery or a new regression.

Three InGameUI consumers can therefore remove their private
`Rva0055A88BDwordField` declarations and casts and call `Drawable::getID`
through the existing canonical header. The affected functions are
`isDrawableSelected`, `evaluateSoloNexus` and `xfer`. All source paths,
ledger rows, pins, hatches and debt registers remain unchanged.

## Verification

- Declared-unmatched checks pass before and after for all three files.
  InGameUI.cpp retains the check's pre-existing diagnostic of 37 unclaimed
  definitions; none are added or edited by this change.
- Scoped byte checks pass all 25 function rows and two data rows, including
  nine renumbered funclet bindings: [selection before](build-before.log),
  [selection after](build-after.log), [other files before](batch-before.log),
  [other files after](batch-after.log). String, float and import checks pass.
- The [object audit](object-audit.json), produced by [this script](object-audit.py),
  preserves all 883 external definitions and 880 external COMDATs. Each unit
  removes exactly the opaque getter reference and adds exactly the real
  `Drawable::getID` reference, whose definition exists in Drawable.obj. Every
  COMDAT's bytes, size and relocation tuples remain equal after normalizing
  that substitution and local relocation labels. Exactly one COMDAT
  fingerprint changes in each unit, belonging to the affected function.
  Pre-edit objects remain scratch under `build/drawable-selection-real-getter/`.
- [Current-object link previews](link-after.log) report LINKS for all three
  units against census `c95fcfcfcd` at 2026-11-05 05:17. The InGameUI.cpp
  diagnostics concern unchanged, unreferenced COMDAT variants, which the
  preview does not treat as blockers. No census or real-link gain is claimed.

LINK-534's next step is to verify the now-existing provider and its consumers
in the authorized real-link workflow. This cleanup needs no additional provider,
alias or pin. No real link, census or runtime smoke was run in this session.
