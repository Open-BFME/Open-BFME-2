### LINK-023: `HAnimClass` views disagree on the vtable layout (`hcanim.cpp` vs `bfmehrawanim`)

(Filed as LINK-020 in its `reverse/re_attempts.log` entry for 0x0018D2A0; renumbered on rebase.)

**Status: Open (constructor emitter cleared; shared views remain). Updated: 2026-10-27; inspected revision: 40d8eced18722ddcee26c59ddc4f3fb8d157d887.**

- **Evidence / scope:** `Code/Libraries/Source/WWVegas/WW3D2/HRawLoadW3D_Unresolved.cpp`
  (149 B, `HRawAnimClass` ctor 0x0018D2A0) lost `??_7HAnimClass@@6BRefCountClass@@@` to
  `hcanim.cpp` and `??_7HRawAnimClass@@6BRefCountClass@@@` to `hrawanim.cpp`. The two winning
  copies come from incompatible `HAnimClass` views: `hcanim.cpp` reads BFME 1's
  `game/.../WW3D2/hanim.h` (23 slots, with `Get_Translation/Get_Orientation(int,float)`,
  `_bfme_hanim_fade`, `_bfme_hanim_v21`), `hrawanim.cpp` reads `reference/shims/bfmehrawanim/hanim.h`
  (21 slots; `HRawAnimClass` appends `Get_VisibilityF` as slot 21). A unit that constructs
  `HRawAnimClass` emits both vtables, so no local view can agree with both owners.
- **Retail (target facts, read from 0x007D5CB8 / 0x007D5D20 / 0x007D5D88, 23 slots each):**
  0 Delete_This, 1 deleting dtor, 2 `Get_Name` (lea +10), 3 dword +40 (name key), 4 lea +30
  (hierarchy name), 5 +44 frames, 6 +4C rate, 7 `Get_Total_Time`, 8 `Get_Translation(Vector3&,..)`,
  9 `Get_Orientation(Quaternion&,..)`, 10 `Get_Transform`, 11 `Get_Visibility`, 12 fade
  (`Get_VisibilityF` / `_bfme_hanim_fade`), 13 +48 `Get_Num_Pivots`, 14 `Is_Node_Motion_Present`,
  15..19 `Has_*`, 20 `Has_VisibilityF` (base returns true), 21 `Class_ID`, 22 pure (raw 0x0018E6F0,
  compressed 0x0018FB70). Neither view has this layout; retail's HRaw ctor stores no `HAnimClass` vptr.
- **Completed:** the unit's `HRawAnimClass` view declares `Get_VisibilityF` as `hrawanim.h` does;
  its HRaw vtable copy now has `hrawanim.obj`'s digest. `./build.sh` 1/1. Tried
  `__declspec(novtable)` on its `HAnimClass` view: the vtable goes but an out-of-line
  `??0HAnimClass@@QAE@XZ` copy then differs from retail's, so reverted.
- **Remaining / next check:** reconcile `HAnimClass` (and the HRaw/HCompressed overrides) to the
  retail layout above in one shared view for `hcanim.cpp`, `hrawanim.cpp`, `htree.cpp`,
  `HRawLoadW3D*.cpp`, re-verifying every virtual-call offset in their matched bodies.

**Canonical-name ABI boundary (2026-11-01):** WorldBuilder A2FF90 self-asserts
Get_VisibilityF for the588B body1903C0 (score8). The normal naming dry-run
renames its implementation and derived declaration, but a private compile
proves it loses the inherited virtual property: the unchanged BFME1 base still
spells _bfme_hanim_fade, so the new function emits QAE rather than rowed UAE.
The QAE body is byte-exact, which does not make it the required virtual entry.
No source/header/row/pin edit was kept. Reconcile the native BFME2 base and
override together; no extra-slot or alias workaround. Unchanged controls80/80
pass. [Compiler proof and reviewed WB body](../../reverse/attempt_support/hanim-visibility-name-20261101/readme.md).

**Constructor emission follow-up (2026-10-27):** at inspected revision 40d8eced18722ddcee26c59ddc4f3fb8d157d887, the current-object preview reproduces the sole HAnim vtable blocker against index 5ce093a71a (2026-10-26 19:02, retail-truth-4). The object reference graph shows that only the unused standalone HAnimClass constructor copy references that table. Marking that existing inline constructor __declspec(dllimport) __forceinline retains its inlined base initialization and stops both unused external copies. No novtable change is needed. The actual 37-byte HAnim constructor remains rowed in hcanim.cpp at 0x0018D170; the native HRaw constructor has no HAnim vptr store. The 149-byte HRaw row remains exact, its one EH graph is EXACT, and declaration and shadow data checks pass. A paired preview retains LINKS for hcanim.cpp, hrawanim.cpp and hanim.cpp, while HRawLoadW3D_Unresolved.cpp changes from blocked to LINKS. This constructor-emission subset is cleared in ordinary-preview scope; census confirmation pending. The incompatible shared class views documented above remain a separate prerequisite for full ABI reconciliation.

**Consolidation follow-up (2026-10-27, inspected `0ea53cd8e3`):** the supported
hrawanim merge dry-run is blocked before class reconciliation: carrying
`BfmeConv1372.cpp`'s empty flag override loses 14 seed rows and four loader
rows. `flag_defaults.py propose` confirms that simply deleting the override
loses its 128-byte row at 0x0018D220 (region build: 126 bytes). No merge,
flag override or path move retained. The constructor donor's handwritten
`toupper` declaration was replaced with `<ctype.h>`; both loader units now
have clean Microsoft-header scans and their two stale queue entries are
retired. Constructor byte verification is 1/1, both loaders' EH graphs are
EXACT 4/4, shadow data checks are clean. Before/after previews against
`bf3dd31211` retain LINKS for both loaders, hrawanim and hanim. hcanim has an
independent pre-existing duplicate `?reset@Rva0018F900FramePrefix@@QAEPAV1@XZ`
in both previews; its earlier clean preview above remains historical.
Next: resolve donor flag compatibility, retry the supported merge, then
reconcile the shared views. Census confirmation remains pending. Evidence:
`reverse/attempt_support/hrawanim-consolidation-flags-20261027.md`.

**Consolidation cleared (2026-10-29, merged at `04440f742e`):** the supported
merge absorbed all four donors into `hrawanim.cpp` (35 rows, no rejects, link
guard passed). Three prerequisites: `BfmeConv1372.cpp` records its real
`-arch:SSE -G7` flags (`beb9e1e2f2`, carried to the TU); both loaders include
the `bfmehrawanim` shim headers in place of private copies, with
`HRawAnimClass` a friend of `MotionChannelClass` (`e10fa34caa`); and
`tu_skeleton.py` composes the seed's trailing `optimize("gsy", on)` after every
donor body (`52e2b25552`), which had compiled each donor size-optimised and
refused it on bytes. Verified: `./build.sh hrawanim.cpp` 35/35, `eh_verify`
EXACT 5/5, `link_check --staged` LINKS with 6,766 own bytes, full gate green.
Census confirmation pending. The shared-view reconciliation above (one
`HAnimClass` layout across hcanim/hrawanim/htree) remains open.
