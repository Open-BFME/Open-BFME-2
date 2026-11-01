# SimpleObjectIterator consolidation: read-only prerequisite audit

Scope: SimpleObjectIterator.cpp plus WWLib/StlportDequeCopyRecord8KeySort.cpp, StlportTrivialDeque8Cleanup.cpp and stlport_deque_e8_pushback_aux.cpp. No files under Code or reverse changed, no claims/builds/publication performed.

No current scoped keys found in gate_baseline, data_check_baseline, code_identity_baseline, dup_defs_baseline, unclaimed_sources_whitelist, header_queue, ms_header_queue, pin_consistency_baseline or flag_overrides. Final destination queue inventory must still be refreshed through owning tools.

Protected-register carry: cleanup donor has three optimize tokens (s off,t on,empty on); auxiliary pushback has one vectorSmallAllocate alternatename. Use merge/counter machinery; no manual new hatches.

The seed's actual supported contracts are eight-byte int/float BfmeE8, eight-byte pointer/float BfmeCopyRecord8 with visible member copy, and a separately opaque trivial eight-byte cleanup view. Equal width is not evidence that their source-level types were the same. Do not merge these names or infer new element semantics during path consolidation.

Key-sort record/comparator declarations agree with the seed. Keep linear_insert and push_heap declaration-only: existing donor evidence records a one-instruction scheduling miss in the would-be emitted push_heap body. Its comparators and folded helpers remain pinned to outside owners.

Cleanup donor explicitly instantiates a whole deque class. The seed currently declares its destructor external to preserve potentially-throwing member cleanup and exceptional base-destructor path. Visibility changes and selected COMDAT changes therefore need the complete byte/EH/link checks, not just moving the58-byte dtor row.

Pushback donor privately redeclares _STL allocator/deque, while the seed includes real STLport definitions. Supported merge may refuse this conflict; do not preserve a second same-name template class or bypass the refusal. Its native auxiliary path requires16-element nodes (128bytes), unconditional reserve(default1), and int/float copy. Its allocator alias carries the existing null-hint two-word cdecl contract.

Combined active path-consumer search found no old donor basename/path in tools, .githooks, .github or other Code outside the seed's generated comments. reverse/symbols.csv has a fold-proof token for the sort donor; tu_skeleton explicitly rewrites fold-proof tokens and path columns. hatch_baseline must follow retained tokens. reverse/link_status.csv is a historical census output; attempt_support proofs and re_attempts are historical evidence, not active paths to rewrite blindly. Original reference/provenance path strings must remain.

This is a before-composition audit, not verification of a proposed merge. Final complete outgoing batch needs its normal ledger, header, byte/EH, identity and affected-provider/consumer checks and the source-path audit recorded immediately before push.
