# MineshaftPortalBehaviour TU consolidation, 2026-11-04

Inspected source: `0ebd1b81e8` (link-step declaration repair).
Approved destination:
`Code/GameEngine/Source/GameLogic/Object/Behavior/MineshaftPortalBehaviour.cpp`.
No source paths or ledger rows were moved in this pass.

## Completed prerequisite

`MineshaftPortalBehaviourLinkStep.cpp` now uses STLport's actual tree definition,
the seed's portal views and the seed's manager declaration, including its two
base classes. The lookup still calls the existing signed-key `_M_find<int>`.
This replaces the donor's conflicting private `_Rb_tree` definition and flat
manager view without changing its row at RVA `0x00373158`, size 115.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Behavior/MineshaftPortalBehaviourLinkStep.cpp`:
  1/1 exact.
- `find_declared_unmatched.py` passed for the seed and all four donors before
  the trial, and for the changed donor after the repair.
- `link_check.py` on the changed donor: LINKS, 115 -> 115 bytes, using the local
  census index dated 2026-11-04 17:56 at `8c757ea0db`. Two unreferenced iterator
  COMDAT diagnostics remain; neither is a blocker. This is a preview, not a
  new census or a claim of linked-byte growth.
- Commit hook passed byte verification, ledger checks and its shadow checks.

## Current composition blockers

`tu_skeleton.py --merge <destination> --dry-run` rebuilt the TU map in memory.
Its final trial accepted no donors and left source and ledger paths unchanged:

| Donor | Final trial result |
| --- | --- |
| `MineshaftPortalBehaviourLinkStep.cpp` | Now compiles, but fails bytes. |
| `MineshaftPortalBehaviourCtor.cpp` | C2995: duplicate `allocator<int>::deallocate` specialization already in seed. |
| `Code/GameEngine/Source/Common/Rva0037381CDtor.cpp` | Redefines `SubsystemInterface` through the private shim versus the seed's library header. |
| `Code/GameEngine/Source/Common/MineshaftPortalNetworkManager.cpp` | Byte comparison passes composition, but link guard refuses changed selected manager vtables for `Snapshot` and `SubsystemInterface`. |

The link-step's former compiler conflicts were `_Rb_tree` redefinition and
incomplete manager/portal declarations. Those are removed by the published
prerequisite. They must not be confused with a successful merge.

The link-step donor has `/Oy-`; the seed normally omits the frame pointer and
has an existing scoped frame-pointer pragma for other methods. Inspection of
the final trial objects found this link-step entry:

```text
push ebx
push esi
push edi
lea eax, [esp+0x14]
push eax
add ecx, 0x10
```

Retail starts:

```text
push ebp
mov ebp, esp
push ebx
push esi
push edi
lea eax, [ebp+0x0c]
push eax
add ecx, 0x10
```

This establishes the frame discrepancy; it does not prove that changing the
frame state alone would make the composed function exact. No new pragma hatch
was added. Next check: reconcile the existing optimization scope with the
donor's required frame, preserving every seed row and delayed template body.
Separately reconcile the manager's actual virtual slots before trying its
constructor merge again. Do not bypass the selected-vtable guard.

The behavior constructor also has a previously documented canonical-module
interface problem; see
`docs/linking_obstacles/canonical-module-header-caller-adoption-hb1-2026-11-01.md`.
This pass does not clear it, retire header debt or remove any link-wide alias.
