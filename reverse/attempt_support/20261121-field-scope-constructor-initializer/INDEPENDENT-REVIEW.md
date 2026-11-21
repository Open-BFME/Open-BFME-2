# Independent V3 tooling review

Verdict: no blocking finding found within the reviewed four-file patch and the explicitly exercised boundaries. One pre-existing-comment encoding regression is P3 and does not block a separate normal tooling admission. This is a bounded correctness review, not a general security guarantee or approval of a game-source adoption.

## Immutable fence

Base: d2e90ccf3b5a6826bce9c68df830c23a38e1b7ad.
Author package: `W:/OpenBFME/diagnostics/continue-20261120-body-recovery-1656/agents/thing/b2-ctor-scope-four-file-tooling-v3-20261121`.
Manifest SHA256: 48e9822bc51d8ddec7615c8837f0fa8d198a46f908dd00e1b84e5ea9c015eeff.
Patch SHA256: 4d96fb028739f9ec77cf2eb3affa2ba33cfacfb8e1b0f6b1c2af7906ad303ad3.

- tools/tu_views.py: 10120bd3edd8619955d71f898961a63cf028739c6ad440c9e1d2e8c04be787cf
- tools/tests/test_tu_views.py: 7726b8ed2685405e67701d9fdc61273f93d7579b6fa976415010af3c3ee8208f
- tools/header_adopt_lane.py: fd188b52966d2d802303f7ec56c3e97b0e4d6df26d17cb9c322db350a704c61b
- tools/tests/test_header_adopt_lane.py: a3c9ba6b41ebf157b8d31908e94b8e84f3d0df043ffb0ce8434cf116ce879acc

Snapshot and live file hashes were checked at start and end. Actual Tracker source remains 5b481f63663772a541ad01154800ef5c685eb4ac3a5b72af56c121267c96631d. Root's separate re_attempts.log overlay was not touched or represented as a clean tree.

## Review and independent probes

Read the full current changes, V2-to-V3 delta, context capture and normal callers. TU read_source preserves CRLF; native prepare_unit takes raw bytes, so these ordinary source frontdoors supply the raw source text required by the new guard. Tool.plan passes its actual root; field_renames carries the pending canonical header as an include seed. Existing default include_walk callers retain their default behavior; complete/raw restrictions belong to the new initializer exception.

Executed `review_probes.py`: 71 compiler-free cases, exit 0. Eight positive owner/syntax controls pass; 59 negative controls refuse; three call/declaration/dereference forms grant no pointer-member definition. One additional physical-newline case demonstrates the context helper does not join a following C token into a macro name, while the strict constructor-prefix/rename reader still refuses that unsupported source. RESULTS.json records all 71 separate outcomes.

The actual guard code runs over a purely in-memory source/header filesystem and a compiler-command fixture. No ownership or scope guard is stubbed. A fixture command is not evidence of the production compiler command. The first private harness run overexpected the context-only helper to reject the unsupported `#define`-newline/C-D source; that expectation was corrected to require refusal at the strict rename frontdoor. No tool code was changed and this was not reclassified as a production test failure.

Covered original P2 family: direct/late-header/command class-owner macros; original FF/VT forms and raw CR variants; OPEN/CLOSE macros in source/header/command; literal and conditional scope fragments split across includes; pending canonical-header macros. Also exercised stale/missing/unread inputs, forced/PCH/response/implicit command inputs, current source/header/command changes between captures, and reuse of a formerly valid context after a header change.

The four narrow syntax readers were considered together: constructor list intervals, structural constructor parameter/list commas, narrowly typed member-call argument separators, and simple pointer-return definitions. Checked qualified/namespace/extern-C constructors, variable shadows, lambdas, comma operators, declarations, foreign/global receivers, malformed/nondefinition pointer forms, original splice refusal and unsupported FF/VT/CR at syntax frontdoors. The full scoped-output versus global-token-output equality requirement remains mandatory for the TU exception.

## P3 and remaining boundaries

P3: header_adopt_lane.py line 2752 contains an accidental mojibake replacement of an existing em dash in a comment. Restoring only that comment in memory preserves the complete AST. Exact hypothetical header SHA256 after that sole restoration: 6d410821b151f29f8792897e526af7d5c6fd2e7a846623a21390d19144c888e8. Root may make that separate textual correction and must bind the resulting actual bytes/AST before normal admission. Reviewer changed no production file.

The new proof deliberately refuses unsupported FF/VT/bare CR even in harmless comments/literals, used macros and incomplete contexts. This conservatism is explicit, not general PP interpretation. V1 and V2 remain historically blocked. No blanket ownership or parser correctness guarantee is made.

The author's reported 1166 passed / 6 skipped / 113 subtests was read, not independently rerun. This review ran zero native compiler or preprocessor calls, no game-source/header/object/cache/ledger/claim/Git writes, no native adopt/accept and no normal build/link gate. Only this private review packet was written. Complete current Tracker macro-owner provenance remains UNPROVEN; syntax 19 mappings/3 intervals/equality does not replace it. Root's ordinary pipeline must retain all gates and may still refuse. Zero task/body/byte/runtime credit.
