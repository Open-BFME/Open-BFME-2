# ScriptList018 PlayerInitFromDict: one source-only candidate refused

Rating: sicher for the measured private controls. No normal header acceptance, linked-byte or runtime pass is claimed.0 debt rows accepted,0 new functions/bytes.

Base64b343fb4109505cdb9073ebc21796b5c02d9500. Root holds class:ScriptList and freshly acquired the actual source file plus31 RVAs (claims-018-player-scope.json). No production source/header, row, pin, claim, tool or Git/index edit was made. Shared match objects were untouched. A separate two-file diagnostic-output mistake is disclosed below.

## Exact single change and private input context

Candidate PlayerInitFromDict.cpp SHA256970e89abbb43f7855e8719280506014702c5b986fad6a5d09cbc15722d40558e replaces only the complete one-line private ScriptList declaration by:

    #include "../../../Include/GameLogic/ScriptList.h"

Original production source SHA256a1100844cc201b679ee4fef7522fb135486a219dfe074e602d7a9d8b22f7e2dc remains unchanged, including its13November mtime. No bodies, other classes, macros, flags, methods or globals changed. The patch and candidate are UNLANDED diagnostic inputs, not an integration recommendation.

Native current-profile flags were obtained from the actual source and compared exactly with both private compiler commands. The same original codegen/include flags are used; only output/source paths differ. Literal quoted includes resolving beside the proper source were mapped to the exact same canonical files through private relative paths, with every mapping/hash recorded. No /I/codegen option was added. Normal baseline31/31 confirms this private original context against retail. Native debug diagnostics add only-Z7/-showIncludes and are separately checked against each corresponding normal object's whole runtime inventory.

Frozen header hashes remain ScriptList.h38704e7eb21d48f9e58995e96b04b99cdb26572d5a34eb58092c9f5ff0001c8a and Snapshot.h966b0ec30c8d777caa46df85bfc0f9013baeed17f8cc2cd1a1c4295172cf2206. Actual opened-input inventories contain86/87 paths; the extra header is canonical ScriptList. See full native commands, mappings, input hashes and original RVA scopes in SOURCE_CONTROL.json / TYPE_AND_PREPROCESS.json and the previous read-only package.

## Native results: real main-body failure

- Original: compile exit0,31/31 strict existing rows exact.
- Candidate: compile exit0,12/31 exact.
- Real failing parent Player::initFromDict002AFCDF is2764B versus retail2762B. There are no unresolved calls in its native byte result.865 reported strict byte differences largely reflect the resulting shifted tail; they are not865 independent logic defects.
- The first changed emitted instruction form is at+0x72A. Original pushes0, then loads TheKey_teamName directly into ECX. Candidate instead materializes that SAME global in EBX, pushes0, and copies EBX into ECX. Its later "team" literal is pushed directly where original first loaded EBX. Relocation names independently identify both objects' same key and string. The native body is2B longer. Earlier changed branch displacements are consequences of that changed block.
- The remaining18 failed row checks concern cleanup identity or the parent's non-exact main-body prerequisite. For instance old$L10490/$L10491 meet two indistinguishable new byte candidates$L11340/$L11339, and scoped cleanups require an exact parent location. No labels were selected by hand, repinned or renamed.
- Native eh_verify alone reports the candidate parent's EH graph EXACT. That narrower EH result does not override the failing parent body or admit its cleanup rows.

MAIN_DIFF.json preserves all native offsets. Its compiled disassembly is UNLINKED raw COFF: placeholder immediates/call destinations are not genuine addresses. DIAGNOSIS_SUMMARY.json annotates the corresponding real COFF relocation symbols. A mismatching body's target-patched byte buffer must not be treated as valid disassembly after its instruction layout has diverged.

## Whole-object and actual type/preprocessor checks

The complete non-debug section/relocation/definition inventory differs in exactly ONE runtime section: ordinal57, .text2762->2764, the failing parent. External definitions, undefined names, weak bindings, COMDAT selections/associations and linker directives remain equal. Every other runtime section is equal, including the EH graph and data. Both-Z7 objects independently preserve their corresponding normal runtime inventory; diagnostic debug info did not cause or hide this failure.

Actual native preprocessor outputs show byte-identical complete Snapshot class bodies before/after. Native Snapshot class records also remain equal. This is the actual NAME_SLOT context with loadPostProcess / const GetSnapshotName / xfer; no macro flip, late undef or fallback was used.

Native debug records show143 complete class definitions on each side. The only changed existing complete class contract is the intended ScriptList: old76B opaque one-slot view becomes the existing76B Snapshot-derived four-slot class with heads+4/+8 and storage+C. No other existing concrete class record's parsed key/size/base/field/method/virtual/static contract changes; there are no unparsed complete classes. Fourteen added forward records come from canonical ScriptList's declared API. Raw whole type streams differ2945->3008 records, so a full non-target raw type-graph equivalence pass is NOT claimed merely from the class presentation comparison. The genuine main-byte failure is already sufficient to refuse this candidate.

NeutralPlayerColor has one external definition in each normal object, identical4B404040ff, no relocations, matching original VA00DBBD28. Its declaration is unchanged. The native sizeof observation below was made on the original source only; it is not an independent candidate-source sizeof proof.

## Diagnostic-output mistake and correction

During the final data observation I inadvertently called data_rows.symbol_size with its default compiled_size callback, rather than limiting the observation to the already-private objects. That callback compiled an unchanged ORIGINAL-source sizeof wrapper twice and wrote these two ordinary diagnostic scratch paths:

- build/data_rows/probe/PlayerInitFromDict_43d5fb1f.cpp
- build/data_rows/probe/PlayerInitFromDict_43d5fb1f.obj

This violated the private-output restriction. It did not touch build/match, the production source/header, ledgers, pins or receipts. Root was notified immediately. The files are left intact; no unknown prior cache content is deleted/restored. Both invocations queried the same original source, so DIAGNOSIS_SUMMARY's per-object size entries have been explicitly relabeled as a reused original-source size observation, not two independent candidate probes. No passing conclusion relies on them. There were two ordinary source controls, two debug controls, two preprocessing invocations and these two unintended original-size invocations; peak parallel compilation was2. No further compiler runs are proposed.

## Decision and reproducibility

This was the only authorized source form. Do not apply the candidate, retire the queue row, repair labels, tune flags, modify the header or proceed to a17-source trial loop on the strength of the partial results. The measured blocker is now concrete code generation in a known whole-file consumer, beyond the stale automatic field-rename diagnostic.

probe_source.py reproduces the original and single candidate in private outputs under build/agent-melee-bfme2-20261120/scriptlist018-player (the repro is sequential to keep Python diagnostic output redirection local). audit_same_candidate.py only audits the same objects and performs the two bounded debug/preprocessor controls; no additional source variant. Production source and both frozen header hashes are checked after the run. Root remains the sole production, acceptance, claim, Git and publication writer.
