# FXParticleSystem "(export unowned)" real-link blockers: dllexport probe

Inspected base: `2ca142bab23`; real link `4f0e20847d` (run 42093361060), confirmed
unchanged at `17904ed53a` (283 "(export unowned)").

## Target facts

- `reverse/exports.csv` has 1,964 retail exports (1,428 code, 536 data). 1,451 spell
  `FXParticleSystem`; the rest are StringBase/AsciiString/UnicodeString, Coord2D/3D,
  Matrix4D, PooledString, MemoryPool, Debug, Xfer, Region2D/3D, IntRange, RGBColor.
- The 283 "(export unowned)" errors in `errors.tsv` are all data exports
  (166 `.rdata`, 117 `.data`): 83 `??_7` vtables of FX classes and template
  instances, 54 `ModuleTag<...>::KEY`/`NAME`, 36 `CategoryModuleInfo<N>::CATEGORY`,
  27 `ModuleTag<...>::IS_DEFAULT`, 17 `CategoryModuleClass(Base)<N>::s_first`/`s_default`,
  12 + 12 function-local `initialized`/`value` of `DefaultModuleKey<N>::GetValue` and
  `DefaultModuleName<N>::GetValue`, 14 guard variables `?$S<n>@?1??GetValue@...`, and 30
  others: WindModuleInfo `DEFAULT_*` constants, the four FX name tables
  (`ParticleShaderTypeNames`, ...), PooledString statics, `UnicodeString::TheEmptyString`.
- Guard numbers are the compiler's per-TU counter. Retail's main FX TU numbers
  Key<1>/Name<1> `$S128`/`$S132`, Key<0> `$S142`/`$S146`, Key<3> `$S156`/`$S160`,
  Key<2> `$S170`/`$S174`, Key<7> `$S184`/`$S188`: 14 per category (4 per GetValue and
  6 more dynamic initializers between). Category 6 is exported twice: `$S24`/`$S28`
  at 0x00A0294C/0x00A02958 beside its locals, and `$S22`/`$S26` at
  0x00A0609C/0x00A060A0. Two retail TUs instantiated it.

## Tool facts

- `exit_link.export_definition` writes every export into the link's `/DEF`;
  `export_sources()` maps an export to sources only through matched code rows'
  `target_rva` (`link_census.ledger()` reads `functions.csv` only). A data export can
  never be attributed. "(export unowned)" means "a data export no object defines",
  not "a ledger name nobody owns".

## Structural inference (probe, not a donor)

The export table has the shape of `__declspec(dllexport)` classes. VC7.1 probe
(`probe_inline_getvalue.cpp.txt`, compiled with `/O2 /GX` in scratch, never through
build.py):

- On a dllexport class the compiler emits and `/EXPORT`s the implicit copy
  constructor, `operator=`, the vtable (`,DATA`) and every static data member that
  is instantiated.
- With `GetValue` defined **inline in the class**, the locals become External and
  are exported as DATA:
  `?initialized@?1??GetValue@?$DefaultModuleKey@$00@FXParticleSystem@@CAPBDXZ@4_NA`,
  `?value@...@4UStr@@A`, `?$S1@...@4IA`.
- With `GetValue` defined out of class (our `FXParticleSystemDefaults.cpp` shape),
  the same locals stay `Static`. That is what our object holds today, named `built`
  (retail: `initialized`) and guarded by `$S1..$S45`.

## Consequences

- 36 local/guard names need the retail shape: an exported class with an in-class
  `GetValue`. The 14 guards also need a TU whose dynamic-initializer order
  reproduces retail's counter. They wait on FX TU recovery, not on a rename.
- The template statics (`KEY`, `NAME`, `IS_DEFAULT`, `CATEGORY`, `s_first`,
  `s_default`) and the vtables need their owner unit to instantiate them. Under
  retail's dllexport, every unit that saw the class did that.
- The 30 "other" names are ordinary data identity work, provider by provider.
- dllexport does not change function codegen (only dllimport does). It does make
  every including TU emit more COMDATs and `/EXPORT` directives, so adopting it in
  a canonical FX header is a maintainer decision to trial with link_check, not a
  seat edit.
