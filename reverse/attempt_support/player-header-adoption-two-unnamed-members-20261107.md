# `class:Player` header adoption waits on two unnamed embedded types, not on padding

Measured 2026-11-07. Target facts are the private views 651 units compile today; the donor
reading at the end is marked as such and proves nothing.

## What the queue asks for

`header_adopt_lane.py accept --class Player` covers about twenty units per batch, each of which
must include `Code/GameEngine/Include/Common/Player.h`, declare no private `Player` body, and
still byte-match. None of the units sampled complies today: each carries its own layout view.

## Why it is not a per-unit edit

Take the smallest, `Code/GameEngine/Source/GameLogic/Object/Die/RefundDie.cpp`. Its view is

    class Player { public:
     bool rva002AB87D(const UpgradeTemplate*) const; bool rva002AB2D9(BfmeTab1026*,bool) const;
     char pad00[0x90]; Rva003B0D7C money; char pad98[0x3BC-0x98]; int stats;
    };

and its body calls `player->money.rva003B0D7C(refund, (Rva0039B7AD *)&player->stats, true)`.

The canonical header already declares both methods (`rva002AB87D`, `rva002AB2D9`). What it does
not have is either data member: `unsigned char m_opaque60[0x9C - 0x60]` covers +0x90 and
`unsigned char m_opaque3B0[0x6F0 - 0x3B0]` covers +0x3BC. Splitting those blocks is mechanical.

The members are well corroborated across the private views, so this is not guesswork:

- **+0x90, 8 bytes.** Sixteen units spell it `Rva003B0D7C m_money`, and thirty-five views pad to
  +0x90.
- **+0x3BC.** Five units spell it `Rva0039B7AD m_3BC`, and the RefundDie body casts
  `&player->stats` to `Rva0039B7AD *`, so the field is that object's start rather than an int.

## The actual blocker

Both members are **by value**, so the canonical header needs complete types, and no header under
`Code/GameEngine/Include/` or `Code/Libraries/Include/` defines `Rva003B0D7C` or `Rva0039B7AD`.
Adding them as they are spelled would bake two address-named placeholder classes into a header
651 units share, and `reverse/canonical_classes.csv` is what governs which classes are canonical.
That is a naming decision about two embedded types, taken once for the whole tree - not a side
effect of adopting one unit's view.

So the order of work is: give those two types real identities first (or decide, with the class
registry's owner, that an address-named canonical class is acceptable here), then the padding
split and the per-unit adoptions are mechanical.

Donor reading, unproven: Zero Hour's `Player` holds `Money m_money` and a score keeper, and its
`Money` is two 4-byte fields, which matches the measured 8 bytes at +0x90. That is a lead for the
naming lane, not evidence of a BFME 2 name - `AGENTS.md` is explicit that a same-size or
same-shape donor hit does not prove one, and an earlier row in this tree already carries a wrong
name taken from a byte-identical donor (`reverse/attempt_support/asobject-asdrawable-swapped-20261107.md`).

## Correcting an earlier note of mine

A scratchpad note from the previous batch said this item was blocked because "the canonical header
lacks members at +0x90 and +0x3BC". That was the symptom. The blocker is that the two types those
members would have are unnamed, and naming them is tree-wide work.
