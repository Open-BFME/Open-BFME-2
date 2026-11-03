# Clear ordinary-accessor provider audit

Bounded read-only audit, 2026-11-03. Exact names, raw bytes, symbolic
relocations, object hashes, index copies and runtime edges are in
`provider-audit.json`; scratch reader `provider_audit.py` never compiles or
edits an index. Control: `control.obj`; candidate: normal build.obj_path for
Code/Libraries/Source/WWVegas/WWLib/Rva0020EE29Clear.cpp.

46 -> 48 external definitions: exactly four changed providers and two added
accessors. The saved index is 2026-11-02 08:35 / 984a4cdc4d (census 06:54 /
357ce2a88f). **Clear's saved slot is 4782**, later than both accessor holders.
The shared accessor findings agree with the existing Selection packet at
reverse/attempt_support/selection-native-fold-witness-20261103/provider-selection.*.

| Provider | Before -> after | Native/current selection and runtime facts |
|---|---:|---|
| vector<void*>::size() const | added 9B | Native owner remains 25B at 23BC0 in stlport_vector_voidptr.cpp; saved first holder 385 (second 441). Current holder bytes still exactly equal native, digest 062d44dd1806. New 9B Clear copy is selection-2, later at 4782, and locally has no runtime incoming because calls inline. Under this saved order it loses to the native copy; that is permitted by retail-truth-3/4, not a blocker merely because its own bytes differ. |
| vector<void*>::const operator[] | added 12B | No exact-symbol native row/pin. First saved holder 895 GameClientDrawableTOC; candidate and all 26 inspected current indexed copies have the same complete 12B/zero-relocation body, digest 77aefc50cdb3. Clear 4782 is later. This proves existing selected-copy compatibility, not native placement. |
| int/Rva003FD14D* _M_find | 60 -> 47B | Pin and matched caller target 2888D4. Candidate has zero relocations and equals all 47 native bytes, digest 19c037c11543. Saved Clear 4782 was the 60B unknown holder; CreateBeaconObject 4902 already supplied a 47B retail copy. Both current copies now match the native 47B body. Clear becomes the native selected copy in this bounded order. |
| one-argument _M_bkt_num_key | 25 -> 26B | No exact native row/pin. Sole saved definer is Clear. It has no current runtime incoming/root reachability after the new erase inlines the operation. The historical index reference came from old bucket/erase bodies, not a remaining outside caller. Native placement remains unknown. |
| _M_bkt_num(pair const&) | 5 -> 26B | No exact native row/pin. No runtime incoming in current Clear or the only outside indexed touching object, CreateBeaconObject; historical global index also says unreferenced. Candidate exactly equals that object's current 26B body/digest d05efd8b25a3. This is a compatible unused copy in this bounded graph, not a newly verified native body. |
| hashtable::erase(const iterator&) | 103 -> 109B | Sole exact-name indexed provider is Clear, and it is live through the unchanged hash_map erase wrapper. No direct exact-name row/pin exists. The actual native call chain below establishes an existing 86B target under other owner spellings; neither old nor new Clear backend equals it. This remains a live native-provider gap, not a dead spare or a proven newly lost row. |

## Concrete live erase chain

Current matched row `?rva00212655@Rva00DFE1C8Host@@QAEXH@Z` is 212655/102B.
Its native call relocations establish:

- +17 -> 2888D4 (_M_find), agreeing with the existing fold pin and native 47B.
- +92 -> **1E2861**, the hash_map erase wrapper.

The unchanged compiled wrapper is **30B** and matches the complete native
1E2861 sequence outside its single REL32 field. Retail's call at wrapper +22
targets **557BB**. Current ledger independently bounds that target at **86B**:

- the existing address-element owner in
  Code/Libraries/Source/WWVegas/WWLib/StlSweepW5Rva000557BB.cpp;
- the matched typed FX-list map ICF representative in
  Code/GameEngine/Source/GameClient/FXListStoreParse.cpp.

The native backend is 86B, ending in ret4. Control Clear erase is 103B;
candidate is 109B; both differ from this target immediately after the common
first four bytes (first candidate unmasked difference +4). The normal 15-row
gate and no-COMDAT preview therefore must not be described as complete native
provider closure for the erase chain. Conversely, this mismatch already
existed in the control; this audit does not prove a new previously-linked-unit
regression caused by the accessor change. It establishes a concrete existing
follow-up boundary instead of asserting that any changed spare blocks work.
The call chain establishes addresses/behavior, not an original application
type identity or permission to add a new name/pin/row.

## Runtime/reference and measurement limits

Actual ordinary COFF relocations (debug/LNK_REMOVE/LNK_INFO ignored) show two
local incoming edges to _M_find and one to erase. Both are root-reachable;
the matched 212655 row supplies the direct evidence for live use. Both bucket
helpers and both added external accessor copies have zero local runtime
incoming. The only outside saved-index object touching changed map helpers is
CreateBeaconObject; its two runtime edges concern _M_find, not either bucket
helper. Index-bounded nonuse is not proof of retail dead-stripping or global
absence in newer, unindexed sources.

The supplied ordinary preview reports two unresolved names, Rva00219B9E and
rva0021BD22, and no COMDAT finding. That is a bounded preview with the saved
order, not a new census or final whole-game/native-selection proof. Whole
objects may differ from their historical index digests; current holder symbol
bytes/digests were inspected separately. No strict-current receipt is invented.

No Code/tool/ledger edit, compilation, gate, index write, network or claim.
