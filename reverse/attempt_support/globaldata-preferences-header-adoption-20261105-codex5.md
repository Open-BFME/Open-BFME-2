# GlobalData preference headers and composition prerequisites

Inspected revision: `2187fb40c2`; 2026-11-05; seat `yasinschroeder-codex5`.

## Retained repair

`Code/GameEngine/Source/Common/GlobalData.cpp` uses the existing canonical
`UserPreferences.h` and `OptionPreferences.h`, removing both private class views.
The existing `// platformsdk` marker moves from below those declarations to the
file header: the adoption layout probe truncates the source at the replaced
view, and previously lost this marker, causing `windows.h` C1083. No compiler
flags, shared headers, function rows, source paths, pins or hatches change.

The supported `header_adopt_lane.py adopt --apply` passes for both classes.
Their queue rows retire only through `header_adopt_lane.py accept --class ...`.
`./build.sh Code/GameEngine/Source/Common/GlobalData.cpp` verifies 141/141 code
rows, all three data rows, 117 funclet labels through the parent EH data,
seven string literals, 53 float literals and nine named imports. The declaration
check reports all defined functions matched. The ordinary current-object link
preview is LINKS, 7,662 -> 7,684 bytes against the 2026-11-04 22:40 census at
`3a95b274a2`. This proves preservation in that preview; the 22-byte difference
from the older census is not attributed to this header repair. No new census
or real-link result is claimed.

## Composition remains blocked

Before the repair, `tu_skeleton.py --merge .../GlobalData.cpp --dry-run` accepted
zero donors. `tu_views.py` also accepted no donor and changed no class:

- `Rva00236285`: the seed's opaque 36-byte `words` overlaps the constructor
  donor's five integers and vector-base storage.
- `Rva002362B4`: the seed models a base occupying all 36 bytes, whereas the
  destructor donor owns its strings and vector directly at offset zero.
- `TerrainLighting` is already shared; repeating view reconciliation buys
  nothing. The lighting donor's canonical GlobalData include currently clashes
  with the seed's SubsystemInterface declaration.
- `MultiPlayOtherMultParsers.cpp` compiles in the trial but loses byte matches.
  Reconcile the INI/MultiPlayMults declarations and examine which complete rows
  change before trying to absorb this donor.

The existing attempt history already records the tutorial-type conflicts and
lighting mismatch; these are cleanup prerequisites, not lost matching coverage.
No source move was applied, so no source-path consumer audit or register transfer
is needed for this commit. The committed TU map remains untouched.

## INI adoption diagnostic

After the SDK marker repair, the supported INI adoption trial progresses past
C1083 but refuses `INI::m_0000 (+0x0, 8 bytes) has no canonical field of that
offset and size`. That opaque prefix is never accessed by the source; the view
only reaches `m_loadType` through its inline getter. The canonical declaration
splits the prefix into its real fields. The tool restores the attempted adoption;
its false reject is recorded with `re_log.py`. Fix the mapping/probe treatment of
unused opaque aggregates in a separate verifier change with regression coverage;
do not bypass it by changing the canonical field layout. The INI queue row stays.
