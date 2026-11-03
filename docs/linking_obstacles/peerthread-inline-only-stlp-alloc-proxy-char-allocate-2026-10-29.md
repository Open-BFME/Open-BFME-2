### PeerThread inline-only `_STLP_alloc_proxy<char*>` allocate (2026-10-29)

At base `1726d2b12a`, `PeerThread.cpp` (174 rows, 18,622 authored bytes) could not
link on one unresolved name, `?allocate@?$_STLP_alloc_proxy@PADD...@Z`. The unit
already declared that member declaration-only "so the kept copy serves the link",
but no object in the tree defines it: retail never had an out-of-line copy. The
rowed caller `??$append@PAD@..@@AAEAAV01@PAD0ABUforward_iterator_tag@1@@Z`
(`0x0001B3E0`) inlines the proxy — its call at +0x5A goes straight to
`allocator<char>::allocate` (`0x000307F0`) between two pushes and an
`add esp,8` — so the declaration-only form only turned the inlining into an
undefined reference. The member is now bound inline to
`allocator<char>::allocate(__n, 0)`, the same idiom the file already uses for the
matching `deallocate` (whose retail body is 0x006892B0). All 174 rows, 117 string
references, 26 empty-string references and 26 named imports stay exact (the
funclet `$L` rows renumber and verify through `parent=`), and the unit previews
LINKS 0 -> 18,622 bytes against index `85f6b7f40c`. Note for the next seat on this
class of name: a declaration-only specialization of `basic_string::append<char*>`
crashes MSVC 7.1 (C1001), and the `template <>` form of it gives C1506, so the
inline-body form is the only one that compiles. Census confirmation pending.
