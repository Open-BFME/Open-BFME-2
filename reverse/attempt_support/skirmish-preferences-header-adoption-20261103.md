# Skirmish preference consumer header adoption

2026-11-03; source base `8a141d9686`. This retires header debt, without
claiming a new census measurement or a linked-byte gain.

All six queued `SkirmishPreferences` consumers now include the existing
`GameClient/SkirmishPreferencesClass.h`. The three with private base views
also explicitly include `Common/UserPreferences.h`. No shared header changed.

- `Common/Rva00521658Feed.cpp`
- `Common/SkirmishPreferencesLoad.cpp`
- `Common/StatsReporterRealTime.cpp`
- `GameClient/GUI/GUICallbacks/Apt/AptLoadScreenInit.cpp`
- `GameClient/GUI/GUICallbacks/Apt/AptSkirmishCallbacks.cpp`
- `GameClient/GUI/GUICallbacks/Apt/AptSkirmishDestructor.cpp`

Paths above are relative to `Code/GameEngine/Source/`. Consumers lacking an
STLport selection now use the existing provider's `stlport46` marker and
`/D_STLP_USE_STATIC_LIB` setting. The callback TU retains its existing STLport
selection. Virtual slot 3 calls now spell `write()`, as established by the
canonical header's retail vtable evidence. In the feed view the canonical
0x20-byte member ends at +0x6B8, so the following padding shrinks to retain
the already verified +0x6C4 and +0x6C8 members.

Verification:

- Scoped `./build.sh`: destructor 12/12 rows, callbacks 56/56, remaining four
  consumers 41/41; string, float, import and funclet checks pass (109 rows).
- `header_adopt_lane.py accept --class SkirmishPreferences --header
  Code/GameEngine/Include/GameClient/SkirmishPreferencesClass.h` passes all
  six consumers and retires their six queue rows.
- The corresponding `accept --class UserPreferences --header
  Code/GameEngine/Include/Common/UserPreferences.h` passes the three base
  view replacements and retires three queue rows. Transitive inclusion alone
  does not satisfy this check; those consumers include both headers explicitly.
- Acceptance uses fresh scoped builds and ordinary per-unit link previews;
  each verdict preserves census-linked bytes. Index metadata: `8661f15284`,
  2026-11-03 20:03 UTC; census `23b85ddde5`, 18:36 UTC.
- Frozen-file checks on all six consumers and `tools/check_csv.py` pass.

The existing LINK-041 global-owner repair and LINK-125 callback data-binding
work remain intact. No aliases, pins, data-owner declarations or shared class
declarations were changed. The obstacle register has no new prerequisite or
changed next step from this adoption.
