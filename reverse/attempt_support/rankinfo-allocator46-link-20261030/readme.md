# RankInfo: consume the native STLport 4.6 allocator

Base: 182dfeedd1e20748b9cb5db88d963a98282ec26b. Claimed source:
Code/GameEngine/Source/GameLogic/System/RankInfoCtor.cpp. The source opts
into STLport 4.6 and drops the old const qualifiers from its allocator
declaration and inline deallocator definition. No compiler flag, class layout,
existing cast view, source path, pin, alias or header is changed.

The rowed vector<int> allocation/copy helper at RVA 0053BD39 now references
the non-const allocator<int>::allocate. Its native REL32 reaches 00068E15,
where the complete 28-byte provider is already rowed in
VectorObjectIDFillInsert.cpp by 7d15ffa2bd52. The old const allocator owner
remains available for other consumers. There is no new function or duplicate
coverage claim in this migration.

Before/after builds pass all four rows (236 bytes). The independent COFF
comparison proves that all four raw code bodies are identical. There is
exactly one row-relocation/undefined-symbol change, QBE allocator<int> to
QAE allocator<int>, resolved to the same native 00068E15 address. Every
remaining external definition has identical raw bytes and relocation
identities after that explicit name substitution.

Two old definitions disappear: __stl_alloc_rebind<int,int> and the int-pointer
allocator proxy's allocate member. Neither is referenced by the kept graph
in index 85f6b7f40c (2026-10-29 15:08), which has 55 and seven other provider
copies respectively. Those counts describe that index, not a current
whole-tree provider verification. No new external definition is introduced.
The proof records these removals explicitly rather than assuming all
definitions were preserved.

All four ledger rows are individually readmitted with add_match
--replace-existing and migrated=stlport-4.6. Frozen-file checks pass, strict
preparation verifies four rows with a reusable receipt, and the paired build
with the unchanged allocator provider passes 15/15 functions. Ordinary preview
reports both sources LINKS against 85f6b7f40c. RankInfo retains 236 bytes;
the provider's 606-byte preview includes the previously added shared range,
so it is not an additional gain from this work. Unique matched coverage
gain is zero, and no new census-linked-byte gain is claimed.

Full affected-consumer verification and scheduled census confirmation remain
pending. The outgoing batch audit is recorded separately below when available.
The newer BFME 1 donor revision is not adopted by this change; the maintained
verified b53c85e7 reference and the prior freshness boundary remain in force.

Model GPT-6; homogeneous four-row source migration t=6 minutes; lane=R;
budget=30m. Ledger readmission, final verification and publication are separate
checks.
