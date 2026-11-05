EventParameter TU-approval investigation (2026-11-05)

Inspected revision: 9ae85b0cf15ae6569b05bd9f5a2a9b2c3619cc67.
No game source, row, TU-map approval or naming change was made.

Current-input checks:
- check_csv.py: OK, 99,455 function rows.
- name_lane.py consolidate --under Code/GameEngine/Source/Common/: current
  report written to build/consolidation, no missing inputs. The report contains
  no EventParameter investigation group or original-path corroboration.
- tu_skeleton.py --plan Code/GameEngine/Source/Common/EventParameter.cpp:
  0 approved rows, 0 donor files, 0 mixed files, 0 refused files.

Target facts from narrow searches of functions.csv and tu_map.csv:
- Constructor 0x000B694C is owned by DelayedLuaEventListConstructor.cpp under
  GameLogic/ScriptEngine; its name suggests EventParameter.cpp in that directory.
- Getter 0x000B696B, destructor 0x000B6971 and scalar deleting destructor
  0x000B9866 suggest Common/EventParameter.cpp from their current source paths.
  The latter three are proposed N rows, marked noncontiguous.
- Xfer 0x003318F7 suggests Common/System/EventParameter.cpp from its owner
  SnapshotXfersBfme.cpp. Parent-owned funclet 0x00761537 remains with the dtor.
- The Common span includes an approved W3DModelDraw.cpp row at 0x000B69EA.
- The literal getter and vtable establish EventParameter's identity, as recorded
  by existing row notes and re_attempts.log; they do not establish a source path.

Structural inference: the naming hints derive directory choices from the current
fragment owners (tu_map.py's N construction), so they are insufficient evidence
for combining these three proposed paths or moving rows across the intervening
approved TU. No matching EventParameter definition was found in the pinned
BFME 1 C++/headers. This is an approval/evidence blocker, not a missing body or
regression. Next useful step: find target original-path evidence, a corroborated
WorldBuilder path, or independently proven inline/COMDAT evidence for the
interleaved rows. Do not change names or the map just to make this proposal
contiguous. No byte or linking gain claimed.
