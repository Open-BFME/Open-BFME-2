### Drawable destructor canonical Module and deleting ABI (2026-10-30)

Cleared for DrawableDestructor: use canonical Module, projecting only slot0's
MSVC scalar-deleting ABI through a declaration-only view. Flags0 destroys and
returns the allocation; native 0x00279485/487/488 dispatch, push returned EAX
and free separately. Preserve that returned pointer rather than assuming the
Module subobject is the allocation. The complete 633-byte parent, all 12 rows,
EXACT EH graph, 24 code definitions and every non-debug runtime section and
reference are unchanged. No table, body, thunk, pin or alias is added. Owning
Module acceptance retires the last queued Module item; preview preserves
LINKS/643 bytes. Other Drawable header debts and census confirmation remain.
[Native caller and deleting-destructor witness](../../reverse/attempt_support/drawable-canonical-module-delete-abi-20261030/README.md).
