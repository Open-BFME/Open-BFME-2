### LINK-031: `TransportContain.cpp` predicts a duplicate module-data ctor after its merge

Status: Open (original preview diagnostics absent; latest payload merge awaits census confirmation). Updated: 2026-10-28; inspected revision: f8b430a969 plus the payload prerequisite and guarded merge (index 14dc3d2467).
Evidence / affected units: `link_check TransportContain.cpp` (with or without
`ContainModuleDeletingDtors.cpp`) reports "does not link", LINKED 1,921 -> 0 B:
`duplicate` + `selected` on `??0TransportContainModuleData@@QAE@XZ` (row 0x00468301).
The current tree has one real definition (TransportContain.cpp; the other textual hit,
ContainModuleDeletingDtors.cpp, is the `EmitVtableTag` overload). The merge d8f97282ee
(absorbed `TransportContainModuleDataCtor.cpp`) landed after the index commit, so the
index most likely still holds the deleted donor's object, which link_check cannot retract.
Identical result before and after 18cd9f0976 (KINDOFMASK_NONE rebinding), so that change
is not the cause.
Completed: diagnosis only.
Remaining / next check: rerun `link_check TransportContain.cpp` against the next census;
if the duplicate persists, find the second definer in the census objects.
Clearance: pending.
Census confirmation: not claimed.

**2026-10-27 recheck and consolidation:** before the pool-key merge,
`link_check TransportContain.cpp` against census index bf3dd31211 (2026-10-27
00:39) reports LINKS, 2,455 -> 2,455 B; the original module-data ctor duplicate
is absent in this scope. Retail primary table RVA 0x00844278 slot 4 names the
already rowed getter 0x00467EE1. Declaring that slot permits `tu_skeleton.py
--merge` to absorb `TransportContainPoolKey.cpp`, including its EH handler and
guard rollback funclet: 26/26 rows match, four EH graphs are EXACT, and the
tool's before/after provider-and-consumer link guard accepts the composition.
The ordinary post-merge preview now reports duplicate/selected on
`getModuleNameKey`, because this index still contains the absorbed pool-key
donor. It is not a new second source definition. Retain this entry until a
fresh measured index confirms the merged owner. Thirteen other whole-file
donors remain rejected (class-view conflicts, or destructor byte mismatch).
Debt is transferred, not retired; the current data check still finds the two
real getter-local names against the older placeholder names in the data
ledger. Evidence and remaining prerequisites:
`reverse/attempt_support/transportcontain-consolidation-20261027.md`.
Clearance: original ctor preview diagnostic absent at the newer index;
post-merge getter preview and census clearance pending. No census increase claimed.

**2026-10-28 declaration prerequisite:** at inspected revision `f8b430a969`,
the ordinary preview against measured index `14dc3d2467` (2026-10-28 02:44)
reports LINKS for the current destination (2,455 -> 2,534 B) and its standalone
payload parser (133 -> 133 B). Neither earlier duplicate diagnostic reproduces
in this scope; census clearance is not claimed. Replacing the parser's private
STL list declaration with the real STLport header and the destination's node
allocator declaration preserves its two matched rows and exact EH graph.
Its five original COMDATs are unchanged; five additional list/iterator copies
are identical to the destination's providers. This addresses one remaining consolidation
prerequisites without claiming native element-type recovery. The destination's
unreferenced `Object::clearCondition` shadow diagnostic remains unchanged.
Evidence: `reverse/attempt_support/transportcontain-payload-consolidation-20261028.md`.

**2026-10-28 guarded payload merge:** the supported tool absorbed the parser
and its EH-handler row into the approved destination. All 28 rows byte-match,
all five EH graphs are EXACT, and the merged object's 648 external COMDATs
equal the original provider union. The tool's before/after consumer guard
accepts the composition. The ordinary preview still reports LINKS (own bytes
2,667); this is existing destination-plus-parser coverage, not a census gain.
The shadow data check has zero findings; no debt is retired. Twelve whole-file donors still need prerequisites, and
the generated funclet at 0x0078AD97 remains in its existing owner. The next
census must confirm the merged owner and batch-wide consumer totals.
The outgoing batch audit is INCONCLUSIVE: the index predates the outgoing
base and lacks per-object consumer names. This is unverified batch-wide
linking, not evidence of a regression or a clean result. The existing
unreferenced `Object::clearCondition` body is unchanged and remains a shadow
identity finding without a register key.

**2026-11-05 AOD header adoption:** one private view and its header-queue row removed; all four cohort previews link with 5,696 bytes preserved against index `f44cbcf5b0`. Remaining canonical-container prerequisites and census/batch-audit limits: [evidence](../../reverse/attempt_support/transport-moduledata-aod-adoption-20261105.md).
