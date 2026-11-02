# LINK-177 blocker (3): the State map's tree helpers sit on the wrong addresses

Seat halilkkaya-lk17, 2026-11-02. Base `0ce4019422` (lk17's StateID commit on `a2e765753c`).

## What lk16 saw

The class-key respell of `insert_unique<unsigned, State*>` (pin 0x004D795B) was refused.
StateMachineDefineState.cpp compiles that body to 132 bytes, but the ledger's body there is 134 bytes.

## The 2-byte difference (fixed in a trial)

The difference is the begin() fast path. Retail (0x004D7998) pushes `0, [ebp+0xc], edi, edi`,
which is `_M_insert(__y, __y, __v)`. The unit's default STLport `_tree.c` pushes only
`0, [ebp+0xc]` and shares the tail. The vendored opt-in `/D_BFME_RETAIL_TREE_INSERT_LAYOUT`
reproduces retail's layout and gives a 134-byte body. That is the same fix FontLibraryInit.cpp got
(LINK obstacles, lk6).

`defineState-retail-tree-flags.patch` adds that macro plus `/Ireference/shims/bfmealloc`.
With it, `./build.sh` passes 2/2 rows. The unit's `_M_create_node<unsigned, State*>` also becomes
the 34-byte bfmealloc body `push 0; push 0x18; call allocator<char>::allocate; ...; call _Construct`.
That is retail 0x00382B7F byte for byte (relocations aside).

## Why the trial is not enough: two of the three identities are wrong

Retail call graph, read from the image:

- defineState 0x004D7B0F calls insert_unique 0x004D795B (call site 0x004D7B31).
- insert_unique 0x004D795B calls `_M_insert` **0x004D9C49** (call site 0x004D79BD).
- 0x004D9C49 calls `_M_create_node` **0x00382B7F** (call sites 0x004D9C71 and 0x004D9C8A).

The ledger instead says:

- **Row** `_M_insert<unsigned, State*>` is at **0x0053479F** (StateMachineDefineState.cpp). 0x0053479F
  is byte-identical to 0x004D9C49 except that it calls 0x00534743.
- **Pin** `_M_create_node<unsigned, State*>` is at **0x00534743**. 0x00534743 allocates **0x20**
  bytes and copies its value through 0x005346D9, which is `Rva005346D9Construct`, a copy through the
  Rb_tree copy at 0x00534581. So it builds nodes of a `map<unsigned, 12-byte map-like value>`, not a
  24-byte `pair<const unsigned, State*>` node.

So 0x0053479F and 0x00534743 belong to another tree, one that holds a 12-byte map as its value.
Its insert_unique bodies at 0x00534827 and 0x005348E7 call 0x0053479F; they are rowed today as the
stand-in `map<unsigned, void*>` (stlport_map_int_ptr_insert.cpp, stlport_map_int_ptr_lower.cpp), and
the `_M_insert<unsigned, void*>` pin at 0x0053479F says it is an "ICF twin of the rowed State
spelling". The State rows only byte-match because the wrong create_node pin resolves the one
relocation that differs.

## What the full repair needs (in one coherent change)

1. Apply the flag patch, so StateMachineDefineState.cpp emits retail's State helpers.
2. Pin `_M_create_node<unsigned, State*>` to 0x00382B7F with
   `fold-proof=Code/GameEngine/Source/GameLogic/AI/StateMachineDefineState.cpp`, and drop the
   0x00534743 pin. 0x00382B7F already carries many fold rows and pins of the same 34-byte body.
3. Repoint the `_M_insert<unsigned, State*>` row from 0x0053479F to an ICF row at 0x004D9C49
   (`add_match.py ... --replace-existing --icf-owner` the Image `_M_insert` row; PathDoXfer.cpp's
   `map<unsigned,int>` row there is the precedent).
4. **Re-home 0x0053479F**, or step 3 loses 136 matched bytes. Its real identity is the
   `_M_insert` of the 12-byte-value tree whose create_node is 0x00534743, and that tree is keyed
   unsigned (0x0053479F compares `jb`). StlSweepR3Rva00534743.cpp rows that create_node as an
   `int`-keyed `Rva00534743Record` tree; the key there is unproven, because create_node does not
   compare keys. Respelling it to `unsigned` and emitting `_M_insert` there (with its `_Construct`
   pin at 0x005346D9 respelled to match) would give 0x0053479F an honest owner. The
   `void*` insert_unique placeholders at 0x00534827 and 0x005348E7 then belong to the same tree.
5. Then the class-key patch can respell all three State helpers to `PAVState@@` and re-admit them
   with fold-proofs. StateMachineDefineState.cpp (233 B) should then link: today its losers are
   exactly insert_unique and create_node, "not retail's body".

Not done here: step 4 is identity work in the Rva00534743Record/Rva005344C0 sweep family
(StlSweepR3Rva00534743.cpp carries `#pragma optimize` hatches), which needs its own claim and
review. Steps 1-3 alone would either fail the 0x0053479F row or drop its coverage.
