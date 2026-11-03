### LINK-069: the four-byte merge sweep combines a string buffer with opaque record helpers

**2026-10-30 repair:** Cleared in the seven-unit ordinary-preview scope;
original element identity and census confirmation remain open. The wrapper
now calls the four existing providers directly through their opaque pointer
and empty-comparator declarations. Its template symbol is unchanged. The
buffer destructor directly names the existing incomplete
`TreeHintRef00217D4C` destruction view, removing its alias. Four unused
placeholder helper pins are removed. No additional layout or original name
is inferred from these bindings.

Strict preparation preserves 87/87 rows and both imports across the wrapper,
buffer initializer/reserve, TreeHintRef and AsciiString algorithm providers,
vector destruction provider and direct caller; all 16 EH graphs are EXACT.
Against index `12b9e7a7c0`, the seven-unit preview retains six previously
linking units and predicts the wrapper gains 141 authored bytes
(5,040 -> 5,181 total). The complete outgoing-batch audit remains INCONCLUSIVE:
its base differs from the index and 33 source objects lack current receipts,
first `Common/Rva003A5DA0Write.cpp`. Carry affected consumers into the next
scheduled census; full consumer selection/loss verification remains open.
[Repair evidence](../../reverse/attempt_support/merge-wrapper-link-20261030-codexb4.md).
The earlier diagnosis below is retained as history.

Status: Blocked on algorithm, element and provider-name reconciliation. Updated: 2026-10-26; inspected revision: `58598f540fd3c84610304b3659ed382a4c05acca`.

Evidence / affected unit: `StlSweepW4Rva004F8C16.cpp`, all three rows byte-exact against the current inputs. Retail's 131-byte wrapper calls 0x004F77AD (51-byte temporary initializer) and 0x004F77E0 (33-byte destructor), rowed as `Rva004F60AA` members in Rva004F60AAInit.cpp; it calls 0x004F840B (303-byte `__merge_without_buffer<TreeHintRef00217D4C,...>`, PAUTreeHintRef00217D4CRva004F9565.cpp) and 0x004F853A (279-byte `__merge_adaptive<AsciiString,...>`, stlport_stable_sort_asciistring_o1.cpp). The sweep's distinct `Rva004F8C16Element` names leave U4/L3/S3. Raw retail references and existing row homes: `build/c136-w4sweep/native-evidence.log` and `provider-rows.json`; current-provider before/after previews and full gates are mapped in `build/link-report.md`.

Completed: diagnosis and unchanged byte verification only. No source trial repeated the documented TreeHintRef/AsciiString helper-spelling conflict or copied the existing providers' incompatible function-pointer adapters. Remaining / next check: reconcile the native string/owning-handle element, buffer operations, comparator and the already rowed algorithms together. Suppressing the sole current-name copies would leave unresolved names; changing the wrapper's template spelling requires ledger work outside this seat. No missing native body, independently proven new fold pin or shared-header change is established by these calls.

Clearance: pending. Census confirmation: not claimed.
