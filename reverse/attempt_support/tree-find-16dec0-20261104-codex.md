# Replace the disproven 0x0016DEC0 set lookup claim

Base: `c0b890798f`. Native 0x0016DEC0 is a 21-byte hidden-result iterator
wrapper calling 0x0016D6A0. That complete 108-byte callee walks the tree by
three signed integer key fields, then rejects a non-equal candidate. It is
the existing Gen_p12pod tree `_M_find`, not `_M_lower_bound` (the latter is
the distinct 67-byte body at 0x0016D5C0).

The old `set<Rva0016DEC0Element>::lower_bound` model used a string-shaped
key and pinned its lower-bound helper to the find body. Matching the outer
21 bytes never established that operation or element. The string comparison
it emitted has no native provider, and implementing it would preserve the
wrong operation. Retraction removes that claim and its false helper pin.

The old twelve definitions have no outside census touch losing its provider;
a source/shim search finds no call to the old wrapper or element outside
that source. The four existing Gen_p12pod providers remain exact. There is
no path-keyed gate, identity, data, header, flag or hatch debt for the removed
source; the pin counter shrinks through `hatch_counters.py --update`.
The retired row is tombstoned and `re_log.py` records the result.

A separately compiled reference reconstruction instantiates only the const
`_Rb_tree<Gen_p12pod,pair<const Gen_p12pod,int>,...>::find<Gen_p12pod>`.
It uses the existing provider's three-integer key/comparison, without inventing
a new application type. The wrapper is exactly 21 bytes with its call resolving
to the existing `_M_find` name at 0x0016D6A0; its emitted helper independently
equals all 108 native bytes and has no relocations. It has no undefined symbols.
This establishes the storage operation and reuses the existing provisional
key identity; it does not recover the application's original key or outer
container name. The actual operation is readmitted separately, preserving a
reviewable false-claim retraction.

The new source remains at the existing path; there is no cross-TU move or new
source file. The address currently has no approved TU. Native-library names
come from STLport's actual template operation, and Gen_p12pod is the existing
callee-owner spelling. The shared helper needs no second row or pin.

Local receipts: `build/seat_tree_find.{cpp,obj}`, the scoped provider build,
`build/seat_tree_old_orphans.json` and the nine-source base preview including
the first copies of both the old and replacement COMDAT sets. Readmission
verification is appended with that commit. No full real-link/census claim.
