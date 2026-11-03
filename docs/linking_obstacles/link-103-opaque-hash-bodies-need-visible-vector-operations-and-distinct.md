### LINK-103: opaque hash bodies need visible vector operations and distinct native key identities

Follow-up repair (2026-10-29, inspected `ac17ccda47`): reveal the existing
STLport count constructors, allocation and vector swap with the stateless
allocator-proxy swap already used in Armor.cpp. Exchanging only `_M_data`
avoids the generic proxy-copy instantiation that regressed the earlier trial.
The Pod72 resize now has the retail 184-byte verdict at 0x0053F1EC, and the
unit improves from L3/S3 to L2/S2 against index `85f6b7f40c` (15:08).
All eight own rows and 1,176 rows across the 44 affected sources byte-verify.
The ordinary-preview comparison preserves all 41 previously linking units,
including stlport_hashtable_asciistring.cpp; no other blocker set changes.
Only the edited source has a strict reusable receipt, so this is not a
census-grade provider closure. Pod44 construction and integer-table resize
still require the native type reconciliation described below. Identity-debt
retirement also refuses an unregistered, unchanged hash-set constructor
callee conflict at 0x0005A112; retain the register and reconcile that family
before retrying retirement. [Scoped evidence](../../reverse/attempt_support/pod-hash-vector-swap-20261029-codex3.md).
Clearance: Pod72 resize only in ordinary-preview scope; current L2/S2.
Census confirmation: pending; no linked-byte gain claimed.

Status: Open (bounded emission repair verified). Updated: 2026-10-27; inspected revision: 40d8eced18722ddcee26c59ddc4f3fb8d157d887.
Evidence / affected units: Code/Libraries/Source/WWVegas/WWLib/stlport_pod_hash_bodies.cpp reproduces L7/S7 against index 5ce093a71a (2026-10-26 19:02, retail-truth-4). Its declaration-only vector<void*> subobject constructors and destructors hide the canonical STLport lifetime operations, and its declaration-only subscript hides native bucket access. The remaining record/key identity conflicts also fall under LINK-002.
Completed: reveal the existing STLport default vector/base constructors and vector/base/proxy/allocator destructors, and retain subscript's header operation through a dllimport/forceinline specialization without an unused external subscript copy. The two erase-bucket copies now have retail verdicts at 0x00053EE8 (58 bytes) and 0x00053F22 (76 bytes), as does the insertion helper at 0x002E037F (112 bytes). The hashtable constructor changes from the wrong 77-byte body to the native 64-byte instruction shape; its recursive verdict remains unknown rather than a full retail proof. The unit's eight matched rows remain exact, declaration/EH/shadow data checks pass, and its preview improves to L3/S3. A 262-source current-provider/consumer comparison preserves all 244 initially linking units and adds no blocker. This is a partial repair, not a unit clearance.
Failed trial / stopping condition: additionally revealing the count constructors/allocation and generic vector/proxy swap cleared the Pod72 resize blocker but made previously linking stlport_hashtable_asciistring.cpp acquire selected-wrong ??0?$_STLP_alloc_proxy@PAPAXPAXV?$allocator@PAX@_STL@@@_STL@@QAE@ABV01@@Z. Those extra edits were reversed, and the consumer links again. Do not repeat that generic-swap trial without resolving its copy-constructor provider. The narrower lifetime/subscript repair remains.
Remaining / next check: the Pod44 _Construct name is pinned to 0x0041072F, whose existing owner is _Construct<pair<const AsciiString,Rva0045EF90Object>> in stlport_pair_asciistring_twins.cpp and calls pair copy 0x004105C4; the emitted trivial integer-key copy is 32 bytes rather than that 45-byte EH body. The integer-table resize name is pinned to the 199-byte AsciiString-key grower at 0x00212858 in Rva00212858Resize.cpp, whose native loop calls hash 0x00055041. These require coherent existing-row key/element identity reconciliation. Pod72 resize reaches the existing 184-byte fold at 0x0053F1EC, owned by Armor.cpp and proven typed fold owners; use its native vector lifetime/swap context together with the actual allocator-proxy copy provider. Suppression alone has no replacement provider for the old Pod44/integer-resize spellings. No new match or independently justified fold pin was identified.
Clearance: only the four removed blocker pairs are cleared in ordinary-preview scope; census confirmation pending. The unit remains blocked by Pod44 construction and both resize copies (L3/S3).
Census confirmation: pending; no linked-byte gain claimed for this unit.
