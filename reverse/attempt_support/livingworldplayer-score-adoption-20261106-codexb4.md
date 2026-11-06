# LivingWorldPlayer score-consumer header adoption

Inspected revision: `6d409fd607`. Class/cohort claimed as
`yasinschroeder-codexb4`; canonical header unchanged.

## Retained scope and target facts

Replace the private LivingWorldPlayer definitions in StatsReporter.cpp,
StatsReporterStrategicResults.cpp and AptTimeLineStats.cpp with
`Code/GameEngine/Include/GameLogic/LivingWorldPlayer.h`.
The existing matched consumers locate the scorekeeper at player +0x2C8,
the side pointer at +0x40, kind at +0x44 and flags at +0x3C4/+0x3C5.
Use those canonical fields and a typed scorekeeper pointer into the header's
opaque +0x2B8 storage, advanced by 0x10. The scorekeeper views remain unchanged;
this pass establishes player identity, not a recovered scorekeeper declaration.
No donor path or original field spelling is inferred.

The strategic reporter retains bool-return helpers as free inline functions:
direct field tests instead choose CMP instructions where retail loads and
tests the bool. With the helpers, its six rows match again.

AptTimeLineStats includes the player header before Drawable.h, selecting
Snapshot's native profile for this declaration-only consumer. Drawable.h must
remain included: its DRAWABLE_FRAMES_PER_FLASH initializer is the rowed
`_$E1` at 0x007B47BF. Dropping that include removes the initializer; the final
source preserves it. No shared header or shim changes.

## Verification and provider audit

- Initial scoped build: 104/104 code rows matched across the three files.
- Final builds: StatsReporter 22/22, strategic reporter 6/6 and timeline stats
  76/76, including all EH funclets and the initializer. Literal, float and
  import checks pass.
- `find_declared_unmatched.py --fail` on all three files passes.
- One `header_adopt_lane.py accept --class LivingWorldPlayer` invocation over
  all three sources: PASS for every source, exactly three queue rows retired.
  Its combined byte/link preview guard passes.
- Compare external-definition sets against saved original objects:
  StatsReporter and AptTimeLineStats remove no external definition. The
  strategic reporter removes only LivingWorldPlayer's inline getPlayerKind,
  getScoreKeeper, getSide, isGuarded and isLost; it adds the two free bool
  helpers. No rowed body, data provider, thunk, alias directive or pin is removed.
- Scan all 23,737 objects under build/match and 8,302 other build objects for
  those five exact decorated names, parsing matching objects' references,
  weak bindings, /INCLUDE and /alternatename directives: no users or alias
  dependencies. The original strategic object was their sole match-cache
  definer. Final definition comparison has no additional removed names.
- `check_csv.py` and `git diff --check` pass.
- Explicit current-input `link_check.py` over the three sources: 3/3 link
  cleanly, 10,978 -> 10,978 linked bytes against the 2026-11-05 15:19 census
  at f44cbcf5b0 (4,640 reporter, 2,237 strategic, 4,101 timeline). The
  timeline's unreferenced allocator deallocate size diagnostic is unchanged
  and not a blocker. This is a scoped preview, not a real image link.

Eight LivingWorldPlayer queue consumers remain. Their existing aggregate and
Snapshot prerequisites in LINK-546 are unchanged. No game-running, real-link
or new census result is claimed.
