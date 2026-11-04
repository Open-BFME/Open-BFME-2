# Subsystem legend loader canonical headers, 2026-11-04

Inspected base: `c0067e0a1a`. Scope: Common/System/SubsystemInterface.cpp
consolidation and its five claimed donors. The planner snapshot was generated
under build/consolidation; no TU map was committed.

## Completed prerequisite

SubsystemInterfaceLoadIniFilesFromLegend.cpp now includes the canonical
SubsystemInterface and SubsystemInterfaceList headers instead of PreRTS and
the legacy subsystem_bfme2 view. BFME_SUBSYSTEM_SLOTS supplies the existing
slot-2 method declaration. The canonical list's getXfer reads +0x24, replacing
the private padded transfer view. Bool was only a bool typedef from PreRTS;
using bool directly preserves the return and local types.

Target facts: the loader accesses m_flag at +4 and m_name at +8, and its two
INI calls read the transfer pointer at list +0x24. Existing canonical headers
already express these layouts. No donor layout or new field identity is asserted.

The scoped naming child proposed subsystemName, legendEntry and loadType; the
parent reviewed the complete mapping and applied all three together through
name_lane.py scoped apply. Six inventoried bindings were retained. Four distinct
asciiString loop declarations share one inventory key and were left unchanged;
the meaningful excluded vector is absent from that regex inventory and remains
unchanged too. The m_flag role remains unrecovered.

## Verification

- ./build.sh and scoped application: 5/5 code rows and the one data row exact.
- Three renumbered unwind labels were located through their parent's exact EH
  data; no label or pin edits. eh_verify: EXACT 1, zero missing/nonexact.
- find_declared_unmatched: all defined functions already matched.
- data_check shadow: zero findings. Converged enforcement: 11 addresses,
  zero second names and zero unjudged rows.
- Strict prepare-current provider receipt and ordinary link preview: LINKS,
  423/423 authored bytes retained against census a62ac1c10b (07:28 UTC).
  This is a prediction; no census/index/status or headline change is claimed.
- Staged code_identity_gate: five rows, zero new findings (shadow).
  tu_ownership --staged, check_csv and diff --check pass.
- The staged-tree link_batch_audit exits 2: its index predates the base, and
  Common/0CreateAHeroManager21FE49.cpp lacks a current consumer receipt.
  Full consumer preservation remains unverified; carry the loader and that
  consumer into the next scheduled census/current-receipt audit. This is the
  same consumer prerequisite recorded by the earlier donor-adoption pass.
- No source moves, aliases, pins, shared headers or protected debt keys change.

## Remaining consolidation prerequisites

Before this edit, the five-donor merge trial accepted none; the loader failed
first on the competing AsciiString definition. The updated trial also accepts
none, but the loader composition now reaches the seed's m_24/m_00 undeclared
errors after the canonical list header replaces its private view. The old
AsciiString failure is cleared for this trial, not the whole merge.

The earlier seed adoption's four byte failures remain unmodified: vector-base
construction for +0x18 and three vector destructor unwind bindings. Narrow
ledger inspection adds an important identity constraint: vector<void *>'s
allocator constructor already has a real owner at 0x00025100
(stlport_vector_uint.cpp, 55 bytes), and its destructor already has a real owner
at 0x00027370 (stlport_vector_voidptr_alloc.cpp, 131 bytes). They cannot simply
receive second pins at the seed's size-optimized helper addresses. Reconcile
these type/profile identities using retail evidence before seed adoption;
retain the prior handoff's full-byte/relocation proof requirement. Notification
specialization ordering also remains. No changed donor besides the loader,
no merge, and no frozen-file workaround were retained.
