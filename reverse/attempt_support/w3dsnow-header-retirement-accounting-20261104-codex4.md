# Snow header retirement after donor absorption

The pre-push range check refused publication after the verified snow blend/state
merge: both Overridable header-queue rows had passed header_adopt_lane.py accept
in the earlier canonical-adoption commit, but their sources no longer exist at
the range tip. Thus the range could not rerun adoption against those paths.

This is the disappearing-source case permitted by AGENTS.md's debt rule.
The accompanying per-key Debt-Retired trailers account only for these vanished
sources. They do not substitute for adoption: both accept verdicts and exact
byte/link checks were recorded before absorption in
[w3dsnow-override-adoption-20261104-codex4.md](w3dsnow-override-adoption-20261104-codex4.md).
All code remains in the approved W3DSnow.cpp, as verified by the normal merge,
23/23 byte rows, 3/3 exact EH records and the unchanged 48 external definitions
in [the merge audit](w3dsnow-blend-state-merge-20261104-codex4.md).
No baseline or queue is edited by this accounting commit; no code row is deleted.
