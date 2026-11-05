# DisconnectManager flag and source-shape follow-up (2026-11-05)

Inspected revision: 805f70fc6bc9. Approved destination:
`Code/GameEngine/Source/GameNetwork/DisconnectManager.cpp`.
Prior boundary: [flag split](disconnectmanager-consolidation-flags-20261105.md).

The current supported dry run accepts no donor, with the same empty seed
override boundary. The unchanged seed passes `./build.sh` (5/5 rows), all
literal/import checks and `find_declared_unmatched.py`.

New tests use `tu_skeleton.Verifier` temporary sources and isolated objects,
not the shared match cache. With `-O1 -Ot -arch:SSE -G7`, the seed matches
4/5: processDisconnectKeepAlive (0x004D3CA8) now matches, but resetPlayerTimeout
(0x004D38C5) does not. DisconnectManagerO1 matches 5/38. Each of the six
small donors matches 0/1. Explicit `-Ob1` produces the same counts. Thus
speed preference across the TU does not solve this composition.

Under `-O1 -arch:SSE -G7`, twelve seed trials each retain 4/5 and still miss
0x004D3CA8: switch/default, early return, unsigned-plus-one condition,
unsigned comparison, nested call arguments, separated declaration/assignment,
a truncated int64-return call cast, varargs call cast, and nothrow, noinline,
forceinline and volatile-return declarations of the cdecl helper. These are
rejected probes, not recovered source or evidence for an alternate signature.
The native body cleans with `add esp,8` before `cmp eax,-1`; the size-preferred
body still compares first then pops ECX twice (47 instead of 48 bytes).

Next check remains a target-supported source or compiler explanation that
retains this cleanup and the other 48 approved rows; repeating these source
forms or enabling TU-wide /Ot is ruled out. No source, row, flag override,
header queue or hatch is changed, and no byte/link/file-reduction gain is claimed.
Scope claims released after probing.
