# HotKey bounded native-copy contract review

**Verdict: positive.** The candidate repairs the actual construction/lifetime blocker. The typed `_Construct<Rva00359032Value>` is now the complete native 45-byte operation, with its own exact EH graph and the real counted-pair-copy target. Consequently the existing 34-byte node and 148-byte insertion have the correct symbolic callee closure. Root's unmodified saved LinkGuard preserves census-linked HotKey.cpp: prepare `null`, refusals `[]`.

Input control is current main HotKey.cpp, SHA-256 `db4c75ce60c1926d36a67645f7fbcc7f1bf8e669e1cb5e00cf9c582ce6239947`. The parent private proof reports all 45 current rows and eight owning parent EH graphs exact. Existing ordinary providers/properties remain identical except `_Construct<Value>`; the only added definition is the compiler-generated copy constructor described below. Root reports the control frozen check passes with 45 rows/five annotations. Normal post-application verification and frozen checks remain root's responsibility.

## Complete native helper and callee closure

| Candidate operation | Native placement | Evidence |
| --- | --- | --- |
| typed `_Construct<Value>` | `0x358CA0`, 45 bytes | all bytes exact with actual handler/FS placement; its separate `eh_verify.verify_row` result is EXACT |
| existing `_M_create_node<Value>` | `0x358DA0`, 34 bytes | allocate 24 bytes through existing `0x307F0`; call the repaired construct at value+16 |
| existing `_M_insert<Value>` | `0x358E9F`, 148 bytes | correct AsciiString compare `0x5598C`, two node calls `0x358DA0`, rebalance `0x25490`, full native instruction sequence/return |

The repaired construct's REL32 at +29 goes directly to the already-rowed pair copy at `0x358B43`; it does **not** call the added 18-byte implicit constructor. The EH prolog call resolves to `0x629188`, the actual native handler pointer is VA `0xB7D872`, and the final FS except-list field remains zero. The separately checked full helper EH graph accounts for that compiler metadata; this is not a relocation-masking waiver.

The real 34-byte pair copy calls StringBase copy `0x365F0`, copies the mapped pointer at +4 and increments pointee+4 when nonnull. Its current owner is `stlport_rb_tree_hint_00218022.cpp`. Current normal source/object/all-header receipts also pass for the comparator (AsciiStringLess.cpp), allocation wrapper (GameMemory.cpp) and rebalance owner (stlport_rb_tree_rebalance.cpp). Exact bodies, symbolic targets, native bytes and receipt hashes are in `provider-proof.json`.

This replaces the prior 23-byte two-DWORD POD copy. The existing name `Rva00359032Value` is retained, while the empty derived view reuses `Pair358C60`'s established copy operation. It is an explicit bounded operation/layout view: it does not establish original C++ inheritance, application container identity or pointee identity. No new pin, alias, compiler profile, explicit forwarding wrapper or header edit is needed or justified by this review.

## Extra implicit constructor

The only new ordinary definition is `??0Rva00359032Value@@QAE@ABU0@@Z`, 18 bytes, EXTERNAL `.text` SELECT_ANY. It forwards to the same existing pair copy through one REL32 at +8. It has no known native address and this report assigns none.

The candidate has **zero runtime code/data relocation references** to this helper. Its only COFF reference is discarded `.debug$F` metadata. The saved index has no definition or touch of the name. HotKeyAddHotKey.cpp has a related bounded declaration view; its current normal object has a fresh source/object/all-header receipt and neither emits nor references this implicit helper. Thus no actual cohort/provider conflict is found in the reviewed scope. `implicit-copy-review.md` records the source/API boundary.

An implicit compiler-generated special member does not require a new explicit source frozen marker or duplicate row merely because a physical COMDAT was emitted. Do not add a native-address pin, absent-from-retail claim or original-class name for it. Whole-object routes change as expected through the real construction graph; route identity is not claimed.

## Guard and application scope

The saved guard artifact is `build/hotkey-native-copy-contract-proof-20261104/link-guard.json`, using index `23b85ddde5`, 2026-11-03 18:36. It includes HotKey.cpp as census-linked, prepares successfully and reports no refusal. This is the actual unmodified guard judgment for the private source replacement, not a fresh whole-image census. No old provider is removed and the new construction/helper bindings explain the only ordinary payload changes.

Root can apply this exact candidate, then run normal 45-row/full-fact/EH/frozen verification and publication gates. Future replacement of ThingTemplate's misleading insertion row remains a distinct ownership/identity step; this prerequisite supplies the missing real native lifetime closure without pretending that step already landed.

All tracked/native reads stopped before report completion. This reviewer ran no build, edited no tracked source/ledger, acquired no claim and made no network or publication call.
