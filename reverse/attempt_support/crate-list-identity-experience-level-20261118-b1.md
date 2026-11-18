# CrateCreationEntryList.cpp identity keys, 2026-11-18 (fleet agent b1, session 36)

Result: blocked. Both `reverse/code_identity_baseline.tsv` keys of
`Code/GameEngine/Source/Common/System/CrateCreationEntryList.cpp` cannot retire
until the `list<crateCreationEntry>` rows around 0x00288xxx are respelled; the
identity findings are real, not stale.

## Evidence (retail bytes, `baselines/.../game.dat`)

- 0x00288978 (44 B, rowed as `_List_base<BfmePod264>::_List_base(const allocator&)`
  in `stlport_pod_list_bodies.cpp`) is `push 0; push 0x110; call 0x307F0`: it
  allocates a 272-byte node, so its element is 264 bytes. Every copy of
  `??0?$_List_base@UcrateCreationEntry@@...` our TUs emit pushes 0x10 (16-byte
  node, 8-byte entry) and is 41 B: it can never equal retail there. The
  symbols.csv pin of that crate spelling at 0x00288978 is therefore a wrong-name
  pin, and `allowed_symbols.py` now classes the _S_sort binding as
  `wrong/extent` (the baseline says `divergent`, so `repair_queue.py retire
  identity` refuses with "new finding").
- `_S_sort` 0x00288E8D calls that constructor at offset 50, and `sort`
  0x00289139 (14 B) is `push ecx; push [esp]; push ecx; call 0x288E8D`. The
  whole family 0x002887EA clear, 0x00288849/0x00288A88 erase, 0x00288A79 swap,
  0x002889A4 ~_List_base, 0x00288B47 ~list, 0x00288E8D _S_sort, 0x00289139 sort
  is the ExperienceLevel list (the TU's own comment already says the merge calls
  `ExperienceLevel::operator<` at 0x00288621; ExperienceLevelSystem.cpp casts its
  levels to `BfmePod264`). The real crate list lives at 0x0035CAB4..0x0035CDDF
  (its `_M_create_node` pushes 16).

## What retires the keys

1. Naming lane: respell the 0x00288xxx `UcrateCreationEntry` rows (and the
   `BfmePod264` constructor row at 0x00288978) to the ExperienceLevel element
   through `rename.py function` with name_basis evidence; the pins at
   symbols.csv lines for 0x00288978 / 0x00288B35 follow.
2. Then CrateCreationEntryList.cpp instantiates `_S_sort` over the 264-byte
   element, its `_List_base` constructor copy folds onto 0x00288978 honestly,
   and the earlier fold-proof pin of `??0crateCreationEntry@@QAE@ABU0@@Z` at
   0x00466EA7 (re_attempts row, claude-opus-5-5) clears the `_Construct` key.

A decl-only suppression of the constructor would make the link bind the crate
spelling to the 272-byte body through a generated /alternatename: a wrong name
moved, not fixed. Not done.
