### Online screen constructors: current hierarchy prerequisite (2026-10-30, codex3)

The source-wide recheck of `Rva005BA1FDCtor.cpp` retains 2/2 exact rows
and U7 against index `12b9e7a7c0`; no source change or census gain. Native
constructor/destructor table stores and singleton accesses pair 0x005BA1FD
with the already-rowed opaque destructor 0x005BA23A, and 0x005BA28E with
0x005BA2CB. Both secondary deleting-thunk families already have rows. The
constructor's polymorphic-member placeholders and the two destructor emitters
need one complete inherited hierarchy; a shared BaseVirt pin cannot represent
the distinct deleting targets. The earlier assigned virtual-table audit remains
open. Both constructor boundaries now carry deferred attempt records.
[Target facts, owner scope and checks](../../reverse/attempt_support/online-screen-constructor-hierarchy-20261030-codex3.md).

2026-11-09, bounded source-binding repair: the remaining three strong
custom-match screen arrays are replaced by existing Rva005BA2CB compiler
tables, independently bound by the native 5BA2CB destructor operands.
Both constructor rows remain exact; the destructor and opaque-wrapper
providers are unchanged, with normal/strict twenty-row checks and LINKS495
preserved. Cached replay clears three strong refusals with the same three
bridges/37 slots; seventeen support receipts remain noncurrent. The 4-byte
views remain short against native 44/92/12-byte tables, so this does not
close the actual hierarchy/member-identity prerequisites above. Full index
regeneration preserves all existing in-image bounds and explicit owners;
its other cache metadata changes are not source recovery.
[Native bindings, object proof and scope](../../reverse/attempt_support/custom-match-screen-tables-20261109/README.md).
