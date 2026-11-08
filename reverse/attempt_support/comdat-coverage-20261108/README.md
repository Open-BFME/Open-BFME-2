# COMDAT copies and kept code in one image, 2026-11-08

Read-only measurements of plain-master image `436de7b90b70a1f12c9773ad9c813da4e60d2a4c`, from the 17,765 objects stored with it
(`image_objects.json`) and its map. Nothing here linked or ran anything, and nothing in the tree changed because of it. Packets:
P70, P72, P73, P74, P75, P76 and P77 in the swarm's `packets.tsv`.

**"Unreached" starts from rows and initializers only.** It means no path from a rowed function or a `.CRT$X` entry through the
relocations these scripts could follow. References through section symbols are skipped, exports aren't roots, and this link uses
`/OPT:NOREF`, so everything is kept whether used or not. It is not proof a body is dead. Check other objects' references before
deleting one, as `RTS/ScoreKeeper.cpp`'s ten bodies were checked.

## What it found

- 117,530 COMDAT functions; 1,162 with copies differing in bytes outside relocation fields; 291 with the same bytes and different
  call targets.
- **A verified row doesn't prove the image runs that row's bytes.** 258 rowed names keep another copy (23,324 B, all COMDAT), 256 of
  them from a non-owner unit. The owner's own copy is retail's for 256. For 2, the owner's own object differs and nobody has read
  why: 0x00318B1E and `addTeam` 0x0032DA4E.
- The first definer on the real command line is what the map keeps, for 29,691 of 29,691 names with several copies.
- Kept code: 9,448,862 B. Rowed 7,788,598 B. Unrowed 1,660,203 B, of which 142,376 B is called directly from a row, 94,567 B reached
  from rows, 31,439 B initializer only, 1,391,821 B unreached.
- Of 2,894 unrowed functions a matching row calls, 2,751 are byte-identical to the retail body that call reaches. 143 differ.
- One object order, simulated with initializer order and data copies frozen, keeps retail's copy for 252 of the 258, breaks no
  rowed name, has 3 conflicts and flips 222 no-row COMDATs nothing proves either way. See P75 for the other scenarios.

## Files

| File | What it holds |
|---|---|
| `comdat.tsv` | Symbols whose copies differ: copies, kept copy, retail or majority verdict, references |
| `comdat_classes.tsv` | The 303 kept copies that differ: cause class, flags, field offsets, canonical-header check |
| `comdat_family.tsv` | Kept copies naming a pool or stock allocator |
| `kept_wrong.tsv` | Names whose kept copy `link_census.py` judged `wrong`, from `link_index.pkl` at `687433edd9` joined to this image's map |
| `cover.bodies.tsv.gz` | Every unrowed kept body: source, size, reach, kind, field offsets. Gzipped: 14 MB as text |
| `cover.units.tsv` | The same by unit, with Zero Hour view, markers and registered classes |
| `cover.allocfree.tsv`, `cover.multi.tsv` | Element types with an incompatible allocate and free; names bound to several retail addresses |
| `unrowed_vs_retail.tsv` | Unrowed functions a row calls, against the retail body at that call site |
| `ordersim.tsv` | Each simulated order: which names it fixes, leaves, breaks or flips |

Scripts, run from a worktree near the image's commit, in order: `comdat_groups.py`, `comdat_classify.py`, `comdat_gaps.py`,
`comdat_family.py`, `verdicts.py`; `image_graph.py`, `image_cover.py`, `unrowed_compare.py`; `order_sim.py`, `order_extra.py`,
`order_sim2.py`.

## Limits

- **`image_objects.json` is not the link's object list.** It omits 181 objects that contributed nothing, including owners whose
  every COMDAT lost, and it lists generated objects late though `retail_vtables.obj` and `retail_initializers.obj` come first.
  `order_extra.py` reads the 181 from a worker seat's `build/match` at `32241dc040`, one stack past the image.
- The allocate-against-free check first counted the game's `_free` and msvcr71's `__imp__free` as one family, and found 5 types. Told apart, it finds 54, which is what `cover.allocfree.tsv` holds. Retail imports `free` too, so the import alone is not a defect.
- Masked means bytes outside relocation fields. A matching copy can still call the wrong body or read a wrong field of a global,
  because those sit under relocations.
- Field offsets are a heuristic over `[reg+disp]` and `add reg, imm`. It missed `isKindOf` until the second form was added, and
  retail's frame-pointer code and arithmetic `lea` inflate "extra fields".
- With no row, "majority" is weak: 258 of 556 such labels have no copy holding more than half, and P63's bad `allocate` is one.
- `unrowed_vs_retail.tsv` covers direct calls from matching rows only. Vtable-reached unrowed code with no marker, up to about
  100 KB, is compared neither here nor by `marked-sole-providers-20261108/`, which covers marked bodies through vtables.
- Call sites count relocations, not execution. Compile flags and the Zero Hour flag come from sources past the image.
- The order simulation links nothing. Moving objects moves `.data` and `.bss`, so anything working by luck of placement can
  break (P30's and P65's shape). That isn't measured.
- Flags-driven and unread, not cleared: `__copy_trivial` and the `vector<void*>` family. Of the 143 differing functions, 41
  address-named ones are unread.
