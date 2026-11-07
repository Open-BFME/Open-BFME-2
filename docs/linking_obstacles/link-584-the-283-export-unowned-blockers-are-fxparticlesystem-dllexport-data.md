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


A second scoped check provides six additional, previously unowned literal defaults at their retail export names. The six .rdata data definitions match retail exactly and leave all 10 existing external code bodies and relocations unchanged. The enum-valued default still needs its original WindMotion declaration; the two .data constants and the shared 0x0081B310 provider are separate.


Retail export 1148 now owns the shared 0x0081B310 constant. The constructor and writer used kG9, while the wind update used a second named copy. All three use the same const provider now. The original four data bytes and all 37 external code bodies verify, with 3 same-address DIR32 edges rebound. The two .data constants and enum declaration remain open.


**2026-11-06 FX name tables (claude-opus-leosmare-1; real link 6e5fe55db8, run 42233431149, 277 unowned).**
All five FX name-table exports now have defining objects in ParticleSystemTemplate.cpp, as retail's
`const char *const` (`3QBQBDB`). `4397ec04fa` respells ParticleShaderTypeNames, ParticleTypeNames and
ParticlePriorityNames (ordinals 1360, 1361, 1359), which were defined mutable (`3PAPBDA`). It also drops
GameLOD.cpp's second, address-named copy of the priority table (`g_00C1B6A4`). `4be08349e1` defines
EmissionVelocityTypeNames and EmissionVolumeTypeNames (ordinals 1178, 1179; 0x0081B668, 0x0081B684).
They had no definition anywhere; their contents are read from retail. Every data row byte- and
relocation-verifies, and link_check is unchanged for all five units. At this run, every unowned
export outside the template statics, vtables and GetValue locals has a provider (Wind defaults:
`d05bc315e1` and the two commits after it). A new real link is the closure check.


**2026-11-06 measured Wind confirmation.** The authoritative [real link at e185a327a7](https://github.com/Open-BFME/Open-BFME-2/actions/runs/42251863906) lists none of the fourteen earlier Wind exports. It reports 269 unresolved symbols, zero duplicates, and no image. The same run still lists DEFAULT_MOTION and the two start/end angle data names.

The follow-up defines those three. The retail export establishes the WindMotion namespace/type; its four values follow the native WindMotionNames table and the pinned Zero Hour donor ParticleSys.h. MSVC places the start/end float exports in .data, matching retail, and the enum constant in .rdata. The existing external code bodies retain their bytes and relocations except two same-address DIR32 references (memory-read). Confirmation of these three exports awaits a real link containing this change.


**2026-11-06 final Wind confirmation.** The authoritative [real link at 1d41894d2a](https://github.com/Open-BFME/Open-BFME-2/actions/runs/42278649602) contains e4e031a8d0. DEFAULT_MOTION, DEFAULT_MOTION_START_ANGLE and DEFAULT_MOTION_END_ANGLE are absent from the unresolved list, after all three were reported at 63d697e218. All 17 WindModuleInfo defaults now have measured export closure. The real linker reports 262 unresolved symbols overall, zero duplicates, and no image.


**2026-11-06 measured remainder (ancalgonn-swarm-link; real link 12de5b58b2, run 42296273754).** 261
unresolved, 0 duplicates; 254 are `(export unowned)`, all FXParticleSystem. None of the "other" names is
left: the Wind defaults, FX name tables, PooledString statics and `UnicodeString::TheEmptyString` all
resolve. The Hemispherical `operator=` code lead is done too (exports 666 and 570 have matched rows at
0x003A8EFC). What remains is template machinery only:
- `ModuleTag<...>` statics (KEY/NAME/CATEGORY/IS_DEFAULT): 108, 54 of them sharing an address.
- vtables: 82 (50 `ConcreteModuleTemplate`), 30 sharing an address.
- `CategoryModuleInfo::CATEGORY`, `CategoryModuleClass(Base)::s_first`/`s_default`: 26, 9 sharing.
- `GetValue` locals 24 and guards 14.
None of the 254 retail addresses has an approved TU (107 of the ModuleTag statics have no tu_map row),
and 93 share an address with another export, so one global per address applies. Rows need the FX unit's
TU evidence and a fold decision before any definition; the dllexport question stays with the maintainer.
The other 7 unresolved names are LINK-168 (`BehaviorModule::crc`), LINK-018 (`Matrix4D`), LINK-073,
LINK-181 and LINK-622 (LockWeaponCreate).


**2026-11-07 generic ModuleTag references.** 38 KEY/NAME exports have same-address s_key/s_name COMDAT owners in the existing particle module units. The data gate refuses the trial because it cannot form a sizeof expression for the encoded reference template arguments. The trial was reverted. [Reproduction and remaining checks](../../reverse/attempt_support/particle-module-tag-reference-admission-20261107.md).


**2026-11-07 generic ModuleTag references.** 38 existing s_key/s_name names in the module and factory units now use the retail KEY/NAME export names. Each four-byte allocation retains its original zero storage, compiler-emitted startup stores, referent and order. The distinct private RenderObjectUpdate specialization gets the same member spelling and stays outside the export admissions. Plain and default tag storage names stay the same. Scoped bytes, data and EH verify. Both objects retain their ordered CRT records and SELECT_ANY data selections. Only the local compiler label numbers and some COFF section positions differ. The next real-link artifact will measure export closure.

**2026-11-07 default and plain ModuleTag follow-up.** The default-tag trial produced twelve names but changed 36 ordered CRT actions in each of the two particle units. The pre-push check found 32 conflicting DIR32 address sets, versus zero in the saved base objects. Comparing resolved initializer bodies also confirms that the previously published 38 generic renames keep the original sequence in both units. The separate four-name Point and Ortho trial hit MSVC 7.1 declaration errors. Both trials were reverted. [Evidence and prerequisites](../../reverse/attempt_support/particle-tag-startup-order-20261107.md).

The Point and Ortho follow-up found a class specialization that preserves the four storage offsets, one defining object, all 306 code rows, 58 EH records, and both objects' ordered CRT and DIR32 evidence. The four new data rows remain blocked on the size probe for non-COMDAT references. The explicit-instantiation variant moved startup writes and failed four code rows. Both source trials were reverted. [Evidence](../../reverse/attempt_support/particle-tag-startup-order-20261107.md).

**2026-11-07 measured generic ModuleTag confirmation.** The [real link at 2d963894b9](https://github.com/Open-BFME/Open-BFME-2/actions/runs/42323777563) contains 21a0899a82. All 38 renamed KEY/NAME symbols were unresolved at fd6d5a2132 and none is unresolved here. The unique unresolved set shrank by exactly those 38 names, from 261 to 223. The run wrote no image.

**2026-11-07 Point and Ortho reference names.** The four previously deferred specializations keep the one defining Modules object, the declaration-only Factories object and the ordered startup actions. The native data verifier now proves the four-byte allocation from the x86 startup stores in shared .bss. All 306 code rows and 58 EH records verify. The before/after COFF comparison preserves both section graphs, 121 and 55 CRT actions, and the original DIR32 bases after the four intended name substitutions. The next real link that includes this commit will measure the four exports.

**2026-11-07 category registration probe.** The 17 registration pointers have unique export addresses and can use the existing provider. The first source trial keeps all verified code, DIR32 addresses and ordered CRT actions. Its private data probe failed on the nested template closing tokens under VC7.1. The trial was restored and the verifier fix is kept separate. [Reproduction](../../reverse/attempt_support/category-registration-size-probe-20261107.md).


**2026-11-07 category registration slots.** The eight default-registration pointers now use the private CategoryModuleClassBase::s_default identity, and the nine list heads use the private CategoryModuleClass::s_first identity. Each export has a distinct zero-filled four-byte slot already read or written by the matched class code. The original object remains the sole provider. All 17 rows pass native size and byte verification. The original initializer actions, code section graph and DIR32 bases are preserved. Real-link confirmation awaits a measurement containing this change.


The partial specialization follow-up for the twelve default references is blocked by VC7.1 C2755. The trial was reverted. [Compiler boundary](../../reverse/attempt_support/particle-tag-startup-order-20261107.md).


**2026-11-07 ButterflyDraw category table.** The one-slot retail table at 0x0081C780 can be emitted with the exact export identity. That source variant changes two shared constructor COMDAT copies and drops the unit from 115 linked bytes to zero in the local preview. The imported-constructor variants lose the verified deleting destructor. All variants were reverted. [Reproduction and prerequisite](../../reverse/attempt_support/butterfly-draw-category-vftable-20261107.md).


**2026-11-07 measured Point and Ortho confirmation.** The [real link at f0c03faea1](https://github.com/Open-BFME/Open-BFME-2/actions/runs/42372269717) includes 340d85d144. Comparing unique unresolved names with 7112adc012 removes exactly the OrthoEmissionVelocity and PointEmissionVolume KEY and NAME exports at 0x00A02CE8, 0x00A02CEC, 0x00A02D10 and 0x00A02D14. No new unresolved names appear. The total falls from 221 to 217, with zero duplicates. The run wrote no image. The 17 category registration exports were published after the measured commit and await their own real-link result.
