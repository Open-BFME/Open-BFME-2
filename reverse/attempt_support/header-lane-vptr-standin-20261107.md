# The header lane refused 113 units over pointers the compiler supplies

Measured 2026-11-07 against `reverse/header_queue.tsv` at 7fd11cc6a27 (6721 rows).

## Where the lane's failures sit

Grouping every queue row by its recorded failure:

| rows | failure |
| ---: | --- |
| 3083 | field renames |
|  822 | byte gate (FAIL) |
|  706 | compile C2039 |
|  250 | manual header |
| ~1860 | the rest (118 pending canonical, 106 pending byte/link, other compile codes) |

The 3083 field-rename rows break down further:

| rows | kind |
| ---: | --- |
| 1062 | a private field has no canonical field of that offset and size |
|  741 | other |
|  689 | the header's layout did not compile |
|  397 | the two disagree on the field's type at the same offset |
|   83 | include cycle |
|   50 | the unit's layout did not compile |
|   33 | anonymous nested struct |
|   28 | line splice or trigraph |

The 1062 "no canonical field" rows name 732 distinct slots, so they are a long
tail rather than a few shared gaps -- with one exception.

## The exception: a vftable pointer is not a missing field

113 of those rows refuse a unit over a four-byte field at an offset the
canonical class fills with a vftable pointer. 83 of them spell it `m_vtable`;
the rest spell it `m_vtbl`, `m_vptr`, `vtable` or `vptr`. `UpdateModule` alone
accounts for 26, then `Rva00253487Base` 9, `Drawable` 7, `UpgradeModule` 5.

`SlowDeathBehavior.cpp` shows the shape. Its private view is flat and declares
no virtual function, so it spells out all three of retail's pointers:

```
const void *m_vtable; // +0x00
const ModuleData *m_moduleData; // +0x04
Object *m_object; // +0x08
const void *m_p0C; // +0x0C
const void *m_p10; // +0x10
```

The canonical `UpdateModule : public BehaviorModule, public UpdateModuleInterface`
declares the virtuals instead, and the compiler lays those same three pointers
down at +0, +0xC and +0x10 -- the addresses `UpdateModule.h`'s target facts
already record for 0x00BF004C, 0x00BEFF90 and 0x00BFBCE4. There is no canonical
*field* at those offsets because there is nothing to name: the member goes away
with the view.

`field_renames` looked each of the view's own fields up in `flat_fields`, which
collects named data members only, and refused on the miss. That is a gap in how
the two layouts are compared, not debt in the tree.

## The fix

`vptr_offsets(name, layouts)` derives the offsets a class fills with a vftable
pointer: its own where it introduces one, and one per non-virtual base that
introduces one, at that base's offset. `class_layouts` already records `vfptr`
per class, so this needs no new compiler output. For canonical `UpdateModule` it
returns `{0, 0xC, 0x10}`.

`field_renames` now passes over a view field of pointer size at one of those
offsets instead of refusing, and records no rename for it.

Deliberately narrow:

- Only pointer-sized fields. `CommandButton::m_unmodelled_00 (+0x0, 20 bytes)`
  is still refused.
- Only offsets the canonical class really fills. A leading pointer whose
  canonical class is not polymorphic is still refused, and
  `BehaviorModule::m_p10 (+0x10)` is still refused because +0x10 is
  `UpdateModule`'s second interface, not one of `BehaviorModule`'s two.
- The check decides only whether the two layouts can be spoken about. A body
  that actually reads one of these members fails to compile, which the compile
  step answers; and the byte gate still has to pass, so a wrong adoption cannot
  come through this door.

Tests: seven in `tools/tests/test_header_field_renames.py`, three on
`vptr_offsets` (own pointer, one per polymorphic base, virtual and plain bases
skipped) and four on the comparison, including the three-pointer
`UpdateModule` shape.

## What it yields, measured

Four units sampled across four classes, each previously refused at its leading
pointer, now get past it and report their next real difference:

- `ActiveBodyValidateArmor.cpp`: `m_curArmorSetFlags (+0xF0)` is `BitFlags<17>`,
  the canonical `fieldF0` is `uint`.
- `CastleUpgradeModuleDataCtor.cpp`: `m_upgrade (+0x118)` is `int`, the
  canonical `m_upgradeToGrant` is `AsciiString`.
- `CastleMemberBehaviorCtor.cpp`: `BehaviorModule::m_p10 (+0x10)` -- a correct
  refusal, see above.
- `AIUpdateInterfacePrivateCommands.cpp`: a 20-byte field -- a correct refusal.

So none of the four adopts outright. The gain is that 113 rows will record the
difference that actually blocks them rather than a classifier artifact, which is
what the next worker needs to act on. Two of the four now point at a type
disagreement at a known offset, which is naming-lane and contract work.

Also found while measuring: `SlowDeathBehavior.cpp`'s queue row is stale. Its
probe no longer compiles at all (C1083), so that row's recorded field-rename
failure predates some header move and does not describe the unit's current
state. `class_layouts` keeps only the error codes from a failed probe
(`re.findall` with a capturing group discards the message), so the missing
include cannot be named from the queue text alone.
