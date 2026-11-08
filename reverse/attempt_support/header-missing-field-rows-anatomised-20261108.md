# The "no canonical field" rows, anatomised against the class contracts

Measured 2026-11-08 over `reverse/header_queue.tsv` (6496 rows). 1027 of them
fail `field_renames` with

    Class::field (+0xN, S bytes) has no canonical field of that offset and size

`header-lane-vptr-standin-20261107.md` counted these as 1062 rows naming 732
distinct slots and called it a long tail. That was true but not useful: it did
not say *how* the two layouts disagree, and the answers turn out to be different
kinds of work. `reverse/class_contracts/<Class>.json` already records every
canonical field's offset and size, so the shape of each disagreement can be
counted without compiling anything.

| rows | how the view's field sits against the contract |
| ---: | --- |
| 518 | nothing starts at that offset at all |
| 195 | a contract field of exactly that offset **and** size exists |
| 104 | one contract field starts there, smaller, and only padding follows inside the view field |
| 115 | the view field spans 2 or more contract fields |
|  51 | the view field is smaller than the contract field at that offset |
|  18 | the class has no contract |

Read as work, that is three groups and one dead end.

## 195 rows: the contract already has the field

A contract field of exactly that offset and size exists, yet `field_renames`
found none. 99 of the 195 are the vftable pointer: the contract records
`__vfptr` at +0 as a 4-byte field, while `flat_fields` collects named data
members only, which is precisely the gap
`header-lane-vptr-standin-20261107.md` closed. That leaves **96 non-vptr rows**
-- `GameSlot` 16, `Drawable` 10, `ScriptList` 9, `INI` 8, `SidesList` 6,
`UpgradeTemplate` 5 -- where the contract knows a field the compiled header does
not spell, or the row predates the header gaining it. Only a re-run separates
those two, and a re-run is cheap.

## 104 rows: the view swallowed the padding

One contract field starts at the view field's offset, it is smaller, and no
other contract field starts inside the view field's extent. The view spelled one
canonical member and the padding behind it as a single word.

`UpgradeMux` is the worked case. Retail's layout, from the header's own target
facts and the contract, is a vptr at +0, `bool m_upgradeExecuted` at +4 and
three bytes of tail padding at +5, eight bytes in all. The facts say "byte" four
times over -- the constructor clears byte +4, slot 0 reads byte +4,
`setUpgradeExecuted` copies an argument byte to +4, `upgradeMuxXfer` transfers
byte +4. Five of its units spell that as `m_executed (+0x4, 4 bytes)`, so
`field_renames` looks for a 4-byte canonical field at +4, finds a 1-byte one and
refuses. The canonical header is right and the views are wrong, but the refusal
is still a classifier artifact: it reports a missing field where the real
difference is a width.

Across the queue the pattern reaches 41 classes, the largest being
`DataChunkInput` 9 units, `GameWindow` 7, `ControlBar` 4, `PlayerList` 4 and
`W3DShadowManager` 4.

Whether to allow it is a narrower question than the vptr case was, and the
answer is not obviously yes. A vptr member has no canonical counterpart by
construction and no body can legitimately read it. A padding-swallowing member
*does* have a counterpart, and a body that assigns it writes four bytes where
the canonical field takes one. Renaming `m_executed` to `m_upgradeExecuted`
changes the width of that store, and the byte gate is what would catch it. So
the allowance would have to be exactly: rename to the one canonical field the
extent covers, and let the byte gate decide, as the vptr allowance does. It
should land with its own tests and a `Verifier-Change:` trailer, and 104 rows is
the ceiling on what it can return, not a forecast.

## 518 rows: nothing starts at that offset

Half the population, and no mechanical lane. The view names a member at an
offset the canonical class does not begin a field at, which is a real layout
disagreement needing per-class evidence work.

## 115 + 51 rows: spanning and undersized

A view field covering 2 or more canonical fields (115 rows, up to 46 fields in
one case) is an opaque block, and the 51 undersized ones are the inverse. Both
want contract work, not a classifier change.

## Caveat on the method

This counts the view against the **contract**, not against the compiled
canonical header, and `field_renames` reads the compiled header. The contract is
the evidence register and can be ahead of the header or behind it. So every
figure here is a classification of the recorded failure text, not a prediction
of what a re-run does -- which is exactly why the 195 group is worth re-running
rather than reasoning about.

## Re-ran the 195 group: 2 of 85 (2026-11-08)

The 195 rows whose contract records a field of exactly the view field's offset
and size were re-run through `adopt`, after removing the 99 vptr rows the
earlier fix covers and the rows under another seat's claim. 85 units in 28
cohorts: **2 PASS, 83 FAIL**.

Both passes were `UpgradeTemplate` (`AIGroupBroadcastOrders.cpp`,
`ObjectRva00294ADD.cpp`), applied, byte-verified 2/2 and retired.

So the hypothesis that these rows were stale is mostly wrong: the contract knows
a field the **compiled header** does not spell, and the row stands. The failures
re-report the same refusal against a different field of the same class, which is
what it looks like when the header is genuinely behind its contract:

| units | refusal |
| ---: | --- |
| 4 | `TreeHintOpaque0043671B::m_slots` |
| 4 | `INI::m_data` |
| 3 | `ScriptList::m_firstGroup` |
| 3 | `Rva00330757Member::m_items` |
| 2 | `SidesList::m_bases`, `ScriptList::groups`, `ModuleInfo::m_info`, `INI::storage`, `GameSlot::m_hero`, `Drawable::m_354` |
| 3 | `no private view found` |

That makes this group **contract-to-header work**, not classifier work: the
evidence exists and the canonical header has not caught up with it. It is also
the group with the clearest next step, because the contract already names the
field, its offset and its size.

Two incidental findings from the sweep:

- Three units report `no private view found`, so their queue rows name a class
  the unit no longer declares -- the same population as the 81 unretirable rows
  in `header-lane-vptr-standin-20261107.md`.
- One refusal printed an absolute path from the reference checkout
  (`/home/dave/.../reference/open-bfme-1/...`) inside a field-rename message.
  Harmless to the verdict, but a message that embeds a local absolute path is
  not reproducible between checkouts.
