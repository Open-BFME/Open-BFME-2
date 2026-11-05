### LINK-584: the 283 "(export unowned)" real-link blockers are FXParticleSystem dllexport data

Status: Open. Updated: 2026-11-06; inspected revision: `2ca142bab23`; real links `4f0e20847d`
(run 42093361060) and `17904ed53a` (both 283).

**What the label means.** `exit_link.py` puts every retail export (`reverse/exports.csv`, 1,964)
into the link's `/DEF`. `export_sources()` attributes an export through matched *code* rows'
`target_rva` only, so a **data** export is always "(export unowned)". All 283 are data exports:
83 `??_7` vtables, 54 `ModuleTag<...>::KEY`/`NAME`, 36 `CategoryModuleInfo<N>::CATEGORY`,
27 `ModuleTag<...>::IS_DEFAULT`, 17 `CategoryModuleClass(Base)<N>::s_first`/`s_default`,
24 `DefaultModuleKey/Name<N>::GetValue` locals (`initialized`, `value`), 14 guards
`?$S<n>@?1??GetValue@...`, and 30 others (WindModuleInfo `DEFAULT_*`, the four FX name tables,
PooledString statics, `UnicodeString::TheEmptyString`). Code exports are attributed normally
and covered by LINK-583.

**Root cause.** Retail's export table has the shape of `__declspec(dllexport)` classes: 1,451
FXParticleSystem names plus the utility classes they use. A VC7.1 probe shows that dllexport
emits and exports implicit copy constructors and `operator=`, vtables, and instantiated static
members. When `GetValue` is defined in-class it also exports the function-local statics and their
guard. Our `FXParticleSystemDefaults.cpp` defines `GetValue` out of class, so its locals are
`Static` (and spelled `built`, not retail's `initialized`). The guard numbers are a per-TU
counter: retail's main FX TU uses `$S128`..`$S188`, and category 6 appears from two TUs (`$S22`/`$S26`
and `$S24`/`$S28`).

**Completed (lk34, not yet census-measured).** Code exports given defining objects: e5e4cb43bb1
`ParticleSystemTemplate::GetAssetList` (ICF twin at 0x0047A69C); 505537db773 both
`parseEventFXListName` statics (0x00563EA8, rename plus twin); 4433e0f399d
`DefaultModuleTemplate<0/1>::parseRGBColorKeyframe/parseRandomKeyframe`. Each is byte-exact, and
link_check shows no LINKS loss.

**Remaining / next check.**
- 38 local/guard names: they need retail's exported class with in-class `GetValue`. The 14 guards
  also need the recovered FX TU's initializer order. They are blocked on FX TU recovery; do not
  rename `built` alone, because the locals stay internal.
- Template statics and vtables: they need an owner unit that instantiates them. Adopting
  dllexport in a canonical FX header is a maintainer decision; trial it with link_check first,
  because it adds COMDATs and `/EXPORT`s in every including unit.
- The 30 "other" names are ordinary data identity work.

Evidence: [probe and counts](../../reverse/attempt_support/fx-export-dllexport-20261106-lk34/README.md).
Census confirmation: not claimed.
