# AIUpgrade.cpp merge: donor views shared, vtable COMDAT still blocks (2026-11-04, claudec2)

Base `39bbb0abb2`; model claude-opus-5-5.

Target facts (retail): table 0x00870BD0 has 17 slots. Own bodies: 0 ??_G
0x00597356, 5 0x000B3FD0 (ICF empty body), 8 getCostPerTick 0x00597476,
12 DoXfer 0x005974CC, 13 0x00597372, 14 0x0047A699 (ICF), 15 build
0x0059738A, 16 canMake 0x00597426. Slots 1-4, 6, 7, 9-11 are inherited
unchanged from Rva0055B0CC's table 0x0086B900 (ctor 0x0055B048).

Done (verified, 9/9 rows match, link_check LINKS for all three donors):

- `AIUpgrade_DoXfer.cpp` and `AIUpgradeBuild.cpp` adopt `CommandButton.h`
  (and DoXfer `CommandSet.h`); `header_adopt_lane.py accept` retired 3 rows.
- `AIUpgrade_DoXfer.cpp`, `AIUpgrade_getCostPerTick.cpp` and
  `AIUpgradeBuild.cpp` now declare one identical Rva0055B0CC/AIUpgrade view
  (base fields public, +0x08 m_builderID, +0x10 int m_remaining10, +0x30
  const CommandButton *m_commandButton; virtuals ~AIUpgrade, getCostPerTick,
  DoXfer, build). Build no longer declares 17 placeholder AIUpgrade slots; its
  slot-7 dispatch goes through `AIUpgradeSlot7Dispatch`. `tu_views.py
  --dry-run` no longer reports a base-clause or slot conflict among them.
  None of these donors defines a ctor/dtor, so none emits `??_7AIUpgrade@@6B@`.

Still blocked (not retained):

- Giving the seed `AIUpgrade.cpp` the same view (all its rows still match)
  makes its `??_7AIUpgrade@@6B@` copy 5 entries, while
  `Rva0055B0CCDerived.cpp` (dtor rows 0x0059734B/0x00597356) emits a 1-entry
  copy. `tu_skeleton.py --merge --dry-run`: "the seed itself fails under every
  merged flag set: link: ... comdat ??_7AIUpgrade@@6B@ (first)".
- `tu_skeleton.py --split Rva0055B0CCDerived.cpp --for AIUpgrade.cpp
  --dry-run` (carving the two AIUpgrade dtor rows so one object holds every
  vtable copy): at HEAD "moved selected COMDAT ??_7AIUpgrade@@6B@ lacks
  matching private/weak-free context"; with the shared seed view "selected
  implementation changes for ??1AIUpgrade@@UAE@XZ; ... ??_7AIUpgrade@@6B@".
  The split guard accepts a changed selected copy only when the census judges
  it "ok", i.e. a vtable equal to retail after relocations.

Next step: either a retail-exact AIUpgrade vtable (every inherited slot of
Rva0055B0CC declared virtual under a name that a row at that address carries;
today slots 1-3, 7, 9, 10 are rowed as non-virtual `Q` or other-class names,
4/11/14 and 5 are ICF bodies) or a split-guard rule that accepts moving a
vtable copy whose digest is unchanged and whose referents move with it.
