# Science tree destructor inlining prerequisite

Inspected base: `624ce0ab67`. Scope: the approved Science.cpp consolidation
group, claimed through the consolidation picker. This changes only the
`StlSweepW4Rva001FF743.cpp` donor before any source move.

The initial supported merge trial accepted no donor. The parser conflicts with
the canonical ScienceStore fields, the destructor donor's composed vtable would
break another unit's selected copy, and both STL donors lose bytes. These are
the previously recorded prerequisites, not lost ledger rows.

The tree destructor at RVA `001FF743` calls `clear()` and its base destructor
out of line. Replace the donor-wide `/Ob0` flag with `__declspec(noinline)` on
the explicit instantiations of those two helpers. This retains their ordinary
template definitions and the verified destructor while allowing the surrounding
TU's normal inlining settings. No type identity, pin, alias, row, or register
key changes.

`./build.sh Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva001FF743.cpp`
passes its one 43-byte row, and the frozen-file check passes. Before/after
objects both have 15 COMDAT bodies and identical external definition/reference
symbol inventories and weak aliases. Four helper bodies change as their own
callees can now inline; no provider name disappears. The destructor remains
byte-exact. The ordinary per-file link preview reports LINKS, 43 -> 43 own
linked bytes, against the 2026-11-04 22:40 census at `3a95b274a2`.
`link_check.py --new-variants` also exits successfully with no new variant
blockers reported for the changed donor.

After refreshing the supported consolidation planner, `tu_skeleton.py --merge
Code/GameEngine/Source/Common/RTS/Science.cpp --dry-run` accepts the seed and
this STL donor. The winning composition preserves every selected row and
passes the census-linked guard. The parser's canonical field conflict, the
destructor donor's selected vtable conflict, the other STL donor's byte failure
and the nine mixed donors remain. Commit this prerequisite before applying the
saved merge plan.

Local diagnostics: `build/science-w4-noinline-build.log`,
`build/science-w4-before-link.log`, `build/science-w4-noinline-link.log`,
`build/science-w4-object-diff.txt`, and `build/science-noinline-dryrun.log`.
No new census, image-ownership gain or source reduction is claimed here.
