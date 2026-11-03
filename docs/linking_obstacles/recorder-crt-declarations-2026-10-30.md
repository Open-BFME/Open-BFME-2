### Recorder CRT declarations (2026-10-30)

At base `b8a353c950`, Recorder removes redundant stdio/allocation declarations
and its local EOF/FILE layer in favor of its existing real CRT includes.
The owning auditor finds zero local occurrences and retires its one
19-occurrence Microsoft-header queue row; included shim findings remain.
Strict preparation passes 133/133 rows and both data rows; all non-debug
section bytes, relocations and external symbol records remain identical.
Preview retains LINKS and 11,146 authored bytes against `6fe1089c24`
(2026-10-30 04:25). The staged audit is INCONCLUSIVE on its older baseline
and missing current `Common/0CreateAHeroManager21FE49.cpp` consumer receipt.
Full consumer selection/loss checks and census confirmation remain open;
carry Recorder and its consumers into the next scheduled census. The separate
Thing header adoption and sweep Windows-shim prerequisites remain.
No census gain is claimed.
[Verification and scope](../../reverse/attempt_support/recorder-crt-headers-20261030-codex.md).
