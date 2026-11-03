# ArmySummaryEntry UI/dispatch consumers: immutable read-only review

All findings use only the root-approved immutable snapshots from revision **9568bd202d7382c56e79ac065a0aa9ea66839a05**, under build/army-entry-header-20261103/readonly-snapshots. Read both complete headers and all four assigned complete sources (68/373/238/82 lines). All six snapshot hashes equal their manifest entries. No other four consumer snapshots or live Code sources were read. No edits to tracked files, builds, claims, network, name proposals or provider experiments.

The registered ArmySummaryEntry declaration is C8 bytes: CarryoverUnit at0..AB, secondary Rva0007DF07 atAC..B3, then int m_b4/m_b8/m_bc/m_c0 atB4/B8/BC/C0 and bool m_c4/m_c5 atC4/C5. CarryoverUnit supplies AsciiString m_name at+4 and is Snapshot-derived. The headers cite target constructor/destructor/table/allocation/xfer facts; this audit does not independently re-verify retail or compiler output.

## Exact source mapping and boundary

| Whole assigned source | Qualified mapping supported by visible offsets/types | Remaining boundary |
|---|---|---|
| StrategicInGameUIArmyDetailsPopulate.cpp | Private name+4 -> inherited CarryoverUnit::m_name, single field use at76. Private key+0 is unused. | Strong pointer-only adoption candidate. Holder destructor42 already uses its existing TargetRef pointer cast at complete-entry+AC; retaining that existing expression needs no new cast. No ArmySummaryEntry construction, destruction, by-value copy or base conversion is performed here. Actual include-context/byte checks still required. |
| ArmyUnitSwapperSelection.cpp | target+B8 -> ArmySummaryEntry::m_b8; fieldBC+BC -> m_bc; fieldC4+C4 -> m_c4. Uses at64/82,109/114/115/128,164/210. | Pointer-only candidate with one private API discrepancy: hasUpgrade() at31 is not canonical. Its single use172 can retain the existing exact boolean expression as qualified m_bc!=0; no new name, cast or canonical member is required. Compiler effects of removing that forceinline accessor are unverified. |
| Rva002B4076Dispatch.cpp | targetB8 -> ArmySummaryEntry::m_b8 in MoveArmyMember27-29. | Holder destructor14 directly takes &entry->ref, where private ref is a TargetRef00217D4C member atAC. Canonical entry has a distinct Rva0007DF07 BASE there and no ref field. There is no type-compatible replacement for that expression in the approved two-header snapshot set. Do not manufacture an unrelated-class cast or new base release API. |
| rva003F2150Rva003F2150Farm.cpp | Existing m_name at369 is inherited CarryoverUnit::m_name at4. Private constructor declaration matches canonical default constructor; allocation368 is of a C8 object according to target comments and canonical size assertion. | This source actually constructs entries and increments a secondary count, then releases the secondary through a holder lifetime. Private m_refVtbl atAC and m_references atB0 are absent from ArmySummaryEntry. The release297 addresses m_refVtbl before its existing TargetRef cast; there is no canonical field of that name. This is a base/ownership API boundary, not a reason to invent a new field or class copy. |

Use per-expression qualified member edits only; several sources contain unrelated name/prefix/count-like members, so token-wide substitution is not justified. Existing casts in the sources are not endorsements of new casts.

## Secondary-base clarification supplied by parent

The parent separately read committed Rva0007DF07.h at the same revision: it is an8-byte virtual class with inline constructor m_04(0), inline empty virtual destructor and public **unsigned m_04 at+4**, hence entry+B0. The count offset is target-backed. Farm's increment296 therefore has the qualified field correspondence Rva0007DF07::m_04 at the same address; its private Int declaration and the canonical unsigned type are not an independently recovered original signedness claim.

However, TargetRef00217D4C is a separately registered class, and ReleaseTreeHintRef00217D4C accepts TargetRef00217D4C*. Rva0007DF07 is not established as that base. Matching8-byte size, vptr shape and count offset do not establish a C++ subtype conversion or justify casting one registered class into the other. Dispatch's address-of-ref and Farm's address-of-vtable therefore remain concrete blockers under the no-new-casts/no-new-base-API scope. Strategic Populate already expresses the raw+AC bridge, so its existing expression can remain while only its entry class/name use is adopted.

## Include/lifetime facts and provenance limits

CarryoverUnit.h explicitly refuses an already parsed legacy Snapshot crc surface: `__SNAPSHOT_H_` set without BFME_SNAPSHOT_NAME_SLOT. Its constructor/copy/destructor and xfer are out-of-line declarations; ArmySummaryEntry likewise declares real lifetime methods. This matters most in Farm, where new ArmySummaryEntry and the counted holder are present, while the two pointer-only UI candidates add no entry lifetime operations. The assigned source text contains no competing full CarryoverUnit or Rva0007DF07 definitions. Transitive non-snapshot headers were not authorized inputs, so this review cannot certify their actual current Snapshot guard state or absence of other include collisions. It proposes no macro forcing.

The source comments separate target facts (B8 target state, BC upgrade word, C4 bool, AC/B0 ownership storage) from WorldBuilder name/callgraph leads. The mapping above retains offset names and makes no claim that an operation's original descriptive name has been recovered. The parent's official adoption run reportedly fails all18 attempted consumers; the semantic ease of the two pointer-only mappings here is not a successful adoption or byte/link verification.

Review complete; all snapshot and tracked reads stopped after this report.
