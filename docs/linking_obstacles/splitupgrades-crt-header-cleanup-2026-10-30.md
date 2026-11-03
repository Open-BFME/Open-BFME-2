### SplitUpgrades CRT header cleanup (2026-10-30)

At base `7032de9ba0`, SplitUpgrades.cpp replaces its two local CRT
declarations with string.h and mbstring.h. A scoped import configuration
preserves the direct _mbscpy thunk and imported strtok calls. The complete
199-byte row, literal/import checks, all 15 COMDAT fingerprints and external
bindings remain exact/unchanged; strict preparation passes and preview
retains LINKS against `85f6b7f40c`. The owning header auditor removes one
queue entry (two declarations). The staged audit is INCONCLUSIVE on the older
index and missing current CreateAHeroManager consumer receipt. Carry that
consumer and this provider into the next scheduled census; full consumer
closure and census confirmation remain pending. No census gain is claimed.
[Evidence](../../reverse/attempt_support/splitupgrades-msheaders-20261030-codex3.md).
