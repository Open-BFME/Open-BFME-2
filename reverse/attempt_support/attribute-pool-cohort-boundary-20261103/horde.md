# HordeContain AttributeModifierPoolUpdate header audit

Read-only audit, 2026-11-03. No Code/tracked edits, builds, compiles, claims, network calls, admissions, or planner runs were performed. Findings concern replacing only the private AttributeModifierPoolUpdate declaration with the canonical header; they do not certify byte or link verification.

## Frozen inputs and read coverage

- Source: `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp`, all 5,218 lines read in bounded chunks.
- Canonical header: `Code/GameEngine/Include/GameLogic/Module/AttributeModifierPoolUpdate.h`, read in full.
- Initial and immutable original source SHA256: `8F41E81AA7332D1FF9E14B54A2F98348B2B95F67FBBF9FA6375C3969A7C8290B`.
- Canonical header SHA256: `925BE909E58EF793DDEB0786D72BA8CF54AD565FB6F007C7CA6D46129DC891A3` (unchanged at final header checkpoint).
- Audit source snapshot: `build/attribute-header-cohort-readonly-20261103/HordeContainIface11CSlots.snapshot.cpp`. Its hash exactly equals the owning tool's original backup at `build/attribute-pool-header-main-20261103/HordeContainIface11CSlots.cpp`.
- A live source checkpoint transiently returned `FE43373BC2F1467392E4B1E6B4CF71BA1B272A139A48622355D9BFEA2A0A009B`, then returned to the original hash. Parent was notified immediately and confirmed the owning adoption tool temporarily swaps Code. Stable scratch content was used to finish the review. Line numbers below refer to the original snapshot.
- Read transitive canonical headers in full: UpdateModule.h, BehaviorModule.h, ObjectModule.h, Module.h, and reference/shims/moduledata/Common/Snapshot.h. This chain does not include ModuleData.h, Thing.h, AIUpdate.h, ContainModule.h, or a full BitFlags header.

## Decision

The two direct AttributeModifierPoolUpdate member calls are signature-compatible and require no field mapping. However, replacing only that private class (lines 127-132) with the canonical include is blocked by three existing full private class definitions: UpdateModule, BehaviorModuleInterface, and UpdateModuleInterface. They also form the deliberately split TransportContain base layout. A safe adoption therefore needs a separate, explicit reconciliation of that existing hierarchy; deleting the pool declaration and adding the include alone is not sufficient.

This agrees with the existing target queue record at reverse/header_queue.tsv:1337: the recorded AttributeModifierPoolUpdate trial for this file stopped with BehaviorModuleInterface redefinition. That record is prior evidence, not a compile performed by this review.

## Every target use and exact API mapping

The private declaration (127-132) has no fields, no bases, no constructor, no destructor, and no virtual declarations. It declares exactly:

| Original declaration | Canonical declaration | Required mapping |
|---|---|---|
| `bool addModifierToPool(const AsciiString &name, int a2)` | `bool addModifierToPool(const AsciiString &name, int duration)` | None. Parameter spelling does not change the signature. |
| `void rva00403744(const AsciiString &name)` | `void rva00403744(const AsciiString &name)` | None. |

All uses of AttributeModifierPoolUpdate in the whole source are:

1. Private class declaration at 127-132.
2. Object's private `AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const` declaration at 638. This is only a declaration, not a getter body here. It does not convert between base and derived pointers.
3. HordeContain::rva0046DB6D at 2248-2250: obtains that pointer, null-checks it, then calls `addModifierToPool(name, a3)`; bool return is ignored. The canonical method remains a nonvirtual, non-const member with the same explicit arguments and bool return.
4. HordeContain::rva0046DC92 at 2275-2277: obtains that pointer, null-checks it, then calls `rva00403744(name)`. Same nonvirtual, non-const void signature.
5. HordeContain::rva004708BC at 2906-2908: obtains that pointer, null-checks it, then casts to the unrelated existing Rva0040334B view before calling its `rva0040334B(result)`. Neither the canonical pool header nor its ancestors define Rva0040334B; the existing unrelated-pointer cast supplies no base adjustment. This is not a call to a new canonical method and should remain unchanged in a pool-only adoption.

No target `sizeof`, field access, array indexing, embedded instance, by-value parameter/result, allocation, constructor, destruction, deletion, RTTI, pointer-to-member operation, or implicit conversion from/to a pool base occurs anywhere in this file. Thus there is no target field mapping at all. In particular, none of the canonical fields at +0x20 through +0xA4 are accessed here.

The narrow current ledger lookup records the exact external providers already used:

- Object::findAttributeModifierPoolUpdate, RVA 0x0028BDD7, ObjectFindAttributeModifierPoolUpdate.cpp.
- AttributeModifierPoolUpdate::addModifierToPool, RVA 0x00403E72, Object/Update/AttributeModifierPoolUpdate.cpp.
- AttributeModifierPoolUpdate::rva00403744, RVA 0x00403744, same provider TU.
- Rva0040334B::rva0040334B, RVA 0x0040334B, same provider TU.

These ledger entries establish current row ownership only. This audit did not independently inspect or verify their compiled receiver adjustments.

## Concrete canonical-include blockers

### UpdateModule private primary view, 1024-1038

The source's UpdateModule is not the canonical full 0x20-byte UpdateModule. It is a private primary view derived from Rva00468D11Slots<32>, with primary slots 32-37 declared here, ModuleData at +4, and Object at +8. Its size contribution before the other bases is 0x0C in the source's documented layout.

The canonical pool header unconditionally includes UpdateModule.h. That defines the real UpdateModule from BehaviorModule plus UpdateModuleInterface, includes its secondary interfaces at +0x0C/+0x10, and stores scheduler words at +0x14/+0x18/+0x1C. Keeping the local full definition is an immediate class redefinition. Removing it without replacing the Horde-specific primary slot surface loses `slot32(Object *)`, `slot33(int)`, `rva0046AF85`, `rva00470DC1`, `rva00474842`, and `rva00470B21` from the base used by this file. Whole-source callers explicitly depend on that surface, including slot32 at 2562/2575, slot33 at 3423/4103, and the explicit UpdateModule cast calling rva00470B21 at 4690.

### BehaviorModuleInterface private secondary view, 1039-1043

The local class has a single virtual anchor. BehaviorModule.h defines the real 47-slot interface. Keeping the local definition collides even if the pool declaration alone is removed. The source uses it as a direct TransportContain base at 1068, so simply removing this definition also changes what that direct base means.

### UpdateModuleInterface private padded secondary view, 1044-1049

The local class has one virtual anchor plus 12 bytes of padding (`m_pad14[0x20-0x14]`). Its 0x10-byte contribution starts at owner +0x10 and carries this TU through owner +0x1F. The canonical UpdateModuleInterface has three virtual methods and no data, contributing 4 bytes; the remaining canonical scheduler data belong to UpdateModule. The two classes are not interchangeable as direct TransportContain bases.

### TransportContain composition, 1068-1075

It currently directly inherits the private UpdateModule, BehaviorModuleInterface, UpdateModuleInterface, and ContainModuleInterface; the private padding then ends it at +0x11C. HordeContain directly appends Rva0046BB38Iface11C (1237), and its first data bytes are +0x120/+0x121 (1390-1391). The whole file depends on these subobject positions, including casts back to `(UpdateModule *)this`, +0xFC builder calls, and explicit +0x20 contain-interface handling.

If the three local classes were removed while the direct-base list remained, canonical UpdateModule already contains BehaviorModuleInterface and UpdateModuleInterface, and TransportContain would acquire duplicate interface subobjects plus different offsets. If the redundant direct bases were removed too, the local Horde-specific primary virtual slots still need their proven positions preserved. Neither broader hierarchy edit is a pool-only replacement, and neither has been byte-verified here.

## Names that are not blockers from this include

An early preliminary message listed NameKeyType, UpdateSleepTime, and ModuleData as possible collisions. Full dependency reading corrects that: Module.h only forward-declares NameKeyType and ModuleData; UpdateModule.h only forward-declares UpdateSleepTime and SleepyUpdatePhase. The local enum definitions at 120-123 and 133-136, and the private ModuleData slot-21 view at 941-945, do not collide with a second full definition brought by this exact include chain. The chain similarly only forward-declares Thing, Object, AIUpdateInterface, and ContainModuleInterface, so the source's existing full private copies of these are not direct redefinitions caused by this one include. No unrelated full Snapshot, Module, ObjectModule, BehaviorModule, Rva002983DAVector, or Rva00297360Element definition was found in this source.

## Lifetimes and emitted providers

The target is used only via borrowed pointers during the three enclosing calls. No pool lifetime or storage operation occurs here, and there are no out-of-line AttributeModifierPoolUpdate definitions in this TU. The canonical header's pool constructor, destructor, virtual overrides, factory, vector operation, and fields are all declarations/storage definitions; it provides no inline pool method body that these calls would instantiate. The three external provider identities above can therefore remain unchanged at the source-signature level.

The broader canonical base chain does contain inline virtual members. Because reconciling the private hierarchy changes class definitions and base relationships, actual emitted symbol/vtable/helper deltas must be checked by the owning verification tool after a concrete edit. This read-only review makes no claim that compiler output, byte coverage, providers, or link behavior is unchanged.

## Scope closeout

No supported field rename is required for the pool class. No name was inferred or proposed. The concrete next prerequisite is reconciliation of the existing split UpdateModule/BehaviorModuleInterface/UpdateModuleInterface hierarchy while preserving the Horde primary-slot and +0x20/+0x11C interfaces. The current queue already records this prerequisite. No further tracked reads were made after completing this report.
