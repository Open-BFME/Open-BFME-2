# BFME2 Item013 — ready for normal ICF admission and native identity retirement

**Private result: exact; public task pass still pending Root.** Source base e587ad3656865550008ac64cf8de1919a9710d53, final observed HEAD `56c8d42325165470cf7b73f16ddb473a755a9045`. Only one private compiler invocation was made. Candidate SHA256 **c68b9d64007a603516cf4bf64504018ba997b4f4ac5f73ba58372ef67683edc1**; original source SHA2562094f52450838ad52ba090b473325f3f428fb73fad28a7c38f14ca4282698e17. Both files use LF throughout.

## Small source change and real failure

The only source change is `#define _BFME_RETAIL_TREE_INSERT_LAYOUT 1` before `<map>` in Code/Libraries/Source/WWVegas/WWLib/stlport_map_bool_subscript.cpp. This selects an existing vendor/header compatibility branch; no compiler flag, header, class, tool or register was changed. It reproduces retail's leftmost value-insertion path that supplies parent,parent to the existing core insert rather than using the already-null search node. The current ordinary command is still MSVC7.1 /O1 /arch:SSE /G7 /MD /EHsc with the same allocation shim/static STLport. Full native/private commands are in COMPILE-ONE.json.

The queued `wrong` classification does not itself prove a differing29B map-insert body. Fresh current COFF already has the exact29B raw body; its external tree-insert name had no proven address, so its index verdict is `unknown`. The actual complete-graph failure is deeper: the unmodified value insert emits132B at retail's134B body002D563D. The original object was fed through the same native recursive proof and fails exactly there. With the one existing branch selected, the entire29→294→136→34 and134 chain succeeds, not just a masked29B comparison.

## Complete private byte/relocation proof

Native `pin_admission._prove_body` was used with an explicit private output and the ordinary current symbol map. Every owner object that the native all-owner comparison could read was first proven current by build.compile_is_current; all18 selected owner-source/object snapshots passed. The native function's compiled-owner memo was populated only from those already-current objects, avoiding any shared compilation. This is a diagnostic invocation of the normal recursive body/identity/relocation machinery, **not** the public admission command or a modified checker. Partial bindings from the negative control are explicitly not proofs. See NATIVE-PRIVATE-RECURSIVE-PROOF.json.

| Native RVA | Full bytes | Actual compiled STL operation | Existing owner retained |
|---|---:|---|---|
|002D464E|34|signed pair node creator|unsigned/bool node creator|
|0046AC52|136|signed-key tree core insert|Rva0046AC52::rva0046AC52|
|002D563D|134|value insert_unique returning iterator/bool|Rva0046AC52::rva002D563D|
|0046E563|294|hinted insert_unique|Rva0046AC52::rva0046E563|
|0046F0A5|29|map hinted insert|Rva0046AC52::rva0046F0A5|

All5 complete bodies (627B already owned in retail) have exact bytes and resolved call relocations, with every matched same-extent owner's relocation offsets/types/addends checked. No DIR32 masking, weak fallback, new pin, wrapper or guessed type alias was used. The primary69B operator[] remains strictly exact/unmasked with no unresolved callee. The Rva0046AC52 source remains byte-for-byte unchanged; all4 old rows and their objects stay intact.

## Original instructions and actual header/ABI contract

The public headers are the actual unchanged vendor/stlport _map.h/_tree.h/_tree.c/_pair.h, with55 opened headers recorded by the native compiler. _map.h158ff supplies the exact lower_bound/default-value/insert/return-second algorithm and171ff supplies the genuine hinted wrapper. The original69B code compares signed keys (`jge`47036E), stores a zero byte for the default value, constructs a4B by-value iterator on the stack, calls46F0A5 and returns node+14. Original29B uses ECX as receiver, forwards the by-value iterator plus entry reference and hidden result pointer to46E563, and returns with ret0C. These agree with the real STL iterator/header API, not an arbitrary Node* alias.

Original node creator2D464E requests24B, places the payload at node+10 and calls the existing byte allocator307F0/22B and pair construction1FF5AC/23B. That constructor copies a4B first member and a1B second member; node links occupy the16B prefix. The signed pair constructor is **already normally rowed** at the same1FF5AC in SelectionIDMap.cpp beside the unsigned FileSystem owner. No new constructor identity is guessed. Original core136B, hinted294B and unique134B all use signed key comparisons, the existing red/black-tree helpers, receiver head+0 and count+4; their entire code and call graph are matched. ORIGINAL-CALLGRAPH.json preserves exact raw bytes and complete disassemblies.

**Type boundary:** the canonical Rva0046AC52 header is an8B neutral view, not proof of the full original map type or full map size. Actual STL _Rb_tree also declares its comparator member. No class fold/typedef/rename of that8B view to the STL map is proposed. The valid route is concrete function ICF with complete byte/relocation proof. Existing12B Pair view in GapBodiesSeat1B and the generator's opaque count slot are older type/header debt, not repaired or silently adopted here. Existing consumers/header contracts remain unchanged.

## Whole-object and selected-provider limits

Before/after:45→45 code functions; zero new/lost names; exactly one code body changes132→134B. All runtime data, directives, weak-default relations, SafeSEH data, external name sets and COMDAT selections are identical. See WHOLE-OBJECT-FOOTPRINT.json. In the current native index (4305841cd0,2026-11-21 05:43), all5 newly proved typed names have exactly one provider, this same bool-subscript object; there is no competing typed copy to move ahead by reordering. The index is historical evidence for that source head, not a new real-link measurement. No new linked coverage or runtime result is claimed.

## Root-only normal completion

All exact commands/symbols/owners are in ROOT-ONLY-ADMISSION-PLAN.json and ROOT-ONLY-ADMISSIONS.ps1.txt. Copy only the hash-checked candidate source. Use the native5 ICF admissions **callee before caller** (34,136,134,294,29), retaining every original owner; supply the actual model token. This provides ordinary name resolution at every step without inventing pins or hand-writing ledger rows. The notes record actual fold-proof source, not gen-alias/object-symbol mappings. No shared header/contract changes are requested.

Then run normal ./build.sh on the entire source and `repair_queue.py retire identity` on it. Only that owning verdict may remove the queued baseline key. If any native admission/flag-selection/whole-consumer/identity check refuses, stop and preserve the evidence rather than force a row or edit the baseline. Normal hook/link guards and final publication/measurement remain Root's job. Source-only patch is not by itself a completed task: existing missing typed-owner facts must be admitted, and **0 new unique physical bytes / no new body credit** is the correct accounting.

Private files only were written. No production source, header, tool, register, pin, claim, Git or shared object/index mutation was performed by this worker.
