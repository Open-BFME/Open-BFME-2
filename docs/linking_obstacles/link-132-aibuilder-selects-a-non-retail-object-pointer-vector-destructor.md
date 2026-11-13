### LINK-132: AIBuilder selects a non-retail Object-pointer vector destructor

Resolved by the link-order rule (2026-10-29): see the census confirmation under the first
LINK-132 entry; the AIBuilder trials below were not needed.

Status: Blocked on the common selected-provider repair; bounded Squad copy cleanup verified. Updated: 2026-10-28; inspected revision: `ee6402fcd2cc9839702b7ac7f40f1422103f296e`; ordinary-preview index: `d92e7e6635` (2026-10-28 15:58 UTC, retail-truth-4).

Evidence / affected units: the Object-pointer vector destructor, `push_back` and true-type `_M_insert_overflow` in `SquadGetAllObjectsAndRemoveDead.cpp`, `HordeContainRva00475F61.cpp`, `SiegeDeployHordeInitiate.cpp`, `SplitHordeSpecialPower_doSpecialPower.cpp`, `ScriptActions_doTeamPartialUseCommandButton.cpp`, `AIBuilder.cpp`, `AIRva005D8B0BCheck.cpp`, `AITactic.cpp`, `AIRoamingDefenseTacticRoam.cpp`, `AIStructureCreepTactic.cpp`, `AITeamBuilder_checkIdleTeams.cpp` and `GameLogicDestructor.cpp`. Current providers and consumers were checked together against the published index.

Completed: Squad declares growth without a body and explicitly instantiates its existing rowed `size()` member at 0x00597612. Its emitted `push_back` changes from the wrong 49-byte digest `79c379741ca1` to the retail 58-byte digest `65a7b42b7239`, matching `StlportVectorPushBackSiblings.cpp` at 0x001F211B. Its wrong 140-byte growth copy disappears; the growth call retains the real specialization name rowed in `StlportVectorObjectPtrInsertOverflow.cpp` at 0x001F2155 (147 bytes), although the preview still selects AIBuilder's wrong copy. All three Squad rows remain exact. No other source edit is retained.

Verification: final builds pass all 165 rows across the twelve assigned units. Frozen-file, EH and ordinary shadow data checks pass for each source; data checks report no findings. CSV and pin-consistency checks pass. The complete ordinary preview covers 29 units, including every indexed consumer blocked by these names, the supplied retail providers and samples, and source files spelling the decorated names. It preserves the existing LINKS result for `Rva001E7270Ctor.cpp`, introduces no blocker and leaves all twelve assigned units blocked. Squad retains both selected-copy blockers (`push_back` and growth); this is copy cleanup, with no linking or census gain.

Rejected and reversed: AIBuilder's plain, forceinline and late extern destructor instantiations change normal cleanup (28/29 rows). Import-inline destruction with `throw()` preserves the parent but loses unwind 0x007928AC (28/29). An inline destructor specialization with extern instantiation, and an extern class instantiation, preserve 29/29 rows but retain the wrong copies. Declaration-only append/growth trials in HordeContain, ScriptActions, RoamingDefense and StructureCreep change matched parents or their unwind rows. AITeamBuilder's growth declaration alone is redundant because its later growth definition remains visible; removing that definition changes `checkIdleTeams` (2/3), so both trials are reversed and that source equals HEAD exactly. Passing parent bytes alone did not establish a corrected COMDAT.

Remaining / next check: AIBuilder still supplies the first indexed copies at position 1975: destructor 14 bytes, append 49 bytes and growth 140 bytes, all wrong. Correct later providers already exist, including the five-byte destructor at 0x001F22A3 in the GenericObjectCreationNugget providers. Preserve checkForNewUpgrades' cached start pointer and normal inline free together with the real destructor jump from unwind 0x007928AC before retrying suppression. No missing match, pin, rename or shared-header change is identified. Census confirmation is pending; no ordinary-preview linking clearance is claimed.

2026-10-28 AoE target consumer: at `1edb5beac7`, refreshed index
`d92e7e6635`, `AISPecialPowerTargetAoE.cpp` has one preview blocker: the
selected `vector<Object *>::push_back` copy is not retail. Its 19 rows
byte-verify, and the frozen-file check passes. The consumer declares and calls
the provider; the existing AIBuilder operation and context trials above remain
the prerequisite. Recheck this consumer after that provider is reconciled.
No repair or census gain is claimed.
2026-10-28 consumer check at `c6ce78d8c9`, index `d92e7e6635`:
`Object/Rva004E00BA.cpp` remains blocked on selected `vector<Object *>::push_back`
and `_M_insert_overflow` copies (31 authored bytes). Its local overflow copy is
already suppressed. The scoped build verifies its single row; recheck this
consumer after the selected provider is repaired and in the next census. No
linking gain is claimed.

2026-10-28 append/overflow follow-up at `d6a91b0f7e6`, index `41c28839bf`:
the served HordeContain file still has exactly the three AIBuilder-selected
vector-operation blockers. Four new append/overflow/context trials change
the parent; the frame-flag trial also changes other rows. All are reverted. Restored provider
and consumer pass 194/194 rows and 17 EXACT EH graphs; all 89 provider
bindings and external object facts equal control. The next repair must
preserve the parent's loop/cleanup compiler context as well as the native
operations. [Trial boundaries and restoration proof](../../reverse/attempt_support/object-vector-append-context-20261028-bce2/README.md).
No clearance or census gain is claimed.

Earlier destructor trial status: Blocked; five clean-C++ configurations rejected and reverted. Updated: 2026-10-28; inspected revision: `3bb77a8a89`; ordinary-preview index: `54b83e4f69`.

Evidence / affected units: the default SplitHordeSpecialPower::doSpecialPower pick byte-matches but selects AIBuilder.cpp's 14-byte vector destructor before the existing retail five-byte providers. AIBuilder's normal upgrade-check cleanup inlines deallocation while unwind 0x007928AC jumps to the vector destructor. [Target facts, trial configurations and restored checks](../../reverse/attempt_support/object-vector-destructor-selection-20261028-codex3.md).

Completed: tested destructor suppression/declaration and the existing provider's allocator model under both EH configurations. The closest allocator trial makes both standalone destructors retail-correct but changes the parent body. All trials were reverted. Restored AIBuilder, target and existing waypoint provider pass 42/42 rows and seven EXACT EH graphs; AIBuilder's external object facts equal the original. The 18-unit indexed consumer preview remains 0/18 with identical blockers.

Remaining / next check: reconcile allocator temporary lifetime and normal inline cleanup with the out-of-line unwind target together. Repeating destructor-only suppression changes either the parent or its unwind. Other container-operation blockers remain in the cohort; this is not a whole-family clearance. Carry a future verified provider repair and consumers into the normal census.

Earlier destructor trial clearance: none; no source edit retained in that trial, debt retired or new linked bytes claimed. Census confirmation: no new result.


2026-11-13 (merge-climb, partial source consolidation at `bc02ffea95e4`):
The official composer absorbs 1 approved donor(s), including
`Contain/Rva0046DA6BDraw.cpp`, into `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain.cpp`.
`./build.sh` verifies 61/61 matched rows, zero row identities lost; CSV
and frozen-source checks pass. LinkGuard and ProviderGuard admit the composition
with index SHA-256 `1ad77bbd3e53ab682e6717c726c7ad0c13e7109b701732394577d685658b23e3`
(meta `1b7a6e9940`, census `1b7a6e9940`).
This partial merge does not reopen or extend the resolved link-order repair above.
Other unmerged donors retain their view/compile/flag prerequisites. No new
census, full-image link or runtime clearance is claimed.

Horde merge identity limit: the non-converged data check reports a new shadow
`wrong-name` at RVA 0x00A0367C. The compiler-generated local static in
`HordeContain::getModuleNameKey` changes from `$S1` to `$S3`; both cached
objects show STATIC storage, four zero-initialized bytes, identical section
characteristics and no relocations. The named TheHordeContainPoolKey symbol
is unchanged. The data ledger still spells `$S1`; it was not changed or
admitted here. All 61 code rows and the registered data-row byte check pass,
but this is not data-identity or image-placement clearance. Evidence on srv1:
`sweeps/merge-climb/landing-horde/shadow-before-after.json` and
`shadow-guard-proof.json`. The data owner must review/admit a correct mapping
through its normal tool path; do not retire this by editing a baseline.
