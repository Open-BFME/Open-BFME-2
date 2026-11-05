# PartitionManager FlightDeck merge environment, 2026-11-05

Base: `a93edd3b6c58`. Claimed scope: the PartitionManagerImpl TU and its four
whole-file merge donors. The current-map merge trial approves 67 rows; seven
mixed sources remain outside this whole-file merge.

## Target facts and compiler experiments

The FlightDeck vector growth body at RVA 0x00627BC0 releases storage by a direct
call to GameMemory at RVA 0x00030830. The seed's ordinary STLport environment
instead imports CRT free, and enables STLport exception cleanup. These are two
separate causes of the donor's merged byte failure.

- Removing `_STLP_NO_EXCEPTIONS` from the donor adds an SEH frame to growth and
  fails its 255-byte row. Retaining that setting but removing `_CRTIMP=` changes
  the release to an indirect import call and fails the same row.
- `_STLP_USE_MALLOC` is redundant for the existing bfmealloc allocator shim:
  removing it alone preserves all four donor rows.
- Replace both broad allocator/import defines with an explicit allocator
  deallocation specialization, using the existing `_STL::free` GameMemory
  provider. Capture that name before STLport imports the CRT name, as the mixed
  partitionmanager_impl.cpp source already does. All four donor rows still match.
- The seed preserves all 30 rows with `_STLP_NO_EXCEPTIONS`. Its two EH parents
  remain EXACT; this setting affects STLport's templates, while the unit retains
  `/EHsc`. The seed also captures the release helper before its first vector
  include so the merged source does not see an ambiguous imported free.

No alias, pin, class identity, source path or protected-register key is changed
by this prerequisite repair. The helper is an inline source wrapper, not a new
retail identity. This does not resolve the separate manager-layout conflict.

## Verification

- `./build.sh` for the donor: 4/4 rows exact (441 authored bytes).
- `./build.sh` for the seed: 30/30 rows exact (3,278 authored bytes), including
  renumbered unwind labels verified through their parents' EH data.
- `find_declared_unmatched.py` for both sources: all defined functions matched.
- `eh_verify.py` for both: EXACT 2, no missing objects or non-exact EH parents.
- Paired link preview: both LINKS, 3,719 -> 3,719 authored bytes, using the
  census index dated 2026-11-05 05:17 at `c95fcfcfcd`. This preserves preview
  coverage and claims no new census measurement or real-link result.
- Strict `link_check.py --prepare-current`: both sources byte-verified, with
  reusable receipts; no census/index/status mutation.
- Final `tu_skeleton.py --merge ... --dry-run`: accepts the seed and FlightDeck
  donor, 34 rows, under the seed's aligned flags; current link guard passes.
  The helper must be captured in the seed before its first include: merely
  declaring `_STL::free` there leaves the later donor helper ambiguous.

The earlier destructor and result-source rejections remain separate:
specialization placement and incompatible manager/result declarations,
respectively. GetObjectsInRange retains its incompatible `-O2 -G6` override.
Their unchanged failure history is in LINK-292's previous evidence.
