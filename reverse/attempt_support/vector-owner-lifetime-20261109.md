# Rva003ED658 destructor ownership

Inspected6f19db3538. This is the next queued class in RvaTreeDtorFamily.cpp.
Its canonical header already proves a12B vector descriptor: begin/end/capacity
are three pointer words, not a tree header/count. No donor was consulted.

The first word is now a real four-byte owning member. Its shared holder keeps
the existing inline14B cleanup definition in the provider. The holder pointer
is void*, avoiding a tree-pointee claim when used for this vector buffer.
The other two words remain unsigned-element pointers. No initialization,
copy operation, extent or method signature changes. The destructor provider
now includes the canonical header instead of its private holder/int/padding view.

Private verification preserves218 native rows and all79 EH graphs. It also
verifies the existing pinned Rva003ED658 destructor directly against58 native
bytes and its exact EH graph at3ED94F. That is verification of an existing
alias, not a new match, pin, fold or hatch retirement. Its legacy marker stays.

The staged header graph reaches23 sources. Normal verification passes899/899
bodies,32 data rows,79 string references,14 floats,11 imports and149 EXACT EH
graphs. link_check's own verdict is23/23 LINKS,35439->35439 authored bytes.
Owning acceptance retires exactly the provider's Rva003ED658 header queue row.
BitRange.cpp's copy constructor still needs its genuine vector-member copy and
unwind lifetime, so its separate row remains. Two other provider classes remain
queued in RvaTreeDtorFamily.cpp; no broader class/source completion is claimed.

Both affected ABI contracts are refreshed by class_contract.decide using an
explicit scratch source containing each exact canonical declaration. Each
compiler-backed proposal has sizeof12 and no undecided attribute. One-view
counts describe those probes, not original retail translation units or types.
Rva0038404A's extent and pointer/count offsets remain unchanged.

Reproduction, input hashes and logs: build/vector-owner-lifetime-20261109/.
No game image was linked or run. The preceding holder packagefea7b1cbef's
broader audit remained INCONCLUSIVE:15 missing receipts, first unchanged
ClearanceTestingSlowDeathBehavior.cpp (index138c18d3c9, basea7a3c4d962).
Its own18-source preview passed. Carry object selection into the next maintained
census/image; local source and debt verification is not runtime clearance.
