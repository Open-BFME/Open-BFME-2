# Remaining Respawn module-data prerequisites

Bounded read-only investigation at immutable published **678d949f99**; the concurrent AI header adoption was not read as a moving source input. No build, source edit, claim, network or gate change. Child's exact donor/seed blob evidence is in `respawn-moduledata-prereq-review-20261103-child.md`.

**Recommendation: first test the existing allocator-header context in the standalone tree donor; keep module-data constructor/lifetime reconciliation as a separate prerequisite.** No new donor merge or byte proof is claimed here.

## Smallest concrete next private test

The actual successful lifecycle merge's current rejection log (`respawn-lifecycle-merge-publication-20261103/apply.log`) identifies the tree donor's first failure as **C2766: allocator<char> already defined**. This supersedes the older generic forward-tree/C2953 explanation for that specific input.

The seed's established bfmealloc include profile loads `reference/shims/bfmealloc/stl/_alloc.h`, which already defines allocator<char> at394 and declares the same static `char *allocate(size_type,const void *)` at411. The standalone `stlport_rb_tree_bfmepod20_insert.cpp` omits that include profile and locally declares a minimal allocator<char> specialization after `<set>`. When merged into the seed, the two declarations collide.

A supported, narrowly motivated experiment is therefore: in the **standalone donor's private candidate**, use the existing bfmealloc header profile and remove only that redundant local allocator<char> specialization. Preserve the opaque BfmePod20 identity, actual tree bodies/instantiations, _M_create_node declaration, existing malloc inline specializations, existing alternate and every other compiler flag. Do not edit the shared shim or add a substitute class/alias/hatch.

This is not a proved safe change: allocator context can affect deallocation, tree/base-tree copies and EH. Require control plus candidate proof of **all eight existing rows, complete EH, ordinary external payloads/properties/routes and selected native providers**, especially rowed14B _Rb_tree_base destructor7FAB3 and tree destructor4AF46E. If it passes, normal verification/banking of the standalone prerequisite precedes another supported tu_skeleton dry run. If it changes an owned body/provider, record that concrete failure; do not force a common profile or add per-body optimization machinery. The present report author ran no compile.

## Constructor member identity: the smallest semantic prerequisite

The seed has three `int[19]` regions atC/58/A4. Construct.cpp has three real `Rva0042526Member` objects there, each automatically calling the existing20B constructor42526 before the body. Factory24F92E allocates120 and calls the149B constructor4AFB4E; existing row notes independently identify all three calls. These are actual member initialization/lifetime requirements, not names that can be mechanically aliased.

An existing shared **Rva0042526Member.h** was found. It explicitly says **not registered yet**, preserves opaque `unsigned char m_bytes[0x4C]`, and declares the out-of-line constructor. Its current actual owner is GameLogic/LargeGroupAudio/LargeGroupAudioAudioMap.cpp; the real header is already used by Rva001DFEAABase. Adopting that existing declaration in Construct.cpp is a small honest prerequisite, but by itself does not reconcile the seed's int-array API or unlock the constructor. No original bitset/condition type is proven by zeroing76 bytes, and the header does not expose an int-array API. Do not introduce reinterpret-cast storage bridges or edit the shared header merely to evade the real field-type boundary.

## Novtable, destructor and emitter boundaries

* Seed and Dtor are Snapshot-derived **novtable** views with matching filter+8, BfmePod20 tree+10C and strings118/11C. The dtor is the closest declaration match, but the actual merge already compiled it and was refused for selected tree/base-tree providers. Field-name alignment alone therefore does not resolve its current blocker.
* Construct is **non-novtable** and installs derived tableC556F8. Dtor96B intentionally has no entry leaf-table store and restores Snapshot through actual teardown. Simply adding/removing novtable to make one declaration compile is not justified: a coherent class must preserve both native behaviors and all generated EH/table/provider facts.
* FamilyDeleting's28B scalar wrapper comes from a base-less four-slot class plus an artificial EmitVtableTag constructor. The full seed has no such ctor, and adding it would automatically construct filter/tree/strings. It is not an independent harmless wrapper or an emission-only shortcut.
* Construct currently uses a map<long,LadderPref> folded-constructor view at10C, while seed/Dtor use the opaque20-byte set-tree. Equal12-byte headers/folded construction do not prove payload identity or teardown compatibility.

## Canonical availability and final scope

ModuleData is registered8B with a31-slot live interface; replacing Snapshot+field04 with it changes the virtual/lifetime surface and is not this small prerequisite. Neither RespawnUpdateModuleData nor RespawnRule was found registered at the fixed commit. Preserve their uncertainty rather than publishing a guessed class header. Existing tree alias and deleting-emitter marker remain debt; no new hatch, pin, row, original type identity or source placement is proposed.

All reads stopped. This is one bounded recommendation, not an autonomous retry loop or a merge approval.
