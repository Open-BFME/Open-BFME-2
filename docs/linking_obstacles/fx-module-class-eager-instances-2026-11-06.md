### LINK-615: FX module classes are built by eager class-static initializers; retail builds them lazily in `getInstance()`
Status: Open. Updated: 2026-11-09; inspected revision: 511eccc7e8.
Evidence / affected units: `Code/GameEngine/Source/GameClient/FXParticleSystemModules.cpp` (and,
until P5's fix, `FXParticleSystemFactories.cpp`) declares `ConcreteModuleClass<TAG>::s_instance` as
a class static and explicitly instantiates the class per tag, so every tag gets a dynamic
initializer that constructs its module class at static-initialization time.
- Retail (target facts): the point-volume instance is a guarded function-local static in
  `getInstance()` (0x003AB3AA: `test [0xE02B74],1`; construct at 0xE02B64 via 0x003AA8EF; atexit
  `__Finstance` 0x007B7F6B). Its callers (0x003AC4FA, 0x003AD2A9 `getClass`, 0x003AD608) are not
  initializers, and no retail initializer calls the constructor.
- The crash this caused (P5, diagnostic image from bridge-only branch `c2fd2520d2`, receipt
  `2026-11-06T020133Z-boot_smoke-f50c8415a8cf`): the factory unit's `s_instance` copy (selectany
  COMDAT, first on the command line) ran before the modules unit set the tag's `s_name`
  (retail initializer #526), and the constructor (+6, retail 0x3AA8F5) read it as null.
- In that image 1,693 table entries; 30 construct a `ConcreteModuleClass` (29 from the factory
  unit, 1 from the modules unit); 29 ran before their tag's `s_key`/`s_name` writer.
Completed: P5's fix removes `s_instance` from the factory unit only (77/77 exact). The modules
unit's copies, numbered after each tag's `s_key`/`s_name` initializers, now win, so the eager
initializers remain as a known difference from retail.
Remaining / next check: convert the modules unit to retail's shape: no class-static
`s_instance`; `getInstance()` holds a function-local static, as
`Code/GameEngine/Source/GameClient/System/FXParticleSystem/NamedModuleClassInstances.cpp` already
does. A trial removal (not landed) showed what that must preserve:
- 27 `??1?$ConcreteModuleClass<TAG>` destructor rows, all at 0x0057C03B (7 bytes, one folded
  body), were emitted only because `s_instance` needed them. In retail they come from the local
  static's atexit `__Finstance` thunks (0x007B7F6B for the point volume); keep them emitted.
- 40 of the unit's 54 `object-symbol=_$E<n>` rows (the tags' `s_key`/`s_name` initializers)
  renumber when the `s_instance` initializers go. Re-pin them only through
  `tools/pin_admission.py --add` or `tools/add_match.py --pin`, never by hand.
- Verify with `./build.sh` (229/229 today), the unit's `_$E` order against retail's table, and a
  diagnostic-link receipt; then remove this entry's known difference from P5.
Clearance: pending.
Census confirmation: not claimed.

**2026-11-07 reference export dependency.** A default-tag export trial kept the same ordered CRT labels but changed the actions those labels referred to. Compare each target thunk's bytes and relocated symbols as well as the labels before any follow-up. The trial changed 36 actions in each particle unit and was reverted. [Object comparison and DIR32 example](../../reverse/attempt_support/particle-tag-startup-order-20261107.md).

**2026-11-09 the category lists hold every class twice; no behaviour change found (swarm Bridge lane; static reading of image
`80921682e8bc` at `f6dcdf1ce5` and retail, no run).** In the image 27 of 28 `ConcreteModuleClass<TAG>` constructors have two direct
callers, a `_$E` start-up registration and `getInstance`; retail's 27 rows have `getInstance` alone, and no retail `.CRT$XCU` entry
reaches them (`Rva001F3FEA::init` -> `staticInitModules` -> `getInstance`). Each constructor pushes onto its category's `s_first`, so
each list holds every class twice, as two separate objects. The 28th is an extra `ModuleTag<1, RENDEROBJECT_UPDATE...>` class with the
`_$E` caller only, which retail does not have, leaving category 1 with 3 constructors against retail's 2; the other categories compared
equal (category 0x0A not compared). The readers are the nine `Rva001F*Parse` functions, which walk from the head until a key matches:
one read in source, the others known only by their sites. `staticInitModules` reaches all 27 `getInstance` in both images, and lazy
nodes are pushed later, so a valid token finds the same class retail would, provided the lazy path runs before any parse. The eager
copies sit in the tail, reached only by a token no class matches, where the walker read runs off the list in retail too. So this is a
retail difference with no behaviour change found, not a crash lead. It does not settle who owns the conversion.

**2026-11-09 second instances, and who has this.** The bridge lane measured the `f6dcdf1ce5` image: 27 of 28 `ConcreteModuleClass<TAG>` constructors have
two direct callers, `getInstance` and a `_$E` start-up registration from the `s_instance` scaffolding; retail's 27 rows have one, `getInstance`, built lazily from
`Rva001F3FEA::init` through `staticInitModules`, and no `.CRT$XCU` entry reaches them. Each constructor pushes onto its category's `s_first` list, so a module class
can get two instances. Category `$01` also has a third `ModuleTag<1, RENDEROBJECT_UPDATE...>` constructor retail lacks, reached only from `_$E`. Whether the walkers
behave differently was still being read by that lane; not established here. Also `(export unowned)`'s 12 `ModuleTag` KEY/NAME wait on this (LINK-584).

The swarm coordinator assigned the conversion to the Link lane, after LINK-073 is settled. The re-pins go through the admission tools only, and the bridge lane's claims
are checked first. Pass test: a before-and-after link measure and a boot comparison.

**2026-11-09 converted (Link lane; ledger `511eccc7e8`, images at 0x2000000).** The class static is gone from `FXParticleSystemModules.cpp`; `getInstance()`'s
function-local static builds each class, and a declared destructor keeps the 27 destructor rows, one folded body at 0x0057C03B. The unit's CRT actions go from 121
to 93: exactly the 28 `s_instance` actions leave, and the other 93 keep their order, matched by each initializer's bytes and relocated symbols. 50 `_$E` rows were
re-pinned through `add_match` and two re-admitted; 229/229 exact. That removes this entry's known difference from P5. The extra `ModuleTag<1, RENDEROBJECT_UPDATE...>`
class is no longer built at start-up, and the unit's code no longer calls its constructor, but the body is still emitted: 28 `ConcreteModuleClass` constructors are in
the map before and after. Retail has no such class, so that body remains a difference.
Pass test, same base and same parent (`ccee751f5b` against `36ed6970eb`): both reach the menu (receipts `2026-11-09T090612Z-boot_smoke-97329605cf0c`,
`2026-11-09T113935Z-boot_smoke-3677301add0a`). Both links report 0 unresolved and 0 duplicates, with the same 29 stubs and 4,034 bridged tables (104 refused).
`image_iso`: 0 defects gained or lost, 146 wrong vtable slots in each, `initializers_unanalyzed` 1,193 -> 1,165. A skirmish run was not compared.
The initializer bridge rises by one, 468 -> 469. Two causes, both read by replaying `image_report.initializer_report` against each image's own objects and ledger:
- `0x007AF496` came up unreachable because two rows name `_$E160` and the re-admission wrote retail's second copy, 0x007B3EBF, which is outside the `.CRT$XCU` table,
  first. `initializer_report` credits a compiler-local label to its first row. `511eccc7e8` restores the order; the replay then gives `not_registered` 469,
  `registered_not_in_retail` 0, nothing unreachable. The first-row rule stays order-dependent, so a later re-admission can repeat this.
- `0x007AB830` (`_Loc_init`) is newly bridged because a shape-only credit moved, not because anything was lost. The base credited `_$E167`, an `s_instance` action, to
  0x007AB81A (`CAtlWinModule`) and `distlod.obj`'s `_$E1` to 0x007AB830; with `_$E167` gone, `distlod.obj`'s `_$E1` takes 0x007AB81A. That credit is by shape only, so
  whether anything really registers `CAtlWinModule` was not established; it was not registered by `_$E167` in the base either.
Clearance: pending landing. Census confirmation: not claimed.
