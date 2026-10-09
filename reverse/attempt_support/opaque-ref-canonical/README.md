# Bounded atomic reference-protocol adoption

Comparison inputs: BFME2 `ef1ad21cb8a0e622343ccae17ff0b18ef2fc3afe`, committed and actual BFME1 `f98983a7d3bb405f1a4ba94bb6a2a168062a819d`.

## Target facts and retained uncertainty

The neutral `OpaqueRefCounted` spelling identifies an already recovered native protocol, not an established original class name. Native complete entries 0x50EC8/11, 0x50ED3/39 and 0x50EFA/31 all pass receiver+4 to the actual `InterlockedIncrement` or `InterlockedDecrement` imports (VA BBA214/BBA21C). On a nonpositive result, Release_Ref loads the receiver's vptr, invokes slot 0 with flags zero, then calls scalar operator delete at RVA 2FD60. These target accesses establish the virtual-destruction protocol and a signed, four-byte Windows LONG at offset 4. They do not establish the original complete-object allocation size, payload, subclass identities or original member names.

The read-only then written `class_contract.py --class OpaqueRefCounted --jobs 4` contract reports class-key by bytes and slot 0 by bytes. Its eight-byte size and absence of bases are majority inferences; its field merger retains the vptr but omits the atomic count. The fixed header therefore retains the independently proven count rather than generating an incomplete declaration from the majority record. The JSON is the tool's unaltered output. Eight bytes describe the evidenced protocol prefix, not a claimed complete original object.

The two pool-pointer members of BfmeStringTailRecord144 are independently supported by its native constructor/copy/destructor chain. For the holder member, raw constructor 51931/31, copy constructor 51950/33, assignment 51971/58 and raw assignment 53D26/41 increment holder+8C. Assignment 51971 and clear 519BD/25 release holder+88 through the actual 50ED3 entry. Together these accesses place the same four-byte count at protocol receiver+4; replacing four raw offset casts with `m_ref.Add_Ref()` preserves every instruction and import relocation. The wrapper's record stride 90 and native layout proof are unchanged. Holder payload and layout beyond this referenced protocol remain unknown.

## Reference repair reviewed

The actual f989 BFME1 `game/Libraries/Source/WWVegas/WWLib/refcount.h` uses non-atomic NumRefs increments/decrements and a virtual Delete_This protocol. It is inapplicable as-is to these atomic target entries and does not establish their original name. No BFME1 OpaqueRefOwnership or StringTailRecord144 unit was found at this revision. Target evidence, rather than the donor spelling, supports this repair.

## Bounded adoption and debt

`header_adopt_lane.py order` was read first. The actual provider was selected by the supported one-unit fixed-header sample (seed 38); `run --header ... --sample 1 --seed 38 --apply` passed and registered the header. The two specifically evidenced consumers were then adopted and all three passed the lane's explicit `accept` gate:

- OpaqueRefOwnership.cpp: 5 rows / 177 bytes.
- StlportVectorOverflowBfmeStringTailRecord144.cpp: 3 rows / 266 bytes.
- stlport_stringtailrecord144_dtor.cpp: 9 rows / 621 bytes.

The original contract census covered 94 private OpaqueRefCounted views. Removing the actual provider and the destructor's empty view leaves 92 private views, recorded by the lane's `write_queue` as unattempted bounded work. The vector's former PoolMember view was outside that census. This repair does not assert compatibility of those other units.

The provider's old PoolMember alternatename and pin are retained because Rva004E18A2Dtor.cpp, GenericObjectCreationNuggetDtor.cpp and ProductionUpdateModuleDataDtor.cpp still call that spelling. Removing the vector's use alone does not justify deleting the remaining binding. No new alias, pin, vftable anchor, compiler override or baseline line is introduced.

## Verification

All 17 complete rows / 1,064 existing C++ bytes passed the per-owner gates. The full gate and current provider/consumer linking refresh are recorded below only after their original processes reach terminal. No new recovery bytes are credited to this repair.

Full repaired-header gate (original session 39997) and unchanged-HEAD control (original 72457) both ended with exit 1 at the same frozen revision and BFME1 pointer. Both passed 73,305/73,305 bodies, STLport 68 constructor folds, 26,956 strings plus 1,553 empty-string references, 4,842 float literals, 4,811 imports, pin consistency, module registry, all source claims and the no-op patch. Their sole red is the identical set of three inherited DIR32 conflicts:

- `?TheTerrainVisual@@3PAVTerrainVisual@@A: bases ['0xdfdc8c', '0xdff080']`
- `?_PresetAlphaShader@ShaderClass@@2V1@A: bases ['0xdb44b8', '0xdb6234']`
- `?s_valueBuffers@PeerThreadClass@@0PAY0BE@DA: bases ['0xe025e0', '0xe0266c']`

The existing dir32.py diagnostic traces these to ColdGlobalDwordGetters/ScriptGlue/GameEngineInit/GameLogicSetGamePaused, WaterRenderObjInit versus four existing alpha-shader consumers, and PeerThreadPushStatsBfme versus PeerThread. None of the three adopted objects touches these symbols. No full-green receipt is claimed. Both complete log SHA256 values are retained below; the original ignored logs remain available in build/reference975/opaque-ref-canonical.

- `full.log`: `6d1b2cdd14338d4f40c9c7e83c7e1783953fb7b6e23055619d9a3f544a4585a4`
- `old-header-full.log`: `ecc749c7549196255346fa568fe1f0627c381c0e4f6371fad93df96d8d5d8b79`

Current link_check --refresh (original 82130, terminal exit 1) retains exactly the pre-existing blockers: vector has two wrong Destroy COMDATs plus their two wrong-selected findings; destructor has the existing BfmePoolRef10::operator= duplicate. The actual OpaqueRefOwnership provider remains linking (177 bytes). No additional linked-byte gain or new blocker is claimed. The index dates from 2026-10-08 21:23 (commit ddae8bfdca); its historical destructor byte count is 600 versus the current verified row sum 621, so it is not a fresh whole-census byte-total claim.

Normal pre-commit (original 43172) widened the STLport header change to its mandatory full gate and refused the same three inherited DIR32 conflicts. HEAD remained ef1ad21. The exact implementation proposal is banked in proposal.patch with candidate hashes in receipt.json; all seven implementation paths were restored, so this evidence commit changes no game source, canonical registry or active contract. Code-identity shadow also reported the same existing BfmePoolRef10 assignment duplicate; data shadow found zero issues. No hook was bypassed and no baseline changed.
