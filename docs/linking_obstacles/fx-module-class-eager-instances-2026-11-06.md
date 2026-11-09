### LINK-615: FX module classes are built by eager class-static initializers; retail builds them lazily in `getInstance()`
Status: Open. Updated: 2026-11-09; inspected revision: f6dcdf1ce5.
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
