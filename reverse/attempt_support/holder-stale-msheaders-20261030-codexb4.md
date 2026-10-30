# Holder destructor stale Microsoft-header queue entries

Inspected base: `94154fcaa4ae82e3d7ed4ad583cafbeaf7462488`, 2026-10-30.
Claimed the three sources listed below.

Commit `5230801e84` already replaced these holders' private C-linkage
`free` declarations with the toolchain's `stdlib.h`. Each source still
uses `/EHs /MD /D_CRTIMP=` to preserve the direct game-allocator call.
The original per-body target checks and before/after object comparison are
recorded in [the repair evidence](holder-dtor-crt-header-20261027.md).
The current queue nevertheless still serves three of those declarations.
The fourth repaired source, Rva0033C3F3Free.cpp, has no queue entry.

The owning `ms_header_audit` scan reports zero local occurrences and zero
include-closure findings for each selected source. Its
`refresh_queue(results, index)` removes exactly the three stale records;
all unrelated queue bytes remain identical. No game source, flags, ledger,
pins, provider names or source paths change. This records existing header
adoption and does not claim a new code repair.

| Source under Code/GameEngine/Source/Common/ | Function rows | Preview authored bytes |
| --- | ---: | ---: |
| Rva0033BD50Free.cpp | 1/1 | 56 -> 56, LINKS |
| Rva0033BD88Free.cpp | 1/1 | 56 -> 56, LINKS |
| Rva0033BDC0Free.cpp | 1/1 | 56 -> 56, LINKS |

All three declared-unmatched checks pass. Strict explicit-provider
preparation verifies all three complete rows with reusable receipts,
including normal byte, literal and import gates. `eh_verify.py` reports
EXACT 3, with no baseline exceptions or missing objects. Ordinary paired
preview uses index `12b9e7a7c0` (2026-10-30 10:11 UTC), retaining all
168 authored bytes. The scan receipt remains in ignored
`build/holder-stale-headers-20261030-codexb4/scan.json`.

These current receipts resolve only the three selected providers' receipt
prerequisite. Earlier wider outgoing-batch audits in the obstacle register
remain unverified; their affected consumers still need the next scheduled
census/current-receipt audit. No census or image-ownership gain is claimed.

The default picker first selected TU approval for the uncreated
Contain/SlaughterHordeContain.cpp. A fresh scoped consolidation packet and
the in-memory rebuilt `tu_skeleton.py --plan` still approve only two unwind
rows in SlaughterHordeContainRva004642D3.cpp, not their parent body. The
older main-code assignments remain proposed/noncontiguous. The existing
independent-anchor prerequisite in the 2026-10-27 Slaughter handoff remains;
no routing assertion, regenerated map or source move was retained, and
that scope claim was released before taking the header cleanup.
