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


**2026-11-07 category registration measurement.** The [real link at 50a776d8b4](https://github.com/Open-BFME/Open-BFME-2/actions/runs/42376713708) contains f138620c0c. All 17 registration exports are absent from the unresolved list. The same run adds nine unresolved s_head references, one per INI parser, so the total changes from 217 to 209, with zero duplicates and no image.

The nine parsers now bind the existing private s_first definitions. Each 110-byte body and EH graph verifies. The one changed DIR32 reference per parser keeps its retail address; each new name has a definition in FXParticleSystem.cpp and none of the parser objects retains the old reference. A real-link run including the parser repair remains pending.


**2026-11-07 claimed, and handed back: the ConcreteModuleTemplate tables (swarm Link lane).**
Claimed by the swarm Link lane (`ancalgonn-swarm-link`) from 2026-11-07: only the two
`ConcreteModuleTemplate` tables `VectorDeletingDtorsV06.cpp` emits, LifeEvent's and TerrainCollision's
own one-slot `6B?$CategoryModuleInfo@$07@1@@` tables (retail 0x0081CA00 and 0x0081CAA0). The
CategoryModuleInfo path (the 0x0081C780 fold, the `CategoryModuleTemplateBase` tables and the shared
category constructor COMDATs) stays with McMickey93. The data-export half moved to the Link lane below,
and the 12 default KEY/NAME were then routed to seat6.

*Landed with this note:* `VectorDeletingDtorsV06.cpp`'s `CategoryModuleTemplate<8>` is retail's nested
shape, `: CategoryModuleTemplateBase<8>, EventModuleInfo` with `CategoryModuleTemplateBase<8> :
ModuleTemplate, CategoryModuleInfo<8>` (one pure slot, protected non-virtual destructor). The unit now
defines both export names; its 4 rows stay exact; it defines no category constructor. It no longer
defines the two `6BSecondaryModuleBase@1@@` tables and their `W3` deleting-destructor thunks, which
`FXParticleSystemModules.cpp` (both) and `FXParticleSystemFactories.cpp` (LifeEvent) still define for
their one referrer, `ModuleCtorChainsA.obj`. Expected: 209 -> 207 at the next real link (with the nine
`s_head` names, about 198).

*Handoff for the rest (McMickey93).* The other 48 `ConcreteModuleTemplate` names (25 own
CategoryModuleInfo-path tables, 23 `6B@` tables) and 5 concrete `6B@` tables (Point 0x0081BAE0,
Cylinder and Line 0x0081BB10, Box 0x0081BB40, Sphere 0x0081BB70; Hemispherical's 0x0081BC60 and
0x0081C00C with them) wait on the CategoryModuleInfo path. These tables are emitted only by
three units, all on the flattened shape `X : ModuleTemplate, SecondaryModuleBase, XInfo` (the source
of the `6BSecondaryModuleBase@1@@` and `6BXInfo@1@@` names retail spells `6B?$CategoryModuleInfo@N@1@@`
and `6B@`):

| unit | FX tables defined | shared `CategoryModuleTemplate(Base)<N>` ctor/dtor COMDATs |
|---|---:|---:|
| `FXParticleSystemModules.cpp` | 80 | 0 |
| `FXParticleSystemFactories.cpp` | 71 | 2 |
| `FXParticleSystem.cpp` | 33 | 53 |

(scan of srv1's full object set at 9c81acd297.) Within each of these units the concrete-template names
cannot be separated from the 0x0081C780 names: the nested base that gives a `ConcreteModuleTemplate` its
retail names also renames that unit's concrete templates' category tables to the 0x0081C780 spellings.
The shared constructor COMDATs that broke the ButterflyDraw trial (above) sit in `FXParticleSystem.cpp`
(53) and `FXParticleSystemFactories.cpp` (2); `FXParticleSystemModules.cpp` has none, so it is the unit
where the nested shape costs no COMDAT conflict.


**2026-11-07 data-export half taken by the swarm Link lane.** With the orchestrator's agreement, the swarm
Link lane (`ancalgonn-swarm-link`) takes the FX data exports from McMickey93: `ModuleTag<...>::CATEGORY` and
`IS_DEFAULT` (27 + 27), `CategoryModuleInfo<N>::CATEGORY` (9), then `ModuleTag<...>::KEY`/`NAME` (12).
Evidence it is free: no FX commit by McMickey93 since `e892c4321b` (15:15), who has moved to Apt since; no
live claim on FXParticleSystemModules.cpp, FXParticleSystemFactories.cpp, FXParticleSystem.cpp or any of
their 432 row addresses (claims.py, 2026-11-07 ~19:15 UTC). Claimed `file:` for the three units. Scope: the
data members only; the vtable and CategoryModuleInfo-path work stays with McMickey93.

Route: ordinary source definitions, each static const defined once. Retail folds these constants onto
shared addresses (the 36 CATEGORY names at 9 addresses, the 27 IS_DEFAULT names at 0x007BAC1C); the real
link runs `/OPT:NOICF`, so each definition keeps its own address here. Any image_iso or data_check report
of one retail address with several names, or of a "wrong" global there, is this known `/OPT:NOICF`
difference, not a defect.

*Data-export progress (swarm Link lane, 2026-11-07).* `65ebadfcb3` defines the nine
`CategoryModuleInfo<N>::CATEGORY` (FXParticleSystem.cpp, 392/392 exact, nine names added and nothing
else); `cdeaf254ee` defines the 54 `ModuleTag<...>::IS_DEFAULT`/`CATEGORY` (FXParticleSystemModules.cpp,
229/229 exact; plus the plain RenderObjectUpdate tag's two, which existing code instantiates implicitly
and retail does not export). data_check: 0 findings on both units; link_check: both LINKS, LINKED
unchanged. Against the real link at b033afb2ab (195 unresolved), the two commits define 63 of them:
predicted 132.

*The 12 `ModuleTag<N, DefaultModuleKey<N>::VALUE, ...>::KEY`/`NAME` are not missing definitions.*
Retail's export table puts them at 0x00A02C88/8C, 0x00A02C98/9C, 0x00A02CA8/AC, 0x00A02CB8/BC,
0x00A02CC8/CC and 0x00A02C48/4C (categories 1, 0, 3, 2, 7, 6). `data_ledger.csv` already rows those
twelve slots, and `functions.csv` their twelve 11-byte dynamic initializers (0x007AF48B..0x007AF5F6),
under an invented name: `DefaultModuleTag<N>::s_key`/`s_name`. Retail exports `DefaultModuleTag<N>`
names (96 of them: vtables, `createTemplate`, ...) but no `s_key`/`s_name`. So the target fact is that
the storage is the reference pair `DefaultModuleTag<N>` inherits from `ModuleTag<N,
DefaultModuleKey<N>::VALUE, DefaultModuleName<N>::VALUE, DefaultModule<N>, DefaultModuleTemplate<N>,
DefaultParticleModule<N> >`. Defining `KEY`/`NAME` beside `s_key`/`s_name` would bind a second global
to each address. That is refused, so the twelve are left for a rename.

Trial (not landed): `DefaultModuleTag<N>` derives from that `ModuleTag`, and `keyReference()` /
`nameReference()` return `Base::KEY` / `Base::NAME`, with `s_key`/`s_name` dropped. FXParticleSystemModules.cpp
stays 229/229 exact, and the object swaps the 12 invented names for exactly the 12 retail names, with no new
references. data_check goes from 0 to 80 wrong-name findings across the unit, because the twelve data-ledger
rows and twelve `??__E?s_key/s_name@?$DefaultModuleTag@...` initializer rows still spell the old names.
To land: the source change, plus a rename of those 24 rows to `?KEY@`/`?NAME@?$ModuleTag@...` and
`??__E?KEY@`/`??__E?NAME@...` (not a placeholder rename, and `rename.py` cannot express the scope change,
so it needs the export-table evidence above, `deleted_rows.csv` tombstones and a `re_log.py` record),
plus the same change to FXParticleSystemFactories.cpp's private `DefaultModuleTag` copy (lines ~719-752),
which still defines `s_key`/`s_name`. Then re-run data_check; the 80 should fall to 0.

*KEY/NAME route needed (false reject recorded in `re_attempts.log`, 2026-11-07).* The 12 exports above are
landable only by a rename the tools cannot yet express, and they are not to be hand-renamed. Routed to
seat6 (`rename.py` owner). The route must do a **data-member rename that changes the owning class**, from
`DefaultModuleTag<N>::s_key`/`s_name` to the `KEY`/`NAME` that `DefaultModuleTag<N>` inherits from
`ModuleTag<N, DefaultModuleKey<N>::VALUE, DefaultModuleName<N>::VALUE, DefaultModule<N>,
DefaultModuleTemplate<N>, DefaultParticleModule<N> >`, **on an export basis** (retail's export table names
`?KEY@`/`?NAME@?$ModuleTag@...` at exactly these addresses and never `s_key`/`s_name`). One application covers:

- the source: `DefaultModuleTag<N>` gains that base, `keyReference()`/`nameReference()` return
  `Base::KEY`/`Base::NAME`, and the `s_key`/`s_name` declarations and template definitions go, in
  FXParticleSystemModules.cpp **and** the private `DefaultModuleTag` view in FXParticleSystemFactories.cpp
  (~lines 719-752; it still defines `s_key`/`s_name`, and left alone it would keep a second copy of each
  reference under the old name);
- the 12 `data_ledger.csv` rows: 0x00A02C48/4C (category 6), 0x00A02C88/8C (1), 0x00A02C98/9C (0),
  0x00A02CA8/AC (3), 0x00A02CB8/BC (2), 0x00A02CC8/CC (7);
- the 12 `functions.csv` dynamic-initializer rows `??__E?s_key/s_name@?$DefaultModuleTag@...@@YAXXZ`
  (0x007AF48B/96, 0x007AF53B/46, 0x007AF567/72, 0x007AF593/9E, 0x007AF5BF/CA, 0x007AF5EB/F6), respelled
  `??__E?KEY/NAME@?$ModuleTag@...@@YAXXZ`, with their tombstones and basis rows;
- a check that FXParticleSystemModules.cpp stays 229/229 and data_check returns to 0 (the trial without
  the row renames shows 80 wrong-name findings).

Expected: real link -12 (to about 120 from the predicted 132).

*The 38 `DefaultModuleKey/Name<N>::GetValue` statics: not taken; they need the recovered TU.* Retail
exports, per default category, `initialized` (`_N`), `value` (`AsciiString`) and a `$S<n>` guard word (12 +
12 + 14). Ours differ three ways: the bool local is spelled `built`, GetValue is defined out of class so
both locals are internal rather than COMDAT externals, and FXParticleSystemDefaults.cpp emits its own
guard numbers (`$S5` for category 1, per `data_ledger.csv` 0x00A029F0). The first two are ordinary source
fixes (24 names). The guard numbers are the blocker, and they gate the batch:

- `$S<n>` is the compiler's counter of generated names across the whole translation unit. Retail's are
  128/132 (category 1, Key/Name), 142/146 (0), 156/160 (3), 170/174 (2), 184/188 (7): 14 ticks per
  category, in the order 1, 0, 3, 2, 7. Category 6 has two of each, 22/26 (0x00A0609C/A0) and 24/28
  (0x00A0294C/58).
- Retail places the guards among the `getInstance` statics of `ConcreteModuleClass<DefaultModuleTag<N> >`
  (0x00A029E8..0x00A02AAC interleave `initialized`, `value`, `$S`, `instance` and `$S1` per category). So
  GetValue was instantiated in the TU that also builds the default categories' concrete classes, and
  about 127 generated names came before the first guard.
- `tu_map.csv` gives the GetValue rows (0x003AA252, 0x003AA97F, ...) no TU. Matching 128..188 honestly needs
  that retail TU recovered, with its content and instantiation order, so the counter lands on retail's
  values. Today the only way to get those exact names is a hatch (alternatename/object-symbol), which is
  not allowed, or new tooling. Prior record: `re_attempts.log` `?$S128@...` blocked. Not taken.

**2026-11-08 vtable half (LifeEvent first) taken by the swarm Link lane.** McMickey93 has made no FX
commit since `e892c4321b` (2026-11-07 15:15) and holds no FX claim (claims.py, 2026-11-08 ~06:10
UTC). The Link lane (`ancalgonn-swarm-link`) claims `FXParticleSystemFactories.cpp` and
`class:LifeEventModuleInfo` to adopt the canonical `LifeEventModuleInfo` header there (LINK-633: under
retail object order, Factories' private 2-slot copy of the class's table at 0x0081C2E4 wins over retail's
4 slots: deleting destructor, loadPostProcess, GetSnapshotName, DoXfer). First obstacle: a dry
`header_adopt_lane.py adopt` fails one of Factories' 77 rows, `??1LifeEventModuleTemplate`, under the
canonical Snapshot base and AsciiString member. Other categories' tables stay McMickey93's.

*LifeEvent done (2026-11-08, swarm Link lane).* FXParticleSystemFactories.cpp, FXParticleSystemModules.cpp
and VectorDeletingDtorsV06.cpp adopt `LifeEventModuleInfo.h` (Factories 77/77, Modules 229/229, V06 4/4
exact); all three copies of `??_7ConcreteModuleTemplate<ModuleTag<8, LIFE_EVENT ...>>@@6B@` (retail
0x0081C2E4) now carry its four slots. The canonical header needed no change: include it before the
FXParticleSystem namespace, with the Snapshot slot macros (BFME_SNAPSHOT_CAPITALIZED_SLOTS, _NAME_SLOT,
_NONCONST_NAME_SLOT, _REFERENCE_XFER). `header_adopt_lane.py adopt` refuses the same adoption on
`??1LifeEventModuleTemplate`, apparently from how it inserts the header (not investigated). Other categories'
tables, and TerrainCollisionModuleInfo's same-shaped private copies, remain open and are not claimed.


**2026-11-08 base-class trial for the 12 default KEY/NAME: startup order does not hold (seat6; master
e9ba150c19).** The route in `c32d83389b` needs a source shape first, so the shape was trialled before any
tool. Blocker: **startup order, the LINK-615 dependency, not rename tooling**, so no rename route was built.
What the 12 are: of the 128 `(export unowned)` at real link c1a124cccc, 78 are vtables, 38 are `GetValue`
locals and guards, and 12 are these.

Each shape was compiled with the build's own command to a scratch object and compared with a clean-source
object: every ordered `.CRT$XC*` entry followed to its initializer, its bytes and every relocation, allowing
only the intended `s_key`/`s_name` respelling and compiler-local labels. A deliberate swap of two default
wrappers was the negative control (it reads as changed). No source was committed and no image was linked.

| Source shape | Compiles | CRT positions changed (Modules of 121, Factories of 55) | Where the 12 stores go |
| --- | --- | --- | --- |
| Primary template with a dependent `ModuleTag<CATEGORY, DefaultModuleKey<CATEGORY>::VALUE, ...>` base | C2143 | | |
| Full `ModuleTag` specializations (the Point and Ortho form) | no: `TemplateType`/`ClassBase` errors, not pursued | | |
| Explicit `template <> class DefaultModuleTag<N>` with that base | yes | 46, 28 | ahead of the other tags |
| Primary template, base named through a non-dependent helper | yes | 36, 36 | after all other tags |
| The same, each default `ModuleTag` class forced complete at the helper | yes | 36, 36 | after all other tags |
| The same, explicit instantiation of each `KEY`/`NAME` at the old definition position | yes | 46, 28 | ahead of the other tags |
| The same, a non-template inline use at the old position, or just before `FX_DEFAULT_WRAPPER(0)` | yes | 46, 28 | ahead of the other tags |

Today's order puts the block straight after `OUTWARD_EMISSION_VELOCITY` and before `LIGHTNING_DRAW`. Every
compiling shape spells all 12 export names, leaves no `s_key`/`s_name`, and keeps the store multiset, all
code sections apart from the `_$E` labels, and (where compared per symbol) the DIR32 address sets. Only the
order moves. Reading: a non-template use or an explicit instantiation emits at once, ahead of everything
deferred, while a use inside a template accessor is queued behind the other tags. No plain source position
lands between them. Class instantiation order is not the driver. This reading comes from these measurements,
not from compiler documentation.

Retail's own order is neither. By initializer address it interleaves defaults with their category's tags:
0x007AF48B/96 category 6's default, then STREAK, QUAD, BUTTERFLY, RENDEROBJECT and LIGHTNING_DRAW, GPU, then
0x007AF53B.. the other defaults. So the sequence the ledger pins today is itself a product of the eager
`s_instance` shape (LINK-615), and closing LINK-615 may be what makes these names land.

Remaining: re-measure after the Link lane's nested `CategoryModuleTemplateBase<N>` shape lands, because it
rewrites this unit. Not measured: whether that shape yields `ModuleTag<...>::KEY`/`NAME` itself.
**2026-11-08 the GetValue statics re-read (merge lane 2, `ancalgonn-swarm-seat5`).** This replaces one claim in the
"not taken" block above: the guard numbers do not gate the batch. The 24 `initialized`/`value` names were fixed on
their own in FXParticleSystemDefaults.cpp; the 14 `$S` guards stay open and now have a sharper description.

*The 24 names (done).* `GetValue` is defined in class in `DefaultModuleKey`/`DefaultModuleName` and its bool local is
`initialized`. Both locals are now COMDAT externals under retail's export names. Checked the LINK-615 way on the two objects: 12 CRT actions before and after, in the same order, each target's
bytes and relocated symbols identical apart from those respellings; 11 of 12 `_$E` labels renumber. Scoped DIR32 is OK
(72 verified rows, 19 witnesses). All 72 rows byte-match. The 12 `$S` guards in this object keep our own numbers. Real
link effect is expected at -24 and not yet measured.

*Target facts about the 14 guards (retail image and export table).*

- Exports name `$S22`, `$S26` at 0x00A0609C/A0, and `$S24`, `$S28`, `$S128`..`$S188` inside the contiguous `.data` run
  0x00A02944..0x00A02AAC. Category 6 is the only one exported twice.
- Every surviving GetValue body uses the second set: 0x003AA252 uses `$S24`, 0x003AA97F `$S128`, 0x003AAE23 `$S184`.
- No word in any section of the image holds the VA of `$S22` or `$S26` (byte scan of all sections). Nothing retail
  kept reads them.
- The word just before them, 0x00A06098, is a pointer referenced by 0x0055C45F and by code through 0x0055C8F3.
- The run's `.data` opens after `WindModuleInfo::DEFAULT_MOTION_START_ANGLE` (0x00A02904, referenced at 0x003A53C4).
  `.data` referencers walk monotonically through `.text` from there until a break at 0x00A02D4C (0x003B15D6).
- `__FILE__` anchors: `fxpswindmodule.cpp` at 0x003A5572, `fxpsemittervolumemodule.cpp` at 0x003AFA64.

*Tree facts (measured 2026-11-08; these move).*

- 0x003A53C4..0x003AFA64 holds 929 rows, 42,656 bytes, in 251 source files; 894 rows have no TU, 30 are proposed and 4
  approved. `tu_skeleton.py --plan fxpswindmodule.cpp` shows 1 row in 1 file. No GetValue row has a TU.
- `$S` maxima by object: FXParticleSystemModules 297, Factories 197, FXParticleSystem 177; Defaults was 48 before the
  move in class. Retail's highest known is 188.
- A GetValue ticks our counter by 4 out of class and by 2 in class ($S1, $S3, ...).

*Donor facts (WorldBuilder; not BFME 2 game source).* WorldBuilder pairs 0x0055C478 and 0x0055C8BC with
`fxpsdefaultdrawmodule.cpp`. Its tree also has `fxpsmodulecategory.cpp`, with `present_in_game_dat=no`.

*Inference, not proven.*

- Two objects compiled these templates. This is the strongest step: `$S<n>` carries its TU's counter, so two guard
  names for `GetValue` of category 6 mean two compilations. The bodies were folded to one copy and both guard words
  stayed, which fits the unreferenced `$S22`/`$S26`.
- The object with the 12-guard run is `fxpswindmodule.cpp`, first in link order among the FX objects, so it kept the
  template copies. This rests on `.data` order and one anchor per unit, and the `.data`-order signal measured 0.92-0.95
  in `tu_evidence.py`'s record, below its 99% gate.
- The object with `$S22`/`$S26` is `fxpsdefaultdrawmodule.cpp`. This rests on an adjacent word plus the donor pairing.
- The 100 ticks between `$S28` and `$S128` were template copies the linker discarded. Nothing in the image records them.
- Retail's 4-tick Key-to-Name gap may be the VALUE initializer interleaved with GetValue. Ours is now 2, and the bytes
  and startup order do not depend on it.

*The 14 guards: two options, neither taken.*

1. An export alias from the guard names to our own guards. Not taken: it is a hatch and nobody adds one by hand.
2. Recovering the two retail TUs whole. Not taken: no approval route reaches them (each fxps unit has one anchor, so C
   and T cannot bracket; namespaced names give no N hint; Zero Hour has no such code; the `.data` signal is under the
   gate), it means class views across 251 files, and a merge concatenates what we hold, so it cannot reproduce a
   counter that ran over discarded copies. No tool measures that counter either.

Nothing is planned around these 14. Expect them to be the last names standing. How they count toward the exit is a
question for the owner, and no work here depends on the answer.

**2026-11-08 `LNK1169` on the diagnostic link since `cdcfc30b16` (swarm Link lane).** The real link at
`cdcfc30b16` (run 42475507882) went from 0 to 3 duplicates, and its diagnostic link stops with `fatal error LNK1169`,
so that run wrote no image. `tools/exit_link.py` uses no `/FORCE`, and the local link's runs use the same tool, so a
test stack based on current master should stop the same way. The three measured names are
`??0?$DefaultModuleTemplate@$00@FXParticleSystem@@QAE@XZ`, `??0?$DefaultModuleTemplate@$01@...` and
`??0LightningDrawModuleTemplate@FXParticleSystem@@QAE@XZ`.

*Cause.* A `*CtorThunk.cpp` unit's out-of-line constructor compiles to a COMDAT with selection NODUPLICATES. The
size-and-base views in `VectorDeletingDtorsV02/V03/V05_Unresolved.cpp` declare no constructor, so `new X[2]` makes the
compiler generate an inline one under the same mangled name, selection ANY. The linker refuses that pair. Each unit is
byte-exact on its own, so per-unit checks do not see it.

*Scale, object level, at `a878db6e8e`.* 14 constructors have this pair: `DefaultModuleTemplate<N>` (`$00`, `$01`, `$02`,
`$05`, `$0A`), `LightningDraw`, `LightningEmission`, `TerrainFire`, `QuadDraw`, `StreakDraw`, `Spherical`,
`Cylindrical`, `Outward` and `Ortho`.

*Candidate fix, not landed.* In each of those 14 views, declare the constructor without defining it, one line each (V02
4, V03 7, V05 3), so `new[]` binds the thunk's definition. Patch against `a878db6e8e`:
[dup_fix.patch](../../reverse/attempt_support/fx-anchor-view-ctor-duplicates-20261108/dup_fix.patch). Measured: 0
NODUPLICATES pairs left, 75/75 rows exact across V01-V05, `link_check` keeps those five units' 2,588 bytes. With the
nested category shape applied too: 784/784 rows, DIR32 OK, 12,548 linked bytes kept. **Untested by a real linker when
this was written.** Those files are claimed by their current owner, so it is offered here and not applied; a test stack
that needs current master can apply the patch on a never-land commit.

**2026-11-08 the vtable half: nested category shape (swarm Link lane, not landed yet).** The 78 `??_7` names in the
`(export unowned)` block need retail's `CategoryModuleTemplateBase<N> : ModuleTemplate, CategoryModuleInfo<N>`, which
`SecondaryModuleBase` flattened. Ten units on that shape define all 78 at object level, with bytes, startup order
(CRT actions 77, 121 and 55, 0 changed) and DIR32 unchanged; they await a link before landing. They overlap the shared
`FXModuleTemplateBase.h` route on 21 table names, of which 14 differ: `CategoryModuleTemplate<N>` (N = 0 to 6) has 1 slot
on `6BModuleTemplate@1@@` in `FXParticleSystem.cpp` against 4 in the header (deleting destructor and 3 pure calls, the
header's retail facts), and `v1` aliased to `__purecall` against `__purecall`. The header's shape is the better one.
Follow-up, the Link lane's next after landing unless the header's owner gets there first: reconcile
`FXParticleSystem.cpp` with the shared 4-slot base. It needs the copy constructors written out, since an abstract
category can no longer force them with `new (storage)`, and real `getClass`/`writeINI` on its concrete classes.

**2026-11-08 the anchor patch above is superseded by `41719888fc` (LINK-636),** which adds the same constructor
declarations in V02, V03 and V05. The patch file no longer applies and is kept only as the record of that measurement. A
diagnostic link with that patch on `1e3153af8c` confirmed it with a real linker: 0 `LNK2005`, no `LNK1169`, image written.
LINK-636 also took the three pure slots out of `FXModuleTemplateBase.h`, so the "4 slots" comparison in the note above no
longer describes the header: its `CategoryModuleTemplate<N>` now has one `6BModuleTemplate` slot, while the retail facts at
the top of that header still describe four.

**2026-11-08 the vtable half: nested category shape landed (swarm Link lane).** Ten units take retail's
`CategoryModuleTemplateBase<N> : ModuleTemplate, CategoryModuleInfo<N>` in place of `SecondaryModuleBase`, and
`CategoryModuleTemplate<N>` loses its `v1`, so all 21 table names shared with `FXModuleTemplateBase.h` agree. The nine `?v1@`
alternatenames go. `DefaultModuleTemplate<7>` and Hemispherical's constructors are real classes instead of stores of one-byte
placeholder addresses.

Measured with a real linker, one before/after pair on one tree (master `0fbd488b31` + the `p43-boot2` stack less its P36
diagnostic, TEST ONLY images `97b1300eb4` and `265ef41f34`, path order):

| | before | after |
|---|---:|---:|
| Stubbed names | 107 | **29** (exactly the 78 go; nothing new) |
| Of the 78 `??_7` names | 78 | **0** |
| `LNK2005` / `LNK1169` | 0 | 0 |
| Bridged tables / already correct / refused | 5,075 / 602 / 240 | 5,078 / 618 / 238 |
| Unindexed bindings | 19 | 23 |
| `image_iso` defects | 1,559 | 1,576 (10 fixed, 27 new) |
| Boot | crash dialog, "The ThingTemplate does not exist in AwardSystemManager" | the same dialog |

The 29 left: 14 `$S` guards, 12 `ModuleTag` KEY/NAME, 2 `Matrix4D` and `??1Rva0022B12DSubsystem`. These stub counts are from
diagnostic links; the next real link is the authoritative count.

Which copy wins, read from the after image's map: every `CategoryModuleTemplate<N>::6BModuleTemplate` is provided by
`retail_vtables.obj` (the bridge), so no table comes out short from the two shapes meeting. `Point`, `Box` and
`SphereEmissionVolumeModuleTemplate::6B@` were `diagnostic_stubs.obj` before and are bridged after.

*The 27 new `image_iso` entries.*
- 24 `no_object_retail_nonzero`: ledger rows whose name no object has any more, 22 `ConcreteModuleTemplate` rows still spelled
  `6B<Info>@1@@` plus `_DefaultModuleTemplate6_vtbl0` (0x0081BFA4) and `_HemisphericalEmissionVelocityModuleTemplate_cvtbl0`
  (0x0081BC60). Expected to clear with a ledger refresh; `no_object_defines_it` should rise by about as many until then. On the
  earlier after image, none of the 22 stopped being bridged (`vtable_bridge.discover_table_names` binds current names by
  address). 0x0081BC60 and 0x0081BFA4 are newly unindexed and stay unbridged until the refresh, keeping their compiled table.
- 3 `vtable_short` at 0x0081BAE0, 0x0081BB40 and 0x0081BB70. **This is a reading, shown here, not proven beyond it: the same
  defect relabelled, not a new one.** The same three addresses are among the 10 fixed:

| address | before: `image_iso` | after: `image_iso` | bridge refusal, both images | placeholder in the map, before / after |
|---|---|---|---|---|
| 0x0081BAE0 | `mapping_ambiguous` `??_7PointEmissionVolumeModuleTemplate…6BEmissionVolumeInfo@1@@` | `vtable_short` `_PointEmissionVolumeModuleTemplate_csub_vtbl` | `strong-definition`, 4 slots | 0x10BDB460 / 0x10BDB43C |
| 0x0081BB40 | `mapping_ambiguous` `??_7BoxEmissionVolumeModuleTemplate…6BBoxEmissionVolumeInfo@1@@` | `vtable_short` `_BoxEmissionVolumeModuleTemplate_csub_vtbl` | `strong-definition`, 4 slots | 0x10BDB429 / 0x10BDB409 |
| 0x0081BB70 | `mapping_ambiguous` `??_7SphereEmissionVolumeModuleTemplate…6BSphereEmissionVolumeInfo@1@@` | `vtable_short` `_SphereEmissionVolumeModuleTemplate_csub_vtbl` | `strong-definition`, 4 slots | 0x10BDB46F / 0x10BDB44B |

  The three placeholders are one-byte `char`s in their `*CopyCtorThunk.cpp` units, untouched here, present and refused in both
  images. With the old table name gone, `image_iso` maps each address to the placeholder alone and reports it short. The defect
  under the label is real and older: those copy constructors install a one-byte address as a vtable pointer. Next: the same
  conversion for Box, Point, Sphere and Butterfly (swarm Link lane, checking claims with Static defects).

Bytes and startup on the tree it was rebased to: see the commits. Startup order for `FXParticleSystem.cpp` goes from 77 to 68 CRT
actions, the 9 removed being the invented `g_categoryModuleTemplate<N>` objects' own, the other 68 unchanged in order, bytes
and relocations; Modules (121) and Factories (55) unchanged.

Not done: the 12 KEY/NAME (LINK-615: startup order) and 14 guards. Re-measure the KEY/NAME trial against this shape, as the note
above asks.

**2026-11-08 measured by the real link at `4a3033f245`:** 107 -> 29 unresolved, 0 of the 78, 0 duplicates, no image yet.
`no_object_defines_it` 3 -> 27, as predicted (24 stale ledger rows until a refresh, plus the 3 from before this landing, which
were stale names too: 0x007C6C54, 0x007C6C58, 0x0084D700). The Box, Sphere, Point and Butterfly copy constructors now install
retail's exported tables, not one-byte placeholders, as the Line unit does; 4/4 rows exact, not yet measured by a real link.

**2026-11-08 the nested shape left 23 units depending on the bridge (swarm Link lane, being moved).** The census at `b9aeebea15`
against `d171e84869` lost 27 linking units and gained `VectorDeletingDtorsV06.cpp`. 3 are deleted files whose rows moved
(`RandomValueMultFactorInit.cpp`, `SmallGaps/rva0045F4C2.cpp`, `GameWindowManagerScript_setWindowText.cpp`). 1 is not from
this work: `VectorDeletingDtorsV02.cpp`'s `??1Rva001F3574Vec` pin, repaired by `4fc4b563a4`. The other **23 come from `e82daa0fe0`..`5c67670252`**:
they name table spellings that batch retired, which no object defines now.

Real link: unaffected. At `4a3033f245` none of these names is unresolved, because `retail_vtables.obj` provides them. Census: real,
because it has no bridge. The pre-push audit said INCONCLUSIVE and did not flag it, and the note above did not warn of it. The bridge
is scaffolding, so these move to retail's names next, Link lane, claiming each file:

- `??_7SecondaryModuleBase@FXParticleSystem@@6B@`, the folded single-pure table 0x0081C780: `Common/Rva0055EFE1Ctor.cpp`,
  `GameClient/System/ParticleSys.cpp`, `Behavior/FakePathfindPortalBehaviour.cpp`, `Behavior/SlowDeathBehavior.cpp`,
  `Behavior/TerrainResourceBehavior.cpp`, `Update/OneRingPenaltyUpdate.cpp`, `Update/RubbleRiseUpdateCtor.cpp`,
  `Update/StructureCollapseUpdateCtor.cpp`, `Update/WallUpgradeUpdate.cpp`, `GameNetwork/BfmeThingDGDConstructor.cpp`,
  `GameNetwork/Rva007F9B80Ctor.cpp`, `W3DDevice/.../W3DFloorDrawCtor.cpp`.
- `…6BSecondaryModuleBase@1@@` and `…6B<Info>@1@@` on template and concrete tables: `Common/Rva003AE1A7CopyCtor.cpp` and, under
  `System/FXParticleSystem/`, `ConcreteModuleTemplateCopyCtors.cpp`, `CylinderEmissionVolumeModuleTemplateCopyCtorThunk.cpp`,
  `LineEmissionVolumeModuleTemplateCopyCtorThunk.cpp`, `ModuleCtorChainsA.cpp`, `ModuleCtorChainsA_Rva003ABAF3.cpp`,
  `ModuleCtorChainsA_Rva003ABAF3_Rva003ABB93.cpp`, `Rva003ACD71Ctor.cpp`, `Rva003AD355ModuleCtor.cpp`, `Rva003ADC4FCopy.cpp`,
  `Rva003ADD0BCopy.cpp`.

Also still naming the old class, without a lost link: `Rva0055BCF1ColorModuleCtor.cpp` (a private view) and the unused
`FX_MODULE_TEMPLATE` macro in `Common/BfmeAccessorMacros.h`.

**2026-11-08 the 23 units move to retail's table names.** Each retired spelling becomes retail's exported name at the same retail
address, from the ledger's address and `reverse/exports.csv`: 24 names, none unmapped. `??_7SecondaryModuleBase@…6B@` becomes
`??_7?$CategoryModuleInfo@$00@…6B@`, one of the names of the folded single-pure table 0x0081C780. That is the address's retail name,
not an identity claim for the behaviour units that store it. 277/277 rows exact, DIR32 OK, `link_check` 25 of 26 with the FX units
(Factories already at 0), no old names referenced. `data_check`: 15 findings, the same 15 as before this change. The census is the
pass test: it should give these units back. Not moved, no link lost: `Rva0055BCF1ColorModuleCtor.cpp`'s private view and the unused
`FX_MODULE_TEMPLATE` macro in a shared header.
