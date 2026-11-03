### MapSelectMenu headless counter data ownership (2026-10-30)

At base `459d69de971f`, an explicit four-byte data row owns the existing
signed headless counter at RVA `00A045C8`; native writer and reader relocations
bind the same loader-zero object. The owning data tool retires the stale
`_isShuttingDown` duplicate-definition key and finds zero remaining keys for
MapSelectMenu. Strict preparation verifies 48/48 code rows and the data row
across the owner and split-out reader. Ordinary previews retain both LINKS
verdicts and their combined 3,742 bytes against index `85f6b7f40c`.
The staged-tree batch audit is INCONCLUSIVE: that index predates the base,
and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry this owner/reader and affected consumer into the next scheduled
census; full consumer closure remains unverified. No census gain is claimed.
[Ownership proof and checks](../../reverse/attempt_support/mapselect-headless-data-20261030-codex.md).
