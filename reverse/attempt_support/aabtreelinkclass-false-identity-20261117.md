# `??_7AABTreeLinkClass@@6B@` @0x00878194 is a false identity (2026-11-17, seat nleigh)

Served item: link-cycle vtable-bridge repair, `??_7AABTreeLinkClass@@6B@` bridged at retail
0x00878194, carrier `Code/Libraries/Source/WWVegas/WWMath/AABTreeCullO1Inlines.cpp`
(`reverse/vtable_bridge_queue.tsv`, survey rank 605, T1 boot crash). Companion ledger rows:
the 32B "literal" vtable rows at 0x00878134/54/74/94/B4 (`reverse/data_ledger.csv` 16951-16955)
and the matched ctor row `??0AABTreeLinkClass@@QAE@PAVAABTreeCullSystemClass@@@Z` @0x005EA038
(`reverse/functions.csv` 21209, "placed by masked whole-.text search of the compiled body -
single hit").

## How the attribution was built, and where it breaks

The chain was: our ZH-shaped `AABTreeLinkClass` ctor (26B, emitted by the O1Inlines TU from the
ZH donor header) matched retail 0x005EA038 under a masked whole-.text scan (single hit); that
ctor stores vtable 0xC78194; the 32B window at 0x00878194 was therefore named
`??_7AABTreeLinkClass@@6B@`. Every link in that chain is shape-only; the semantics prove the
body belongs to the LivingWorld auto-resolve dialog's state-handler family, not to a cull link.

## Falsification evidence (all addresses reproducible with tools/retail_body.py)

1. **The ctor's sole caller is a state-machine transition, not the cull system.**
   `callers(0x5EA038)` = {0x5EA183} only. 0x5EA183 (rowed in
   `Rva005EA0F6Method.cpp` as `?rva005EA0F6@Rva005EA183@@QAEXXZ`'s sibling): `push 0x10; call
   ??2@YAPAXI@Z (0x0002FDA0, global operator new, rowed mem_ops.cpp)`; ctor(obj, this); then
   `add esi,0x14; call 0x575674` (the refcounted `Object*` setter, rowed
   `Rva00575674Set.cpp` — stores the new pointer, releases the old one through its slot0
   virtual with flag 0), then tail-jumps the new object's vtable slot1. A cull link is
   pool-allocated (`AutoPoolClass`), never global-new'd into a refcounted field, and never
   immediately dispatched.

2. **The shared slot0 deleting dtor frees with global delete and restores base vtable
   0xC780F4 — not CullLinkClass's.** Slot0 = 0x5EA28F (28B): `call 0x5EA2AB` (7B setter:
   `mov [ecx], 0xC780F4; ret`), flag test, `push esi; call ??3@YAXPAX@Z (0x0002FD60, global
   operator delete)`. CullLinkClass's own rowed ctor `??0CullLinkClass` (0x719CA0,
   gridcull.cpp) installs **0x8EFCA8**, and the CullLinkClass family's 4B tables live at
   0x8EFCA8/AC/B0... — so 0xC780F4 cannot be CullLinkClass, and any CullLinkClass-derived
   class's dtor must restore 0x8EFCA8-family pointers. 0x5EA2AB restores 0xC780F4.

3. **Retail holds exactly ONE pool-link deleting dtor — GridLinkClass's.** Our TU emits
   `??_GAABTreeLinkClass` as the 36B pool shape `56 8b f1 e8 <dtor> f6 44 24 08 01 74 xx
   85 f6 74 xx 56 b9 <Allocator> e8 <Free_Object_Memory> 8b c6 5e c2 04 00`. Scanning
   game.dat .text for that shape and four variants (tests swapped, no esi-test, inlined
   7B base dtor, member-operator-delete form) yields exactly one hit: 0x0071B470, already
   rowed as `??_GGridLinkClass@@UAEPAXI@Z` (gridcull.cpp; Allocator VA 0xE1D05C, pool-free
   fold 0x196470, vtable cell 0x8EFCAC). No second AABTreeLinkClass-shaped pool dtor exists.

4. **One owner class constructs two different sibling states.** 0x5EA0F6 (same owner class
   Rva005EA183): `push 8; call ??2` (8B object), vptr **0xC78134**, same refcounted setter,
   same slot1 tail-jump. A cull system never builds two differently-sized link classes from
   one owner; a state machine transitions between states.

5. **The slot targets are the dialog's handlers, already rowed under dialog names.**
   Retail cells (image-relative RVA): 0x878134=[5EA28F,5EA46F,B3FD0,B3FD0,50B238x3,47A699];
   0x878154=[5EA28F,B3FD0,B3FD0,5EA254,50B238x3,47A699];
   0x878174=[5EA28F,5EA266,5EACBD,B3FD0,50B238x3,50B5C6];
   0x878194=[5EA28F,5EA70B,B3FD0,B3FD0,5EA2B2,5EAEAF,5EA7A7,50B5C6];
   0x8781B4=[5EA5E3,5EA68B,...]. 0x5EA46F is rowed as
   `?Startup@ClosingStateHandler@Impl@DynamicAutoResolveDialog@StrategicInGameUI@@UAEXXZ`
   (StrategicInGameUIDynamicAutoResolveDialog.cpp); 0x5EA7A7 is that TU's `OnReinforceAnimDone`
   (`dec [ecx+0xC]` = `m_numReinforceAnimsToComplete`, whose field the same TU declares at
   +0x0C of `ShowBattleStepStateHandler`, with `m_owner` (Rva005EA183*) at +0x04 — exactly the
   ctor's stored argument). `StrategicInGameUIDynamicAutoResolveDialog.cpp` lines 273-291
   already model the 0xC78194 class truthfully: **ShowBattleStepStateHandler**, 8 slots,
   `Startup()` at 0x00878198 and `OnHitAnimDone(int,int)` at 0x008781A8.

## What retail's true AABTreeLinkClass looks like, and why it is not yet placed

ZH shape (donor `aabtreecull.h`): 16B {vptr, CullSystem, Node, NextObject}, `AutoPoolClass`
base, ctor `mov eax,ecx; mov ecx,[esp+4]; and [eax+8],0; and [eax+0xC],0; mov [eax+4],ecx;
mov [eax],<vtable>; ret 4`, deleting dtor = the 36B pool shape, vtable = a 4B cell in the
CullLinkClass 0x8EFCA8 family. None of these bodies has been found in retail under its own
address: the masked ctor scan hit the dialog state's ctor instead, and no second pool dtor
exists. The cull system itself (`AABTreeCullSystemClass::Collect_Objects_Recursive`,
`Update_Bounding_Boxes_Recursive`, `Insert_Object`, ...) is `present-unmatched` in
`aabtreecull.cpp` (markers at lines 204 ff.) — its retail bodies are unrecovered, and the link
construction lives there. Recovering that family is the path to retail's true
`??_7AABTreeLinkClass` (4B cell) and `??_GAABTreeLinkClass`.

## What the fix requires (maintainer/class-reconciliation lane)

- The data-ledger row at 0x00878194 (32B, literal) should carry the dialog family's name
  (ShowBattleStepStateHandler table, base family 0xC780F4), and the ctor row 0x005EA038 should
  be re-homed to the state class's ctor. Rows land only through the sanctioned tooling with the
  class gate; that is the same "class reconciliation before Code admission" wall the
  neighboring Rva005EA0F6 attempt recorded (`reverse/re_attempts.log` line 19831).
- After re-homing, the bridge row for `??_7AABTreeLinkClass` needs a retail address for our
  4B table — which only recovering the AABTreeCullSystemClass family can supply. Until then
  the queue row cannot retire honestly; forcing our 4B copy into the 8-slot dialog window
  would be a lie the byte probes above refute.
- Our TU's own AABTreeLinkClass bodies (26B ctor row @0x5EA038 — false hit; 36B `??_G`, 7B
  `??1`, 4B `??_7` — unrowed) stay as-is until the true retail bodies surface; they keep the
  ZH donor shape, which is evidence, not progress.

## Scratch probes used (untracked, `build/`)

`probe_pool_dtor_scan.py`, `probe_pool_dtor_decode.py`, `probe_dtor_variants.py`,
`probe_ab_starts.py`, `probe_vtable_cells.py`, `probe_family.py`, `probe_obj_syms.py`.
Note `rb.disasm` prints call/jmp targets as VA (base+RVA): `call 0x42fda0` in a listing means
RVA 0x2FDA0.
