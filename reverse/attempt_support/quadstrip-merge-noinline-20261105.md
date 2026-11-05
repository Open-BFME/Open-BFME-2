# QuadStrip2D merge prerequisite trial, 2026-11-05

Base: `006a74b68c`; preceding docs-only commit: `149b50224f`.
The picker claimed QuadStrip2D.cpp and W3DAnimationInfoVectorInsert.cpp.
Both pass find_declared_unmatched. The Common/ evidence planner confirms the
approved group and mixed library owners; the TU mapper rebuilt current inputs
in memory rather than committing a stale map.

The unmodified `tu_skeleton.py --merge .../QuadStrip2D.cpp --dry-run` rejects
W3DAnimationInfoVectorInsert.cpp with `bytes`; no donor is accepted. The seed's
copy-constructor comment already warns that exposing that body in the insert
unit changes scheduling. A bounded test added `__declspec(noinline)` to the
copy constructor's declaration in each source. Normal ./build.sh verified all
19 rows across both separate sources, including the renumbered parent funclet
and constructor fold. The same merge dry run still rejected the donor on bytes.
No differing instruction, exception-profile cause or missing symbol is proven
by that summary, so this is not a new codegen diagnosis.

Both noinline edits were reverted byte-for-byte. No source move, row change,
new alias, hatch adjustment or debt retirement remains. The broader LINK-198
naming/provider collision remains unresolved; no W3DModelDraw identity was
changed. Scope claims released. Do not repeat the noinline-only trial; preserve
the seed's existing complete provider until the shared identity and insertion
provider can be reconciled, then recheck byte and consumer closure together.
