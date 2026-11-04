# GameResults worker TU merge

2026-11-04; owner `yasinschroeder-codex3`; prerequisite commit
`705b6236a8` (runner-rebased); enclosing obstacle LINK-135.

`tu_skeleton.py --merge Code/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThread.cpp`
accepts the seed and `GameResultsThreadClassThreadFunction.cpp`, preserves
19 primary rows plus the existing response-destructor alias, and removes
one Code source file. Six function-ledger rows and five TU-map source cells
are repointed; approvals and assignments are unchanged. The ordinary apply
repeated the search after the prerequisite commit invalidated the dry-run
cache; the earlier prerequisite note's cached result was not reused.

Verification:

- Destination `./build.sh`: 20/20 exact, three funclet pins resolved through
  the parent's EH graph, 13 named imports verified. `eh_verify.py`: EXACT 1/1.
  Frozen-file check: all definitions already matched. CSV and diff checks pass.
- The merged object has precisely the old objects' union of 626 external
  COMDAT names. Each normalized byte/relocation digest, size and selection
  equals a prior variant; none is added, missing or changed. These digests
  normalize local referents; the separate EH check verifies the worker graph.
- Defined-symbol union (626), effective undefined-symbol union (26), weak
  defaults, alternate names and forced includes are unchanged. No alias is
  removed. The ordinary merge's census-linked donor guard passes.
- The pre-existing divergent BfmePod16 allocator variant remains unchanged.
  No identity, data, header-adoption or hatch key is retired. Neither source
  owns a protected identity/data/header key; the merge engine refreshes header
  ownership and the Microsoft-header scan with no further queue change.

Tooling/path audit covers the complete pending move against `dba4e36e1e`:
worker fragment to the approved GameResultsThread TU. Searches of tools,
hooks, workflows, Code, reverse, docs and root build/configuration files find
no active old-path consumer. Ledger and map owners resolve to the destination.
Remaining mentions are source-origin comments, attempt history, the previous
census snapshot, and STLport trial evidence. The STLport queue explicitly
filters historical leads against current source/name/extent ownership; its
old worker mismatch row is not a live lead. Historical records are retained.
The consolidation planner was regenerated before applying the move; no old
compiler receipt is used as proof for the merged destination.

Batch audit of staged tree `83112aa800fa400a6d5d96073ae65f8f8442ac83` against
`dba4e36e1e` exits 2: census `3a95b274a2` predates the outgoing base; three
affected objects lack current receipts, first
`Code/GameEngine/Source/Common/Rva00419CFBConstructor.cpp`.
This is INCONCLUSIVE, not linking clearance. The provider/consumer scope must
be confirmed by the next scheduled census; no census or ownership gain is
claimed. An initial audit against the original pre-rebase base also included
unrelated incoming changes and is superseded by this current-range audit.

Scoped naming at the final TU path reviewed the complete worker function:
native proposal and parent review retain all nine inventoried names. Manual
coverage also retains the omitted constructor-style `lock` binding; catch
ellipsis has no binding and call commas do not declare additional locals.
`scoped apply` completes with nine retained, zero renamed; no extra byte run
is needed for this read-only naming result.

Remaining donors: both teardown sources still fail composition bytes;
startup still fails AsciiString redefinition. Mixed-file and unapproved
sources remain outside this merge. No rejected donor was changed.

Local receipts: `build/codex3-results/merge.txt`, `merged-build.txt`,
`merged-providers.json`, `path-audit.txt`, `batch-audit-current.txt`.
