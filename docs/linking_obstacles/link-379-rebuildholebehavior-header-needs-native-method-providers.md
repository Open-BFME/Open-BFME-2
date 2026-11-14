### LINK-379: RebuildHoleBehavior header needs native method providers
Status: Cleared at the providers, pending census confirmation. Updated: 2026-11-05; inspected revision: 8e4a7fa9d5.
Evidence / completed: [Canonical-header trial and retained pool-key cleanup](../../reverse/attempt_support/rebuildhole-header-codexb5-20261105.md); pool-key adoption accepted, destructor trial byte-matches but loses 227 -> 0 preview bytes and is restored.
Completed: native GetSnapshotName (0x0048331C) and onDie (0x004835FB) moved into RebuildHoleBehavior.cpp, loadPostProcess ICF alias (0x00497805); both units adopt the header; [provider evidence](../../reverse/attempt_support/rebuildhole-header-providers-claudec-20261105.md).
Remaining / next check: confirm in the next census; the AICommandInterface and AIUpdateInterface rows of RebuildHoleBehavior.cpp remain (private views in update()).
Clearance: link_check 4 of 4 LINK; RebuildHoleBehavior.cpp 1,213 -> 1,259, RebuildHoleBehaviorDtor.cpp 227 -> 232 preview bytes.
Census confirmation: no new census claimed.


2026-11-14 merge-climb, base `7dfc096d04e68cc6666bdedc00ef396ff014822c`: official `tu_skeleton --merge`
absorbs only `RebuildHoleBehaviorXfer.cpp` into `RebuildHoleBehavior.cpp`. All 21
matched row identities remain, zero lost, one source removed. The moved EH rows
follow their recorded parent (?xfer@RebuildHoleBehavior@@MAEXPAVXfer@@@Z at 0x004833EC).
Build verifies three EH label equivalences; ProviderGuard/LinkGuard pass, and
fresh-index preview LINKS 1328 -> 1676 bytes. Index SHA256
`dda3d19aaa1de0d1c6399c1fdf3f83cd054596d9391256e56322cf951d3808ae`. Remaining: pool-key/dtor donors: Object view undefined; module-data dtor: class declaration missing; one mixed donor remains.
This is a partial source consolidation, with no new census, canonical-layout
or real-image/runtime claim. Receipts: srv1 sweeps/merge-climb/ready-landings/rebuildholebehavior/.
