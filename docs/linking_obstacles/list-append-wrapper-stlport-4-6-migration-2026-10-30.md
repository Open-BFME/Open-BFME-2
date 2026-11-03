### List append wrapper STLport 4.6 migration (2026-10-30)

The eight-byte Rva001B4D0E append wrapper now selects STLport 4.6 headers.
Its external COMDAT fingerprint, provider binding and external symbol records
are unchanged. Strict preparation verifies all 29 rows across the wrapper and
StlportListInsertFootprints provider; joint ordinary preview retains 2/2 LINKS
and 845 authored bytes against `12b9e7a7c0`. The old census blocker was already
repaired by `d98221c12c`; this header migration claims no census gain. The
enclosing type and 72-byte element identities remain unresolved.

The complete staged outgoing audit from `33564ef244` is INCONCLUSIVE on the
older index and 15 source objects without current receipts, first
Common/BfmeConv1456.cpp. Carry the wrapper, native push-back provider and
affected consumers into the next scheduled census/current-receipt audit;
full selection and loss verification remain open.
[Evidence and publication scope](../../reverse/attempt_support/list-append-stlport46-20261030-codexb4.md).
