### LINK-199: SidesListNotifier constructor caller needs inline base teardown

Status: Cleared for the remaining SidesListCtor consumer. Updated: 2026-11-05; inspected revision: `264eab81ce`.

Four notifier callers now adopt the canonical header; six header-debt entries pass owning acceptance. `SidesListCtor.cpp` remains queued because canonical base teardown emits a call where its retail destructor and EH actions require inline nullable free. Reconcile that lifetime codegen before retrying; the failed trial is restored. Verification: 97/97 bodies exact and all five checked units retain 3,711 census-linked bytes in the published-index preview; no new census result claimed. [Scope, evidence and next check](../../reverse/attempt_support/sideslist-notifier-adoption-20261104.md).

2026-11-04 recovery: reassigned this newer entry from occupied LINK-198 to LINK-199; prerequisite unchanged. [Recovery checks](../../reverse/attempt_support/runner-recovery-20261104-codex/README.md).

SidesListCtor now adopts both canonical headers with TU-local inline base teardown and an intrinsic callback-record copy; owning acceptance retires its notifier row and both changed sources preserve 1,060 linked bytes in ordinary preview. No census confirmation claimed. [Verification and provider audit](../../reverse/attempt_support/member-notifier-header-20261105-codex.md).
