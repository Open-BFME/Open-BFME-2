# dx8fvf AngleFXInfo allocation-and-copy consolidation

Inspected revision: `a615f92744`, 2026-11-05. This follows the local
allocation-proxy prerequisite ([evidence](dx8fvf-angle-proxy-20261105-codexb.md)).
One source file is removed; no new matched or census-linked bytes are claimed.

## Placement and composition

The existing 78-byte code row at RVA `0x00181500` is approved for
`Code/Libraries/Source/WWVegas/WW3D2/dx8fvf.cpp` by the current TU inputs.
`name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WW3D2/` was
rerun after the prerequisite and read before applying the merge. Its original
paths, alternatives and mixed-routing warnings are investigation evidence;
placement approval comes from the current TU map, rebuilt in memory by the
merge engine. The committed map changes only this row's source field.

`tu_skeleton.py --merge` accepts the seed and Rva00181500Finish.cpp, verifies
all 13 code rows, deletes the donor, and repoints functions.csv and tu_map.csv.
The seed's data row stays with the same owner. The census-linked composition
guard passes, including the affected-copy check that originally refused the
allocator proxy. No alias, pin, private class, shared header or compiler flag
is added. Both existing link-wide alternatename providers remain intact.

## Verification and debt ownership

- `./build.sh .../dx8fvf.cpp`: 13/13 code rows, one data row, 14 string
  literals, and named import/float checks pass using the final path's current
  object receipt. No baseline is used for those checks.
- `find_declared_unmatched.py`: all defined functions already matched.
- `eh_verify.py`: the single EH row is EXACT; none absent or baselined.
- `check_csv.py`: 99,475 function rows, 9,321 symbol rows and 2,268 data rows;
  OK. The merge changes no row count, extent or identity.
- `link_check.py`: LINKS, 2,775 bytes (2,697 seed + 78 donor). Index census:
  2026-11-05 15:52 at `112a456a2c`. This is a preview, not a new measurement.
  `--new-variants` also passes. The existing unreferenced ICoord2D-vector
  `empty()` diagnostic remains nonblocking; it was present before composition.
- Data identity: zero findings. Code identity remains in shadow and reports
  that same `empty()` divergent definition. Neither source has code/data debt,
  header-queue or MS-header-queue keys to retire or transfer.
- `tu_skeleton` runs hatch_counters --update. All occurrence counts are kept;
  its only baseline diff consumes the existing pin-admission allowance token
  at `0x0014F3C4`, retaining the count of 220. No pin or alias is removed.

## Tooling compatibility audit

Audited the full pending range from origin/master `85ca8f6bbf2f` through
`a615f92744` plus this merge. Its path removals are ActiveBodySetMaxHealth.cpp
(the earlier queued merge) and Rva00181500Finish.cpp. A combined repository
search for both basenames and source paths, including hidden hook/workflow
files, tools, source/header includes, build/configuration files and active
registries, finds no extra active consumer needing a path change. Scoped
searches of code/data debt, header/MS-header queues, data ownership and
fold-proof registers confirm current owners. The earlier ActiveBody transfer
retains both destination header obligations; no debt is retired here.

Surviving old paths are historical link_status.csv census rows, attempt
records, merge-origin comments, this obstacle's history, and the descriptive
shared-specialization comment in AngleFXInfoVectorInsertOverflow.cpp. None
opens or compiles the removed files. Temporary tu_skeleton sources are gone.
The final TU's current object, composition guard and normal commit checks
provide the new-path verification; old object receipts are not reused as proof.

## Remaining prerequisites

The untouched AngleFXInfoVectorInsertOverflow.cpp donor's empty flag override
costs the destination three region-default rows. StructureToppleUpdate.cpp is
still rejected for ICoord2D and HMODULE declaration conflicts. The three mixed
satellites remain intact. Those need separate verified prerequisites before
another supported merge. Full-image link and census confirmation remain for
the scheduled measurement; this pass reduces source count by one only.
