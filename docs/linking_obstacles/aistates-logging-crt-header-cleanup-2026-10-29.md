### AIStates logging CRT header cleanup (2026-10-29)

At base `2ede5f876a`, AIStates.cpp replaces its local fprintf declaration with
stdio.h and typed stream casts, preserving direct CRT thunk calls. All eight
rows and every external object fact remain exact/unchanged; strict preparation
passes and preview retains LINKS for 4,714 bytes against index `85f6b7f40c`.
The header auditor removes one queue finding. The batch audit is INCONCLUSIVE:
the index predates the base and the affected CreateAHeroManager consumer lacks
a current receipt. Carry this provider/consumer scope into the next scheduled
census; no census gain or full consumer closure is claimed.
[Evidence](../../reverse/attempt_support/aistates-stdio-20261029-codex3.md).
