# Cylinder emission writer export identity

Inspected base: `85d0ac929f8`, 2026-11-06. Owner:
`codex-20261106-round2-seat2`, namespace `refs/claims/`.

## Target and freshness

The ordinary picker twice drew the already-landed Line writer. Current source,
commit `e4d9af0c900` and its tracked handoff established freshness; both stale
claims were released without another edit or compile. The supported picker
`python3 tools/next_work.py --claim --shard 1/3` then served Cylinder writer
`0x0055D815`, 368 bytes including three EH rows, and claimed its RVA and file.

`reverse/exports.csv:1944` gives the exact exported name at that address:
`?writeINI@CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z`,
or `void writeINI(File &, unsigned int) const`. The ledger already owned the
339-byte body and its EH rows in
`Code/GameEngine/Source/GameClient/Rva0055D815Write.cpp`; its private view
instead spelled `rva0055D815(File *, unsigned int)` without const qualification.
There is one existing body, not an unrowed regression. No registered/shared
Cylinder module-template header was found.

Authoritative real-link run `42174078539` at `da59156dc4f2` lists this exact
missing export in `errors.tsv:302`. Its scoreboard reports 308 unresolved names,
zero duplicates and no image. This artifact predates this repair.

## Change and consumer safety

Reconcile the existing source declaration/definition with the exported signature;
use `&file` where existing pointer helpers require it. Keep all operations,
offsets and source paths. Update the existing EH handler name and both funclet
parent notes, and tombstone both superseded names. No body, pin, alias, shared
header, vtable or initializer table was added.

`rename.py function --rva 0x0055D815 --new '<exact export>' --basis canonical:export
--evidence reverse/exports.csv:1944 --dry-run` refuses the signature change beyond
the identifier. `docs/naming.md`, "Renaming by hand", explicitly covers this
canonical signature case. Evidence is recorded with `re_log.py`; `name_basis.csv`
is unchanged. Searches of current Code and symbol/data ledgers found no other
old-name caller, pin, data symbol or `/alternatename`. The staged consumer tool
also reports zero users, as measured below.

## Checks

Final normal gates used the existing provisioned x86 QEMU compiler wrapper,
with this worktree exported read-only. No compiler, include, gate or policy
change was made.

- `python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameClient/Rva0055D815Write.cpp`:
  all defined functions matched, before and after.
- `python3 tools/check_csv.py`: OK, 99,515 function rows, 9,320 symbol rows,
  2,272 data rows, unchanged.
- `./build.sh Code/GameEngine/Source/GameClient/Rva0055D815Write.cpp`:
  4/4 rows exact and five literals verified, zero skipped. Both compiler funclet
  labels are renumbered; verified parent EH data places their bodies at the same
  existing retail RVAs, without a new label pin.
- `python3 tools/link_check.py --prepare-current Code/GameEngine/Source/GameClient/Rva0055D815Write.cpp`:
  one explicit provider byte-verified with a strict reusable receipt; 4/4 rows
  and five literals; no census/index/status changes or extra sources.
- `python3 tools/link_check.py Code/GameEngine/Source/GameClient/Rva0055D815Write.cpp`:
  LINKS, 1/1 units; LINKED 349 -> 349 bytes against the exact published
  index `47fd56b879`, 2026-11-06 05:39 UTC (copied unchanged from root).
- `python3 tools/name_dependents.py --staged`: two old code/data target names
  lost; zero referencing units of 18,026 scanned.
- Read-only COFF check: exact new export definition 1; old parent occurrences 0;
  new EH handler definition 1. Reproduce without compiling by running:

```python
import sys
sys.path.insert(0, 'tools')
import build
p = build.obj_path('Code/GameEngine/Source/GameClient/Rva0055D815Write.cpp')
symbols = build.read_object_symbols(p.read_bytes())
new = '?writeINI@CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@UBEXAAVFile@@I@Z'
old = '?rva0055D815@CylinderEmissionVolumeModuleTemplate@FXParticleSystem@@UAEXPAVFile@@I@Z'
print(sum(s['name'] == new and s['section'] > 0 for s in symbols))
print(sum(s['name'] == old for s in symbols))
print(sum(s['name'] == '__ehhandler$' + new and s['section'] > 0 for s in symbols))
```

The file already linked under census rules; no linked-byte gain is claimed.
The expected export repair needs the next automated real-link measurement.
No new image, startup/menu/skirmish/save-load run or retail CRC comparison was
performed. These checks do not clear the separate Cylinder class/vtable and
unowned-data export prerequisites in the existing obstacle history.
