# Consolidation seat 1 late-session probes — 2026-11-04

This supplements the earlier shard 1 blocker records with the four remaining
destinations and mixed routes tested in this continuation.

## LivingWorld.cpp

The plan had 79 approved rows, 3 donors, 12 mixed files, and two donors refused
for unapproved rows. No donor was accepted. `LivingWorldSetActive.cpp` fails on
a duplicate `SubsystemInterface` and missing special-member declaration;
`Rva002BF6D6Dtor.cpp` fails on missing or invalid `LivingWorld` fields. The
target and relevant donor units are census-linked.

The `Rva002BF4F3.cpp` split carved four byte-matching rows, but LinkGuard
rejected two selected COMDATs because their private/weak-free context changes.
No split was applied.

## HotKey.cpp

The plan had 76 approved rows, 4 donors, 6 mixed files, and no unapproved-row
refusals. No donor was accepted. The STL tree erase donor duplicates STL
`operator!=`; the destructor donor has a compile error; and
`HotKeyAddHotKey.cpp` needs `Rva00359032Value`. The prerequisite views are
`HotKeyMap`, `HotKeyMessageActionMap`, `Rva0027EA49`, `Rva00358B65`,
`Rva00358D62`, `Rva00358E6A`, and `Rva00359032Value`. The report lists four
census-linked units.

## GameWindow.cpp

The plan had 107 approved rows, 4 donors, 5 mixed files, and no unapproved-row
refusals. No donor was accepted. `GameWindowWinSetInstanceData_Rva0031495c.cpp`
duplicates `Coord3D` and lacks `GameWindow` fields; `GameWindowFields.cpp` lacks
`WinInstanceData::m_enabledDrawData`; and `GameWindow_winSetText.cpp` lacks the
`winSetText` declaration and `m_instData`. The target and three donors are
census-linked.

The `GameWindowManagerSendMsg.cpp` split carved two byte-matching rows, but the
combined destination fails because `GameWindowManager::VirtualE0` and
`Virtual94` are absent. No split was applied.

## StrategicInGameUI.cpp

The plan had 101 approved rows, 2 donors, 15 mixed files, and one donor refused
for unapproved rows. No donor was accepted; `Rva005E5FFBDtor.cpp` failed
compilation. The largest mixed source, `OwnedPointerResets.cpp`, routes a row to
this TU, but its split is rejected because `StrategicInGameUI` is already
defined. The target and destructor donor are census-linked.
