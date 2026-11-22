# Item012: SidesListNotifier TU approval — blocked, no source trial

Inspected current HEAD e587ad3656865550008ac64cf8de1919a9710d53, matching Root's claim snapshot. **Sicher:** the native pass criterion is not met: a fresh in-memory map still proposes all4 rows; the normal `tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Map/SidesListNotifier.cpp` exits0 but reports **0 approved rows,0 donors**. Exit0 merely completes inspection, not the queued approval. No compiler test or merge was started.

## Whole served family

The4 proposed primary rows remain N-only/noncontiguous:

| RVA | Bytes | Body | Current source |
|---|---:|---|---|
|0032AE25|109|SidesListNotifier::dispatch|SidesListNotifierDispatch.cpp|
|0032AE92|112|SidesListNotifier::dispatchIndexed|SidesListNotifierDispatch.cpp|
|0032B522|30|SidesListNotifier::post(callback,owner)|SidesList_sidesInfo.cpp|
|0032B540|37|SidesListNotifier::post(callback,owner,index)|SidesList_sidesInfo.cpp|

Both entire source files were read. Dispatch has4 ledger rows/239B including its real10B handler77B5BF and8B unwind77B5B7; sidesInfo has34 rows/1817B, including existing SidesList/SidesInfo methods and their compiler companions. Current `find_declared_unmatched.py` says all defined functions already matched. No extra unrowed body was found to recover or use as a filename anchor.

The existing canonical notifier is16B, nonvirtual, based on Rva00330757Member's begin/end/storage words and index+0C. Post records are8/12B; dispatch loads the listener into ECX and uses the callback with owner/(owner,index). The LatchRestore table belongs to a stack guard, not the notifier. Both served files already include the canonical header, so there is no missing notifier-header adoption to fix. Listener original identity remains expressly unknown. No class/layout/header change is proposed.

History confirms original dispatch recovery e174719c75, canonical registration5e2341c4e4 and adoption64b84a8c13. Prior blocked dispatch codegen trials were subsequently landed; they are not current work. LINK-199's constructor-lifetime obstacle is already recorded cleared, and the Nov4/Nov5 support documents explain the accepted adoption; do not retry those old failures.

## Why approval is blocked

A **fresh native `tu_map.current_rows` rebuild with shared picker cache disabled** records18 approved SidesList.cpp rows between the two Notifier pairs. Direct S/Z anchors:32B070(SidesInfo::swap),32B0A9(findSideInfo),32B13F(findSkirmishSideInfo),32B1E1(isPlayerDefaultTeam),32B2A5(validateAllyEnemyList). Current promoted E/T rows fill the remaining original SidesList.cpp interval, including32AF02,32B389 and32B3EB. Exact18-row matrix is in CURRENT-MAP-AND-PACKET.json. It is not legitimate to rename those real anchored owners merely to free the Notifier span.

The native naming/consolidation report completed in isolated `build/consolidation/agent-thing-item012-20261121`; its `--check` passes input/output currency. Its committed-map annotations correctly say STALE; the fresh native rebuild above is the authority, not those stale hints. The catalogue contains **SidesList.cpp** from WorldBuilder/ZH/BFME1-EA, and no SidesListNotifier.cpp or SidesListNotifier.h path. The dispatch packet's4 placements are unresolved; the34-row sidesInfo packet is mixed/incomplete, with32 hints to SidesList.cpp and the2 unresolved post bodies. No independent target F or donor-backed Z/S filename anchor was surfaced for a separate Notifier TU.

The name-only path plus runtime relationship suggests these may belong to the surrounding SidesList.cpp object, but that is **a hypothesis, not approval**. Canonical class adoption and byte equality do not establish a separate original TU. Native contiguity gates must remain unchanged. Names/votes, a private compile, an arbitrary path move or splitting the mixed source cannot fix this missing evidence.

## Scope and next condition

No additional production scope or compilation is justified from these observations; Root's current destination-file claim is sufficient to record the blocker. Before any future independently justified change, minimally reserve both current source file paths above, class: SidesListNotifier and RVAs32AE25,32AE92,32B522,32B540, plus the dispatch companions77B5B7/77B5BF if moved. Existing member-pointer post alias at32B522 in SidesListCtor.cpp and all canonical header consumers must remain intact; a real shared-header/name change would require its own larger scope. No such change is requested here.

Reopen only with independently recheckable original identity/TU or legitimate existing placement evidence that makes the normal fresh-map plan approve the4 rows. Otherwise record the concrete N-only/noncontiguous18-interleaver blocker and release through Root. No task credit, new body credit, byte gain or runtime improvement is claimed.

Only private diagnostic/report outputs were written. No compile, production/tool/ledger/cache mutation, Git mutation, vote, claim action or new agent.
