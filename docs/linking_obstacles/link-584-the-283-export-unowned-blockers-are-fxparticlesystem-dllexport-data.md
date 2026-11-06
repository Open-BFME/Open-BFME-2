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
- The 30 "other" names are ordinary data identity work. Leads: three of the 17 exported
  `WindModuleInfo::DEFAULT_*` constants are already owned under address names, and they
  are the providers to respell. `windDefault_00E02904` (Rva003A53C4Finish.cpp) is
  `DEFAULT_MOTION_START_ANGLE` (RVA 0x00A02904). `windDefault_00DC0A9C` is
  `DEFAULT_MOTION_END_ANGLE` (0x009C0A9C). `g_00C1B310` (fxpswindmodule.cpp) is
  `DEFAULT_MOTION_END_ANGLE_MAX` (0x0081B310). Retail spells them `static const float` (`2MB`),
  yet the first two sit in `.data`; settle that placement before respelling.
- Code-side lead (not data): export 666 puts `HemisphericalEmissionVelocityModuleTemplate::operator=`
  at 0x003A8EFC. That is the 18-byte body that calls `SphericalEmissionVelocityModuleTemplate::operator=`
  (0x003A738E). The Hemispherical template therefore derives from the Spherical one, with an
  implicit assignment that both it and `ConcreteModuleTemplate<HEMISPHERICAL tag>` inline.
  `FXParticleSystemModules.cpp` declares it beside the Spherical template instead, so providing
  these two exports means reshaping that class. Check its vtables before trying.

Evidence: [probe and counts](../../reverse/attempt_support/fx-export-dllexport-20261106-lk34/README.md).
Census confirmation: not claimed.


**2026-11-06 Wind defaults.** Retail export ordinals 1154, 1145, 1157, 1142, 1143, 1152, 1149 now have their existing four-byte float providers under the exported names. The owner and writer keep their matched code and bind the same retail addresses. All 7 exported data definitions verify against the image. The COFF comparison retains 34 external code bodies; 15 DIR32 edges use the replacement name. The two .data constants and the shared 0x0081B310 provider still need separate reconciliation. A new real-link run is the remaining closure check.
