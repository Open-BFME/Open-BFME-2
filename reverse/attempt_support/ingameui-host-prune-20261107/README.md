# InGameUI host donor cleanup

Base d4b1d294df, 2026-11-07. The served approved-TU consolidation initially
accepts no donors. The existing host still selects Zero Hour's InGameUI header,
while many donors use the canonical BFME 2 header. Four unused host definitions
can be removed independently of that broader layout/flags reconciliation.

isScrolling, setSelecting and isSelecting have present-unmatched markers and
comments claiming competing select-any copies. The current object defines and
references none of those names: the comments describe an older state. Their
rowed 7/19/7-byte bodies remain in InGameUIInputModes.cpp, whose existing anchor
keeps them emitted. Removing the three inactive definitions changes no provider.

The fourth body, setScrollAmount, is an unused Zero Hour struct-Coord2D spelling
(`...UCoord2D...`). The verified owner at RVA 0x0029A85B uses class Coord2D
(`...VCoord2D...`). These are distinct decorated names and different bodies.
The index lists only the host touching the U name; the host has no runtime
reference to it. This change removes that unused reconstruction, without
renaming it onto the existing owner. expireHint and resetIdleWorker have other
signature/access differences and remain separate prerequisites.

## Verification and limits

- Private and normal builds preserve all eight code rows and two data rows;
  one compiler float verifies. Compiler flags remain unchanged in this commit.
- Before/after objects add no external definition and remove only the U
  setter. All 102 simple external code comparisons retain flags, bytes and
  relocations. The three remaining complex sections belong to unchanged,
  unrowed SuperweaponInfo machinery; the simple comparison makes no claim
  about their local/EH relocations. Ordered CRT records are identical.
- The frozen-file check passes; live unmatched markers decrease 37 -> 33.
  hatch_counters.py --update retires those four counts. The same owning-tool
  refresh removes two already-stale counters: an old StatusBitsUpgrade alias
  and a second pin at 0x004B48D3, already removed by earlier work. No code or
  pin is changed for those two metadata corrections.
- The private probe reads the old source from git and the frozen eight-row
  subset, writing candidates only under ignored build/. Its regional trial
  isolates the existing flag obstacle: the scalar deleting wrapper at
  0x007593F0 uses `add esp,4`, while /O1 selects `pop ecx` (25 versus 23 bytes).
  A separate /O1 /Ot trial preserves all eight rows and passes LinkGuard, but
  changing that override is separate work requiring the full repository gate.

No source file, function row, pin, class identity or shared header moves here.
No new census, real image, whole-class or merge clearance is claimed. The
114-donor trial is evidence of prerequisites, not a source-file reduction.
