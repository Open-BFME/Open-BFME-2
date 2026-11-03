# CollectionDefClass constructor cleanup

Base: `678d949f99`. Source: `Code/Libraries/Source/WWVegas/WW3D2/collect.cpp`.

Remove only the unrowed donor `CollectionDefClass::CollectionDefClass()` and
its present-unmatched marker. Explicitly instantiate the existing
`DynamicVectorClass<char *>` constructor so its ledger-owned 94-byte body
remains emitted. No function row, name, compiler flag, pin, alias or path changes.
The hatch register drops one present-unmatched entry (2397 -> 2396).

Target evidence: neither functions.csv nor symbols.csv names CollectionDefClass;
the removed definition is the donor initializer of SnapPoints and two vectors.
This edit makes no claim about recovering a retail CollectionDefClass identity.
All five matched rows pass ordinary byte and string/float/import checks before
and after. Scoped DIR32 checks all five rows and two symbols with no conflicts
(no outside witnesses selected). All 140 common COMDAT body/relocation fingerprints and their selection
policies are identical. The removed constructor is the only lost definition;
there are no new definitions or changed undefined names. See provider-audit.json
for exact object hashes and the census index metadata.

The published index (2026-11-03 20:03, provider commit 8661f15284, census
23b85ddde5) has no other object touching the removed constructor name.
A literal binary search of all 26,141 `.obj` files under build/match after the
edit finds no occurrence of `??0CollectionDefClass@@QAE@XZ` (rg -l -a -F).
No alias directive is changed. This rules out a current local consumer losing
its sole constructor provider; it does not assert whole-image link closure.

True source-restored base/tip previews are identical apart from elapsed time:
both report 41 unresolved names, four COMDAT conflicts and 0 linked bytes.
No linking or real-link gain is claimed. The historical full-constructor trim
remains blocked on retail ownership of EFB4C/5AD93A, as recorded in
real-link-mesh-pair-20261103.md. The other constructor and its hatch remain:
the next substantive repair still needs that identity/ownership reconciliation.
The remaining ctor was not retried without new evidence.
