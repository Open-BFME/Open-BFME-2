### LINK-442: Erase helper retirement needs wider consumer audit

Status: Repair landed / awaiting verification. Updated: 2026-11-05; inspected revision: f87dd00ce4.
Completed: HordeMeleeSwarm and BannerUI erase callers use the existing 0x002161A5 dispatcher; its redundant BfmePod28 pin and unmatched marker are removed. Both providers byte-verify and the paired preview preserves 6,848 LINKS bytes.
Remaining / next check: the wider audit is inconclusive against older index c95fcfcfcd; unchanged consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Refresh affected consumer receipts and repeat the audit, or confirm the cohort in the next scheduled census.
Clearance: paired preview only; wider consumer clearance and census confirmation pending.
Evidence: [scope, trials and verification](../../reverse/attempt_support/horde-copy-helper-retirement-20261105.md).
