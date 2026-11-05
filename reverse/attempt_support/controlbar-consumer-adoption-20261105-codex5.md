# ControlBar consumer header adoption

Base: `71a259afde`. Canonical header unchanged:
`Code/GameEngine/Include/GameClient/ControlBar.h`.

Replaced private ControlBar declarations in:

- `Code/GameEngine/Source/Common/RTS/PlayerList.cpp`
- `Code/GameEngine/Source/Common/RTS/PlayerList_getNthPlayer.cpp`
- `Code/GameEngine/Source/Common/Rva002D34FEChain.cpp`

The observer cycling body uses the header's `setObserverLookAtPlayer`, which
stores the same pointer at +0x210. The command-button helper also drops its
partial StringBase declaration; the header supplies the canonical string type.
No shared header, function row, pin or source path changes.

Verification:

- Original and final scoped builds: 37/37 matched code rows and one data row;
  string, float and import reference checks pass. Generated funclets verify
  through parent EH data after label renumbering.
- One `header_adopt_lane.py accept --class ControlBar` over all three sources
  passes and retires three header-queue rows.
- Base and tip `link_check.py` both report 3/3 LINKS, preserving the census's
  2,524 bytes (669 + 1,809 + 46). Index: 2026-11-05 15:19, `f44cbcf5b0`.
  This is a preview, not a new census or real-link measurement.
- External definition counts remain 25, 36 and 1. The only removed external
  definition is `?setObservedPlayer@ControlBar@@QAEXPAVPlayer@@@Z`, replaced
  by the canonical setter's emitted definition. A scan of all 70,748 `.obj`
  files under `build/`, including scratch and saved base objects, found no
  undefined reference, weak reference or INCLUDE directive for the removed
  name; its only occurrence was its definition in the saved base object.
  No object was unreadable.
- Undefined external sets and weak bindings are unchanged in all three
  objects. No alternatename binding is removed. Rva002D34FEChain gains the
  canonical string header's seven existing aliases through its include.
- `check_csv.py`, `find_declared_unmatched.py` over the three files, and
  `git diff --check` pass.

The other ControlBar cohort layout and subsystem conflicts remain outside
this repair. No consolidation or full-image progress is claimed.
