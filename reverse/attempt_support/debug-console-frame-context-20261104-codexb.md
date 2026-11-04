# Console TU header frame context

Inspected f62d096cd88f9dbe355601a0cad7e3a4ba99809c on 2026-11-04.
Scopes: debug_io_con.cpp, DebugIOConConstructor.cpp and
DebugIOConDestructorThunk.cpp under Code/Libraries/Source/debug/.

The current approved merge has 13 rows and no mixed/refused donor. Before
this change, tu_skeleton.py --merge ... --dry-run accepts neither donor:
both report a retail conflict for ??_GDebugIOInterface@@MAEPAXI@Z as well
as a DebugIOCon vtable conflict. Previous identity trials are documented in
[the round-three handoff](debug-console-identity-20261029-round3.md).

## Verified prerequisite

The seed compiled _pch.h under /Oy-, before its existing optimize("y",on)
pragma. _pch.h brings in the inline interface destructor. Move that existing
pragma before _pch.h, retaining optimize("y",off) before the out-of-line
console methods. debug_io_flat.cpp already uses this header frame context.
No pragma, pin, alias, class view, compiler flag or register entry is added.

./build.sh Code/Libraries/Source/debug/debug_io_con.cpp passes 6/6 rows,
13 imports, three string references and its renamed-label EH mapping.
find_declared_unmatched reports all definitions accounted for (the existing
two present-unmatched definitions remain). data_check reports zero findings.
The ordinary link preview reports LINKS, 958 -> 958 authored bytes, against
census 2026-11-04 17:56 at 8c757ea0db.

The repeated merge dry-run removes the interface deleting-destructor conflict
from both rejected donors. Both remain rejected for ??_7DebugIOCon@@6B@
(first-copy / another-unit-copy conflicts). No merge is applied, no source
path moves, and no census, ownership, linked-byte or debt reduction is claimed.
The retained source change is a prerequisite for the merge, not its completion.

## Remaining provider evidence

Retail's constructor and destructor install DebugIOCon table VA 0x00BC15F4.
Its seven entries are:

| Slot | Target VA |
| --- | --- |
| 0 | 0x00440E20 |
| 1 | 0x004408D0 |
| 2 | 0x004408C0 |
| 3 | 0x00440B10 |
| 4 | 0x00A9E440 |
| 5 | 0x00440B50 |
| 6 | 0x004386C0 |

These are target-image facts, read from game.dat's mapped image. Slot 2 is
the already rowed nine-byte byte-flag predicate at RVA 0x000408C0, currently
projected as a free fastcall function in DebugIOConDestructorThunk.cpp.
The shared Zero Hour interface has six slots and does not declare this slot.
Its source supports the base role/layout, not the missing BFME 2 method name.
No original name or richer prototype is inferred here, and no ABI/name change
is applied to that existing row.

Next: reconcile the native seven-slot interface and complete console provider
views, including the slot-2 member ABI and the existing identity debt, then
repeat byte/EH checks and the merge selection guard as a cohort. A free-function
projection must not be replaced by an invented second name or alias merely to
fill the table. Keep the existing identity key until its supported retirement
verdict and link guards pass.
