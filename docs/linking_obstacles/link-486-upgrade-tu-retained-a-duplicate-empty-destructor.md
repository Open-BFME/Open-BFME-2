### LINK-486: Upgrade TU retained a duplicate empty destructor
Status: Cleared for duplicate-definition cleanup; TU consolidation remains open. Updated: 2026-11-05; inspected revision: 9415065957.
Evidence / affected units: Upgrade.cpp and UpgradeCtor.cpp; [target facts, rejected merge and verification](../../reverse/attempt_support/upgrade-duplicate-destructor-20261105.md).
Completed: removed the destination's empty Upgrade destructor and three stale lifecycle markers; retained the matched lifecycle donor and all row owners. Byte verification passes 27/27; present_unmatched falls by three.
Remaining / next check: the [guarded retry](../../reverse/attempt_support/upgrade-merge-retry-20261105.json) accepts no donors; UpgradeCtor now fails bytes instead of C2084, while its standalone 3/3 rows pass. Compare composed lifecycle code and declarations against that object; canonical subsystem/header conflicts remain separate prerequisites.
Clearance: duplicate body removed; current ordinary link preview LINKS, 754 -> 754 bytes, index c95fcfcfcd (2026-11-05 05:17). No source-file reduction claimed.
Census confirmation: awaiting; no new census claimed.
