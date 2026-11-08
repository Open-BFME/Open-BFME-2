# ChangeStanceGroupOrder native table, 2026-11-08

Inspected base: `c82864e07f`. Related obstacles: LINK-625/P42 and LINK-619.
Scope: ChangeStanceGroupOrder.cpp and GroupOrderDerivedDtors.cpp, including
their existing GarrisonObjectGroupOrder and AttackObjectGroupOrder providers.

Both ChangeStance C++ table emitters previously produced 15 slots against
retail's 14. The constructor TU also defined an independent, correct 14-slot
hand-built array named `g_0086A36C`. Keeping that array did not repair the
compiler-generated class table.

The two emitters now share a temporary, TU-scoped ABI view. It preserves the
existing rowed names, the base's 0x18-byte storage and the leaf's 0x1C-byte
storage. It is not a recovered original hierarchy or a canonical-header
adoption. The canonical Snapshot/GroupOrder recovery remains open. No donor
source path, complete argument domain or new original method name is claimed.

Four complete trivial leaf bodies are independently byte-verified and admitted
through add_match.py's ICF-owner route: true/RET4 (5 bytes), empty/RET4
(3 bytes), incoming-word passthrough/RET4 (7 bytes), and false/RET8 (5 bytes).
Existing GroupOrder signatures are retained; the passthrough does not establish
its argument's semantic role. These rows claim existing folded ranges, not
20 newly covered retail bytes. They supply the exact four previously missing
slot targets without pins or aliases.

The data-row ownership transfer changes only the name/evidence/model of the
existing 56-byte range at RVA 0x0086A36C. Address, extent, source and matched
status are preserved. The old name is tombstoned with that replacement reason;
the hand-built array and its declaration block are removed. No other current
source uses the old name. Historical data_ledger/queue records remain untouched.

Verification:

- Normal `./build.sh` on both sources: 15/15 code rows and the one 56-byte data
  row pass. Both frozen-file checks pass; there are no EH rows in this scope.
- Each current compiler table has its own read-only 56-byte COMDAT section,
  exactly 14 relocations, and every slot independently resolves to its retail
  target, including the weak deleting-destructor default.
- Public `data_rows.verify_row` verifies the complete compiler-table row:
  56 bytes equal to retail, all 14 relocation targets correct, structural
  COMDAT size 56. `final-proof.json` records the result and both slot lists.
- Private candidates verified 9/9 and 6/6 rows before application. Compared
  with the original objects, only the target table changes, four leaf COMDAT
  bodies are added, and no code provider is removed. Garrison/Attack facts are
  unchanged. `initial-provider-comparison.json` preserves that comparison;
  its size proof has been corrected to the structural vftable proof.
- Final normal/private external COMDAT facts agree exactly (15 and 17
  sections respectively). Removing the unrelated strong manual data definition
  leaves those COMDAT facts unchanged.
- Strict `link_check.py --prepare-current` provides reusable receipts for the
  two explicit sources. Paired current-object preview against census index
  eba83a23be (2026-11-08 14:08) reports 2/2 LINKS, 317 to 337 authored bytes.
  That 20-byte increase is the four ICF rows, not unique coverage or a census
  headline change.

No source path moves, gate/baseline edits, new hatches or generated-source
edits. Full-link selection, bridge retirement, canonical shared hierarchy and
actual-image/runtime verification remain pending. A matching table and a
two-object preview do not prove the game runs.
