# ScriptEngine template getters: canonical header adoption

Inspected revision: `02ff0f381429de70f6f56162c65593c5bf72ce2b`.

`ScriptEngineGetActionTemplate.cpp` (0x00203926, 27 bytes) and
`ScriptEngine_getConditionTemplate.cpp` (0x00203941, 30 bytes) now include
`Code/GameEngine/Include/GameLogic/ScriptEngine.h`. Their private ScriptEngine
and template-record definitions are removed. The header keeps the template
storage opaque, so each getter computes its existing table address within
`m_opaque1C`; the table offsets, 128-byte stride, bounds and fallback index
are unchanged. No shared header, compiler flags, function identity or ledger
ownership changed.

## Verification

- Before and after: `./build.sh` passes both complete bodies, 2/2 rows, 57 bytes.
- `find_declared_unmatched.py` passes both changed files before and after.
- `header_adopt_lane.py accept --class ScriptEngine` passes both files and
  retires exactly their two rows from `reverse/header_queue.tsv`.
- Before and after: `link_check.py` reports both files LINKS, retaining 27 and
  30 authored bytes against the 2026-11-05 05:17 census at `c95fcfcfcd`.
- Enforced converged-data check: zero second names, zero unjudged rows.
- EH check: no EH-bearing rows, no missing objects, no non-exact graphs.
- No source paths move and no pins, aliases, hatches or data definitions change.
  No code/data debt keys belong to these two files. The only retired register
  entries are the header rows accepted by their owning tool.

Local build, acceptance and preview logs use the prefix
`build/codex4-scriptengine-getters-`. These previews do not update the census
or establish a successful real link or smoke run.

## Consolidation context

The fresh `name_lane.py consolidate --under
Code/GameEngine/Source/GameLogic/ScriptEngine/` survey flags private class and
header conflicts. `tu_views.py --class ScriptEngine --dry-run` routes this class
to its existing canonical header. The broad read-only merge trial was
interrupted after eleven minutes of compilation, before a verdict or source
change; no merge or file reduction is claimed. Its other scope claims were
released. The seed's header adoption and the remaining donor conflicts still
need separate verified repairs before another composition trial.
