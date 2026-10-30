# Wide monetary parser: unused narrow allocator copy

Inspected base `dc24521e86`, index `ccafe54d1d` (2026-10-30 15:43).
`stlport_wide_money_get_string.cpp` emits an unused 18-byte const
`allocator<char>::deallocate` COMDAT, with only a `.debug$F` incoming relocation.
Its throwing global C++ `free` binding differs from the selected provider.
This is linking cleanup, with no new coverage, identity or original-TU claim.

The TU-local imported forceinline specialization preserves the vendor
`__sgi_alloc::deallocate` operation, assertion and existing throwing-free
context. It is placed after this file's existing malloc-allocator cleanup
specialization; placing it earlier instantiates that helper too soon (C2908).
No header, pin, row, alias, counted hatch or compiler setting changes.

Private before/after verification passes all 16 rows and all emitted handler
parent EH graphs. Only the unused allocator disappears; all 95 retained
external code bodies are identical. Symbolic relocations are identical after
comparing same-section static labels by their actual section offsets. In the
parser's jump table the compiler renumbers labels but every target offset and
all 2,824 section bytes, including table words, are unchanged. External names
and the import-symbol set are unchanged.
[Private comparison](money-get-comparison.json), [actual object](money-get-actual.json).

Literal build.sh, frozen-definition and strict preparation pass. Together with
the separately checked formatter, preparation passes 33/33 rows and the
ordinary preview retains 2/2 LINKS, 0 -> 5,446 authored bytes: parser 2,830,
formatter 2,616. This is a bounded preview, not a census or full-image link.
Broader affected-consumer selection/loss checks and scheduled census
confirmation remain separate.
