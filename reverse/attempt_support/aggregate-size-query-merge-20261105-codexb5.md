# Aggregate size-query consolidation, 2026-11-05

Base: `fb66556563`; declaration repair: `740c0e97b8`.

The default picker claimed `agg_def.cpp` and `AggregateDefRva001A3930.cpp`.
The first merge trial reproduced the prior compiler refusal: the TU-scoped
`AggregateDefClass` shim lacked `rva001A3930() const`. The separate repair adds
that nonvirtual declaration and replaces the donor's private offset view with
`m_SubobjectList.Count()`. Its 40-byte retail body and symbol are unchanged.
This does not establish a recovered method name.

The refreshed WW3D2 consolidation planner identified the donor as a whole-file
candidate. Its committed TU-map row is approved by S for `agg_def.cpp`; the merge
tool also rebuilt routing from current inputs. After repair, the dry run and
applied merge accepted both files, rejected none, and retained all 41 rows.
Three mixed files remain outside this merge: `FontCharsClassConstructorBFME.cpp`,
`collect.cpp`, and `render2dsentence.cpp`. They need separate ownership closure.

Verification:

- Repair: `./build.sh` verified 41/41 rows in the two sources. The header-dependent
  commit gate verified both consumers. Declared-unmatched checks passed.
- Merge: `./build.sh Code/Libraries/Source/WWVegas/WW3D2/agg_def.cpp` verified
  41/41 rows in one source, including the size query and three funclet pins.
- `find_declared_unmatched.py` passed. The existing AggregateLoaderClass::Load_W3D
  hatch remains; no unclaimed-body admission was added.
- `eh_verify.py` found four EXACT EH rows, no missing objects and no baseline debt.
- Before merge, current-object link previews passed both units (4,298 + 40 bytes).
  After merge, the TU preview passed at 4,338 bytes. The merge link guard passed
  against both census-linked inputs. This is no new census or linked-byte gain.
- `tu_ownership.py --staged`, data shadow, converged data, ledger integrity,
  case-collision and staged whitespace checks passed before commit.

Path/debt audit (outgoing batch based on `fb66556563`):

- Only removed source: `Code/Libraries/Source/WWVegas/WW3D2/AggregateDefRva001A3930.cpp`;
  all its rows move to `Code/Libraries/Source/WWVegas/WW3D2/agg_def.cpp`.
- Searched the full old path and basename across tracked tooling, hooks, workflows,
  source/includes, shims, build/config files, documentation and registers. No active
  hard-coded consumer requires a change. Two source comments retain the old basename
  as historical ownership notes; the TU retains a donor-provenance comment.
- `functions.csv` and the existing TU-map source cell are repointed by tu_skeleton;
  the map was not regenerated for commit. No data/body-owner/doxygen entry needs moving.
- No donor data/code-identity/header/ms-header debt keys exist. The destination's
  existing ms-header queue row and hatch entries remain. Hatch update has zero diff;
  no debt was retired, pins changed, or link-wide aliases removed.
- Historical `link_status.csv`, earlier attempts and banked evidence retain old paths.
  The planner snapshot was checked current before application and is naturally stale
  after the move. No cached donor receipt is used to prove the merged TU.
