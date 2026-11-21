# Green private ControlPoint lifetime bank package

**Ready for Root's normal admission.** This is a three-source prerequisite package, not a VNI/event repair, a completed queue item, new unique retail coverage or runtime proof. All work was private; no production file, claim, Git state, shared object/index, flag, SDK, alias or tool was changed by the worker. The existing legacy alias directive in the old destructor source is byte-preserved, not extended.

Basis: Root Source `40496f82be14ec699d35ea9c0100c0e3d366a7c1`. Original source hashes and final candidate/patch/object/evidence hashes are in `MANIFEST.json`. All three files retain LF endings, UTF-8 without BOM and their exact original compiler/library directives.

## Final source artifacts

| Production target | Final private source | Patch | Existing rows retained | Intended normal rows after admission |
|---|---|---|---:|---:|
|`Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_copy_ctors_bfmealloc.cpp`|`stlport_rb_tree_copy_ctors_bfmealloc.cpp.txt`|`base-CANDIDATE.patch`|13/13|15|
|`Code/Libraries/Source/WWVegas/WWLib/stlport_int_ascii_tree_dtor.cpp`|`stlport_int_ascii_tree_dtor.cpp.txt`|`dtor-CANDIDATE.patch`|1/1|3|
|`Code/GameEngine/Source/Common/Rva00064640Insert.cpp`|`Rva00064640Insert.clean.cpp.txt`|`caller-CANDIDATE.patch`|10/10|12|

The allocator provider uses its existing bfmealloc context. The destructor uses its existing `/EHs` context and existing genuinely nontrivial destructor-only storage view. The Record source retains its `/EHsc`/STLport46 context and uses ordinary declarations of the real external base constructor and tree destructor; it emits neither the wrong stock33B constructor nor the wrong52B destructor. There is no new padding/trivial-lifetime map view or construction adapter.

## Six exact compiler bodies and their roles

Full names, source targets, exact original ICF-owner arguments, sizes and notes are in `FINAL-COHORT.json` and the **unexecuted** `ROOT-ONLY-ADMISSIONS.ps1.txt`.

| Admission | RVA | Size | Independent native evidence |
|---|---|---:|---|
|Actual Record-node alloc-proxy constructor|0014F3C4|11|Actual pointer-bearing4B proxy, const allocator reference plus node pointer, complete receiver/RET8 body.|
|Actual Record-tree header-node base constructor|00417B55|36|Actual44B node allocation with hint0 through existing307F0 and the proven11B proxy; correct whole constructor/RET4.|
|Actual nontrivial Record-tree destructor|002B80CE|56|Actual Record clear2B70B3, header ownership and guarded free30830, including native EH-state deactivation.|
|Actual Record-tree-base destructor|0007FAB3|14|Original parent-EH edge at7768C1 reaches7FAB3; the complete guarded header-free body and its free relocation are exact.|
|Actual Record-tree comparator/allocator initializer|004FF681|42|Exact call to the independently proven36B base provider, count/header/color/root/left/right initialization and RET8.|
|Actual Record-set default constructor|005011C1|25|Exact real42B tree call and return-this sequence, no invented wrapper or provider.|

All six have complete strict byte/relocation comparisons, `masked=false` and zero unresolved operands. The56B destructor's full EH graph is **EXACT**. Its auxiliary14B cleanup callback is independently strict against the original EH destination, and the existing named frame-handler binding is verified at629182. Merely masking exception-data relocation bytes was not used as callback proof.

Initializer dependency checks used an in-memory view containing only already independently exact providers, in11→36→42→25 order. That view was never written as a pin, alias, production row, register or cache. Root must perform normal admissions so the ordinary build obtains these names legitimately. The C++ names describe the existing neutral canonical Record type; no original EA mangled class name is asserted.

The actual normal-header native type evidence already supplied in `../controlpoint-closure/NATIVE-TYPE-EVIDENCE.json` establishes Record28B/key+18, node44B/payload+10, tree/set12B, allocator1B and proxy4B. The destructor file deliberately models only its proven nontrivial destructor-visible tree/base contract, not a reconstruction of every STL method.

## Existing rows and complete footprint

All24 existing row instances remain strict/unmasked with no unresolved operands. Every previously emitted public code body keeps its raw bytes and named relocations. New code/data/weak/COMDAT definitions are enumerated rather than suppressed.

| Source | Physical non-debug nodes before→after | Retained evidence |
|---|---:|---|
|Allocator context|137→155|All137 old nodes, local edges, associations and old externals preserved.|
|Destructor context|7→12|Six old nodes identical; the old `.sxdata` is explicitly extended, as described below. Old code, old handler and its target code remain unchanged.|
|Record caller|84→101|All84 old comparable nodes and every old public code body retained.|

There are no new `.CRT` initializer sections. Seventeen genuinely new code names have no previous definer in the native index inventory at Source2023f0eeb0; the index binding is explicitly historical, not a globally current selected-provider guarantee for a later Head.

Three new names are defined by more than one packet source: the1B node-allocator destructor,1B alloc-proxy destructor and14B tree-base destructor. Each copy has identical raw code, identical named relocations and COMDAT `ANY` selection2. Either input order therefore selects an identical payload. This is a scoped code/selection proof, not an actual full-image link.

### Actual `.sxdata` change

The destructor object's SafeSEH registration section grows **4→8 bytes**, from one handler to two. Its raw COFF symbol-table indices change from `1c000000` to `2100000032000000`; these are symbol indices, not image pointers. Decoding proves the old handler name/value and its identical mapped code are retained, with the new typed destructor's genuine handler added. Both associated exception graphs match the same original lifetime behavior. This metadata growth is intentional and is **not** called an unchanged whole object.

The failed stock-profile negative controls remain separately retained: stock33B base constructor and52B destructor do not pass the native36/56 extents; the earlier25/42 pair remained unresolved until correct providers were independently proved. No gate, profile or type was changed to make those failures disappear.

## Root-only integration order

1. Apply the allocator-context candidate and normally admit11B proxy then36B base constructor. Keep all13 prior rows.
2. Apply the destructor-context candidate and normally admit56B tree destructor and14B base cleanup. Keep the prior56B spelling and legacy directive unchanged.
3. Apply the clean Record candidate and normally admit42B tree initializer then25B set initializer. Keep its10 prior rows and original profile.
4. Run the normal whole-file builds, EH/admission/ICF/ownership and publication gates on the actual production files. Commit verified substantive source changes separately as required by the project. If a normal tool refuses, preserve its reason; this package authorizes no bypass.

The script contains exactly those six ordinary `add_match.py ... --icf-owner ...` commands and stops on any refusal. No command in it has been executed by this worker. Do not copy the private objects into shared build output. No generated map, alternative name, flag register or shared header needs editing.

All six physical addresses were already owned. These instances total184 bytes of typed bodies, **zero new unique retail bytes**. They prepare a correct lifetime contract for the still-unmodified VNI consumer. Event2BAEAB/2BAE8F are deliberately untouched and still require Root's additional reservations before the next task.

## Evidence locations

- `PROBES.json`: the two unchanged provider contexts, controls/candidates,13+1 retained rows and emitted definitions.
- `NATIVE-AND-FOOTPRINT.json`: strict11/36/56 comparisons, complete EH callback proof, full provider-node graphs and explicit SafeSEH growth.
- `CLEAN-CALLER.json`:10+10 row control/candidate, exact42/25 closure and absence of wrong local storage providers.
- `FINAL-COHORT.json`: the three-source inventory, all new definitions, three identical shared COMDATs, snapshot-index inventory and six ICF argument sets.
- `ROOT-ONLY-ADMISSIONS.ps1.txt`: Root-only ordinary admission recipe.
- `MANIFEST.json`: hashes and exact production-target/source-artifact mapping.
