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
