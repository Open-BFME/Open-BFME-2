# StringBase facade adoption batches (2026-11-15)

Scope: declaration-only private StringBase templates; registered canonical header unchanged.

Completed locally: first batch 27 units (657bbcbcc0c), second batch16 units. Only private template definitions were replaced by canonical includes through header_adopt_lane.py adopt; no method bodies, shared headers or ledgers were edited. Both batches passed normal rows, their own positive link_check verdicts and accept. There were no StringBase queue rows to retire. The source cleanup does not clear the S4 element/provider identity in LINK-045/LINK-083 or the vtable repairs surveyed in LINK-514: VslotMemberForwarders.cpp and the S4 partition instantiation only lose their unrelated StringBase facade.

Second-batch validation: 86/86 functions, 0 data rows; all16 ownLINKS 3678->3678 bytes, 138 dependency entries. All30 trial units were byte-verified and refreshed together after restoring rejected files, so retained consumers do not rely on stale trial objects. Ordinary published-index prediction only, no fresh global census or real-image/runtime claim.

Remaining (unchanged originals): first batch refused GapJmpThunksSeat8.cpp (conservative surgery guard), Rva0033B830Ctor.cpp (private base constructor), Rva0045EF90Dtor.cpp (AsciiString alias conflict). Second batch refuses:

- FAIL Code/GameEngine/Source/Common/Rva005F91C6Assign.cpp: Code\GameEngine\Source\Common\Rva005F91C6Assign.cpp(13) : error C2371: 'UnicodeString' : redefinition; different basic types
- FAIL Code/GameEngine/Source/Common/WaterDrawFXShaderParameterSourceNamespace.cpp: Code\GameEngine\Source\Common\WaterDrawFXShaderParameterSourceNamespace.cpp(15) : error C2371: 'AsciiString' : redefinition; different basic types
- FAIL Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldObjectParser.cpp: Data rows: FAIL 1 of 1
- FAIL Code/GameEngine/Source/GameClient/System/FXParticleSystem/LifeEventModuleInfoCopyCtorThunk.cpp: Code\GameEngine\Source\GameClient\System\FXParticleSystem\LifeEventModuleInfoCopyCtorThunk.cpp(12) : error C2248: 'StringBase<T>::StringBase' : cannot access private member declared in class 'StringBa
- FAIL Code/GameEngine/Source/GameClient/System/FXParticleSystem/TerrainCollisionModuleInfoCopyCtorThunk.cpp: Code\GameEngine\Source\GameClient\System\FXParticleSystem\TerrainCollisionModuleInfoCopyCtorThunk.cpp(12) : error C2248: 'StringBase<T>::StringBase' : cannot access private member declared in class 'S
- FAIL Code/GameEngine/Source/GameLogic/AI/ai.cpp: no private view found
- FAIL Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainModuleDataDtor.cpp: Code\GameEngine\Source\GameLogic\Object\Contain\GarrisonContainModuleDataDtor.cpp(27) : error C2248: 'StringBase<T>::~StringBase' : cannot access private member declared in class 'StringBase<T>'
- FAIL Code/GameEngine/Source/GameLogic/Object/Update/SpellRechargeModifierUpgradeModuleDataDtor.cpp: Code\GameEngine\Source\GameLogic\Object\Update\SpellRechargeModifierUpgradeModuleDataDtor.cpp(57) : error C2248: 'StringBase<T>::~StringBase' : cannot access private member declared in class 'StringBa
- FAIL Code/Libraries/Source/WWVegas/WWLib/Rva001EC311Ctor.cpp: Code\Libraries\Source\WWVegas\WWLib\Rva001EC311Ctor.cpp(38) : error C2248: 'StringBase<T>::__ctor' : cannot access private member declared in class 'StringBase<T>'
- FAIL Code/Libraries/Source/WWVegas/WWLib/Rva002CFD61Erase.cpp: Code\Libraries\Source\WWVegas\WWLib\Rva002CFD61Erase.cpp(9) : error C2371: 'AsciiString' : redefinition; different basic types

Adoption byte-passed but own link regressed; restored and excluded:

- Code/GameEngine/Source/Common/System/Rva0021C459Cleanup.cpp: [['does not link', '94', '0']]
- Code/Libraries/Source/WWVegas/WWLib/stlport_rva005ec594_clear.cpp: [['does not link', '55', '0']]

Next steps: establish the real owning wrapper type before replacing aliases/direct StringBase construction; resolve the two missing/selected-provider failures against current cohort objects before retrying. Do not make the base constructor/destructor public, edit the shared header, bypass surgery checks, or add pins as a workaround. Full logs, byte/dependency manifests and restored-cohort receipts are in the slotnames stringbase-batch1-results and stringbase-batch2-results packets. Other StringBase inline/access/provider groups remain outside these declaration-only batches.

## Shadow diagnostics carried forward

The second-batch commit hook reports one new shadow code-identity binding finding: `MilesAudioManagerGetEnvironmentName.cpp`, compiler funclet `_$E2`, retail row 0x007B6B37, marked wrong. It also reports shadow data-name findings for `?g_str009E0878@@3V?$StringBase@D@@A` in ScriptEngineRva00357AF8.cpp and the function-local `s_names` at 0x009E1E54 in MilesAudioManagerGetEnvironmentName.cpp. These are not adjudicated as repairs or cleared by the source cleanup. All93 row bytes and all9 EH rows verify exactly, and all18 own link verdicts pass; the ordinary gates remain the stated admission scope. Independent review must inspect the shadow reports rather than infer whole-object, data-identity or runtime equivalence from these checks. Full output: slotnames/stringbase-batch2-commit.log.

Final disposition: both ScriptEngineRva00357AF8.cpp and MilesAudioManagerGetEnvironmentName.cpp are excluded from the second batch after those shadow diagnostics. Their original sources were restored; the complete trial cohort was rebuilt and refreshed, and the retained16 passed rows, their own LINKS and accept again. The intermediate18-unit shadow observations are carried here as reasons for exclusion, not as admitted diagnostics.
