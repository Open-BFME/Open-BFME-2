# Streak renderer TU approval: inline setter crosses another TU

Inspected `47cc49694d`, 2026-11-05. No source, name, or map change.

`tools/next_work.py --claim` selected twenty proposed rows in six sources
for `Code/Libraries/Source/WWVegas/WW3D2/streakRender.cpp`.
`tools/tu_skeleton.py --plan` rebuilt the map from current inputs and approved
only five EH rows, with no complete donor available; the RenderStreak donor
still contains four unapproved rows. The primary pass test remains blocked.

Target facts: `Set_Texture_Mapping_Mode` at `0x007416F0` is a 17-byte row
owned by `streakRender.cpp`. Its definition in
`reference/shims/bfmestreak/streakrender.h:211` is inline. The map assigns it
an S anchor for `streakRender.cpp`. That stretches the TU's span across
`StreakLineClass` definitions independently anchored to `streak.cpp`, including
`0x00741730` through `0x00742C50`. The main renderer run starts at `0x00742EB0`.

Donor fact: the committed Zero Hour input defines this setter inline in
`GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streakRender.h:205`;
its `.cpp` only calls it. This does not establish the target's original TU.

Inference: a header COMDAT kept from an earlier object explains the separate
setter address without a wrong function name. Renaming the valid class/method
or moving its row to force contiguity would not be justified. Next useful work
is distinguishing header-inline placement evidence from a class-site S anchor,
with held-out validation of any ownership-tool change. Do not merge these
proposed rows or commit a regenerated map as a remedy.

Verification: `find_declared_unmatched.py` passes (21 matched rows);
`./build.sh Code/Libraries/Source/WWVegas/WW3D2/streakRender.cpp` passes
21/21 with string, float, import, and renamed-funclet verification. Existing
code and byte coverage remain intact. No link or headline improvement claimed.
