# Share STLport's vector definition in the Apt adder seed

Base `ae61e35305b`. The claimed consolidation target is the current TU-map
home AptOverButtonHandlerAdder.cpp, with one clean donor
TreeKey00242F5EPushBack.cpp and one mixed AptCallbackAdders.cpp left alone.
The supported initial dry run accepts nothing: the seed's private vector
class conflicts with the donor's real STLport definition (C2953/C2955).

Replace only that private vector template with <vector>. Preserve the two
existing out-of-line contracts by explicit declarations for the opaque
vector's erase and vector<AsciiString>::push_back. No instruction body,
address, element spelling, shared header, pin, flag, row or register changes.
The incomplete opaque element remains opaque; no layout/name inference is
made about it. STLport's real three-pointer storage serves the same accesses.

The standalone seed still passes all three rows and strict preparation,
with no EH graph or unmatched definition introduced. Every one of its five
COMDAT byte/relocation fingerprints and 12 external binding facts is
identical. Ordinary preview retains LINKS/195 bytes at index984a4cdc4d.
The original two-source control passes4/4 and retains both LINKS/250 bytes.
The prerequisite is separately committed before attempting any source move.

The evidence planner's seed packet leaves original-path attribution
unresolved; it does not approve a merge. Routing is rechecked by tu_skeleton
against the current in-memory map. The WB AptCallbackAdders.cpp evidence
for the mutable pair family is retained as target evidence for that family,
not a newly proved original path for this seed. The existing mixed file is
not split here. Final composition, provider selection and the outgoing path
consumer audit remain separate checks.
