# Buddy response allocator repair

Inspected source revision: `678d949f99`, 2026-11-03.
Affected unit: `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread_Unresolved.cpp`.
Preview index: census 2026-11-03 20:03 at `8661f15284` (fetched before testing).

The picker's five missing virtual names already have current providers. A joint
preview with `BuddyThread.cpp` and `VslotSmallBodiesAM.cpp` instead found the
`__imp_?allocate@__new_alloc@_STL@@SAPAXI@Z` import and non-retail response deque
push/pop auxiliary COMDATs. This is existing placeholder/link cleanup, not a lost row.

Using `/D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc` removes
the allocator import and the growth COMDAT blocker. No pins, aliases, ledger
rows, source paths or shared headers change. `./build.sh` passes all 23 rows;
`find_declared_unmatched.py` is clean. The final [joint preview](link-preview.log)
keeps both provider units linking (3,243 and 271 bytes) and leaves only the pop
helper's COMDAT/selected-copy failures. The constructor unit remains 0 -> 0;
no census gain or complete unit clearance is claimed.

[Object and retail bytes](helper-bytes.json) distinguish the remaining issue:
the emitted pop helper is 45 bytes and calls `allocator<BuddyResponse>::deallocate`,
whereas retail at `0x00550B06` is 46 bytes with a null test and direct free call.
The growth helper has retail's 110-byte instruction shape. The standalone
`build.compile_function` byte reader still lacks its map-reserve name binding;
the JSON preserves that unresolved relocation rather than claiming a strict
standalone match. The joint link preview accepts the growth helper.

A reverted trial removed the existing declaration-only response deallocator
specialization. That emitted the retail pop helper, but broke `getResponse`
(`0x005510D3`, 102 bytes): the compiler omitted its EH-state store
`mov [ebp-4], ebx`. Keeping that declaration preserves all 23 matched rows.
Next: reconcile or supply the pop helper through its approved owner while
preserving the caller's exception contract. The address is already rowed under
`BfmeOpaque2148` in `StlportDeque2148Cleanup.cpp`; do not claim a new body or
add a second real name/pin without resolving that owner. Repeating the inline
deallocator trial alone cannot close this unit.

The commands used for current-input validation were:

```sh
./build.sh Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread_Unresolved.cpp
python3 tools/find_declared_unmatched.py Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread_Unresolved.cpp
python3 tools/link_check.py Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread_Unresolved.cpp Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThread.cpp Code/GameEngine/Source/Common/VslotSmallBodiesAM.cpp
```
