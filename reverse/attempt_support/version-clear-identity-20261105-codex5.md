# Version-record clear: retire the wrong destruction binding

Inspected base: `10918f451d52d9683b1823bd804a8cc12fa9d411`.
Scope: `Code/Libraries/Source/WWVegas/WWLib/StlportVectorGrowthFootprints.cpp`,
clear row `0x004282EF` (30 bytes), and its existing provider
`destroyVersionRecords` in `Code/GameEngine/Source/Common/VersionDestructor.cpp`.

## Target facts and change

The clear row calls retail `0x002385E6`, whose ledger owner is
`destroyVersionRecords(void *, void *)`. That complete 25-byte loop destroys
24-byte entries through the destructor at `0x00238580`. The formerly emitted
generic `_Destroy<BfmeNarrowRecord00427F75 *>` instead reached the different
destructor at `0x0022CCEF`. The earlier range-erase repair documents the same
distinction in [its evidence](version-range-direct-20261024/readme.md).
Equal strides do not establish equal element identities.

A forced-inline explicit specialization now forwards the clear call to the
existing native provider. Explicitly instantiate `__destroy_aux` to retain
its separate 25-byte row at `0x0022D928` and the footprint's 28-byte scalar
deleting destructor at `0x0022D0C9`. The first specialization-only trial
stopped emitting those two rows; the final source retains both and verifies.
No new type identity, layout, name, pin, alias or recovery is claimed.

The saved original object came from the normal scoped builder. Comparing
external code definitions with `allowed_symbols.Obj` and `digest` finds
429 before and 427 after, no added definitions, and exactly one changed
surviving definition: the clear row. Its bytes remain
`568bf1ff7604ff36e8000000008b3685f65959740756e800000000595ec3`.
Only its REL32 at offset 9 changes, from the generic `_Destroy` name to
`?destroyVersionRecords@@YAXPAX0@Z`; offset 23 still references `_free`.
The two removed unrowed definitions are the generic `_Destroy` and its
`__destroy` wrapper for this footprint. The identity scanner's complete
ledger-object inventory has zero missing objects and zero remaining object
referrers to either removed name. No linker directive was removed or changed.

## Verification

- `./build.sh` on the edited source: 81/81 matched rows, all literal,
  float and import checks pass. Declared-unmatched check passes.
- `link_check.py --prepare-current` on the source and VersionDestructor:
  121/121 rows and one data row pass; 18 literals and two empty strings
  verify; both providers have strict reusable receipts.
- `eh_verify.py` on those two providers: EXACT 14, zero baselined,
  missing-object or non-exact rows.
- `allowed_symbols.py --source` on the edited source: 234 references
  (165 owner, 63 fold, 5 EH, 1 alias); zero rows with a wrong binding.
- The first retirement refused stale/missing verification inputs without
  changing the register. Normal `./build.sh` on its 36 missing/stale
  provider units then passes 1,319/1,319 rows and nine data rows, including
  11 complete STLport constructor folds, 245 literals, 50 empty strings,
  123 float literals and 53 named imports. No provider source was edited.
- `repair_queue.py retire identity` then passes and removes exactly the
  source's one wrong-binding key, with zero remaining findings.
- `check_csv.py`: OK (99,455 function rows, 9,322 symbols, 2,268 data rows).

## Link preview and remaining measurement

Ordinary paired `link_check.py` predicts LINKS for both providers against
the published index at `c95fcfcfcd`, dated 2026-11-05 05:17: 6,470 and
1,289 authored bytes respectively, unchanged at 7,759 total. This repairs
identity debt, with no claimed linked-byte gain or new census measurement.

The staged-tree `link_batch_audit.py` against the inspected base exits 2:
the index predates the base and the first affected consumer without a
current receipt is
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`.
The wider affected-consumer selection remains unverified; carry the edited
provider into the next scheduled census/current-receipt audit. The paired
preview and identity verdict do not clear that wider scope.
