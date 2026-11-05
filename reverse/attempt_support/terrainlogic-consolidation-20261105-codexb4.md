# TerrainLogic composition and retained-record reconciliation

Date: 2026-11-05. Inspected revision: `e06b0b97c9` (reconciliation included).
Claimed the seed and all 24 clean donor file scopes before trials.

## Current placement and merge result

The Map consolidation planner reports a stale committed map and incomplete
structural routing; it does not grant approval. The supported merge rebuilds
the map in memory: 315 approved destination rows, 23 mixed sources and two
refused sources. No regenerated map is committed.

With census index `c95fcfcfcd` (2026-11-05 05:17), the merge reaches compilation.
The earlier `tu-merge:TerrainLogic.cpp` attempt's stale split-residual duplicate
is not the current reported blocker. Both supported dry runs accept no donor.
No source file was removed and no ledger row moved.

## Landed source reconciliation

The seed's Rva0027EA49 record had a raw TargetRef00217D4C pointer at +4 and no
assignment declaration. The existing erase donor's matched assignment at
0x0027F589 copies +0 and calls the retained-reference assignment for +4.
The seed now uses the existing TreeHintRef00217D4C wrapper and declares that
assignment. This expresses the existing retained-reference ABI without
claiming an original record name or application role.

`./build.sh TerrainLogic.cpp` matches 149/149 rows, with 18 EXACT EH rows,
51 funclet bindings, four literals plus the empty string, 50 float literals
and 26 named imports. A COFF comparison against the saved original object
has identical 256 external definitions, undefined references, COMDAT names
and digests, and weak externals. There is no provider/binding change from
this declaration-only reconciliation.

## Isolated erase-pair trial

The supported retry no longer reports C2600 for the assignment declaration.
A diagnostic trial using tu_skeleton's compose/Verifier with just the seed
and Rva002821CFErase.cpp separates two remaining problems:

- `union-first` puts the merged record declaration after the seed's explicit
  STL instantiations, producing undeclared-type errors. The full merge's
  abbreviated report for this donor was only `compile: `.
- `first` compiles and matches 151/153 rows. The unmatched rows are the 29-byte
  copy dispatcher at 0x00281AB7 and 55-byte erase at 0x002821CF. The expected
  template dispatcher symbol is absent; the object instead has an undefined
  non-template `?__copy_ptrs@_STL@@YAPAURva0027EA49@@PBU2@0PAU2@ABU__false_type@1@@Z`.
  The erase symbol is emitted. Changing /Ob2 to /Ob1 in the scratch candidate
  leaves the same two rows unmatched.

The seed uses `reference/shims/bfmealloc/stl/_algobase.h`, whose copy-dispatch
tag parameter is by value and whose implementation is force-inlined. The donor
uses STLport 4.6, where that tag is passed by const reference. This is a concrete
header/API prerequisite for composition; changing only the record view does
not resolve it. Next inspect the effective overload declarations and reconcile
the STLport/header configuration while preserving every seed row and provider.
Do not add an alias or change the shared shim merely to force this pair through.

Other donors still report canonical-header/private-view conflicts (including
SubsystemInterface and TerrainLogic), incompatible STL allocator declarations,
or byte losses. RailroadGuideAIUpdate's flag override costs 121 seed rows.
The Clear donor uses AreaRefValueView::pointer, whereas the seed's wrapper
uses m_ptr; tu_views correctly reports these incompatible private field types.
These donors need their own verified reconciliation before another broad trial.

## Final checks and limits

The separate erase donor passes 4/4 byte checks. Both defined-function checks
are clear. The final paired link preview passes 2/2 units, 13,569 -> 13,569
bytes, against the downloaded index; this is a preview, not a new census.
Code/data identities and path ownership stay unchanged. No protected keys,
header queue rows, hatches or aliases were removed. No path-consumer update
is needed because neither source moved. The pre-commit hook passed the seed's
byte, data, EH and converged checks; its shadow identity findings do not imply
an improvement and the object comparison shows they were not changed here.

Progress before composition: SOURCE FILES 18,188, BYTE-MATCHED 100.00%.
No source-file reduction or linked-byte gain is claimed. No real link, nightly,
boot or game smoke runner was started.
