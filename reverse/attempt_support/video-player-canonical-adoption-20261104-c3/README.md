# VideoPlayer.cpp adopts VideoPlayerClass.h: one rename short

Base: 26361cc690 (2026-11-04). Target: the approved
`Code/GameEngine/Source/GameClient/VideoPlayer.cpp`.

`tu_skeleton.py --merge VideoPlayer.cpp --dry-run` rejects every donor:
VideoPlayerAddVideo, VideoPlayerGetVideo and VideoPlayerRemoveVideo include the
canonical `Code/GameEngine/Include/GameClient/VideoPlayerClass.h`, while the
seed keeps a private VideoPlayer and the 14-slot `subsystem_interface.h` shim
(C2011 SubsystemInterface redefinition). `adopt_first` names VideoPlayer for
the seed. tu_views has no plannable class (Rva001D28F0Element is spelled both
class and struct in the ledger).

Trial (`seed_adopts_videoplayerclass.diff`, not committed): replace the shim
include with VideoPlayerClass.h, drop the private VideoPlayer and Rva006892F0
classes, spell the fields the header's way (m_field0C/10/14) and define slot 9
as `VideoPlayer::reset()`.

- With the ledger unchanged: `./build.sh` 33/34; the only failure is
  `?Rva00689180@VideoPlayer@@UAEXXZ` not found (the body is now `?reset@...`).
- With the row's symbol respelled locally to `?reset@VideoPlayer@@UAEXXZ`
  (reverted afterwards, cache entry deleted): 34/34 matched, EH funclets
  verified. `??_7Rva006892F0@@6B@` is 116 bytes with 29 relocations, the
  29-slot table the header's target facts give for 0x00CE48A0 (the shim gave
  14 slots, 56 bytes).

Blocker: the row rename. `rename.py function --rva 0x00689180 --new reset`
refuses `canonical:zh` (no zh-body candidate; ZH's reset body differs) and
`inferred` needs a `name_agreed.csv` record. The key
`VideoPlayer.cpp|function|0x00689180|Rva00689180` has one blind vote
(gpt-6.1-sol, 2026-10-28) and `name_lane.py next --key` did not serve it.
Evidence for the name: retail table 0x00CE4918 slot 9 holds 0x00689180 and
slot 9 is SubsystemInterface's reset; Zero Hour `VideoPlayer.h:279` declares
`VideoPlayer::reset` (donor fact, not proof of BFME 2's spelling).

Private views in W3DMouse.cpp, W3DView.cpp and SidesList.cpp still declare
`virtual void Rva00689180();`; a landed rename must respell them too.

Next: once the name is agreed, rename the row, apply the diff, then re-run
the merge dry run.
