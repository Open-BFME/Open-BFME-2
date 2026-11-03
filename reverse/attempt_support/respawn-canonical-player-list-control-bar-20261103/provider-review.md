# Canonical PlayerList / ControlBar operation review

**Result: no provider-loss or binding issue found in the focused current cohort.** The `both-operations` private variant passes22/22; the main normal build log likewise reports22/22 with literal/float/import checks. No edit, compile, claim, network or push was performed by this review.

## Current witnesses for both new inline helpers

Re-read actual normal COFF bytes/properties and checked source MD5, object MD5 and **every recorded header digest**, rather than trusting the older index or a payload-equal witness list alone. Full details: `current-helper-receipts.json`.

| New helper | Fully current outside source/object witness | Complete body / properties |
|---|---|---|
| `?getLocalPlayer@PlayerList@@QAEPAVPlayer@@XZ` | Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBuffer.cpp |4B `8b4110c3`, no relocations; EXTERNAL `.text`, ANY COMDAT2; payload/properties equal candidate |
| `?markUIDirty@ControlBar@@QAEXXZ` | Code/GameEngine/Source/GameLogic/Object/Update/MonitorConditionUpdateUpdate.cpp |5B `c6412801c3`, no relocations; EXTERNAL `.text`, ANY COMDAT2; payload/properties equal candidate |

These witnesses use the actual existing operations: canonical PlayerList.h42 returns m_local at+10 and ControlBar.h203 stores true at+28. The source-facing change uses those public APIs; no pin, alias, new row or duplicate bounded class is needed.

Some earlier listed witnesses are **not current**: GameClientDrawableTOC source/InGameUI receipt, StealthUpdateLogic source/AIUpdate receipt, and GettingBuilt/RiderChange header receipts differ. They establish byte copies only and are deliberately not the freshness proof above.

## Removed const getter and route/property result

`?getLocalPlayer@PlayerList@@QBEPAVPlayer@@XZ` is the only removed definition. `const-getter-review.md/.json` independently checks its three saved-index touches against current actual objects:

* Object.cpp and GameLogicInit.cpp still define exactly4B `8b4110c3`, no relocations. Both objects have current source/object/header receipts (97/126 dependencies).
* Neither outside object has undefined/weak/alias/INCLUDE references or runtime code/data incoming relocations to the const symbol. Only the getter's own debug metadata names it.
* The current seed object has no old const definition/reference. Its receipt is current. Saved index23b85ddde5/Nov3 18:36 orders Object935, GameLogicInit1376, seed12921, all with the same symbol digest. Removing the later seed copy leaves the earlier provider and body intact.

Recomputed control-versus-both-operations properties/routes: **all shared ordinary provider properties are unchanged; undefined, weak, alternate and INCLUDE sets are unchanged**. The only route-table change is the defined-name set: remove QBE, add QAE and markUIDirty. The operations proof also reports every existing common payload/relocation identical. Both additions match current outside definitions exactly, including selection/storage properties.

## Cohort protection and limits

The saved index has34 QAE copies and6 markUIDirty copies, with no native-address verdict/selection exception for these symbols. The seed position12921 follows the first existing QAE copy890 and markUIDirty copy9360, so neither addition replaces that first body under the saved order. Their currently read bytes equal the new copies. This is a selected-copy/call-route protection argument for this cohort, not recovery of a distinct retail address or original constness contract.

The old const copy is not a unique required provider; no outside runtime use was found in its complete indexed touch set. This remains bounded by current inspected objects and the saved index; it does not claim a new full-image census/real link or certify every stale outside source. Root's current normal owning-header checks and outgoing provider/consumer gates remain the final publication checks. No paths move in this header-operation change; the separate two-donor publication audit remains applicable unless relevant moves/consumers change.

All tracked reads stopped after the focused review. Scratch reports only were written.
