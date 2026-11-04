# GameResults worker allocator and CRT composition prerequisites

Inspected base: `fbe9ceac7e`; owner: `yasinschroeder-codex3`; 2026-11-04.
Scope: `GameResultsThreadClassThreadFunction.cpp` and its approved
`GameResultsThread.cpp` TU. LINK-135 remains the enclosing obstacle.

The initial ordinary `tu_skeleton --merge --dry-run` accepted no donors.
The worker and both teardown donors failed bytes; startup failed with an
AsciiString redefinition. This reproduces the earlier handoff's boundary.

The worker defined `free` as `Rva00030830GameFree` before parsing STL headers.
The merged seed parses those headers first, so the macro cannot change their
already-parsed allocator bodies. This is an include-order explanation, not
evidence for a new class, member or original source name.

The repair removes that macro and expresses the null-checked game-wrapper
call directly in the existing inline string-proxy deallocation specialization.
The wrapper's existing identity and the worker's matched calls are retained;
no header, compiler flag, pin, alternate name or protected register changes.

That edit alone still accepts zero donors in the ordinary search. A focused
seed/worker composition under the worker's flags matches every worker row,
but loses four seed rows: the two `_M_initialize_map` instantiations,
`_M_create_nodes<BfmePod28>` and `Rva0041A3C4::rva0041A3C4`.
Under the seed's flags, only `Thread_Function` differs. Its 295-byte body
calls `_isdigit` directly, versus retail's 298-byte body with an indirect
`__imp__isdigit` call. The seed's `/D_CRTIMP=` is needed for its direct
`_free` call (51 bytes versus 52 with `__imp__free`); the STL exception
configuration accounts for the deque initialization differences.

The seed now parses the toolchain's `<ctype.h>` with `_CRTIMP` temporarily
set to `__declspec(dllimport)`, restoring the previous macro immediately.
All other CRT headers retain the seed's existing configuration. This uses
the real header's declarations rather than a private `isdigit` declaration.
A focused composition through `tu_skeleton.Verifier` then matches all 20
seed/worker rows, including the worker's three funclets. This trial does not
itself authorize a merge or establish linking; the ordinary search remains
the acceptance path.

The final ordinary `--merge --dry-run` exits zero and accepts the seed plus
worker: 19 primary rows (the worker's response-destructor alias is additional).
Its census link guard passes. Both teardown donors remain rejected for bytes;
startup remains rejected for AsciiString redefinition. The winning composition
is cached by the tool for the separate merge commit. No rejected donor is
edited in this prerequisite pass.

The focused composed object has exactly the original two objects' union of
626 external COMDAT names. Every normalized byte/relocation digest, size and
selection kind equals a pre-existing variant; none is missing or new. This
does not establish which variant an outside consumer selects; the merge's
link guard must judge that binding.

Standalone verification:

- `./build.sh` worker: 6/6 exact, including its three unwind funclets;
  five named import references verified.
- `eh_verify.py` worker: EXACT 1/1 EH graph, no baseline exception.
- `find_declared_unmatched.py` worker: all definitions matched.
- Before/after COFF comparison: all 548 external COMDAT names, normalized
  byte/relocation digests, sizes and selection kinds unchanged; no added,
  removed or changed copies. Complete defined/referenced symbol sets, weak
  defaults, alternate names and forced includes are also unchanged. Digests
  normalize local referents; the separate exact EH check covers the worker's
  local EH graph.
- `link_check.py` worker: LINKS, 306 -> 306 own bytes against census
  2026-11-04 22:40 at `3a95b274a2`. This is a preview, not a new census.
- Seed `./build.sh`: 14/14 exact and eight named imports verified. All 620
  external COMDAT providers and complete symbol bindings equal its pre-edit
  object. The worker retains all 548 providers and bindings too.
- Seed link preview: LINKS, 902 -> 902 own bytes against the same census.
- `ms_header_audit.py scan <seed> <worker> --write-queue`: both files have
  zero local Microsoft declarations and zero failed scans. The owning tool
  removes the worker's obsolete free-macro entry and the seed's stale free
  entry; unrelated queue rows are untouched. This is not SDK include-closure
  migration.

Scratch receipts: `build/codex3-results/worker.before.{cpp,obj}`,
`worker-compare.json`, `worker-link.txt`, `worker-dry-run.txt`.
No source paths move in this prerequisite change; no protected baseline,
identity, data or header-adoption key is retired.
