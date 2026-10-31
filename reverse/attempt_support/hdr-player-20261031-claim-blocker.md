# hdr-player handoff, 2026-10-31

Base: e847f7c836 (fresh origin/master). Seat: hdr-player. Sandbox: bx_bx95zygy,
fleet-hdr-player, bfme2-toolchain-20261031a. No Code changes or adoptions.

## Claim blocker (observed on the Windows PC)
BFME_CLAIM_OWNER=hdr-player; python tools/claims.py claim class:Player
returned exit 1: 'claimed 0:' and
'not claimed: class:Player (held by someone else)'.

A fresh read-only claims.conflicts({claims.key_of('class:Player')}) identified
class:Object held by object. The expanded footprints intersect at
file/31eae7c3b5c44a69 and file/ff0df1f9a5e95c79. No direct class:Player
holder appeared in the live claim list. This is a logical footprint conflict,
not evidence that the claim backend is broken. The acquire implementation
deliberately fences intersecting class scopes, including shared ledger sources.
No force, claims-disable flag, direct ref manipulation or tool patch was used.
The task requires skipping held scope and forbids touching Object.
Consequently Player was not edited, no Player contract attributes were
decided, and no header was registered. Retry the ordinary class claim after
the overlapping Object scope is released; do not bypass the conflict.

## Independent PlayerList reconnaissance (source/tool evidence only)
class:PlayerList was claimed successfully on the PC. Current dest on the base:
Code/GameEngine/Source/Common/System/game_engine_subsystems.h
(BFME 1 donor game/GameEngine/Source/Common/System/game_engine_subsystems.h).
This differs from the Common/PlayerList.h destination assumed in the packet.

Sandbox class_contract.py --class PlayerList --write completed, exit 1:
305 views, 9 uncompiled, bases SubsystemInterface then Snapshot
(retail-ctor inference), sizeof 20 (majority).
Undecided: inherited@0x0, inherited@0x4, inherited@0x8, inherited@0xc,
slot1, slot2, slot3, slot4, slot11, slot12, slot13.
Do NOT freeze sizeof 20 or the conflicting slots from this output.

Existing matched-source leads (not independently revalidated against image here):
PlayerListCtorBFME2.cpp describes primary base 12 bytes, Snapshot at +0x0c,
local at +0x10, count at +0x14, 20 pointers at +0x18 (total 0x68),
and allocation of twenty 0x758-byte Players.
PlayerListDtor.cpp describes primary vtable 0x00BFD618 and the secondary
Snapshot adjustor at RVA 0x002A7ECD. These source comments are leads,
not new retail layout proof.

Prerequisite: canonical_classes.csv names SubsystemInterface header
Code/Libraries/Source/subsystem/SubsystemInterface.h, whose surface declares
only the virtual destructor, no init/reset/update or inherited slot surface.
The older reference/shims/subsystem_bfme2/subsystem_interface.h describes
fourteen primary slots, with init at 1, reset at 9, update at 10, and
PlayerListCtorBFME2.cpp uses that shim. A correct shared PlayerList
inheritance surface needs this difference reconciled from retail first;
copying the private shim or guessing new inherited slots is not a remedy.
Snapshot's registered header is reference/shims/moduledata/Common/Snapshot.h.
No PlayerList header attempt or donor rewrite was made.

## Verification and freshness
Sandbox tools/check_csv.py passed: 99253 function rows, 9361 symbols,
2253 data rows. No build, commit or compiler ran on the PC.
Only PlayerList contract introspection compiled in the sandbox.
No new build.sh byte verification or link preview was run; no link gain claimed.
BFME 1 pinned inputs: 7a8a034afa7dd3530d9a99dc48cfec711626256c.
Official upstream master from ls-remote: a0ae28a558faaf36a4cab43b7e772a1b0dcdb9ea.
The reference freshness update remains unverified; no success stamp was written.
Retained the verified pin rather than advancing it without a full verification.
No push, new hatch, pin, baseline or tools change.

Next: coordinate release of overlapping Object scope, reclaim Player normally,
then inspect retail vtable/layout and matched callers for each of the 14
Player decision attributes. Keep donor facts and target proof separate.
If PlayerList remains necessary, first establish its base's complete slot ABI.
