# STLport 4.6 owning-return clone

The default picker claimed `Code/GameEngine/Source/Common/Rva004E74A0Clone.cpp`.
Its earlier trial already reproduced the destructor but could not find the
clone or its EH handler: STLport 4.5.3 declares `auto_ptr` as `struct`, while
4.6 declares it as `class` (`vendor/stlport-4.6/stlport/stl/_auto_ptr.h:42`).

Switch the existing C++ unit to `// stlport46`, change the clone and handler
return-type manglings from `?AU` to `?AV`, and carry the funclet's parent token.
The old ABI keys receive deletion tombstones. No game identifier, layout,
function extent, pin or alias is added. The destructor fold-proof note now
names its current provider in `PolygonTrigger.cpp` and its actual pointee.
Each of the four rows was recorded with `add_match.py --replace-existing`.

Both the control and migrated unit pass `./build.sh`: 4/4 rows, 112 row bytes
including the existing destructor fold, with no new unique-byte claim.
`find_declared_unmatched.py` passes before and after. Both EH reports are
EXACT. The local cleanup changes from compiler label `$L3050` to `$L3013`;
the exact parent graph binds it to the unchanged retail address 0x007922C7.
The stable ledger label remains supported by that graph.

The included COFF reports show all seven COMDAT body digests and sizes equal
after normalizing the two class-key spellings. Undefined and weak symbols
are unchanged. These are compiler facts, not proof of original game names.
The old object report was captured from the unchanged main checkout; the
4.5.3 control and 4.6 trial both ran in a separate prepared worktree at
BFME 2 `cf3cb470f7aa46c241e5daefdb746bc4e1fb9c9d`, reference `efb2b2a`.

Strict provider preparation passes. Ordinary `link_check.py` predicts LINKS
and retains 73 -> 73 recorded linked bytes against index `85f6b7f40c`.
The batch audit is INCONCLUSIVE: that index predates the base, and affected
consumer `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`
lacks a current receipt in this worktree. Carry the changed clone provider,
its class-key spellings and affected consumers into the next scheduled census.
No census-linked or runtime gain is claimed. No nightly, link cycle or smoke
run was started.
