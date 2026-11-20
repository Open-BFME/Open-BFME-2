### LINK-694: river primary table needs native-bound inherited identifier normalization
Status: Blocked. Updated:2026-11-18; inspected revision:9dcb0c7478c.
Evidence / affected units: Rva0030C1FCOwnerCtor.cpp/Notifiers.cpp/Dtor.cpp,
base8691EC7slots versus river8088FC13slots. [Native proof and handoff](../../reverse/attempt_support/river-primary-override-proof-20261118-root20.md).
Completed: no source change;46/46control rows and2EXACT lifetimeEH. Evidence-only
derived-identifier normalization plus qualified base call preserves all34runtime
sections after the one intended mangled-symbol mapping. Generic rename refuses
the inherited placeholder identifier, so no rename/adoption was admitted.
Remaining / next check: a general native-slot/caller-bound mechanical override
normalization path, then all inherited broadcasts, pure int-slot6, false-base/true-river
slot1 and full class/provider/lifetime reconciliation. Do not add aliases or invent
readable naming claims to evade the guard;538099 is a nonvirtual helper.
Clearance: none for13-slot retirement; current source still emits four primary slots.
Census confirmation: next scheduled real bridge absence required; not claimed.
