# HordeMeleeAmoeba unchanged merge dry run (2026-11-04)

Allocated `Code/Libraries/Source/WWVegas/WWLib/HordeMeleeAmoeba.cpp`; plan:
47 approved rows, 7 donor files, 6 mixed files. Dry run accepted no donors.
The setter and xfer donors fail with MSVC C3190 for `vector::resize(unsigned
int,BfmePod60)`; the overflow donor fails C2118 (negative subscript); the
deleting-dtor donor fails C2511 for the `EmitVtableTag` constructor; the resize
helper donor redeclares `_STL::allocator`/`vector`. The sort donor is refused by
LinkGuard: its census unit loses the selected retail `copy_backward` COMDAT.
LinkGuard inspected all six census-linked units. No source edits or claims were
made. Reconcile the class/template views and selected provider before retrying.
