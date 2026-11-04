# dx8fvf private-view reconciliation, 2026-11-04

Starting revision: `4ee23edebd`. Scope claimed by
`yasinschroeder-codexb5`: the dx8fvf TU and its four consolidation donors.

## Evidence and repair

`name_lane.py consolidate --under Code/Libraries/Source/WWVegas/WW3D2/`
reported stale committed map data, conflicting descriptor declarations,
compiler settings, and partial routing. The merge tool rebuilt routing in
memory; no map or ledger was edited. Existing descriptor recovery evidence is
[`docs/reconstruction/dx8fvf-descriptor.md`](../../docs/reconstruction/dx8fvf-descriptor.md).
It describes the target's 96-byte layout and initializer/caller evidence;
`BfmeFVFDescriptor` remains a reconstructed name, not a recovered original name.

The first merge dry run accepted no donors. It encountered placement-array-new
redefinitions between WWLib's `always.h` and VC7.1's `<new>`, Windows handle type
conflicts, and the AngleFXInfo donor's incompatible flag override.

The TU now defines VC7.1's `__PLACEMENT_VEC_NEW_INLINE` guard before `always.h`,
which already supplies the array placement operators. Its descriptor uses the
same public class key as the declaration builder. The builder's opaque tail was
expanded to the fields already recovered in the initializer TU.
`tu_views.py` then applied one identical compiler-layout-verified declaration in
both sources, preserving the 96-byte layout and adopting the seed's
`additionalBasis` and `extensionCount` field names. It added no new private
canonical class, pin, alias or debt retirement.

## Verification

- `./build.sh` on both changed sources: **12/12 code rows**, one data row,
  fourteen string literals, and the builder's compiler-renumbered EH funclet
  verified. Both files pass `find_declared_unmatched.py`; the TU's existing
  FVFInfoClass constructor marker remains unchanged.
- `link_check.py` on both current objects: **2/2 LINKS**, preserving the
  preview's **2,697 bytes** (877 and 1,820). Index: census 2026-11-04 11:27 at
  `3a8028f34e`. Its unreferenced vector `empty()` size diagnostic remains
  nonblocking. This is a preview, not a new census measurement.
- `tu_views.py` completed its before/after merge checks: **0 -> 0 donors**.
  The builder now gets past the missing `rva001818C0` declaration and fails
  merged bytes. `Rva00181500Finish.cpp` fails the link guard on selected
  `allocator<AngleFXInfo>::deallocate`; StructureToppleUpdate retains Windows
  handle declaration conflicts; AngleFXInfoVectorInsertOverflow retains the
  flag-override conflict. No merge was applied and no source was deleted.
- No affected entries were found in the canonical class, header queue,
  Microsoft-header queue, code-identity or data-debt registers. Existing TU
  hatches and debt registers were not edited.

Next: identify which builder row loses bytes under composition, then reconcile
that compiler/include environment before retrying the merge. Preserve the
working standalone providers. The MapUtil real-link duplicate remains outside
this repair's scope.
