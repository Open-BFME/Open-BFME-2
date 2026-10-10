# Canonical Apt base audit (2026-10-10)

This is evidence, not a recovery or a linking receipt. BFME2 b5f8a2c524 and committed BFME1 575ba2b04743f190f069805fbdc59936123c45da were held fixed. All three isolated MSVC7.1 objects were written under ignored build/reference975/apt-base-audit; production sources, rows, pins and headers were unchanged.

The existing AptScriptFunction.h canonical view carries original Redwood6 PDB names and virtual contracts. Its real AptValueWithHash constructor has the same masked86B instruction body as retail6D6360; AptObject constructor has the same masked43B body as6D6410. These are shape controls only: newly spelled callee/vtable relocations were not admitted or bound. In particular AptValueGC's constructor and destructor have no current defining spelling in the tested units.

Neither ordinary nor ordinary-inline hash teardown reproduces the native6D63C0/76B body: MSVC emits82B including an extra vtable store. Ordinary Object teardown emits11B. Force-inlining the hash destructor in Object emits82 masked-equal bytes, but stores the AptValueWithHash vtable; native6D6470 storesCEA264, the Object table. Thus that superficially equal body is not relocation-exact and cannot establish an owner rename or fold proof.

The current TextFormat view also calls ??1Rva006D6360@@UAE@XZ, whose old pin points to6D6470, despite that class being used as the28B hash base. Other private units use the same spelling for a different32B complete base. A blanket destructor-pin change would break those consumers. No such change was attempted.

Dedicated donor repair review: BFME1 575 includes6776aeff888361103b1824e9d6ee7b452bba2f2f, replacing Apt ClearObjectName aliases with direct defining references, and its own AptScriptFunction.cpp/AptNativeHash.cpp are unrelated release/iterator units. Direct defining references are applicable as a repair principle; the donor contains no matching canonical PC base teardown to transplant. The existing BFME2 canonical header supplies a contract lead, not a complete linked provider chain. This repair is blocked, not a verifier false reject. Keep the original exact setter1108 bank and four current base blockers; no new C++ or LINK credit.

JSON companions preserve the compiler command, canonical-header digest, sizes, masked differences and original relocation spellings. The unchanged production home remains restored.
