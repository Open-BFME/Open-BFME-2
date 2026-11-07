# `AsObject` and `AsDrawable` are swapped: 0x00306A5E dispatches through the Drawable slot

Measured 2026-11-07. Target facts are retail tables and rowed bodies; the donor name is marked as
such. Nothing was edited: the correction needs a tool that can respell a matched row's signature.

## The two rows

Retail's Module.cpp TU family holds two 16-byte null-guarded virtual dispatchers, consecutive and
immediately before the two module constructors - the order Zero Hour's `Module.cpp` declares
`AsObject` and `AsDrawable` in:

    0x00306A4E  16B  ?Rva00113BA0@@YAHPAVGenSlot08@@@Z        S2NullCheckedTailDispatch.cpp
    0x00306A5E  16B  ?AsObject@@YAPAVObject@@PAVThing@@@Z     Module_AsObject.cpp
    0x00306AA7 108B  ??0ObjectModule@@QAE@PAVThing@@PBVModuleData@@@Z
    0x00306B19 108B  ??0DrawableModule@@QAE@PAVThing@@PBVModuleData@@@Z

## Which slot each one calls

- `0x00306A4E`'s view is `class GenSlot08 { virtual int slot00(); virtual int slot04(); virtual
  int slot08(); }` and the body dispatches through `slot08()`, the third virtual, so **+0x8**.
- `0x00306A5E`'s view (`Module_AsObject.cpp`) declares four placeholder virtuals before
  `asObjectMeth`, so its call is the fifth slot, **+0x10**. The unit's own header comment says so:
  "the virtual at slot +0x10".

Both rows are `matched`, so those offsets are retail's.

## What those slots return

`Code/GameEngine/Source/Common/Thing/thing.h` records, as target facts, that Thing's table has
eight slots, that Object's table `0x00BFC300` overrides slots 1-2 and Drawable's `0x00BFB0B4`
overrides slots 3-4 with `0x0047A6A9` (`mov eax,ecx; ret`), "so slots 1-2 return the Object and
3-4 return the Drawable", and it places non-const `asObjectMeth` at slot 2 (**+0x8**) and
non-const `asDrawableMeth` at slot 4 (**+0x10**).

So:

- **0x00306A4E** calls +0x8, the Object slot. It is `AsObject`, and it is still a placeholder.
- **0x00306A5E** calls +0x10, the Drawable slot. It is `AsDrawable`, and it currently carries the
  name `AsObject`.

## Why the wrong name is there

The row's own note is `BFME1 byte-identical donor; b1 0x00113BC0`: the name came from the BFME 1
reconstruction, not from BFME 2 evidence, and the placeholder beside it is named after the
adjacent BFME 1 address `0x00113BA0`. Byte-identical donor bodies do not prove which of a
consecutive pair is which, and here the slot the body dispatches through contradicts the donor
name. `AGENTS.md`: "Exact bytes, a placement or a same-name hit do not prove a donor name."

## Why it is not fixed here

Both corrections change the mangled signature, not only the identifier, and no tool will do that
to a `matched` row:

    rename.py function --rva 0x00306A5E --old '?AsObject@@YAPAVObject@@PAVThing@@@Z' \
        --new '?AsDrawable@@YAPAVDrawable@@PAVThing@@@Z'
    -> refused: changes the mangled signature beyond the identifier
       (identifier-only rewrite is ?AsDrawable@@YAPAVObject@@PAVThing@@@Z)

The suggested identifier-only spelling keeps `Object*` as the return type, which would be a second
wrong name rather than a fix: a free function's MSVC name carries its return type, and this one
returns the Drawable. `add_match.py --replace-rva` is the documented path for a conversion whose
name really changes, but it "accepts scaffold rows only" and both of these are matched.

This is the same missing capability recorded for the ModelConditionFlags width rows in
`reverse/attempt_support/modelconditionflags-width-20261107/`, reached from an unrelated
direction: a matched row whose correct name differs from its current one by more than an
identifier has no landing path today.

## Order of work when that exists

1. `0x00306A5E` -> `?AsDrawable@@YAPAVDrawable@@PAVThing@@@Z`, with `Module_AsObject.cpp` renamed
   and its view's placeholder virtuals re-counted to reach +0x10 as `asDrawableMeth`.
2. `0x00306A4E` -> `?AsObject@@YAPAVObject@@PAVThing@@@Z` (the name is free only after step 1),
   with `S2NullCheckedTailDispatch.cpp`'s `GenSlot08` view replaced by a Thing view whose
   `asObjectMeth` lands at +0x8.
3. Both units can then take canonical `thing.h`, which is what the `class:Thing` header-adoption
   batch needs from them: `Module_AsObject.cpp`'s four placeholder virtuals exist only to push the
   call to +0x10 under the wrong name, and canonical Thing already puts `asDrawableMeth` there.
