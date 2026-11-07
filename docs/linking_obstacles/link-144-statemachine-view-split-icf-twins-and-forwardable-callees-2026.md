### LINK-144: StateMachine view split, ICF twins and forwardable callees (2026-10-24 Opus pass)
(Registered as LINK-122 in bc18bc988b, which collided with the census-hygiene LINK-122 below; re_attempts' StateMachine.cpp tu-merge line cites this entry by the old number.)
Status: Mostly cleared; three units open (below). Updated: 2026-10-29; inspected revision: 38dbdee4d7; census 2026-10-29 15:08 at 85f6b7f40c (retail-truth-5).
Census confirmation (2026-10-29, `reverse/link_status.csv` at 85f6b7f40c): linked=yes for DozerAIUpdateCtor.cpp, WorkerAIUpdateCtor.cpp, StrategicHUDBattlePromptMovieClip.cpp, StlportVectorDtorDeferredOwners.cpp, ActiveBodyConstructor.cpp, BackAwayAndCowerStateMachine.cpp (was Rva003444CEStates.cpp; the StateMachine vtable split no longer blocks it) and IntFloatMapSubscript.cpp (repaired by other seats). Still linked=no: CrateCreationEntryList.cpp, AptPlayerTooltipMap.cpp, Rva008312E0StringReplace.cpp (the constructor and /Od-frame leads below stand).
Evidence / affected units: `link_check.py --refresh` over the 543 census-blocked units (index 7e43384268), then per-unit rechecks.
Completed (each verified with `./build.sh` and `link_check.py --refresh`; census confirmation pending):
- 47da7755f1: 0x004D750F is `StateMachine::setGoalObject(const Object *)` (slot 14 of 25 StateMachine vtables), 0x004D7435 its worker `internalSetGoalObject`; rows renamed, the `/alternatename` alias removed. `DozerAIUpdateCtor.cpp` and `WorkerAIUpdateCtor.cpp` LINK (0 -> 12,691 B).
- 5882084a63: `StrategicHUDBattlePromptMovieClip.cpp` forwards both page vectors' `_M_clear` to the shared 4-byte clear worker 0x00577EF1 (0 -> 2,249 B).
- 7506232830: `_Destroy<BfmeAssignRecord104 *>` forwards its loop to `Rva003B8B61Destroy` (0x003B8B61), so `stlport_asciistring_record_bodies.cpp` emits retail's 0x003B8E13 shape; `StlportVectorDtorDeferredOwners.cpp` LINKS (0 -> 145 B).
- 579941b25f: ActiveBody's damage-creation vector copy (call 0x004BF6A1) forwards to the rowed `vector<BfmeE12>::operator=` 0x004BF4CE (0xC stride); the base ctor stays the BfmeE16 row 0x00211E58 retail calls. `ActiveBodyConstructor.cpp` LINKS (0 -> 432 B).
Remaining / next check:
- `Rva003444CEStates.cpp` (184 B) stopped linking with 47da7755f1: its dtor-only StateMachine view must now declare the virtual, so its `??_7BackAwayAndCowerStateMachine` copy (2 slots) differs from `Rva004D759CDerived.cpp`'s (1 slot). `Rva004D759CDerived.cpp` emits 16 StateMachine-derived vtables, each also emitted by 1-2 other units; the fix is one StateMachine slot list (`reference/shims/bfme2_statemachine/StateMachineView.h`) adopted by all of them.
- `IntFloatMapSubscript.cpp` (698 B): retail keeps two unfolded copies of `map<int,float>`'s plain `insert_unique` (rowed here at 0x005DFD8D; the hinted insert 0x003590C9 calls the twin 0x005C6AFD, rowed as `map<int,Rva005C6AFDElement>::insert_unique`). One name cannot serve both; `_M_create_node` alone is forwardable (0x005C6728).
- Constructor wall: a callee ctor folded onto another element type's row cannot be forwarded without changing the rowed caller (`CrateCreationEntryList.cpp`: `_List_base<crateCreationEntry>` ctor -> 0x00288978 rowed for BfmePod264, used by 5 other units; `AptPlayerTooltipMap.cpp`: hashtable ctor -> the Rva002249ADElement row).
- AptPlayer recheck (2026-10-30, `c9c0fea9be`, ordinary index `85f6b7f40c`): all nine rows remain exact; preview retains U1/C2/S1 and zero linked bytes. The unresolved `Rva00224C95` destructor, hashtable constructor and AptPlayer table still need the heterogeneous member types, existing destructor owner and complete table contract recorded above. No source changed; [selection evidence](../../reverse/attempt_support/module-header-ms-headers-20261030-codexb5.md).
- `Rva008312E0StringReplace.cpp`: the inline `erase`/`replaceBase` bodies reserve retail's /Od frame (0x9C; forwarders shrink it to 0x54), so they cannot become forwarders.
Clearance: the four completed units, per-unit previews only.
Census confirmation: awaiting.
- 2026-11-03 prerequisite: StateMachineDtor.cpp and StateMachineXfer.cpp adopt canonical State; 7/7 rows exact, EH exact, preview preserves 706/706 B; private StateMachine/map-lifetime and seed transition declarations still block consolidation. [Evidence](../../reverse/attempt_support/statemachine-state-adoption-20261103-codexb4.md).
- 2026-11-05: five more StateMachine consumers adopt the canonical header (including BackAwayAndCower); five header-debt rows retired, 23/23 rows exact and preview preserves 4,558 B. AttackPosition adoption restored after link loss; compare its derived vtable/provider bindings before retrying. Wider reconciliation remains open. [Evidence](../../reverse/attempt_support/statemachine-cohort-adoption-20261105-codexb3.md).
- 2026-11-05: AIStateMachine_setTemporaryState.cpp and VslotSmallBodiesAJ.cpp adopt canonical StateMachine; the former also adopts State/AIStateMachine. Four header debts retired, 83/83 rows exact, preview preserves 1,219 B and COFF definitions/references/aliases are unchanged. [Evidence](../../reverse/attempt_support/statemachine-common-adoption-20261105-codexb.md).
- 2026-11-07, State transition prerequisite: the canonical State header now
  declares the seed's three rowed transition helpers and types +0x10 as the
  condition pointer and +0x14 as its count (legacy field spelling retained).
  The seed adopts it, retiring one State header debt. Normal 23/23 rows,
  three data rows and 2 EXACT EH graphs pass across seed/constructor; both
  current previews retain 903 authored bytes. No external definition changes;
  67 simple code-section comparisons and both vtable definitions are equal.
  The merge dry-run now accepts StateCtor.cpp (previously no donors), with
  its 23-row composition passing the link guard. Applying that merge remains
  separate. The other four donors still require Machine/map/CRT/enum
  reconciliation; seven mixed files stay. No image/runtime clearance.
  [Proof and remaining boundaries](../../reverse/attempt_support/state-transition-canonical-20261107/README.md).
- Same pass, approved constructor merge: tu_skeleton.py absorbs StateCtor.cpp
  into the retail StateMachine TU, transferring six function rows, three
  verified data rows and five data-ledger owners. Normal 23/23 and 2 EXACT EH
  graphs pass; the merged preview conserves the pair's 903 authored bytes.
  One source file disappears. Fresh destination State acceptance and MS-header
  scan pass; current Machine/map debt remains. The batch path-consumer audit
  finds historical references only. Existing vtable placeholders and all four
  remaining donor boundaries are retained; actual image/census confirmation
  stays open. [Audit](../../reverse/attempt_support/state-transition-canonical-20261107/consolidation-audit.md).
