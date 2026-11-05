### LINK-379: RebuildHoleBehavior header needs native method providers
Status: Blocked. Updated: 2026-11-05; inspected revision: 0602a52962.
Evidence / completed: [Canonical-header trial and retained pool-key cleanup](../../reverse/attempt_support/rebuildhole-header-codexb5-20261105.md); pool-key adoption accepted, destructor trial byte-matches but loses 227 -> 0 preview bytes and is restored.
Remaining / next check: reconcile canonical GetSnapshotName, loadPostProcess and onDie providers with existing native owners (0x0048331C, 0x00497805, 0x004835FB), shared consumers and the secondary-interface ABI before retrying destructor adoption.
Clearance: pending for the destructor; pool-key scope preserves 182 -> 182 preview bytes.
Census confirmation: no new census claimed.
