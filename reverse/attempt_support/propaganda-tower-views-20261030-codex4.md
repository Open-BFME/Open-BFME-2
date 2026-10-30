# PropagandaTowerBehavior scan consolidation prerequisite

Base: `53504ff70395e14eb52595b0638719dc12e1439e`.
Scope: the approved PropagandaTowerBehavior TU and its Constructor, DoScan,
ModuleDataCtor2, Update and Xfer donors. All six file scopes were claimed.

## Evidence and change

`name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Behavior/`
was run and regenerated after reconciliation. The committed TU map is stale;
`tu_skeleton.py` rebuilds assignments in memory. No regenerated map is committed.
Seven mixed sources are outside this whole-file merge scope.

`tu_views.py` accepted the UpgradeTemplate and ObjectTracker unions. The former
combines the existing type at +0x04 with the bit index at +0x38. The latter
shares the existing inline constructor/destructor and fields at +0x04/+0x08.
Neither emits an additional COMDAT in the six verified objects.

The seed and DoScan views now also agree on Object, module data and the
behavior's partial flat view. Object's existing position/ID fields occupy
padding at +0x38/+0x74, retaining the seed's body/flags at +0x254/+0x380.
DoScan's radius and pulse pointers retain +0x08/+0x14/+0x20. The seed's
Snapshot/AsciiString module-data declaration supplies the common spelling;
the native field-parse data and existing matched destructor support its
member offsets and owning string. No external donor implementation was used.

The behavior views retain the existing emitted slot calls and field accesses
(module data +0x04, object +0x08, tracker list +0x28, upgrade +0x2c). These
partial views do not establish the complete native hierarchy or vtable.
Constructor, interface-based Update and Xfer reconciliation remains open.

## Verification

- Original sources were rebuilt normally before object snapshots. After the
  change, `link_check.py --prepare-current --paths-from` byte-verified all
  23/23 rows across six sources, the data row and one string literal. No
  baseline, pin, row identity, source path or hatch count changes.
- `eh_verify.py`: all four parent EH graphs EXACT. Renumbered scan funclet
  labels resolve through the verified parent data to the existing addresses.
- `find_declared_unmatched.py` passes all four changed sources.
- Before/after objects contain 68 external COMDATs. All 67 retained names
  have identical digest/size pairs; strong definitions, undefined names and
  weak directives are unchanged. The one private inline getter changes its
  return-type decoration from `...ABEPBUPropagandaTowerBehaviorModuleData...`
  to `...ABEPBVPropagandaTowerBehaviorModuleData...`. Its bytes are identical.
  Normalizing that spelling makes the entire scan object facts and relocation
  graph equal. The published index's touches list the old name only in DoScan;
  no other indexed object consumes it. No new public binding is required.
- The bounded six-source link preview reports LINKS for all six, retaining
  1,674/1,674 bytes against index `12b9e7a7c0` (2026-10-30 10:11). This is a
  prediction, not an updated census figure.
- The staged-tree batch audit (base HEAD, tip from `git write-tree`) is
  INCONCLUSIVE: the published index is older than this base, and affected
  consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt.
  Carry the six providers and affected consumers into the scheduled census;
  full consumer selection/loss verification remains pending.
- The supported merge dry run changes from accepting no donors to accepting
  the seed plus DoScan, retaining 17 rows. The other four donors still fail
  composition on incompatible/missing class declarations. No merge applied
  in this prerequisite commit.

## Reference freshness boundary

The local BFME 1 marker was stale. The checked-out reference is the previously
verified `1d5131d3f193cdf01a99da66ccd6828639585650` (see
`reference-1d5131d3-20261030.md`). Fetching official upstream found newer
`aeb018303`; changing the reference was refused because its file claim is
held by another worker. No submodule or success marker was changed. This
pass reconciles existing BFME 2 source only; it does not claim verification
of the newer donor revision.
