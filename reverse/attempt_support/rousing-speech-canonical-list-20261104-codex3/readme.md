# RousingSpeechUpdate canonical list prerequisites

Inspected base: `676354884a`. Scope: the approved RousingSpeechUpdate TU and
its four whole-file donors, reserved by the default picker's file claims.
The Update-subsystem consolidation planner was regenerated before the trials.

## Applied repair

The seed and behavior destructor include the existing canonical
`GameLogic/Module/Rva0029FB3BMember.h` instead of defining private list views.
The seed retains its existing ObjectID node/iterator representation through
local inline begin/end helpers over the canonical sentinel pointer. The native
list element and node evidence is unchanged.

The destructor's virtual base now has 0x84 bytes after its four-byte vfptr,
placing the actual four-byte list member at +0x88. Its body resets that member;
the member's implicit destructor invokes the existing 0x00268902 owner. This
replaces the empty private list view, raw +0x88 receiver, and separate
`PoolMember::Rva00268902` call. No shared header, pin, alias or compiler flag
changes.

## Verification

- `./build.sh` passes independently for the seed (25/25 rows) and behavior
  destructor (1/1, complete 60-byte body).
- `find_declared_unmatched.py` passes for both edited sources.
- `header_adopt_lane.py accept --class Rva0029FB3BMember SOURCE` passes for
  each source and retires exactly those two header-queue rows. The behavior
  constructor's separate list queue row remains.
- `link_check.py --prepare-current` verifies all 26 rows with strict reusable
  receipts, including string/float/import checks.
- The combined ordinary `link_check.py` preview reports both sources LINKS,
  preserving 1,181 + 60 = 1,241 authored bytes against the census index measured
  at `8c757ea0db` (2026-11-04 17:56 UTC). This is a prediction, not a census gain.
- `check_csv.py` passes (99,450 function rows, 9,328 symbol rows, 2,268 data rows).

The commit hook initially reports one shadow `wrong/unknown` binding for
`??1Rva0029FB3BMember@@QAE@XZ` at 0x00268902. Its selected definition is the
29-byte destructor in `Common/Rva004DF418Finish.cpp`; the cached object still
references `g_freeList` even though the current source uses `g_freelistPool+8`.
Building that unchanged provider through `./build.sh` passes all four rows.
Repeating `allowed_symbols.py --source .../RousingSpeechUpdateBehaviorDtor.cpp`
then reports three references (one owner, one fold, one alias) and zero wrong
bindings. No source or register change is needed for this stale-object finding.

Publication also rebased the preceding queued TBuff consolidation. Its
Microsoft-header queue conflict is resolved by retaining both the upstream
WeaponSet row and the TBuff row; the following existing TBuff verdict commit
still retires only its own row. TBuff passes all 25 rows after resolution.

## Consolidation boundary

Both the initial and final supported merge dry runs accepted zero of four
donors; the final output is in `merge-dry-run.log`. The
non-applying `tu_views.py` report after this repair still identifies conflicting
behavior base clauses, module-data `novtable`, filter-member storage, and the
trigger Object view's nested type. These conflicts are not resolved by list
header adoption. No donor is removed, no source path or ledger row moves, and
no matched or census-linked coverage gain is claimed.

The remaining first steps are to reconcile the actual SpecialAbilityUpdate
base and derived special-member declarations, then resolve the module-data
storage/declspec and trigger fields. The final merge's `adopt_first` list no
longer includes the two repaired sources; it retains list/SpecialAbilityUpdate
for the behavior constructor and SpecialAbilityUpdate for the trigger.
