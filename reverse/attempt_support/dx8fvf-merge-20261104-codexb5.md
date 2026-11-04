# dx8fvf declaration-builder consolidation, 2026-11-04

The merge follows the verified shared-view repair and
[compiler-environment reconciliation](dx8fvf-eh-mode-20261104-codexb5.md).
`name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WW3D2/`
was refreshed for the final prerequisite; its snapshot check passed before
application. `tu_skeleton.py` rebuilt stale TU assignments in memory, accepted
only the descriptor-builder donor, and applied the merge itself.

## Result and checks

`BfmeFVFDescriptorVertexDeclaration.cpp` is absorbed into approved retail TU
`Code/Libraries/Source/WWVegas/WW3D2/dx8fvf.cpp`. Source count falls by **one**.
Six code ledger rows move, including the ICF-folded vector destructor and its
EH funclet/handler; five committed-map source cells follow. No map assignments
were regenerated or changed. The destructor's fold proof points to the new
emitter. No bytes or new census-linked coverage are claimed by the move.

- `./build.sh dx8fvf.cpp`: **12/12 code rows**, one data row, fourteen string
  literals; the renamed compiler funclet label resolves through the parent's
  EH data. `check_csv.py` and `find_declared_unmatched.py` pass. The admitted
  old-layout FVFInfoClass constructor remains unchanged.
- The merge's census link guard passed with both old units replaced by one
  object, including its affected-provider/consumer checks. The current-object
  `link_check.py` preview reports LINKS and 2,697 bytes (877 seed + 1,820 donor),
  using census 2026-11-04 11:27 at `3a8028f34e`. The existing unreferenced
  vector `empty()` size diagnostic remains nonblocking. This is no new census.
- Read-only `build.compile_function` against the normal verified merged object
  also proves the implicit `vector<ICoord2D>::_M_insert_overflow` at 0x00181770:
  **259/259 exact bytes, no unresolved references**. Its ledger owner remains
  MapUtil.cpp; no second row was added. The corresponding obstacle entry now
  points to the merged emitter and retains its other prerequisites.

## Batch path/debt compatibility audit

Audit base: `origin/master` at `8b3af2679e`; staged merge over HEAD `b97e366db0`.
The complete pending diff's only removed Code source is this donor; other fleet
commits are preserved. Combined full-path/basename searches covered `tools/`,
`.githooks/`, `.github/`, Code includes and declarations, docs, and reverse
ledgers/registers. No active tooling, workflow, include or build consumer names
the removed file. Doxygen already lists only the destination TU. Active ledger
source cells and the folded destructor's proof resolve to the tracked destination.
The sole old-path source comment records provenance. Old obstacle repair records,
attempt support, `stlport_trial.csv` and census `link_status.csv` are historical
observations, not active source owners, and remain intact.

Neither path has code-identity/data debt, header-queue or Microsoft-header-queue
entries to transfer or retire. Rechecked the relevant registers after the move;
none point to the removed source. The merge invoked the owning hatch-counter
update, which produced no diff: the seed's two existing alternatenames and its
old constructor marker remain, with no hatches removed or added. No retirement,
whitelist or baseline exception is claimed. The only map edit is mechanical
source repointing by `tu_skeleton.py`.

## Remaining prerequisites

AngleFXInfoVectorInsertOverflow retains its incompatible flag override.
StructureToppleUpdate retains ICoord2D and Windows declaration conflicts.
Rva00181500Finish is still refused because the composition breaks another
unit's AngleFXInfo allocator-proxy binding. Their sources and rows are untouched.
The three mixed files (MapUtil, GapLeavesSeat8 and stlport_vector_pair) remain
satellites; this merge does not solve MapUtil's duplicate or make its implicit
STLport row carveable by spelling.
