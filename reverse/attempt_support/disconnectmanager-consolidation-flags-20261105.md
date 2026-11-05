# DisconnectManager.cpp TU merge: flag split (2026-11-05)

Target: approved TU `Code/GameEngine/Source/GameNetwork/DisconnectManager.cpp`
(flag override `''` in reverse/flag_overrides.csv), 7 donors, 49 approved rows.

`tu_skeleton.py --merge --dry-run` accepts 0 donors: DisconnectManagerO1.cpp
"loses 32 row(s) under the carried flag override ''", the other six "no baseline match".

Per-flag-set verification (tu_skeleton.Verifier, each file compiled alone beside the TU):

| flags                 | TU seed | O1 donor | other 6 donors |
|-----------------------|---------|----------|----------------|
| '' (current override) | 5/5     | -        | -              |
| -O2                   | 5/5     | 6/38     | 0/6            |
| -O1                   | 4/5     | 35/38    | 4/6            |
| -O1 -arch:SSE -G7     | 4/5     | 38/38    | 6/6            |

Target fact: the one seed row lost under /O1 is
`?processDisconnectKeepAlive@DisconnectManager@@QAEXPAXPAVConnectionManager@@@Z`
(0x004D3CA8, 48 B). Retail cleans the cdecl call to 0x004D39DE with `add esp, 8`
before `cmp eax, -1`; /O1 emits `cmp eax, -1; pop ecx; pop ecx` (47 B), the /Os
form. Retail therefore holds /Ot-shaped and /O1-shaped bodies among the rows the map
approves for this TU.

Next step: either a source shape for processDisconnectKeepAlive that /O1 compiles
to `add esp, 8`, or evidence that 0x004D3CA8 belongs to another TU (tu_map
review). With that row solved, an override change to `-O1 -arch:SSE -G7`
(Verifier-Change, full gate) admits all 7 donors.
