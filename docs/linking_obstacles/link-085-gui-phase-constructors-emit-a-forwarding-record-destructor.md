### LINK-085: GUI phase constructors emit a forwarding record destructor instead of its native owner

Status: Open; record subset cleared in ordinary-preview scope; census confirmation pending. Updated: 2026-10-26; inspected revision: `2a45addda1806342ac5c52757f63be902dcd428e`.

Evidence / affected units: `GameClient/GUI/Rva0057621ACtor.cpp` and `Rva005776A7Ctor.cpp` use the same 16-byte record as `Common/Rva00576C4BDtor.cpp`. Retail cleanup entries 0x0079B3ED and 0x0079B6D6 call 0x005CD7DA directly. That complete 39-byte destructor is already rowed as `??1Wrap2000576C4B@@QAE@XZ`; it checks byte +0xC, resolves pointer +4 and invokes slots 6 and 1. The old holder emits a forwarding destructor and references the undefined `??1Rva005CD7BD`.

Completed: bind both existing record members to that rowed destructor with a declaration, retaining their inline construction and layout. All 10 constructor-unit rows and both EH graphs remain exact; frozen-file and shadow data checks pass with zero data findings. Each constructor loses U1/L1/S1. The paired 37-unit preview preserves all 28 LINKS units and adds no named blocker; the final 39-unit current-provider preview has 30 LINKS units, including both added unchanged hero providers. Raw receipts and the complete scope are in `build/c136-gui-w2/` and `build/link-report.md`.

Remaining / next check: planning remains U10/L2 and retreat remains U4/L1. Their primary native translator tables have 26 slots, while the private `Gen_uwm_00429191` and `Rva005776A7Interface` views omit the actual translator/destructor contract. Planning's secondary base is five pure-call slots, and its derived table contains five rowed adjustors; replacing only the base declaration would leave derived overrides unresolved. Reconcile the full interfaces with `UserInputTranslator`, the named phase units and the already linking destructor owners. The retreat destructor is already rowed as `Rva005770F7`; its owning-pointer cleanup is the 30-byte method at 0x0057702E. Planning's listener/base/owned-pointer cleanup spellings and duplicate constructor ownership also remain. No new function body, pin, marker, row or compiler flag was added.

Clearance: only the shared record binding is cleared in ordinary-preview scope; census confirmation pending. Neither assigned constructor now LINKS. Census confirmation: not claimed.

Current retreat recheck (2026-10-29, base `593c57cc04`, index
`85f6b7f40c`): the file is unfrozen and its current object still previews
0 linked bytes, with unresolved `Rva0057702E::~Rva0057702E`,
`Rva005776A7::~Rva005776A7`, `Rva005776A7Interface::r0`, and
`Gen_uwm_00429191::s0`, plus a differing first-copy
`Gen_uwm_00429191` vtable. The named retreat phase view declares only
slots 0 through 18, so it does not yet supply the complete 26-slot contract
needed for the constructor. No source change or census clearance is claimed.

**2026-11-02 current checkpoint (GPT-6, basee12978fd83b):** the supported
picker claims the retreat constructor, its frozen check passes, and the
current-object preview against984a4cdc4d confirms the same U4/L1 and zero
linking bytes. The 26-slot interface/destructor prerequisite above remains;
no source trial or signature/alias shortcut was added. Claims are released.
[Current diagnostic and next prerequisite](../../reverse/attempt_support/retreat-constructor-check-20261102/readme.md).
