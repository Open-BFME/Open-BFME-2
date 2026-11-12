### ObjectTypes remove donor merge held for the next census (2026-10-29)

Status: cleared. Commit `7a8a411f96` merged the remove donor into
`ObjectTypes.cpp`. On 2026-11-12 the merged TU verified 14/14 rows with the
shared ObjectTypes declaration. Against the census at `c31795c94c`,
`link_check.py` reported LINKS, 576 -> 576 bytes for this TU.

Original obstacle (2026-10-29)

The ObjectTypes remove donor (`ObjectTypesRemoveObjectType.cpp`, rows
0x003769C2 and 0x00376B1E) is reconciled to the merged `ObjectTypes.cpp` view
(pushed `ea153f2145a`): it resolves `_STL` through the real STLport algobase
(`/Ivendor`, the include before `<vector>` so the allocator shim's by-value
tag copy stays out), calls the rowed AsciiString destructor directly
(alternatename count 2911 -> 2910), and declares the same converged
`ObjectTypes` class the TU carries (`remove` beside `addObjectType`).
`tu_skeleton --merge --dry-run` accepts the composition and bytes (14/14
rows verify in probe) but the LinkGuard refuses: the merged unit would place
earlier in link order than the census can judge until a census measures
`ObjectTypes.cpp` at its post-merge path. When the next census publishes,
dry-run again (expect the guard to pass), run the real merge (2 rows),
verify the TU 14/14, and push; claims 0x003769C2/0x00376B1E stay with the
merge scope until then.
