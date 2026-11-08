# vtable_bridge: weak `??_E` slots (proposed tooling fix, not landed)

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
