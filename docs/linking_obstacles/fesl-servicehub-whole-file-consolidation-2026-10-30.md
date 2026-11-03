### FESL servicehub whole-file consolidation (2026-10-30)

At base `e37b19e3ab`, the supported merger combines three whole-file donors
into `Code/Libraries/Source/Fesl/servicehub.cpp`, removing two source files.
All four rows (227 bytes) and four string references verify. The merge guard
accepts all three census-linked inputs; six COMDAT fingerprints, four strong
definitions, three external dependencies and two aliases match the combined
originals. Strict preparation and ownership/data checks pass. Five mixed files
still hold eight approved rows. The new path is absent from index `85f6b7f40c`,
so ordinary preview cannot judge it. The initial batch audit is INCONCLUSIVE
on the older index and three missing receipts; strict preparation now verifies
all three affected sources (32 rows). The follow-up audit remains INCONCLUSIVE:
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry that consumer,
the prepared GameNetwork sources and the new provider into the next scheduled
census; full consumer closure remains unverified and no census gain is claimed.
[Evidence](../../reverse/attempt_support/servicehub-consolidation-20261030-codexb.md).
