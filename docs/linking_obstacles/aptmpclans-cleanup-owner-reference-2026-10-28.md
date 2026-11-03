### AptMpClans cleanup owner reference (2026-10-28)

Recovery status: upstream `db7cbb506c` already landed both the AptMpClans
cleanup correction and the independent AptOnlineHome correction. Recovered
notes preserve the prior investigation; current CSV validation passes.

At inspected base `996e138889`, cleanup row `0x0079C65F` still named the
donor deleted by merge `bd20921ccb`: a later-rebased funclet cohort retained
the old source. The row now follows its existing parent and handler into
`AptMpClans.cpp`. All 28 rows and six EH graphs verify exactly, and the
destination has a strict current receipt. No game source or emitted object
changes. [Ownership proof and checks](../../reverse/attempt_support/aptmpclans-unwind-owner-20261028-codexb4.md).

The destination is absent from census index `d92e7e6635`, so no ordinary
linking verdict is claimed. The staged-tree batch audit is INCONCLUSIVE:
older index and missing current receipt for affected consumer
`Common/AIHarvestPrepareSiteState.cpp`. Carry the repaired owner and affected
consumers into the next scheduled census. This repairs a dangling ledger
reference; it claims no measured linking or ownership gain.
