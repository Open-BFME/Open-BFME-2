# Downloader registry inline allocator cleanup

Inspected base `0deec88cb3`, provider index `ccafe54d1d` (2026-10-30 15:43).
The registry unit's only preview blocker is its unused const narrow allocator
copy. It and the proxy/rebind definitions have only `.debug$F` incoming
relocations. Their removal is linking cleanup, with no new native coverage.

The existing BFME shim completely specializes `allocator<char>`, so another
member specialization fails C2910 and a late annotated member declaration
fails C2761. A specialization of the primary allocation-proxy template instead
performs the existing char cleanup directly: a null check followed by
`_STL::free`. Imported forceinline retains the native inline operation without
instantiating the unused allocator, proxy or rebind copies. The existing
throwing namespace free declaration, const allocator semantics and ignored
size argument are preserved. No header, pin, row, alias, hatch or compiler
setting changes.

Private before/after verification passes all 21 registry rows and six owned
EH graphs EXACT. All 45 retained external code bodies and symbolic relocation
destinations are identical, and the import-symbol set is unchanged. Exactly
three debug-only external definitions disappear. The actual strict object
reproduces the private candidate.
[Private proof](registry-comparison.json), [actual object](registry-actual.json).

The selected proxy and rebind providers remain unchanged in
`stlport_narrow_num_get_bool.cpp`. Its proxy and the rowed provider in
`stlport_narrow_string_insert_aux.cpp` independently reproduce the complete
18-byte native body at `006892B0`. Other providers remain; no new symbol
binding is introduced. [Provider and selection proof](provider-proof.json).

Literal build.sh and frozen checks pass. Strict preparation of the changed
pair and both existing providers passes 38/38 rows, 14 literals, five empty
strings and 19 named imports; all eight cohort EH graphs are EXACT. The
ordinary preview retains 4/4 LINKS, 942 -> 3,717 authored bytes: registry
0 -> 1,907, URL builder 0 -> 868, existing providers unchanged. These are
bounded predictions, not a new census, unique coverage or a full-image link.
Full affected-consumer selection/loss and scheduled census confirmation remain
separate.
