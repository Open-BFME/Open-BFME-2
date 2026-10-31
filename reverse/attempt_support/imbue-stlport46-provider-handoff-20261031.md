# Narrow imbue 4.6 migration with the old proxy provider retained

Base: `3c7a254a38d19b1c4c05750250e184070968eb4a`. The default claimed picker
served `stlport_narrow_ios_imbue.cpp`. Its complete six-row unit, not only
the 27-byte library lead, is migrated. The related wide unit is separately
claimed and retains STLport 4.5.3 to supply its remaining consumers.

## Source and ABI

The narrow marker selects 4.6. Its two explicit force-inline allocator
deallocate definitions drop `const` to agree with 4.6's two-argument member
declaration (`vendor/stlport-4.6/stlport/stl/_alloc.h:358`). The direct `free`
body, malloc/static-library/CRT flags, all other suppressions, grouping
assignment and parent implementation stay unchanged. Every existing row is
repointed by `add_match.py --replace-existing`, preserving historical notes
and appending `migrated=stlport-4.6`.

LINK-140 already warns that the narrow unit is the last old proxy allocator
provider. A marker-only trial fails C2244; reconciling the two const qualifiers
passes all six rows but removes that provider. Do not land that intermediate
state. The wide unit removes its old imported force-inline proxy override,
allowing the same 4.5.3 vendor definition to emit. Its additional bodyless
`__malloc_alloc<0>::allocate` declaration retains the existing out-of-line
malloc owner instead of introducing a wrong local implementation.

## Actual-object evidence

All five external code definitions removed from the narrow object are present
with identical raw bodies and symbolic relocations in the final wide object:
`__stl_alloc_rebind`, proxy allocate/deallocate and const allocator
allocate/deallocate. In particular proxy allocate remains 25 bytes and calls
the same `__malloc_alloc<0>::allocate` provider. All 27 retained narrow external
code definitions are identical. Wide retains 30 identical definitions; its one
changed unrowed `append<char*>` copy becomes identical to the already-emitted
narrow copy. Its other two added code definitions are the unchanged old
allocation providers. This is an object-provider handoff, not a source-path move.

The two new non-const 4.6 allocator definitions in the narrow object have only
`.debug$F` incoming relocations in this pair. Full selected-provider/consumer
loss verification remains distinct from that observation. No new body, pin,
alias, hatch, shared header, compiler flag or game-runtime improvement is claimed.

Normal builds pass all 7/7 rows across the pair. Both complete EH graphs are
EXACT, frozen definitions pass and strict two-source preparation succeeds.
The initial bounded preview against `ccafe54d1d` retains 2/2 LINKS and 513
authored bytes. Fetching the published index imports 19,030 reusable objects
and advances its snapshot to `3c7a254a38`, dated 2026-10-31 13:43; the final
pair preview retains the same 2/2 LINKS and 513 bytes. That index lists the
narrow unit itself as the old proxy's only direct touching unit. The old
LINK-140 consumer list is historical, so the object-preserving handoff is
verified directly rather than assuming those old consumers still exist.
The outgoing audit's currency/consumer limits remain separate and must stay
in the obstacle register. A preview is not a new census or a full-image link.

The normal publisher lands the repair on its first attempt as
`b4d0c4f5547f5fb9fa26dfca3ab6d6ea4fe0273d`, after rebasing onto
`d8afc35512fc89d1ae4da5ce63875ea2ed3a28af`. Its hook verifies all seven rows,
both EH graphs and converged data. The outgoing link audit is INCONCLUSIVE:
the index predates that outgoing base and two affected objects lack current
receipts, first `Code/Libraries/Source/WWVegas/WWLib/stlport_basic_ios_init.cpp`.
Those qualifications remain open for the scheduled census; neither the
successful push nor the two-file preview proves full consumer-loss clearance.

Qwen reviewed only the supplied provider-loss scenario, on four CPU threads
with CUDA hidden. It identified the stated unresolved-reference risk but
provided no independent binary evidence or source patch. Host COFF, row, EH
and link checks establish the results above.

## Reference and reproducibility

The committed BFME 1 pin stays `7a8a034afa7dd3530d9a99dc48cfec711626256c`.
The new account-wide 168-hour clock adopts the existing successful October 29
check at its original UTC time; it does not claim a new upstream check or a
new verification of that committed pin. No reference checkout is advanced.
Raw requests, responses, control sources/objects, strict and ordinary logs and
the complete COFF inventory are saved under the create-only run
`W:/OpenBFME/diagnostics/continuation-20261031-1439` and hashed for handoff.
