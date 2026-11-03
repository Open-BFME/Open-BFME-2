# Clear: legitimate vector-accessor visibility hypothesis

Verdict: the shared codegen explanation is CONFIRMED, but this exact candidate is NOT ready to land because it emits a new nonretail size() provider and other spare-provider changes remain unverified. All15 parent rows stay exact. The beacon _M_find becomes the exact native47B, zero-relocation body at RVA2888D4, without rewriting that helper or using raw storage. No further trial was run after the provider blocker was identified.

The vendor generic accessors were read: vector::size is finish-minus-start; const operator[] returns *(begin()+index); const begin is _M_start. The real member specialization can legally access that inherited vector storage directly. The current Clear source declaration-only size/const[] hide these implementations, explaining its old60B _M_find with2 REL32 calls. The kept CreateBeaconObject source was inspected: its visible existing begin/size bodies enable the corresponding native helper. That source's preexisting dllimport/forceinline attributes were NOT copied into this candidate or added as hatches.

The candidate changes ONLY the two declaration-only specializations to ordinary inline definitions:

```cpp
template <> inline size_t vector<void*>::size() const {
    return size_t(this->_M_finish - this->_M_start);
}
template <> inline void *const &vector<void*>::operator[](size_t n) const {
    return *(this->_M_start + n);
}
```

Other declarations (including nonconst[], begin/end and const-begin suppressions), all flags, vendor headers, parent bodies, pins and aliases remain unchanged. No raw class/storage view, explicit _M_find specialization, pragma, volatile, asm or import attribute was introduced. The old46B/G7/storage-expression experiments were not repeated.

The frozen scanner first printed 'All defined functions are already matched'. Exactly2 sanctioned private Verifier compilations: control and candidate, both15/15 parent rows; no owning EH graph is emitted in either. Before _M_find is60B with calls at offsets15/31 to size()/const[]; after it is47B and its ENTIRE bytes equal native2888D4 with zero relocations. Thus this is a successful codegen result, not merely matching length.

## Provider/route result: concrete blocker retained

Ordinary external definitions46 ->48. No existing provider is removed. Existing provider storage/section/COMDAT-selection properties are unchanged, but2 accessor definitions are added and4 spare bodies change:

| Definition | Control bytes | Candidate bytes | Evidence |
|---|---:|---:|---|
| beacon _M_find<int> | 60 | 47 | native47/zero-reloc EXACT |
| _M_bkt_num_key | 25 | 26 | changed; no matching row/pin native extent found by exact name |
| _M_bkt_num | 5 | 26 | changed; no matching row/pin native extent found by exact name |
| hashtable::erase(const_iterator) | 103 | 109 | changed; no matching row/pin native extent found by exact name |
| const vector<void*>::size | absent | 9 | NEW COPY differs from native25B owner |
| const vector<void*>::operator[] | absent | 12 | NEW COPY; exact-name native placement not established here |

The size() native owner is current matched row RVA23BC0/25B, Code/Libraries/Source/WWVegas/WWLib/stlport_vector_voidptr.cpp (the current unit uses /Od /Ob1 and is migrated4.6). The candidate's9B full body cannot be that25B implementation. This is an actual native-provider mismatch, not an assumption from comments. The current index has retail/wrong size copies; its date/meta and all exact symbol names, raw bodies/relocs and binding facts are retained in provider-bindings.json. Index None verdicts for the other spare helpers are explicitly unverified, not clean native results.

Defined-name delta is exactly the2 accessor names; the same2 names leave undefineds because their bodies become visible. No new undefined, forced include, weak default or alternate route. All other ordinary providers outside the4 changed spare bodies retain full bytes/symbolic relocations. No selected-provider or whole-image link approval is claimed; parent-row exactness does not justify the new wrong/unverified copies. A separate legitimate provider-emission/ownership solution is required before this codegen win can land. Do not hand-add dllimport/forceinline suppression, pins, aliases or a check exception to force it through.

Artifacts: control.cpp/candidate.cpp; both private objects; proof.json with15-row/helper/provider/property/route results; provider-bindings.json with narrow existing native owners/index facts. Harness ../gamewindowmanager-readonly-20261103/clear-accessor-visibility-probe.py. Existing separate LWRM canonical-header work was not touched. No tracked Code/ledger/index change, normal build/shared-cache write, claim, network or additional compiler trial. No linking/census/image-ownership gain claimed. Tracked reads stopped.
