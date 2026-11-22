# Item009: complete the last Rva0050EA74 source-table slot

**Candidate ready for Root's normal admission; not yet landed or task-complete.**
Source basis is published, quiet HEAD
`bfa69a6bb49d7a1e8e4ef29477ebeee071785da0`. Only the existing shared
`Code/GameEngine/Include/Common/Rva0050EA74.h` changes: replace its unrecovered
slot comment with the existing neutral interface model `virtual void v05() {}`.
No production source, ledger, tool, claim, shared object or index was written by
this worker. The old primary table is20 bytes; retail and the proposed source
table have six slots/24 bytes. No class or method original name is claimed.

## Original receiver and slot evidence

`retail-facts.json` reads the original PE, hashes it, and retains whole bytes,
disassembly and the relevant existing rows. It does not infer a signature from
the new empty body.

- Base constructor RVA0050EA74 installs VA00C6551C at0050EA96. Its real six
  table slots are0050EA58,0050E7BB,0050E7C0,005748AD,005748AD,000B3FD0.
- The independent typed page factory/OnPageLoaded in AptTributePageLoaded.cpp
  constructs StatusPage/TributePage through005103A3/00510B72 and stores their
  counted pointers in the same screen's+27C map.
- Both native constructors call0050EA74 without adjusting the receiver.
 00510B72 then installs VA00C65670. Its six slots are00510CA7,0050E7BB,
 0050E7C0,005748AD,005101C0,005101E2.
- Dispatcher0050F65B loads the pointee from that map node into ECX at0050F66B,
  loads its vptr, and calls[vptr+14] at0050F670 with no explicit argument pushes.
  The caller does not consume the return value. Iterator advancement follows.
- The actual81-byte override005101E2 already has a normal row as the neutral
  void/noarg member of Rva005101C0 in VslotSmallBodiesS.cpp; its field accesses
  agree with the constructed TributePage prefix and child at+24.
- Three existing complete sibling views already declare neutral `void v05()`
  in exactly this sixth position. This preserves their existing C++ model.

**Proof boundary:** receiver/stack width/unused result and table ownership are
original facts. Void/noarg/nonconst is the supported existing neutral C++ model;
an unused result cannot uniquely recover the original C++ return type or
constness. The original class/method name remains unknown. In particular neither
the new inline body nor the identical Coord2D destructor proves that name.
Transport's independent read review found no concrete ABI blocker and records
this same limitation in the preserved `independent-review/` artifact copies.

## Native bytes, types and complete local footprint

`probe.json` retains every strict per-row result; `ROW-SUMMARY.json` is its
compact independently countable summary. Native Verifier's matched set counts
an ICF RVA once, so its console6/7 for the constructor is not a failed row:
all seven actual records are independently checked exact/unmasked/unresolved0.

| Existing scope | Existing strict rows |
|---|---:|
| Two actual shared-header consumers: Ctor + Disp8ByteOneSetters |43|
| Four untouched sibling constructor/callback/destructor files |39|
| Real page dispatcher and factory/OnPageLoaded |21|
| Independent selected Coord2D owner's whole source |44|
| Total existing records verified |147|

Both changed-header consumer variants keep all43 original rows exact. The
proposed `?v05@Rva0050EA74@@UAEXXZ` is the entire1-byte `C3`, with no relocations,
masking or unresolved binding. Original exported `??1Coord2D@@QAE@XZ` at the same
RVA independently emits the same whole1-byte body. All44 owner rows also pass.
The already covered empty primitive has449 existing records; these are not new
roots, tasks or physical coverage. The proposed one-row ICF bank adds0 unique
bytes.

`native-layouts.json` contains normal native compiler CodeView for both real
consumers before/after: Rva0050EA74 remains20 bytes, existing base at0 remains8
bytes, all fields and existing virtual roles are identical. Only vslot5=v05()
is added. No field, base, access-specifier policy, packing or compiler flag is
changed. Existing sibling private views are not silently replaced or called a
full canonical adoption; their pure/concrete differences remain recorded debt.

`coff-audit.json` examines all physical code/data/CRT nodes, public/weak symbols,
actual local relocation edges and COMDAT selection/association:

- Ctor26→28 nodes: all26 old nodes remain except the independently proved
  primary-table extension20→24. The first five actual pointers/relocation kinds/
  addends retain their targets; the new offset20 is DIR32/addend0 to the actual
  emitted new member. Added nodes are exactly1-byte code and its16-byte DebugF.
- Setter73→73 nodes: everything preserved, no added definition or data.
- No CRT initializer, new global/data owner, layout change, alias directive or
  speculative pin is introduced.

## Native six-slot planner, including the admission negative control

`native-vtable-plans.json` uses the unmodified vtable_bridge.plan against only
the two actual ledger tables and explicitly isolated compiled inputs. This is
bounded native evidence, not a real link:

| Inputs | Generated bridges | Refusals | Already correct tables |
|---|---:|---:|---:|
| Current source/current rows |1|0|1|
| Candidate/current rows plus independently proved private proposed row |0|0|2|

`native-vtable-no-admission-control.json` proves that the candidate body alone,
without the new row's normal identity binding, still leaves1 bridge. The tool
has not inferred an original name or accepted an unadmitted inline body. No
register was altered to achieve the positive private plan.

## Quiet current providers and selection orders

`provider-currency.json` checks all nine scoped normal shared objects only after
Root reported its full gate/publication finished. Every ordinary native
compile_is_current check is true, all source hashes match the private probe and
the shared original Coord2D whole body is stillC3/no relocations.

The native index is b146a56624/2026-11-21 01:46. Root's bfa publication differs
only by the recorded Apt handoff/queue evidence; all Code, tools, AGENTS and
code/symbol/data/flag ledger inputs compared by this script are byte-identical.
The index SHA is bound before/after the native check. It is not falsely relabeled
as an index whose metadata saysbfa.

The unmodified native ProviderGuard, with real old rows and the explicitly
proposed after-row/order, reports **three expected repair deltas**, all for
`??_7Rva0050EA74@@6B@`: bytes, retail order and path order. There is no claim that
the whole definition is identical: its former20-byte incomplete table becomes
the independently proved24-byte table. No other finding occurs. The same actual
Ctor object remains selected under both orders (digest00f01ca6e7a0→d0b466dd5117).
The base table remains740ab5d72710 under both orders. The new member has just its
real Ctor provider8bf7b464aaa2 under both orders, with no old-name alias or
selection override. Full native reference-walk evidence is complete.

## Root-only integration recipe

1. Verify Root's existing009 scopes and the exact input hashes in MANIFEST.json.
   Copy `Rva0050EA74.h.txt` to the held existing Header, preserving its LF bytes.
   The supplied `page-slot5-header.patch` expresses the same change.
2. Bank the actual emitted member through normal add_match, not pins or a
   handwritten ledger edit:

   ```text
   python3 tools/add_match.py '?v05@Rva0050EA74@@UAEXXZ' 0x000B3FD0 1 Code/GameEngine/Source/Common/Rva0050EA74Ctor.cpp --icf-owner '??1Coord2D@@QAE@XZ' --notes 'Native page table0x0086551C slot5; ECX noargs callback0050F670 discards result; complete1B RET and relocations equal original exported Coord2D empty owner; neutral existing slot model;fold-proof=Code/GameEngine/Source/Common/Rva0050EA74Ctor.cpp'
   ```

   This is the native function-row --icf-owner route, not pin_admission's
   minimum-concrete-byte pin route. No pin or gate exception is proposed.
3. Normal build the two actual Header consumers; bank the verified change with
   the scoped original-name/ABI/ICF evidence. Root's normal header/full gate and
   normal link audits remain authoritative. Do not mask the intentional table
   extension as provider identity or change a provider/verifier baseline.
4. Measure and publish the real current image through the permitted prepared
   local exit-link route. The served pass test is satisfied only when the actual
   published real link neither bridges nor refuses table RVA0086551C and all
   old coverage remains. Until then this candidate is0 completed served items.

No game launch, smoke runner, direct link_cycle command or shutdown was performed.
