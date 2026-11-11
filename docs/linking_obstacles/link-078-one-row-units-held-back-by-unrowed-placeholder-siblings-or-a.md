### LINK-078: one-row units held back by unrowed placeholder siblings or a split class name
Status: Repair landed / awaiting verification. Updated: 2026-10-26; inspected revision:
`e303e68966` (index 2026-10-26 19:02 at `5ce093a71a`).
Evidence / affected units:
- `Code/GameEngine/Source/Common/BfmeConv890.cpp`, `BfmeConv907.cpp` and
  `BfmeConv821.cpp` each held one matched row beside `present-unmatched` bodies
  whose externals nothing defines. Completed: the unrowed bodies and their types
  were dropped (nine `present_unmatched` hatch lines retired); previews LINKS
  0 -> 34, 0 -> 31 and 0 -> 31.
- `Code/GameEngine/Source/Common/Rva000647B5Ctor.cpp` named its class
  `Rva000647B5`, but retail's dtor 0x000647D4 for the same vptrs
  (0x007C5A5C/0x007C5A24) is rowed as `Rva000647D4`. The same respell (with
  the factory 0x00042036) landed independently in faf38d4803.
- `Code/GameEngine/Source/Common/StaticInit/Rva00C6E31EInitializers.cpp`
  (0x007B556E): the same `CImage::s_cache`/`rva007B9B0A` repair landed
  independently in 748950b51b; see LINK-067.
- `Code/GameEngine/Source/Common/Rva006F84C0DeletingDtor.cpp` (0x006F84C0)
  still defines a placeholder `~Rva006F84C0` body retail lacks. Retail 0x006F8460
  (rowed `??1Rva006F8460`) stores base vtable 0x008EC9CC: it is the ICF fold of
  an inline base dtor and the implicit dtors of the 0x18-byte subclass (vtable
  0x008ED358, `??_G` 0x006F8490) and the 0x1C-byte one (vtable 0x008ED364,
  `??_G` 0x006F84C0). A VC7.1 `??_G` always calls its own `??1` (implicit and
  `__forceinline` dtors tried; both emit an out-of-line `??1Rva006F84C0`).
  Remaining: a fold-proof pin of `??1Rva006F84C0` onto 0x006F8460 from a TU
  whose inline base dtor reproduces it, or one family header reconciling the
  `Rva006F6A50Cluster.cpp`, `Rva006F8DA0Cluster.cpp` and
  `FamilyDeletingDtors_Rva006F8460.cpp` views (that file merged into
  `Code/Libraries/Source/Apt/AptDisplayList.cpp` on 2026-11-11). Deferred (re_attempts.log).
- `Code/Libraries/Source/WWVegas/WWLib/StlSweepR3Rva00551B02.cpp`,
  `StlSweepR3Rva005838DC.cpp` and `StlSweepR3Rva005AFEDB.cpp` each row a
  placeholder `??_GRva...Record` whose `??1` is a pin onto a real owner's
  dtor. The owners' objects already emit the byte-identical 28-byte `??_G`
  comdats (`??_GGameSpyBuddyMessageQueue`, `??_GRva005838B5`,
  `??_GRva005AFE3F`). Remaining: re-row each address under its real `??_G` in
  the owner's unit, retire the sweep file and its pin. Blocked because
  `reverse/tu_map.csv` approves no unit for any of the three: 0x005838DC has
  none, and the other two are only proposed. Deferred (re_attempts.log).
  2026-10-28: `tu_map.csv` now approves `GameSpy/Thread/BuddyThread.cpp` for
  0x00551B02, and `tu_skeleton --merge` moved `StlSweepR3Rva00551B02.cpp` into
  it (`./build.sh`: 24/24 matched). Remaining for that address: re-row it as
  `??_GGameSpyBuddyMessageQueue` inside BuddyThread.cpp.
  2026-10-27 link repair (inspected `95cc135fbd`, index `73061d9452`): each
  sweep unit's record now has a `dllimport __forceinline` destructor that calls
  the owner's rowed `??1` by its own name (`??1GameSpyBuddyMessageQueue@@UAE@XZ`
  0x00551988, `??1Rva005838B5@@UAE@XZ` 0x005838F8, `??1Rva005AFE3F@@UAE@XZ`
  0x005AFE3F; FamilyDeletingDtors2.cpp precedent), so the `??_G` rows no longer
  reference the pinned `??1Rva...Record` names; those three symbols.csv pins are
  dropped. `./build.sh` 3/3 exact; `link_check` 0 -> 28 B for each unit
  (+84 B), owners Rva00587F69Dtor.cpp and Rva005AFE3FDtor.cpp keep linking,
  BuddyThread_Unresolved.cpp keeps only its own deque/GameSpy blockers. The
  re-row under the owners' real `??_G` names stays open (tu_map).
Clearance: pending.
Census confirmation: awaiting the next census.
