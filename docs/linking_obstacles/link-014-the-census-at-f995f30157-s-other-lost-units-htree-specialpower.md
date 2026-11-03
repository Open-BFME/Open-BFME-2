### LINK-014: the census at f995f30157's other lost units (htree, SpecialPower, FX, BfmeE8, INI _M_find, BfmeConv499)

**Status: Open (partial repair landed). Updated: 2026-10-26; inspected revision: 65972bab0b.**

- **Evidence / scope:** 22 units linked in the census at ef9c691284 but not at f995f30157,
  for causes other than LINK-013 and the INI `__lower_bound` copy. Found by diffing
  `reverse/link_status.csv` (f995f30157 vs 763dc8759f) and reading the f995f30157
  index's blockers.
- **Completed** (each `./build.sh`-exact and previewed with `tools/link_check.py` against
  the f995f30157 index):

  | Unit(s) | Cause | Repair | Preview |
  |---|---|---|---|
  | `htree.cpp` | Merge af2f149baa dropped `/O1 /DNDEBUG`, so four unrowed Zero Hour definitions (`Create_Interpolated` ×2, `Create_Morphed`, `Vector3::Lerp`) called `_assert`, which retail does not import. | `/DNDEBUG` restored (35306cabab). | 0 -> 2,175 B |
  | 14 special-power ports | My landing of 83b2c3fa65 respelled `~SpecialPowerModule` protected after bcac7d81eb had bound the ports to the public spelling. | Public spelling restored (74fdf83172). | 0 -> 1,212 B |
  | `FXParticleSystemDefaultTemplateDtor.cpp` | My c81e10ce9d anchor made `FXParticleSystem.cpp` emit copies of the `DefaultModuleTemplate<2>/<3>` and Ortho dtors ahead of the owner. | Dtors declared in its views (d4fa3d06f2). | 0 -> 64 B |
  | Two `stlport_vector_e8_*` units | Once 289c748fb3 rowed `vector<BfmeE8>::_M_fill_insert`, their whole-class instantiations were non-retail copies first in link order. | Member declared decl-only; `__copy_backward` instantiated explicitly (1f6a6430ad). | 43/43 BfmeE8 users link, +950 B |
  | `_M_find` owner, `StlSweepR3Rva0002CB7D.cpp` | `INI.cpp`'s `_M_find<AsciiString>` called `vector<void*>::operator[] const` out of line. | Accessor forced inline as the owner does; copy now equals retail (f37ca79179). | +110 B |
  | `BfmeConv499.cpp` | 51cc7ed5dc dropped the alias for placeholder `bfmeDoBNH`. | Builds its handle base in place from `TextureAsset::Get`; orphaned pin dropped (65972bab0b). | 0 -> 27 B |

- **Ctor vtable reconciled (2026-10-26):** the ctor and dtor private views now
  declare the same named interface slots: `onSpecialPowerCreation` at slot 7,
  `pauseCountdown` at slot 9 and `startPowerRecharge` at slot 15. Both views now
  bind the same external definitions; this removes the ctor's pure slot 7 and
  the dtor's pure slots 9/15. `./build.sh` passes 7/7 rows across the two
  sources; `tools/link_check.py` against the 763dc8759f check index now links
  `SpecialPowerModuleCtor.cpp` for its 340 bytes (0 -> 340 B).
- **Dtor unit and 14 ports reconciled (2026-10-26):** the minimal
  `BehaviorModule` view in `SpecialPowerModuleDtor_Unresolved.cpp` shared the
  canonical class name, so it emitted two non-retail
  `??_7BehaviorModule@@6B...` COMDATs. Renaming that local, layout-only view
  `BehaviorModuleView` stops those false table owners without changing the
  `SpecialPowerModule` vtable or dtor bytes. `./build.sh` passes 5/5 rows;
  `tools/link_check.py` links the dtor unit for 222 B and all 14
  `??1SpecialPowerModule@@UAE@XZ` consumers for 1,212 B (0 -> 1,434 B).
- **OCL remainder repaired (2026-10-26, inspected `eec2395dbd`):**
  [The paired native-call-view check](../../reverse/attempt_support/ocl-native-call-views-20261026/readme.md)
  clears the three blockers in `OCLSpecialPower.cpp`, which was outside the
  original fourteen ports. The existing BFME2 SpecialPower shim supplies the
  public destructor declaration; the existing native query view supplies the
  static ring-search ABI; the options constructor is declared out of line to
  bind its existing 55-byte owner. All 110 cohort rows and eleven EH graphs
  verify. The actual before/after preview changes OCL from blocked to LINKS
  for 40 authored bytes; all eleven cohort units then link. No new harmful
  COMDAT variant, wrong selected provider or indexed outside incoming edge
  to a removed definition is found. No pins, rows or shared headers change.
- **Remaining / next check:** confirm the OCL forty-byte gain and the earlier
  repaired scopes in the next normal census. OCL's seven unmatched donor
  methods remain separate reconstruction debt.
- **Clearance:** preview scope only (the units listed above and the 14 ports).
- **Census confirmation:** confirmed by the census at `73061d9452` (2026-10-27 14:34):
  htree.cpp, SpecialPowerModuleCtor.cpp, SpecialPowerModuleDtor_Unresolved.cpp,
  OCLSpecialPower.cpp, WeaponModeSpecialPowerUpdateCtorThunk.cpp,
  FXParticleSystemDefaultTemplateDtor.cpp, the three `stlport_vector_e8_*` units,
  StlSweepR3Rva0002CB7D.cpp and BfmeConv499.cpp are linked; no special-power port
  appears among the 217 census-unlinked units. Checked 2026-10-28 by seat halilkkaya-lk3.

#### Current-provider follow-up, 2026-10-25

The [39-source verification](../../reverse/attempt_support/link-regression-clusters-20261025.md)
at `aa31e9bac4` plus the two consumer access corrections confirms the six
historical regression clusters in ordinary preview. All eight AsciiString
units link (11,872 B), as do htree (2,175 B), all three E8 owners (928 B),
the FX template destructor (64 B), and BfmeConv499 (27 B). These are inherited
repairs verified together, rather than additional changes made by this pass.

The expanded check exposed two consumers of the public `BehaviorModule`
destructor formerly emitted by the minimal SpecialPower view:
`SpecialPowerModuleCtor.cpp` and `WeaponModeSpecialPowerUpdateCtorThunk.cpp`.
Their local views now declare that destructor protected, matching the 16
existing indexed providers. Normal verification passes 6/6 rows across both
consumers and a provider, with both consumer EH graphs EXACT. The constructor
links for 340 B; WeaponMode keeps its census-linked 112 B. No forwarding
implementation or new alias is retained.

The recorded combined result at that base is 32/39 clean units; six independent
candidates and the broader DumbProjectile provider unit were blocked as detailed
in the evidence. Concurrent upstream repairs in LINK-015 and LINK-016 supersede
the VectorClass<Vector3> and XferSave residuals from that snapshot.
OCL's protected SpecialPower destructor, findPositionAround and
FindPositionOptions remain open. Float-format's attempted active append
declaration triggers VC7.1 C1001; its alternate syntax fails C2768/C2244/C1506.
An `extern template` declaration of the same member (the MSVC C4231 extension),
tried in `urlBuilder.cpp` on 2026-10-26, also ends in C1001 (`_string.h(573)`); restored.
Both float trials were restored. Broader family closure and census
confirmation remain pending.

- **OCL current-input audit (2026-10-26, inspected `896af21680`, index `d1f046749a`):** `build/link-report.md` and `build/link-worker-20261026/` preserves the three unchanged OCL findings with current providers. The protected destructor and nonstatic `findPositionAround` references originate in the unmatched donor methods; the matched 42-byte constructor remains exact. The recovered finder at `0x00285202` is the static cdecl spelling in `TerrainLogicFindPositionAround.cpp`, and `SpecialPowerModuleDtor_Unresolved.cpp` supplies the public destructor. Adopting those contracts and the native `FindPositionOptions` layout requires reconciling the shared declarations; this seat changes no shared header or unmatched marker decoration. Next check: repair that header family and its consumers together. OCL clearance and census confirmation remain pending.
