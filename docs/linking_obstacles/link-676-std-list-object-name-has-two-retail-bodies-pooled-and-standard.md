### LINK-676: std list<Object*> name has two retail bodies: pooled and standard

Status: Open (sentinel part repaired). Updated: 2026-11-14; inspected revision: `f3d63e710a`.

**The crash.** Crash triage, bisect image B (`9714f328cf`, linked at master `7477c3573a`, TEST ONLY). It crashed in
`GeneralAllocator` (retail 0x000331A5) under `_free` <- `_List_base<Object*>::~_List_base` <- `AIGroup::~AIGroup` <-
`AI::destroyGroup`. Path order ran clean. Evidence: srv1 `~/bfme2-ops/seat2/build/triage/lookahead/bisect-B/finding.md`,
`crash_route.txt` and `bisect/triage/B/copies.tsv`. B kept a copy of
`??0?$_List_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@ABV?$allocator@PAVObject@@@1@@Z` that takes
the list's sentinel from `FreelistPool::pop`. The destructor that ran frees it with `_free`.

**Retail has two different `list<Object*>` families.** Measured on retail game.dat.
- *Standard-allocator family.* Base ctor 0x004EC36C (41 bytes, AIGroup.cpp's row) calls 0x0014F3C4 (alloc_proxy
  ctor), then `push 0; push 0xC; call 0x000307F0`, which is `BucketAlloc::allocate` / `allocator<char>::allocate`.
  Base dtor 0x004EC395 calls clear 0x0023DAA5, then `_free` 0x00030830. Every retail call to 0x004EC36C comes from
  AIGroup (ctor, groupEnter), HordeDispatchSpecialPower (doSpecialPower*, three), TunnelTracker (ctor) and
  Drawable 0x00278C7C.
- *Pooled family.* Base ctor 0x001EB984 (40 bytes) pops its sentinel from the Object-pointer pool at VA
  0x00DB8FEC; create_node 0x001EB9AC pops from the same pool. Retail callers of 0x001EB984: 16, in about 12 units
  (InGameUIObjectListSort, LinearCampaignAddCarryover, GameLogicInit, AIGroupRva00372571, ...); insert 0x001EBD16:
  8; push_back 0x001EC03C: 9. Both list ctors rowed in stlport_list_objectptr_insert.cpp (0x004702FB copy,
  0x001EBCC6) call 0x001EB984.

One template instance cannot have two bodies, so retail's pooled family is a different type: a list over another
allocator. The ledger already names that type for the base ctor, `_List_base<Object*,Rva001EB984PoolAllocator<Object*>>`
at 0x001EB984 (StlportObjectFreelistListBaseCtor.cpp). Our tree still spells most pooled-family code with
`allocator<Object*>`, and pins the standard names to the pooled addresses:
- `symbols.csv` binds the standard `_List_base` ctor name to 0x001EB984 ("address read from the REL32 ... at
  0x4702FB"), while AIGroup.cpp rows the same name at 0x004EC36C;
- `symbols.csv` binds the standard `_M_create_node` name to 0x001EB9AC.

**Which copy binds to what.** Byte verification masks relocations, so each copy below matches retail's bytes
whatever its call targets. At master `f3d63e710a` (objdump of the built objects):
- HordeDispatchSpecialPower.obj, TunnelTracker.obj and DrawableFlashAsSelected.obj bind the allocation call to
  `?allocate@?$allocator@D@_STL@@SAPADIPBX@Z` (retail's 0x000307F0). That is correct; Horde's own pooled
  specialization went in `05f2670d62c`, which is after image B's base.
- stlport_list_objectptr_insert.obj bound it to `?pop@FreelistPool@@QAEPAXXZ` on `g_freelistPool00DB8FEC`. It
  specialized the standard name with the pooled body (`4264bf6fc11`, 2026-11-05, which also gave Horde the same
  body). At this revision it was the only explicit pooled specialization of that ctor a source search found;
  only these four objects were inspected, not every emitted COMDAT. Retail-order selection can keep it.

Completed: stlport_list_objectptr_insert.cpp drops that specialization (this commit). Its copy of the standard
ctor is now stock STLport, binding `allocator<char>::allocate`. The unit is still 7/7 and `link_check` is 1 of 1
(217 -> 217 bytes). Code identity (shadow) now reports the unit's two list ctors, 0x004702FB and 0x001EBCC6:
their base-ctor call binds a body that is retail 0x004EC36C, while retail calls 0x001EB984. That was true
before too, hidden by the pooled body; item 2 below clears it. No source now defines a body for the standard `_List_base<Object*>` ctor other than stock;
Player.cpp only declares it. Effect, at source level: the standard name's ctor body is the stock
standard-allocator one wherever it is defined, so its sentinel matches the standard destructor's `_free`. That
includes the pooled-family lists, which still use the standard name. Not established: every emitted COMDAT, the
copy a final image selects, or a runtime pass. Node creation (item 1) is still open, so standard-list
allocation is not fully repaired.

Remaining / next check:
1. *Node creation, same pattern.* Four units define the standard-named `list<Object*,allocator<Object*>>::_M_create_node`
   as an out-of-line pooled body (`inline __declspec(noinline)`, `FreelistPool::pop`): HordeContainRva00473212.cpp,
   LinearCampaignAddCarryover.cpp, stlport_moduledatavector_push.cpp and GameLogicDestroyObject.cpp. Any standard
   list that calls create_node out of line gets pooled nodes from whichever copy the linker keeps. Retail's
   standard family inlines node creation; only the pooled insert 0x001EBD16 calls 0x001EB9AC. Check: whether
   any object emits a stock out-of-line copy of that name, and whether a standard list's clear (generic
   0x0023DAA5, `_free`) can meet a pooled node.
2. *The lasting fix is the type.* Retype the pooled family's code to
   `list<Object*,Rva001EB984PoolAllocator<Object*>>`, which is about 12 caller units plus this unit's 7 rows (new
   mangled names, so a rename per row). Then delete both standard-name pins (`_List_base` ctor -> 0x001EB984,
   `_M_create_node` -> 0x001EB9AC), so each name has one address.
3. *Two rows at 0x001EB984:* `?init@Rva001EB984Member@@QAEPAXPAX@Z` (Rva001EB984Init.cpp) and the pooled
   `_List_base` ctor (StlportObjectFreelistListBaseCtor.cpp). One is an over-claim; settle it with the retype.

Clearance: sentinel part, pending a bisect/real image built after this commit that runs AI::destroyGroup without
the GeneralAllocator fault. Node part and type: open.
Census confirmation: awaiting.

**2026-11-14 the sentinel repair landed; the retype is parked (waste lane).** `729b351200a` removed the pooled
specialization of the standard ctor name. The runtime defect behind bisect B is fixed. What remains is identity
debt: the two shadow code-identity findings on 0x004702FB and 0x001EBCC6.

Item 2 (the retype), measured and parked by the coordinator:
- *First slice: 18 sources.* stlport_list_objectptr_insert.cpp's 7 rows, plus the 17 units whose own rows call those
  addresses in retail (29 call sites, found by retail call target):
  - 0x001EBCC6: InGameUIObjectListSort.
  - 0x001EBD16: LinearCampaignAddCarryover, InGameUIUpdateFormationPreview, FormationAssistant, LightSubPoint,
    HordeContainRva00473212, HordeContainRva00475F61, MoveToFormationGroupOrder.
  - 0x001EC03C: GameLogicDestroyObject, InGameUIIdleWorker, ArmySummary_LoadArmyEntry, stlport_moduledatavector_push,
    AutoHealBehaviorPlayerScan, HordeContainIface11CSlots, HordeContainRva00475F61.
  - 0x00423890: stlport_list_gamewindow_assign_dispatch, GameWindowManagerScript.
  - 0x004702FB: HordeContain.

  12 of the 17 still spell the type with `allocator<Object*>`; the rest already use `Rva001EB984PoolAllocator`.
- *Refused route.* `rename.py function --respell --identity` refuses it. A dry-run on push_back 0x001EC03C gave
  "names no placeholder type ... an identity respell replaces a placeholder-typed spelling only". This respell goes
  the other way: the real `_STL::allocator<Object*>` becomes the placeholder `Rva001EB984PoolAllocator<Object*>`.
- *Candidate routes:* (a) a reviewed `tools/retail_identity.py` family entry for the pooled `list<Object*>`, proven
  from retail's bytes (the 0x00DB8FEC pool pops and the call graph above); or (b) a new respell route for a
  standard-allocator spelling whose retail callee is a distinct pooled instantiation.
- *Upper bound on scope.* An object-store scan (every cached variant, so stale ones too) finds 322 sources whose
  objects name at least one of the nine standard spellings: insert in 224, _M_create_node in 159, the base ctor in
  138, push_back in 83. Most are standard-family users that keep the standard names. Whichever route is chosen also
  decides whether a unit that merely names the old spelling must be prepared.

The retype waits for a tool route. Tool lane 2's current queue is the crash bisect and the initializers extension.
