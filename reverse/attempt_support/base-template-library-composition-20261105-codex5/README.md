# BaseTemplateLibrary composition prerequisites

Inspected base: `2871403012`; 2026-11-05, seat codex5.

The claimed destination is
`Code/GameEngine/Source/GameLogic/SkirmishAI/AIBaseBuilder/BaseTemplateLibrary.cpp`.
The supported consolidation planner and `tu_skeleton.py --merge ... --dry-run`
were used; the merge tool rebuilt stale TU assignments in memory. No map was
committed and no source path or ledger row moved.

## Verified preparation

- The destination now includes the canonical SubsystemInterface header with
  `BFME_SUBSYSTEM_SLOTS`, preserving the fourteen-slot base view. This removes
  the shim/canonical C2011 conflict with `Rva0022BD9ASubsystem.cpp`.
- The destination and `BaseTemplateLibraryParseBaseTemplateFiles.cpp` place the
  identical inline `vector<void*>::end()` specialization in its own namespace
  block. Composition can deduplicate it instead of failing C2995.
- The constructor donor uses the destination's exact spelling of the identical
  `hash<Rva0041EFE0Element>` declaration, removing C2766 on composition.

The final three-source `./build.sh` passes **19/19 rows**, string references,
source claims and five parent-EH-verified funclet pins. All three
`find_declared_unmatched.py` checks pass. Ordinary link previews preserve
114 + 487 + 67 = **668 bytes** against census index `3a95b274a2`
(2026-11-04 22:40). These are preview results, not new census measurements.
The existing split-destructor alternatename stays in place. No pin, flags,
baseline, queue key or shared header is changed or retired.

## Remaining composition boundaries

The final supported dry run accepts no donors; see `merge-dry-run.txt`.

1. `AIBaseTemplate.cpp` still fails C2883: its namespace-local throwing `free`
   declaration conflicts with the earlier STL using-declaration. Its deliberate
   allocator/EH contract needs reconciliation before composition.
2. `Rva0022BD9ASubsystem.cpp` now compiles in the merged TU but fails the tool's
   whole-source byte check. The tool reports only `bytes`, so this pass does not
   attribute a specific row or instruction. Next inspect the constructor and
   parent cleanup differences under the combined declarations/compiler profile.
3. The parser donor composes with matching bytes but the link guard reports
   that the new object breaks another unit's copy of the hashtable destructor
   for `pair<const int, Rva0041EFE0Element>`. Reconcile that selected COMDAT and
   its consumers before merging; retaining only byte matches is insufficient.

The parser donor also retains its ChunkInputStream/DataChunkInput header queue
entries. `OpaqueScalarDeletingDtorsB10.cpp` is mixed, and
`parseAIBaseDefinition.cpp` has three rows without approval for this TU; neither
was edited or moved. LINK-009's split owner identities remain unresolved.

`final-build.txt` and `link-preview.txt` preserve the bounded verification
receipts. No merge, source-file reduction, linked-byte gain or family clearance
is claimed. Carry these changed class declarations into the next scheduled
census; the outgoing batch still receives the normal link audit.
