# ExperienceLevelSystem hash-table prerequisite (2026-11-04)

Base: c9b195c9c0. No source paths or ledger rows move in this change.

Replace the hash-clear donor's private `_STL::pair` definition and container
forward declarations with the real STLport headers. Declare the existing
out-of-line `_List_base<BfmePod264>` destructor and clear specializations rather
than instantiating an unknown element destructor. `BfmePod264` remains incomplete;
this change makes no claim about the element's original name or fields.

Unify `Rva00289371HashTable` in Common/ExperienceLevelSystem.cpp, the hash-clear
donor, and the approved GameLogic/System/ExperienceLevelSystem.cpp TU. The
`tu_views.py --class Rva00289371HashTable --dry-run --no-merge-check` plan finds
size 0x14 in the donor: functors +0, bucket begin/end/capacity +4/+8/+C, count
+0x10. The other two prior declarations were pointer-only views. Forward-declare
the nested Node in the common view and define its value-bearing layout in the
donor, keeping STL types out of the other view declarations.

## Verification

- `./build.sh` on all three files: 53/53 function rows and 2/2 data rows exact;
  parent EH graphs, strings and imports pass. All three
  `find_declared_unmatched.py` checks are clean; `git diff --check` passes.
- Rebuild HEAD's two ExperienceLevelSystem sources normally with `./build.sh`,
  save their objects, restore the proposed declarations and rebuild. Common's
  22 COMDAT digests and the destination TU's 253 are identical before/after,
  including symbolic relocations; no COMDAT is added or removed in either.
- The hash-clear donor keeps all three original COMDAT digests and adds only
  the real pair destructor (8 bytes) and list destructor (5 bytes). The pair
  copy agrees with the existing stlport_hash_map_int_list_pod264.cpp provider
  in bytes and symbolic relocation. Retail pair bytes at 0x00288B89 are
  `83c104e913feffff`; list bytes at 0x00288B47 are `e958feffff`. Both jump to
  the existing base destructor at 0x002889A4, as the new copies do. The rowed
  clear (73 bytes) and node deleter (28 bytes) keep their code unchanged.
- `link_check.py` on the three files: all LINKS; 101 + 239 + 2832 = 3172
  authored bytes remain linked in this prediction against the 2026-11-04
  02:25 census index at 5a13f2cd61. No census or real-link gain is claimed.
  The preview retains its unreferenced `_Destroy<BfmePod264>` majority-copy
  diagnostic in the destination TU; the HEAD control rebuild proves this
  change does not alter that TU's COMDATs.
- No hash-clear code/data identity or header-queue key exists to retire.
  Existing destination header queue and hatch entries remain unchanged.
  No alias, pin, escape hatch or protected-register entry is removed.

## Merge false reject and next step

The supported `tu_skeleton.py --merge
Code/GameEngine/Source/GameLogic/System/ExperienceLevelSystem.cpp --dry-run`
still accepts no donor. For the hash-clear donor the old C2953 private pair
redefinition is gone. The new first error is C2027: undefined
`Rva00289371HashTable::Node` at its member uses. The independently compiled
source is valid. The composition parser gives both these declarations the
same key, discarding the qualified nested definition:

```text
class Rva00289371HashTable             -> ('type', 'Rva00289371HashTable')
struct Rva00289371HashTable::Node      -> ('type', 'Rva00289371HashTable')
```

Reproduce without compiling: run `composition_chunks` on
Common/Rva00289371HashClear.cpp and print `key_of(kind, chunk)` for those two
`decl` chunks. A separate tooling change must preserve the qualified type key
and add regression coverage before retrying the supported merge. No tool is
changed here and no merge is applied. The other donors retain their previously
recorded class, declaration-order and specialization blockers; see
[the prior prerequisite handoff](experience-level-merge-prerequisites-20261103-1212.md).
