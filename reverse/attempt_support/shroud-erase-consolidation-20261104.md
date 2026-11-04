# Shroud erase consolidation audit

Inspected prerequisite revision: `5890c716fd`. The complete pending source-path
batch absorbs only `Code/Libraries/Source/WWVegas/WWLib/Rva0007300FErase.cpp`
into its approved `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroud.cpp`.
The comparison header added by the prerequisite commit remains at its new path.
This removes one source file and retains both erase rows (0x0007300F, 68 bytes;
0x000733D8, 73 bytes). The map was rebuilt in memory for approval; its committed
diff only repoints these two existing source-column cells, without regenerating
assignments.

## Verification and bindings

- `tu_skeleton.py --merge` accepts seed plus erase donor and passes its guard for
  all three census-linked units, including the rejected interpolation donor.
- `./build.sh W3DShroud.cpp`: 27/27 matched, six funclet pins verified, nine float
  literals and eight named imports verified. `find_declared_unmatched.py` passes;
  the two admitted STL helper definitions are retained from the donor.
- `check_csv.py`: passes, with 99,442 function rows.
- `link_check.py W3DShroud.cpp`: LINKS, 2,030 owned bytes. Against the 2026-11-04
  11:27 census/index at `3a8028f34e`, the old seed and donor jointly owned the same
  2,030 bytes (1,889 + 141). This is preservation in a preview, not a census gain.
- The selected single-iterator erase remains the retail provider at 0x005530A8
  in `stlport_map_int_ptr_o1.cpp`; the declaration-only specialization prevents
  composition under /G7 from emitting a conflicting non-retail COMDAT. No pin,
  alias, provider source or compiler flag changes in the merge.
- `allowed_symbols.py --source`: 72 references, 60 owner, six alias, five EH,
  one wrong. The pre-existing setShroudLevel/custom-allocator binding finding
  remains; this pass does not retire code-identity debt.
- `data_check.py`: zero findings. `tu_ownership.py --staged`: passes.

## Registers and path consumers

Neither donor nor destination has a data-check or code-identity baseline key.
The donor's canonical-header key was accepted by `header_adopt_lane.py` in the
first prerequisite commit. The destination's seven existing class-header keys
remain. The merge tool refreshes the Microsoft-header queue; its existing ABI
conflict remains, with the changed include line recorded. Both admitted helper
hatch keys transfer to the destination, keeping their counts. The unrelated stale
ThingFactory::newObject hatch line removed by the whole-tree updater was restored
unchanged, so this commit does not retire another worker's debt. Across this pass,
only the first prerequisite retires two obsolete begin/end hatches.

Audited `git diff --name-status --find-renames origin/master` through the applied
merge and searched the old full path, basename and slash variants across active
tools, hooks, workflows, source/headers, root configuration, docs and registers.
No active tooling or include consumer needs an update. `functions.csv` and
`tu_map.csv` resolve both rows to the destination. Remaining old-path mentions:
the last measured `link_status.csv` (historical measurement, not rewritten),
attempt evidence/logs, the merge provenance comment and DOTManager's explanatory
comparison comment. These remain historical references. No directory is moved.

## Remaining prerequisites

W3DShroudInterpolate.cpp remains separate: its local iterator comparison first
fails C2995 during composition, and the canonical owning W3DShroud lifetime view
still needs LINK-225's work. No canonical owning-class adoption or full-image
link/runtime result is claimed. See also
[the template prerequisites](shroud-erase-merge-prerequisite-20261104.md).

Publication preflight initially refused the earlier, already-local
BuildingBehavior identity retirement because provider objects were stale.
Normal scoped builds of ToggleMountedSpecialAbilityUpdate, CritterEmitterUpdate,
PartTheHeavensUpdate and RadiateFearUpdate pass; the native identity verdict now
reports no problems or remaining findings for BuildingBehaviorModuleDataDtor.
No source changes were needed for these object-cache repairs.

The following push preflight exposed two publication-accounting issues after
rebasing. The header acceptance preceded a later donor deletion in this batch;
the final range therefore requires the permitted per-key `Debt-Retired` trailer
for a vanished source, despite the earlier passing acceptance. Both row names
and RVAs remain live in the destination, so tombstoning them would be incorrect.
The follow-up commit supplies that trailer and preserves the passing adoption
evidence. Separately, the earlier local BuildingBehavior entry is renumbered
LINK-232 to avoid the upstream LINK-231 entry. Its content and status are kept;
the old filename/ID has no other active path consumer.
