# TargetObj005C8DBF consolidation audit

Result: absorb `Code/GameEngine/Source/Common/Rva005C8FBD.cpp` into
`Code/GameEngine/Source/Common/TargetObj005C8DBF.cpp`, removing one source file
and retaining all nine rows (289 bytes). The preceding view-reconciliation
commit and this merge are the audited batch, based on `be366d041e`.

The Common consolidation evidence snapshot was regenerated after view repair
and passed `name_lane.py consolidate --check` immediately before application.
`tu_skeleton.py --merge` rebuilt the stale TU assignment map in memory, accepted
the destructor donor, and preserved all three census-linked units through its
link guard, including outside-provider and selected-COMDAT checks. The committed
map changes only five source cells; it does not regenerate TU assignments.

Verification:

- `./build.sh Code/GameEngine/Source/Common/TargetObj005C8DBF.cpp`: 9/9 rows,
  three renumbered funclets located through verified parent EH data, one float
  literal verified.
- `find_declared_unmatched.py`: no unrowed definitions; `check_csv.py`: passes.
- `link_check.py` against the 2026-11-05 15:19 census at `f44cbcf5b0`: destination
  and remaining HostClass005C8E0A donor both link. This is preview evidence,
  not a new census measurement or real-link result.
- Six function-source cells and the Holder38FBD fold proof follow the merged
  provider. No definitions or alternatename pragmas were removed; the folded
  Holder38FBD destructor remains emitted, and the external Rva005C8C73
  destructor reference remains unchanged.
- No donor keys exist in the code-identity, data-check, hatch or flag-override
  registers. The existing AudioManager header-queue row stays on the destination.
  The merge tool refreshed header/MS-header reports, producing no queue changes.
- Path/basename searches covered tools, hooks, workflows, source/includes,
  configuration, documentation and path-keyed ledgers. No active hard-coded
  tooling consumer needs updating. Remaining old paths are historical trial/
  census evidence and generated skeleton comments in HostClass005C8E0A; the
  authoritative ledger and fold proof use the destination.

Remaining work: the HostClass005C8E0A donor still fails composition at the
AudioManager/TheAudio declarations; its TargetObj view also disagrees in size
with the destination (0x2c versus 0x38). `tu_views.py --dry-run` records that
conflict; no speculative view was applied. The prerequisite commit's shadow
identity check also reports `uw_007a0e1a` calling `??1Rva005C8C73@@QAE@XZ` where
retail targets the wrapper at 0x005C8D66. The destructor declaration and call
predate this batch; this merge preserves them and does not retire that finding.
