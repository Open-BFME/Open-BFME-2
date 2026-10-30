# Terrain fire emission CRT header cleanup

Inspected base: `7f540888a6`, 2026-10-30. Source:
`Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva0055E6D4Write.cpp`.

The Microsoft-header picker selected its local `free` declaration. The earlier
blocked attempt correctly found that an ordinary `<stdlib.h>` replacement
changes the retail direct call into an imported indirect call. Using the
existing `/D_CRTIMP=` compiler setting with the real header preserves that
binding and removes the local declaration. No function bodies, source paths,
ledger identities, pins or shared headers change.

Verification before and after the edit:

- `./build.sh` verifies all four rows, including the 313-byte parent, its
  handler and both unwind funclets, with four string references.
- `eh_verify.py` reports the parent graph EXACT. The frozen-file check passes.
- All 553 COMDAT fingerprints (bytes and relocation targets), 570 external
  symbol records and the one weak external equal the pre-edit object.
- `data_check.py --converged` passes: 11 addresses, no second names.
- The Microsoft-header auditor reports clean; its scoped `refresh_queue`
  removes exactly this source's one-definition queue entry.
- Strict current-provider preparation passes. Ordinary preview against index
  `85f6b7f40c` (2026-10-29 15:08) retains LINKS, 322 -> 322 authored bytes.

The staged-tree batch audit is INCONCLUSIVE: the index predates the base and
affected consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
lacks a current receipt. Carry that consumer and this provider into the next
scheduled census. Consumer-wide closure remains unverified; no census gain
is claimed. The earlier blocked attempt is retained and superseded by a solved
entry in `reverse/re_attempts.log`.

Selection review before the independent header cleanup: the default picker
served `StlSweepW4Rva002BC47D.cpp`. LINK-040's prerequisite remains the real
52-byte element identity shared across its existing private views. No new
trial or source edit was made there; both its RVA and file claims were released.
