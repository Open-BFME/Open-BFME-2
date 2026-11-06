# Sorting renderer list ownership, 2026-11-06

Read-only review, current HEAD `baa896fe56`. No source/ledger edits, claims,
builds, network or naming proposals. The two normal renderer COFFs' dependency
receipts match their current source MD5s. Their existing byte matches do not
establish shared runtime storage.

## Verdict

This is a real state-ownership problem, together with obsolete preferred
identities and incomplete placeholder storage. It is not fixed by changing
`data_ledger.csv`'s preferred names. There are **three independent private
list-storage definitions**, plus two separately defined four-byte vptr owners.
The root's five DX8-global repairs do not resolve these list findings.

## Current providers and consumers

* `SortingRendererBFME1.cpp:380-381` defines two storage-class-3 COFF symbols,
  `_sorted_list` and `_clean_list`, each twelve bytes. Their first dwords have
  relocations to `??_7?$DLListClass@VSortingNodeStruct@@@@6B@`; head/tail are zero.
  `Flush_Sorting_Pool` 12E8C0, `Flush` 12F190, `Insert_VolumeParticle` 130410
  and `BfmeSortingDispatchAt0012FE00::Insert` 12FE00 reference these objects.
* `sortingrenderer.cpp:157-158` defines a second private pair with the same
  COFF spellings, also twelve bytes each. `Deinit` 130A20 references this pair,
  with operands at object+4/+8. The linker does not coalesce storage-class-3
  symbols merely because their text names match another object's locals.
* `SortingNodeStructDtor.cpp` defines a third private `_clean_list`: an
  **eight-byte** head/tail-only object. Rowed `Get_Sorting_Struct` 12FD80
  references its offset zero. The relocation mapper assigns this fragment
  RVA 9B6210, i.e. native complete clean-list+4. The ledger note claiming that
  a shared `_clean_list` spelling shares storage is not true of the real link.
* `Rva007B6880Thunks.cpp:2032,2160` separately defines `void *g_00DB6200`
  and `void *g_00DB620C`. Each is only the native vptr word, not a complete
  list. The data index still calls these identities unowned. Neither has a
  data-row/converged-row establishing complete backing storage.

## Target facts

Retail VA DB6200 and DB620C each contain exactly the observed twelve-byte
prefix `[0x00BD23B4, 0, 0]`. The next distinct data starts at DB6218. Thus the
ledger's four-byte extent for 9B620C is an artificial split at the independently
referenced head field 9B6210, not evidence for a four-byte list.

Retail vtable BD23B4 has the one observed slot 52D780. Constructor RVA 12D750
is 17 bytes: install that vptr and zero +4/+8. Complete destructor 12D770 is
7 bytes: restore that vptr. Scalar deleting destructor 12D780 is 31 bytes:
restore vptr, optionally delete, return this. Current owners are placeholder
`Rva0012D750` in `Q1ZeroingConstructors.cpp` and `Rva0012D780` in
`InlineDtorDeletingDtorsC03.cpp`. These facts corroborate the existing
`DLListClass<SortingNodeStruct>` layout; byte equality alone does not approve
renaming both placeholder classes or their vtable.

The two 11-byte routines 7B7090/7B70A0 restore the list vptrs. They are
**atexit cleanup routines**, not missing head/tail startup initialization:
12-byte initializers 7ACD90/7ACDA0 register those respective addresses via
atexit. Those initializer rows live in
`Rva007AB85CAtexitInits_Rva007ACD90.cpp`. Both renderer objects also emit their
own private-list cleanup contributions, so merely retaining all existing
initializers while adding shared objects needs a provider/CRT audit.

## Existing failed hypotheses — do not repeat unchanged

1. `reverse/attempt_support/sorting-renderer-shared-state-20261029-round2.md`
   and its saved patch made complete lists external and added the missing
   vptr prefix to the eight-byte reader. Five of 52 rows failed: Deinit,
   Get_Sorting_Struct, both Insert entry points and Flush. Losing private
   storage changed null checks and register scheduling. Scalar-only sharing
   was retained; the list experiment was reverted.
2. `reverse/attempt_support/sorting-list-owner-cast-20261105-codexb/README.md`
   tried the narrower allowed address-cast route through existing void-pointer
   owners, including local list references. It retained 10/11 renderer rows;
   Deinit gained redundant null checks. The owners remained undersized even
   if the cast had matched. No baseline key was retired.

## Supported prerequisite / smallest next step

The required final invariant is one complete twelve-byte object per native
list, every relevant consumer referencing that object (including clean+4),
and one truthful constructor/destructor/vtable/CRT identity. Keep both the
native complete extents and the private-visibility codegen contract in scope.
Do not add aliases, pointer-only substitute owners or a second name at either
address, or retire the current keys while distinct private states remain.

There is currently **no independently supported tiny source fix**: the obvious
shared-global/cast approaches were already tested and failed. A new source-level
compiler/alias-visibility explanation must first preserve the five known
failures while completing storage. Alternatively, approved TU recovery can
retain native TU-private lists, but its prerequisites are substantive:

* The committed TU map approves Deinit, Insert_To_Sorting_Pool, Release_Refs,
  Flush_Sorting_Pool, Flush and Insert_VolumeParticle for lower-case
  `sortingrenderer.cpp`. These approve a useful partial recovery path.
* The BFME1 file is mixed: DX8Wrapper bodies belong to dx8wrapper.cpp; other
  rows are unassigned or proposed elsewhere. A wholesale merge is not approved.
* Get_Sorting_Struct 12FD80 is only **proposed** for SortingNodeStruct.cpp;
  Insert 12FE00 is also only **proposed** there, with conflicting/noncontiguous
  naming evidence. Merging only currently approved renderer rows would leave
  these two active readers/inserters on private fragments.
* Constructor/destructor/cleanup/initializer addresses above have no TU
  approval in the committed map. Refresh the in-memory map before any move;
  these observations are not permission to hand-move their rows.
* The two renderer SortingNodeStruct views differ (sphere/Vector3 tail versus
  float tail, and different state/header views); the dedicated lifetime unit
  supplies the native 0x2A8/16-texture view. Reconcile against target layouts,
  not by copying the seed's donor view into every source.

No list/global/class name approval or canonical SortingRenderer/SortingNode/
DLList registration was found in the current naming/canonical registers.
`sorted_list`/`clean_list` are useful existing donor identifiers, not a newly
established original BFME2 symbol proof. The eventual identity change should
use the supported naming/data-owner workflow after the source-level proof;
no proposal was created in this review.

Before choosing this as a repair, claim the complete consumer/provider scope
and record the above blocked prerequisite in the obstacle/handoff path. No
dedicated current SortingRenderer obstacle entry was found; the historical
attempt handoffs above already preserve the failed hypotheses.
