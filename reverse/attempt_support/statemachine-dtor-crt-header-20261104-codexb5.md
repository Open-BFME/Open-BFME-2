# StateMachine destructor CRT-header trial

Inspected source: `6fbd44876f`; file claim:
`file:Code/GameEngine/Source/Common/StateMachineDtor.cpp`.

The Microsoft-header queue selects the local `void free(void *)` declaration.
The source deliberately hides the CRT declaration while including `<cstdlib>`,
then declares a throwing C++-linkage free. The existing pin
`?free@@YAXPAX@Z` binds this call to the game allocator at RVA `0x00030830`.

Trial: remove the `free` macro rename, undef and local declaration, retaining
`<cstdlib>`. An initial additional `<crtdbg.h>` include was unnecessary and
removed. Both trials pass `./build.sh` on all six ledger rows, with both funclet
labels verified from the parent EH graph. The source scanner reports no
unmatched definitions; `ms_header_audit.py scan --write-queue` removes the
file's local-definition queue row.

That is insufficient: ordinary `link_check.py` against the published census
index at `3a8028f34e` (2026-11-04 11:27) rejects the trial. The emitted
`_STL::_Rb_tree<unsigned int, pair<unsigned int const, State *>, ...>`
destructor is not retail's body and its selected copy is wrong. Preview:
LINKED 171 -> 0 bytes. The trial object refers to `_free`, rather than the
original C++-linkage free; the ledger's `_free` row is at `0x00030830`, while a
historical pin also exists at `0x00628F98`. No pin edits were attempted.

Reverted the entire source and queue trial. The original source again passes
all six rows and ordinary link preview retains LINKS, 171 -> 171 bytes on the
same index. No game-source or header-queue changes remain. No census gain is
claimed.

Next useful work requires preserving the throwing game-allocation teardown
semantics while replacing the private declaration. Check the emitted tree
destructor and the affected consumers, not only the rowed map wrapper and
parent destructor. Repeating a plain CRT-header substitution is not useful.
