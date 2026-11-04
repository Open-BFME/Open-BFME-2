# FXShaderSetup vector view prerequisite repair

Inspected revision: `9caf2e13f3825ee03be67473f5f2ebb0b618def4`; date: 2026-11-04.

The default picker claimed the FXShaderSetup TU and its donor-file scope. The
consolidation planner was run for `Code/Libraries/Source/WWVegas/WW3D2/`.
Its packet is investigative: compiler environments differ, the committed TU map
is stale, and routing/header prerequisites remain. No source moves or map
regeneration are part of this repair.

## Target facts and change

`tu_views.py --dry-run` found a 12-byte `Rva0015229CVector` in
`Rva0015229CEraseRange.cpp` and a 12-byte `Rva00152BDBVector` in
`Rva00152BDBValueVectorResize.cpp`. Their three pointer members occupy offsets
0, 4 and 8. The shader TU had method-only declarations of those same types.
The compiler-layout-driven tool copied each complete view to both owners:

```
python3 tools/tu_views.py Code/Libraries/Source/WWVegas/WW3D2/FXShaderSetup.cpp --class Rva0015229CVector --class Rva00152BDBVector --no-merge-check
```

Both classes were applied. `--no-merge-check` limits this pass to declaration
reconciliation, with the tool's per-source layout/byte/unmatched checks. No
class, field or method identity was newly inferred; existing donor spellings
were retained. No ledger rows, pins, aliases, register keys or source paths
changed. The existing resize aliases remain link-wide.

## Verification

Before the change, `./build.sh` verified the shader TU: 53/53 rows, 29 funclet
pins and one complete emitted constructor fold.
After the change, `./build.sh` over all three changed sources reported:

```
Source claims: OK (3 sources, scoped byte-verified)
Compile: 0 of 3 TU(s) (deps-cache: 3 current)
Funclet pins: 29 row(s) verified past a renumbered $L label
    $L7894 (Code/Libraries/Source/WWVegas/WW3D2/fxshadersetup.cpp): $L7894 was renumbered; verified parent EH data places $L61426 at 0x00766C77
    $L8061 (Code/Libraries/Source/WWVegas/WW3D2/fxshadersetup.cpp): $L8061 was renumbered; verified parent EH data places $L60531 at 0x00766CA6
    $L8195 (Code/Libraries/Source/WWVegas/WW3D2/fxshadersetup.cpp): $L8195 was renumbered; verified parent EH data places $L60665 at 0x00766CC0
    $L8449 (Code/Libraries/Source/WWVegas/WW3D2/fxshadersetup.cpp): $L8449 was renumbered; verified parent EH data places $L61503 at 0x00766D1C
    $L8547 (Code/Libraries/Source/WWVegas/WW3D2/fxshadersetup.cpp): $L8547 was renumbered; verified parent EH data places $L61574 at 0x00766D9A
STLport folds: 1 complete emitted constructor(s) verified against retail owners and resolved callees
Functions: OK 58/58 matched across 3 source file(s)
String-ref verify: OK (0 literals + 5 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)

```

`find_declared_unmatched.py` passed before and after for each changed source;
`git diff --check` passed. No byte coverage, linked-byte, debt-retirement or
source-count gain is claimed. This is a prerequisite repair.

## Remaining work

The broad whole-TU dry run was stopped after roughly ten minutes of candidate
compilation without a final verdict. It produced no applied merge and supplies
no merge/link clearance. Do not treat it as a failed or successful byte result.
An accidentally concurrent preliminary tool invocation was also stopped before
applying any source changes; its temporary files were removed.

The view survey still identifies canonical `FXShaderSetup` and
`Rva0007BB16Record` adoption, `Rva00151DAB`, `Rva0015148D`, `Rva001514B2`, and
`BfmeAssignRecord36` reconciliation. In particular, `BfmeAssignRecord36`'s
`bytes` rename also reaches `Rva001524F9Element::bytes`, so the automatic tool
refuses that rename. Resolve that binding specifically before retrying it.
Recheck fresh routing evidence and these declarations before a future bounded
merge trial. Neither this repair nor the baseline checks verify the complete
TU's linking or any consumer family; the next ordinary census remains the
source of linking headline figures.

## Publication-time audit

The runner accepted the repair as `841efef1fa` for fleet publication, together
with the checkout's two existing GiantBird commits. No accepted commit was
amended. The commit hook verified all 58 rows, eight EXACT EH graphs and the
converged-data checks. Code identity remains in shadow mode and reported two
unresolved bindings in the shader TU: `$L8585` to the record-vector destructor
at `0x0007C632`, and `FXShaderSetup::InitializeShader` to `AsciiString::clear`
at `0x00036410`. This pass did not determine whether those findings predate the
declaration repair and claims no identity cleanup.

A post-handover `link_batch_audit.py` check over all five outgoing source paths
against `origin/master..HEAD` returned exit 2:

```
link batch audit: INCONCLUSIVE baseline: index at 8661f15284, outgoing base origin/master; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 4 source object(s) lack current receipts; first: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/GiantBirdAIUpdate.cpp

```

The input list was NUL-terminated as required by the audit. An initial
newline-terminated list had been refused before analysis and was corrected.
The stale-index/missing-receipt result supplies no link clearance. Carry the
changed sources and affected consumers into the next normal census; the fleet
publisher's hook still judges the outgoing batch on its landing inputs.
