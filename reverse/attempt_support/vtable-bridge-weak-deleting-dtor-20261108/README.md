# vtable_bridge: weak `??_E` slots — LANDED at `b9aeebea15a` (2026-11-08)

> **Closed. Do not implement this.** The seat that held `tools/vtable_bridge.py`
> landed it the same day, in a stronger form than `vtable_bridge.patch` below:
> `slot_matches()` resolves a weak slot through `weak_resolutions()`, which
> requires the name to have exactly one recorded default, no `None` among them,
> and **no definition anywhere** — and additionally requires that copy's own
> weak record to name the same default, which the patch did not check. All three
> regression tests this file asked for exist in
> `tools/tests/test_vtable_bridge.py`
> (`test_weak_destructor_slot_resolving_to_the_retail_default_is_correct`,
> `test_weak_name_defined_anywhere_is_compared_by_its_own_name`,
> `test_weak_records_that_disagree_leave_the_default_unproven`), plus
> `test_weak_default_bound_to_another_retail_address_does_not_match`; 112 pass.
>
> `vtable_bridge.patch` is superseded and will not apply (`definitions()` now
> keeps a `weak` map beside `pointers`, so the 4-tuple it introduces is gone).
> It is kept only as the record of what was proposed.
>
> The three false-reject records that cite this file
> (`??_7ThreadClass@@6B@` 0x0087B6AC, `??_7Rva005ED152@@6B@` 0x008785B8, and
> `vtable_bridge-weak-deleting-dtor`) are stale in their reason for that
> commit's sake, not this one's. Verified 2026-11-10.

## What was proposed (historical)

Target facts: when no array `new` of a class exists, MSVC emits its vector deleting
destructor `??_EX@@UAEPAXI@Z` as an undefined weak external whose IMAGE_WEAK_EXTERN
default is the scalar deleting destructor `??_GX@@UAEPAXI@Z`; the class's vftable slot
relocates to the weak name and the linker binds it to `??_GX` unless some object defines
`??_EX` strongly.

`tools/vtable_bridge.py` `matches()` and `source_slot_mismatches()` compare only the
ledger address of the slot's own name, so such a slot never matches the retail target
even when `??_GX` is the rowed retail body. Measured on the queue published at
f9b8b46525 against the current ledger: of 5,076 bridged tables, 1,866 have such a slot
and 492 differ from retail in nothing else. Examples: `??_7ThreadClass@@6B@`
(0x0087B6AC, `??_GThreadClass` 0x00610620) and `??_7Rva005ED152@@6B@` (0x008785B8).

`vtable_bridge.patch` (against 1e48af29a7) records each pointer's weak default in
`definitions()` and lets a slot resolve through it only when no kept object defines the
weak name strongly. Not landed: `tools/vtable_bridge.py` was claimed by another seat on
2026-11-08. A landing needs a `Verifier-Change:` trailer and regression tests in
`tools/tests/test_vtable_bridge.py`: a weak slot whose default is the rowed target
matches; the same table with a strong `??_EX` in another kept object does not; a weak
slot with no aux record or a non-external default does not.
