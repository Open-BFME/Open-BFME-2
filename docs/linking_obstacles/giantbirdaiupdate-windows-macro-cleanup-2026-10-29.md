### GiantBirdAIUpdate Windows macro cleanup (2026-10-29)

At base `9ddec6b7fb`, windows.h replaces five local macro definitions while
all six rows, both EH graphs, 55 COMDATs and external bindings remain exact
or unchanged. The owning Microsoft-header auditor reduces the file's six
findings to one. The free ABI finding remains: a tested stdlib.h replacement
changes the direct call into an IAT call and fails the update row; it is
reverted. Strict preparation passes and ordinary preview retains LINKS
1,791 -> 1,791 bytes against `85f6b7f40c`. The outgoing audit is INCONCLUSIVE
on the older index and missing current CreateAHeroManager consumer receipt.
Carry that provider/consumer scope into the next scheduled census; no census
gain is claimed. [Checks and prerequisite](../../reverse/attempt_support/giantbird-windows-header-20261029-codex.md).
