### LINK-089: SupplyTruckAIUpdateCtor's private interface slots disagree with native callbacks
Status: Blocked on interface and provider-name reconciliation. Updated: 2026-10-26; inspected revision: 2a45addda1806342ac5c52757f63be902dcd428e.
Evidence / affected units: `SupplyTruckAIUpdateCtor.cpp` remains U9 against index `d1f046749a`. Its constructor and destructor anchor the interface table at RVA 0x00852F38. Projecting the current private declaration onto that native table maps its gainOneBox slot to the rowed loseOneBox worker at 0x004A6E8E and its getActionDelayForDock slot to the unrelated byte setter at 0x00210CD3. The SupplyTruckStateMachine owner already records later native interface offsets for the force-state accessors. Equal calling-sequence sizes do not establish the current slot names or signatures.
Completed: every assigned row passes the combined byte gate, and the current native row providers were included in the paired preview. No source or ledger change was attempted. `build/c136-logic/native-references.log` labels table projections separately from direct calls and lists the exact row names and homes; `weather-native.log` also preserves the raw native table bytes.
Remaining / next check: recover the complete interface order and argument types, then reconcile the existing rowed workers and folded getters under supported real names. Do not bind these current slots to address placeholders or propose pins from the mismatched projection alone.
Clearance: pending.
Census confirmation: pending; no gain claimed.

**Slot-count follow-up (2026-10-30, inspected `449de049fd`):** the native
interface table at RVA 0x00852EE8 holds 20 `__purecall` slots and the derived
table at 0x00852F38 holds 20 workers (slot 20, `AIUpdateInterface::onCollide`
0x0026DF0D, starts the next table), so BFME 2's SupplyTruckAIInterface has 20
virtuals against ZH's 13. Target facts: slot 2 is the rowed 0x004A6E8E
loseOneBox worker and slot 3 the 0x004A6EC6 gainOneBox(Int) worker; slot 19 is
the 0x004A6F0A getActionDelayForDock(Object*) row. Consumer views (private,
not yet target-proven) agree on getNumberBoxes slot 0, isAvailableForSupplying
4, isCurrentlyFerryingSupplies 5, set/isForcedIntoWantingState 11/12,
set/isForcedIntoBusyState 13/14 and getPreferredDockID 15
(`SupplyTruckAIUpdate.cpp`, `SupplyTruckStateMachineOnEnter.cpp`,
`AIPlayerQueueSupplyTruck.cpp`, `SupplyCenterProductionExitUpdate.cpp`). Slots
1, 6-10 and 16-18 have no supported names (float getters at 7 and 10 make one
of them getWarehouseScanDistance only by ZH analogy). The ctor's 13-slot
declaration is therefore wrong in count as well as order; reconciling it needs
names for the BFME 2-only slots and fold admissions for the ICF-shared slot
bodies (0, 4, 12, 15, 17, 18). No source or ledger change made.
