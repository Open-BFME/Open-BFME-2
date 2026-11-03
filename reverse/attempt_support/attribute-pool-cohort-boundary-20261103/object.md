# AttributeModifierPoolUpdate: Object.cpp bounded read-only review

Scope: whole immutable original Object.cpp, all 5733 lines, plus the entire canonical AttributeModifierPoolUpdate header and its UpdateModule/BehaviorModule/ObjectModule/Module/Snapshot dependency declarations. No edits, claims, builds, normal-cache writes, or network. Root's owning adoption temporarily swaps live Code files, so the original root backup was used throughout.

Inputs:
- build/attribute-pool-header-main-20261103/Object.cpp: SHA256 514CFB9860FA1F971468912E3280EEC168196273A5CFA847AEEEA647A3EFF899.
- Code/GameEngine/Include/GameLogic/Module/AttributeModifierPoolUpdate.h: SHA256 925BE909E58EF793DDEB0786D72BA8CF54AD565FB6F007C7CA6D46129DC891A3.

## Target use is already signature-compatible

Original lines 858-863 are only two ordinary nonvirtual declarations: Bool rva00403382(Int, Real*, Int) and Bool rva00403448(Int, Real*, Int, Int). Bool=bool, Int=int, Real=float in this TU, exactly the canonical signatures. Object::rva0028C149 (3086-3092) and Object::rva0028C15E (3101-3107) obtain the primary pool pointer from the existing findAttributeModifierPoolUpdate() declaration (2003), null-check it, and call those methods directly. There is no up/downcast through the pool's new bases and no adjustment expression. No field substitutions are needed or justified: no AttributeModifierPoolUpdate fields are touched.

The whole file contains no pool by-value instance, new/delete, destructor/constructor definition, sizeof, copy, RTTI, or member-pointer operation. The remaining pool mentions after the two bodies are tu-skeleton historical/unabsorbed ownership comments, not live code. In particular finder 28BDD7 remains a separate source; it is not defined in this Object.cpp.

## Exact blocker to one-class-only replacement

Including the canonical pool header brings canonical UpdateModule, but original lines 923-936 already define an incompatible, nonpolymorphic 12-byte UpdateModule carrier with explicit m_vtable at 0, m_pad04, m_object at 8. It is a real active definition, not a forward declaration. Canonical UpdateModule is a 32-byte BehaviorModule + UpdateModuleInterface hierarchy and has no m_vtable field. The current queue failure for AttributeModifierPoolUpdate + Object.cpp explicitly records that absent field (header_queue.tsv line 1337 at read time).

This private UpdateModule is required by ObjectHelper (945-953), whose rowed constructor at 3133-3140 calls the base constructor, writes m_vtable plus the derived m_p0C/m_p10 pointer words, and calls setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER). Replacing the pool declaration alone therefore causes a class redefinition. Removing the carrier along with it would leave m_vtable unavailable and change ObjectHelper's base/member layout (old derived pointers at C/10 versus a real 0x20-byte (32-byte) base): that is a separate representation/constructor recovery, outside this one-header review. Neither a guessed field mapping nor a token rename resolves it.

## Header and provider scope

Object.cpp already reads canonical Module at 138, canonical ModuleData at 2040, and canonical BehaviorModule at 2049. Its full private BitFlags template, NameKeyType enum, UpdateSleepTime enum, Object, ThingTemplate, Player, GeometryInfo, and BfmeFixedStorage128 views are unrelated existing declarations; the new chain merely forwards those relevant names rather than defining them. Do not erase or relabel them as part of this target. Rva00297360Element is already a complete class here (1141); the pool header's forward declaration does not conflict. No pre-existing full Rva002983DAVector definition was present in the source (only an unabsorbed row comment).

Pool methods/constructor/destructor in the canonical header are declarations, so pointer-only pool callers do not themselves require a new pool vtable/deleting helper. However this is a read-only conclusion, not a compiler/provider receipt. The actual active ObjectHelper constructor is precisely why canonicalizing its UpdateModule prerequisite could emit/change tables, lifetime calls, EH and ordinary providers. Snapshot was already read through Module before BehaviorModule; preserve that existing include context. This audit does not assert any new emitted vtable is native simply because method call signatures agree.

Verdict: receiver and two direct-call signatures need no adaptation; pool field mapping is empty. A whole-declaration pool include alone is blocked by the independently active UpdateModule/ObjectHelper carrier. Owning acceptance or a separately proven base/constructor recovery is required; no extra target names, pins, aliases, or diagnostics proposed.

