# Staging-room transfer composition prerequisite, 2026-11-05

Inspected parent: ed94c4b914. LINK-562. Scope: StagingRoomGameInfo.cpp and
GameSpyStagingRoomXfer.cpp in Code/GameEngine/Source/GameNetwork/GameSpy/.

The supported consolidation planner was run for the GameSpy subsystem. Its
original-path evidence includes StagingRoomGameInfo.cpp; the map is stale and
is only a hint in that report. tu_skeleton rebuilt the map in memory and approved
82 rows, leaving the mixed stlport_pod_vector_bodies.cpp outside the merge.
The first composition failed because the seed omitted GameSpyStagingRoom::xfer
and the donor assumed inheritance from its separate SkirmishGameInfo call view.

Target facts, read directly from retail:

- VA 00C193C8 slot 3 targets RVA 003FFA3C; VA 00C19440 slot 3 targets
  RVA 004FDAC7. Existing GameInfo.h and GameSpyStagingRoom.h declare xfer
  in that inherited slot; their GameSpyStagingRoom derives from GameInfo.
- The 39-byte transfer body at RVA 004FDAC7 calls Version1 at 004FDADC
  (RVA 000053EE), then calls RVA 003FFA3C at 004FDAE4.
- The ledger already names that latter provider SkirmishGameInfo::xfer.
  This repair retains that existing binding through an explicit call-view cast;
  it makes no new claim about the provider's original class identity or layout.

The seed now declares the inherited transfer slot and its derived override.
The donor no longer asserts an incompatible inheritance relationship merely to
make its qualified out-of-line provider call. No shared header changes.

Verification:

- ./build.sh on both files: 82/82 rows exact; 34 string literals, nine empty
  string references and ten import references pass. No float literals.
- Declared-unmatched check passes before and after.
- Both current-object link previews LINKS, preserving 6,143 + 39 = 6,182
  authored bytes against index c95fcfcfcd (2026-11-05 05:17).
- The supported merge dry run accepts both files, rejects none and passes its
  guard for both census-linked units.
- [COFF comparison](symbol-delta.json): all external definitions preserved;
  donor external references unchanged. The seed adds only the existing transfer
  reference. Its vtable changes only offset 0x0C from __purecall to that symbol,
  independently proved by retail above. Other slots remain a partial view.

No debt retirement, source move, census change or runtime result is claimed by
this prerequisite. Apply the successful supported merge next.
