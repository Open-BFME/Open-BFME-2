# Next StringBase adoption batch (2026-11-15)

Completed locally: eight units replace their private primary template through `header_adopt_lane.py adopt --apply`; their method bodies remain unchanged. The shared string_base.h shim, tools, ledgers, queues and escape-hatch registers are unchanged.

- `Code/GameEngine/Source/Common/BfmeAssignRecord36Assign.cpp` — no switch
- `Code/GameEngine/Source/Common/Rva0033B830Ctor.cpp` — `/DBFME_STRINGBASE_PUBLIC_COPY`
- `Code/GameEngine/Source/Common/Rva005396E6Dtor.cpp` — `/DBFME_STRINGBASE_PUBLIC_DTOR`
- `Code/GameEngine/Source/GameClient/System/FXParticleSystem/LifeEventModuleInfoCopyCtorThunk.cpp` — `/DBFME_STRINGBASE_PUBLIC_COPY`
- `Code/GameEngine/Source/GameClient/System/FXParticleSystem/TerrainCollisionModuleInfoCopyCtorThunk.cpp` — `/DBFME_STRINGBASE_PUBLIC_COPY`
- `Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainModuleDataDtor.cpp` — `/DBFME_STRINGBASE_PUBLIC_DTOR`
- `Code/GameEngine/Source/GameLogic/Object/Update/SpellRechargeModifierUpgradeModuleDataDtor.cpp` — `/DBFME_STRINGBASE_PUBLIC_DTOR`
- `Code/GameEngine/Source/GameNetwork/Rva004D60CADtor.cpp` — `/DBFME_STRINGBASE_PUBLIC_DTOR`

The seven per-unit BFME_STRINGBASE_PUBLIC switches follow the existing 56-unit pattern and add no hatch. They provide layout-view access; retail's members remain private, and the shim is unchanged. Rva0033B830Ctor, LifeEventModuleInfoCopyCtorThunk and TerrainCollisionModuleInfoCopyCtorThunk each call the copy constructor from a reference and therefore use only PUBLIC_COPY, with no PUBLIC_DEFAULT_CTOR. The four destructor units use only PUBLIC_DTOR. No unit receives an unused PUBLIC_COPY; the shim warns that it can change code generation.

Validation: 28/28 retained function rows match, every retained code_identity_gate --staged check reports zero new findings and data_check --enforce passes, accept passes all8, and vt_undefined reports zero newly undefined references (also checked from saved before/after COFF on srv1). Every unit's own link verdict is LINKS, totaling840 ->840 bytes. The nine-source baseline/proposal cohort includes SubsystemInterfaceCopy; all9 ownLINKS remain908 ->908. The index was fetched once successfully for the refreshed bank base: published2026-11-15 22:33 /6dea5665d6. This establishes scoped rows, data/identity admission and linking predictions, not whole-object equality, fresh global census, real-image link or runtime success.

The original 151-unit list had43 landed facade adoptions and108 private copies remaining. This proposal removes five of the17 refused facades and three non-facade copies: after this batch lands, the seat's facade total becomes48/60 and original-list adoptions51/151, with100 originals remaining. These are proposed counts until publication.

The cheap facade link group was re-tested on the preceding run: Rva0021C459Cleanup (94 ->0) and stlport_rva005ec594_clear (55 ->0) still select a non-retail COMDAT despite byte-passing adoption; both are restored. The initial guard-free/nonalias inline group had19 candidates; twelve claimed by other workers were skipped, seven tried, one passed without a switch and six were restored. Rva005396E6Dtor now passes via the header lane's PUBLIC_DTOR route. The other first-trial originals remain unchanged. Its old20:31-index cohort had an excluded original Aura constructor with unresolved Rva003623E5Member destructor; baseline/proposal comparison lost no bytes, and the existing alias-removal-sole-providers-2026-11-15.md/exit-link register already records that symbol. No repair or new regression is claimed for that excluded unit.

Remaining supported work: retry foreign-held files after their claims release. The other inline/codegen views include three alias cases and seventeen qualified-use/provider surgery refusals; extra-friendship has31 guard-free candidates for bounded ordinary trials, and19 provider units need provider-preserving evidence. Preserve the shared shim and supported tooling routes.

Evidence in slotnames scratch: sb3-results (first nine-unit trial and baseline isolation), sb-switch-config.json (claim leases, exact switches and source evidence), sb-switch-results (per-unit identity/data, rows, own link verdicts, before/after COFF and source/dependency hashes), sb-switch-post-frozen.json, and the header lane's ev/sb-switch-pass.txt /ev/sb-switch-trial.tsv. The first sandbox's census fetch correctly refused a missing census ancestor; the bank was rebased onto current master before the successful fetch and all switch trials.

# StringBase facade refusal classes

17 unchanged facade trials after 43/60 landed. One-line reason per unit; historical trial outcomes, checked for current source/private-view presence. No shared-header or gate change is authorized.

- `Code/GameEngine/Source/Common/GapJmpThunksSeat8.cpp` — **surgery guard**: conservative template surgery refuses a preceding brace-containing statement.
- `Code/GameEngine/Source/Common/Rva0033B830Ctor.cpp` — **access**: private StringBase constructor.
- `Code/GameEngine/Source/Common/Rva0045EF90Dtor.cpp` — **alias**: AsciiString typedef conflicts with canonical class.
- `Code/GameEngine/Source/Common/Rva005F91C6Assign.cpp` — **alias**: UnicodeString typedef conflicts with canonical class.
- `Code/GameEngine/Source/Common/System/Rva0021C459Cleanup.cpp` — **link loss**: byte-passed; own LINKED 94 -> 0.
- `Code/GameEngine/Source/Common/WaterDrawFXShaderParameterSourceNamespace.cpp` — **alias**: AsciiString typedef conflicts with canonical class.
- `Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldObjectParser.cpp` — **data row**: 1/1 data row fails after adoption.
- `Code/GameEngine/Source/GameClient/System/FXParticleSystem/LifeEventModuleInfoCopyCtorThunk.cpp` — **access**: private StringBase constructor.
- `Code/GameEngine/Source/GameClient/System/FXParticleSystem/TerrainCollisionModuleInfoCopyCtorThunk.cpp` — **access**: private StringBase constructor.
- `Code/GameEngine/Source/GameLogic/AI/ai.cpp` — **surgery guard**: conservative template surgery refuses a brace-containing macro.
- `Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainModuleDataDtor.cpp` — **access**: private StringBase destructor.
- `Code/GameEngine/Source/GameLogic/Object/Update/SpellRechargeModifierUpgradeModuleDataDtor.cpp` — **access**: private StringBase destructor.
- `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00357AF8.cpp` — **shadow finding**: data identity: wrong-name literal at 0x009E0878.
- `Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerGetEnvironmentName.cpp` — **shadow finding**: identity: wrong EH funclet row at 0x007B6B37 and wrong-name s_names literal at 0x009E1E54.
- `Code/Libraries/Source/WWVegas/WWLib/Rva001EC311Ctor.cpp` — **access**: private StringBase constructor.
- `Code/Libraries/Source/WWVegas/WWLib/Rva002CFD61Erase.cpp` — **alias**: AsciiString typedef conflicts with canonical class.
- `Code/Libraries/Source/WWVegas/WWLib/stlport_rva005ec594_clear.cpp` — **link loss**: byte-passed; own LINKED 55 -> 0.

Cheapest bounded retest: the two link-loss cases already byte-passed; retry the ordinary adoption/rows/cohort link path on current master and the once-fetched index. Five of the six access cases have the existing per-unit PUBLIC_COPY or PUBLIC_DTOR route supplied by the header lane; the shim stays private and unchanged. Rva001EC311Ctor still needs its own constructor-shape evidence. Alias cases require type reconciliation; guards belong to tooling; data/identity cases need their own evidence repair. No guard or access widening.

Header-lane head start: Rva0033B830Ctor, LifeEventModuleInfoCopyCtorThunk and TerrainCollisionModuleInfoCopyCtorThunk each need only BFME_STRINGBASE_PUBLIC_COPY. GarrisonContainModuleDataDtor and SpellRechargeModifierUpgradeModuleDataDtor need only BFME_STRINGBASE_PUBLIC_DTOR. These are five of the original seventeen, pending this seat's rows/identity/link/accept checks. The additional Rva005396E6Dtor and Rva004D60CADtor use PUBLIC_DTOR; BfmeAssignRecord36Assign already passes without a switch. Existing56-unit access-only pattern, no new hatch; no shared shim edit.
