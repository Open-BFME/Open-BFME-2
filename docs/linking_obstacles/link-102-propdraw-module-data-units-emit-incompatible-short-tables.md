### LINK-102: PropDraw module-data units emit incompatible short tables

**2026-10-30 Snapshot identity follow-up:** remove the TU-local macro in
`W3DPropDraw.cpp` that emitted Snapshot lifetime bodies under the unrelated
post-effect base name. Its nine-byte constructor conflicted with the native
13-byte `BfmeModuleDataSnapshotBase` owner at 0x0011646E. The native owner and
LookupTablePostEffect's 22-byte constructor now both preview LINKS, while the
two canonical Snapshot witnesses retain LINKS. All 17 cohort rows and one data
row pass strict preparation; all 64 external code/data definitions and
relocations are conserved after correcting only the false base spelling.
The five-unit preview against `ccafe54d1d` changes 154 -> 189 authored bytes;
this is not a census gain. W3DPropDraw's remaining DrawModule table and deleting
destructor blockers, and the full module-data table prerequisites below,
remain open. [Provider/consumer scope and proof](../../reverse/attempt_support/w3dprop-snapshot-provider-link-20261030/README.md).

The landed two-source batch audit at `c122e7b157` remains INCONCLUSIVE on the
older index and the missing current affected-consumer receipt for
`Common/0CreateAHeroManager21FE49.cpp`. Carry the provider/caller and wider
consumer scope into the next scheduled census. The identity check also reports
the retargeted `ModuleData` destructor as a divergent definition in shadow
mode; no baseline is expanded or retired. Its raw code is unchanged, and the
only changed relocation names the canonical Snapshot table already verified
by the owned native destructor row. This does not clear the full ModuleData
contract or broader consumer selection.

**2026-11-01 base identity follow-up (halilkkaya-tool-o4):** the post-effect
base now has one name. `rename.py class --fold BfmeModuleDataSnapshotBase
--into Rva001164B6` (bfa1fe66bf; retail vftable 0x00BCFB24 is the ctor's only
+0 install and is named `??_7Rva001164B6@@6B@`) renamed the 0x0011646E ctor
row to `??0Rva001164B6@@QAE@XZ` and dropped the alias pin
`??1BfmeModuleDataSnapshotBase@@UAE@XZ`; 4aff2b39fb put the seed and both
LookupTablePostEffect donors on one view (12/12 exact). Joint link_check of the
provider, the three units, InlineDtorDeletingDtorsC01.cpp and
Rva00101FD8Create.cpp: 6 of 6 LINKS, 1,621 -> 1,621 B. Remaining prerequisite
for the `LookupTablePostEffect.cpp` merge: the census index (39dfbbdb50) still
records the provider defining the pre-fold `??0BfmeModuleDataSnapshotBase`, so
tu_skeleton's link guard reads `unresolved ??0Rva001164B6@@QAE@XZ` for the
merged object (its `moved_provider` exemption covers merged-away providers,
not renamed ones). Re-run `tu_skeleton.py --merge` after the next scheduled
census indexes the renamed provider. Census confirmation: pending.

**2026-11-12 post-effect base table.** The destructor emitter and derived
unit now share the `Rva001164B6` declaration. The real destructor emits
the five-slot table at retail RVA `0x007CFB24`, so the synthetic
emission constructor is removed. The 13-byte constructor still installs
the same external table. A C++ constructor trial emitted a divergent
deleting destructor, and sharing the inline base destructor changed the
derived destructor's retail bytes and unwind. Both trials were reverted.
The three units verify 64 code rows, two data rows and two EH graphs.
With the factory included, all four retain 1,658 linked bytes on index
`80569f4278`. Bridge retirement awaits a real-link receipt. The derived
table at `0x007CFAC8` still needs its slot 2 provider.

Status: Blocked on shared ModuleData interface and slot-owner reconciliation. Updated: 2026-10-27; inspected revision: 97c23353111e60304b56434c02d20bee3465d83f.
Evidence / affected units: W3DPropDrawModuleDataCtor.cpp emits a four-slot Snapshot table while W3DPropDraw.cpp emits a nine-slot Zero Hour ModuleData table. The constructor's sole ordinary-preview blocker is `??_7W3DPropDrawModuleData@@6B@`. Retail at RVA 0x007CD420 has 31 function pointers; the next word at 0x007CD49C begins the DistanceFog string, so the data ledger's 136-byte span includes that following literal. Native slot 14 reaches 0x000CED14, already rowed under W3DTreeDrawModuleData; slot 19 reaches the return-this body at 0x0047A6A9. The existing Common/BfmeModuleData.h models 31 generic slots, while the update_modules_bfme2/Common/Module.h view used by the destructor still models the short interface.
Completed: inspected both emitted tables, native slots, existing row owners and the shared headers. Both constructor-unit rows are exact. Current paired preview retains the constructor L1 and the destructor unit's independent ModuleData/DrawModule blockers. No source trial or shared-header edit is retained.
Remaining / next check: reconcile the shared ModuleData slot names and native overrides, then adopt both units together while keeping their constructor, complete destructor, deleting destructor and EH rows exact. Making both units emit the same short table would retain a non-retail interface. Shared-header edits and row renames are outside this worker's allowed scope.
Clearance: pending.
Census confirmation: not claimed.
