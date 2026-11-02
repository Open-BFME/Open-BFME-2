# Retreat UI constructor: current contract boundary

Base `e12978fd83b39565226b43fedb3bdce6cfed084a`, model GPT-6.
The picker confirmed the source/RVA claim for constructor `0x005776A7`
(160 bytes), `GameClient/GUI/Rva005776A7Ctor.cpp`. Frozen-file check passes.

The current object against published index984a4cdc4d retains zero linking
bytes. Its unresolved names are the owning-pointer destructor Rva0057702E,
the derived Rva005776A7 destructor, Rva005776A7Interface::r0 and
Gen_uwm_00429191::s0. The last carrier's vftable also differs from the
first selected copy. These are LINK-085's existing U4/L1 prerequisites.

The native primary table has the documented 26-slot translator contract;
the named retreat view still declares only slots 0..18. The constructor's
two-slot stand-ins are not a complete replacement. Native destructor
ownership and all corresponding interface overrides must be reconciled
together, rather than binding an incomplete table merely to make it link.

No source, row, signature, flag or pin was changed. No old failed trial was
repeated. The source and RVA claims were released after the inspection.
`preview.log` preserves the current diagnostic; no new coverage or gain.

`t=3 model=gpt-6 lane=R budget=30m`
