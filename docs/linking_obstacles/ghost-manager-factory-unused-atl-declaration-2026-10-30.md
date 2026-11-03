### Ghost-manager factory unused ATL declaration (2026-10-30)

At base `c647a75e55`, GameEngine_GameEngine_createFileSystem.cpp removes its
unused `extern CComModule _Module` declaration. The owning Microsoft-header
auditor finds zero remaining local occurrences and retires the unit's one
queue row; included-shim findings remain separate. All seven rows, both
EXACT EH graphs, 44 external COMDAT fingerprints, external bindings and
reference edges are preserved. Strict preparation passes; ordinary preview
retains LINKS, 161 -> 161 authored bytes, against `12b9e7a7c0`
(2026-10-30 10:11). No provider, path, pin or runtime behavior changes.
The scoped staged audit is INCONCLUSIVE on that older index and the missing
current `Common/0CreateAHeroManager21FE49.cpp` consumer receipt. Carry this
unit and its wider consumers into the next scheduled census; full consumer
selection/loss verification and census confirmation remain pending.
