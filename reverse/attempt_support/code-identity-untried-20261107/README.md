# The code-identity register's unworked sources, diagnosed (2026-11-07)

`reverse/code_identity_baseline.tsv` holds 96 wrong or divergent code bindings over 57
sources, in shadow mode. 14 of those sources carry no mention in `reverse/re_attempts.log`
under their own path, so they looked unworked. This is a read-only diagnosis of all 14, one
reviewer per three or four plus one I took myself. Nothing was changed: no source, ledger,
pin or baseline line, and no claim taken.

`diagnoses.json` holds the per-source records with addresses, pins and prior-work links.

## First, a correction to how "unworked" was measured

Searching `re_attempts.log` for the source path understates prior work, because the log
keys its entries on **symbols and addresses**, not on source paths. Three of these 14 turned
out to have directly relevant recorded attempts that a path search missed - lines 85034,
100738 and 101227, each naming the symbol or the address rather than the file. Anyone
repeating this survey should search the log for the symbol and the retail target too.

## What the 14 actually are

- **stlport-template, 6.** A unit spells a private or donor-named class for what is really
  a shared STLport container instantiation, and reaches the shared body through a pin.
- **pin-only, 4.** The symbol has no owner row at all and exists only in `symbols.csv`.
- **misnamed-row, 1.** The row name is wrong for the body at that address, which another
  row already owns.
- **other, 2.** A compiler atexit-cleanup name, and an empty-ctor fold needing a byte check.
- Plus the one I diagnosed: `Bfme5FindAndErase.cpp`'s private `BfmeVecAG::bfmeErase`, pinned
  to `0x001FF51F`, which is an ICF-folded STLport `vector<T*>::erase` already rowed under
  several instantiations, canonically in `stlport_vector_voidptr_opt.cpp`.

So the dominant mechanism is the one LINK-626 named for destructors: a private spelling
bound to a shared retail body by a pin alone. The census resolves it; the real link does not
read pins.

## The cases where the fix is a type correction, not a rename

This is the useful part, and it was not obvious before the survey. Three of these are
*wrong models*, and renaming anything would entrench the error:

- **W3DModelDraw.cpp** - the three rows call a `__copy` whose real owner handles a 24-byte
  element (`int words[6]`), while the unit's `BitFlags<117>` view is 16 bytes.
  `re_attempts.log:101227` already recorded the cause: retail's `__copy` strides 0x18. The
  element must be respelled to the real 24-byte `BitFlags<N>`; `N` in 161..192 is an
  unverified estimate and needs its own evidence. The `?clear` and `?erase` rows themselves
  are correctly rowed - only their callee binding is wrong.
- **Rva00654130PointerMapErase.cpp** - the pin binds a `void*`-key `_M_find` to a body
  owned by nine int-key `_M_find` rows, and retail's callee is the *signed* int-key find
  (cmp/jl). The source's key model is wrong, not its spelling. `re_attempts.log:85034`
  records that a `map<int,void*>` trial then resolves through another pin to an *unsigned*
  body, so the `less<unsigned>` family has to be reconciled first.
- **IntFloatMapSubscript.cpp** - `re_attempts.log:100738` records the float-map insert
  differing from the int-int insert at +0x6b, so the fold these pins rely on is unproven and
  the map's value type may be misidentified. Settle that before touching the bindings.

## Already owned, and lower priority

- `ProductionPrerequisite.cpp`'s copy-ctor pin is the blocker LINK-182 already plans to
  clear by readmitting the PerTurnStats instantiations. `W3DAnimationInfoVectorInsert.cpp`
  is blocked by LINK-198 plus a naming decision. Neither should be duplicated.
- `Rva00803890FeslDtor.cpp` is **census-only**: the unit defines its own base body in-unit,
  so the real link is unaffected and only the census records a wrong binding. That makes it
  lower priority than the rest, and the distinction is worth drawing before anyone spends a
  batch here.

## The established technique, already written down

`stlport_vector_voidptr_opt.cpp` documents how this family is solved where it has been
solved: explicit `__declspec(dllimport) __forceinline` specializations for `begin`, `end`,
`size` and `operator[]`, plus a file-static `max` overload, specifically so the TU "emits no
external COMDAT" for those helpers. Its header comment also explains why the body lives
there at all - the image holds the frameless 34-byte `erase`, not the /Od unit's 84-byte one.

That technique suppresses helpers a unit should not own. It does **not** apply where retail
genuinely calls the shared body: `Bfme5FindAndErase.cpp`'s rowed `bfmeRemove` has a REL32 to
`0x001FF51F` at `0x0042119D`, so that call must stay a call, and the repair is to make the
unit use the real container type rather than to inline anything away.

## Follow-up: the W3DModelDraw element, and why the recorded next step is wrong (2026-11-07)

`re_attempts.log:101227` ends with "Next: establish the real bit count
(ModelConditionFlags count) and respell the view." That step cannot work as written, and
this records why before anyone spends a batch on it.

**What the 24-byte stride is measured against.** The body at `0x00626EF0` is rowed as
`__copy<Rva00626EF0Element*>` (96 B, PartitionManagerImpl.cpp), and that element is literally
`struct Rva00626EF0Element { int words[6]; }` - 24 bytes, with an explicit
`_STL::__copy<Rva00626EF0Element*,...>` instantiation in the same unit. The 0x18 stride and
the `idiv`-by-3 reciprocal `0x2AAAAAAB` the earlier note measured are consistent with that.

**ModelConditionFlags is spelled three different widths in this tree**, and none is 24 bytes:

| spelling | storage | bytes | where |
|---|---|---|---|
| `BitFlags<117>` | 4 dwords | 16 | W3DModelDraw.cpp, ThingTemplate.h, Rva0033DCD1.cpp |
| `BitFlags<304>` | 10 dwords | 40 | BitFlags304GetSingleBitFromName.cpp, which asserts "This BFME2 binary's ModelConditionFlags is BitFlags<304>" on retail evidence: 0x000B42CA references the literal "FRONTCRUSHED", an entry of ZH's `ModelConditionFlags::s_bitNameList[]`, and its matched sibling BitFlags304BuildDescription.cpp reads the same extern array as `ModelConditionNames` |
| `Rva00049BE8` | `UnsignedInt m_bits[19]` | 76 | typedef'd `ModelConditionFlags` in W3DDisplayGatherAnimationDebuggingInfo.cpp |

So "establish the real bit count and respell the view" does not reach a 24-byte element under
any of these: 16, 40 and 76 all miss it, and **no `BitFlags<N>` width used anywhere in the
tree is 6 dwords** (the widths in use are 11, 15, 17, 21, 69, 101, 104, 116, 117, 128, 154,
218, 304, 591). A bit count alone cannot explain the stride.

**A hypothesis that does fit the arithmetic, not confirmed.** The element may not be a bare
flag set but a pair. W3DModelDraw.cpp instantiates
`pair<BitFlags<117> const, ModelConditionInfo const *>` (line 162), and a 20-byte flag set
plus a 4-byte pointer is exactly 24. `BitFlags<154>` is 5 dwords, i.e. 20 bytes, and already
exists in this tree. That would make the vector the SparseMatchFinder's cache of
(flags, matched-info) pairs rather than a vector of flags, which is also why our
`vector<BitFlags<117>>` spelling binds its `__copy` to the wrong body.

This was not confirmed. The `SparseMatchFinder` declarations in
`Rva0033DCB8.cpp`, `Rva0033DCD1.cpp` and `stlport_rb_tree_0033c646_insert.cpp` are stubs -
`int m_dummy`, `unsigned int m_bits`, `char m_pad[0x370]` - so none of them settles the
cache's element type, and the pair hypothesis needs its own evidence from retail.

**What to settle first, in order.** Which of the three ModelConditionFlags widths is right
for this binary is a tree-wide question, not a W3DModelDraw one: it affects every unit that
spells these flags, and two of the three spellings cite evidence. Until it is settled,
respelling W3DModelDraw's template argument would be guessing at a number, and the three
baseline rows should stay as they are.
