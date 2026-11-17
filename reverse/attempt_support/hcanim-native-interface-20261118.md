# HAnim native interface recovery

The served hcanim.cpp emitted a 23-slot HAnim table with two obsolete empty
translation/orientation overloads, no key slot and no memory-query slot.
The constructor and native tables establish key slot 3, destination-reference
queries at 8/9, fade at 12, six presence predicates at 15-20, Class_ID at 21,
and the final pure memory query at 22. Neither class adds data to its bases.

The file now explicitly includes scoped BFME 2 animation headers. They preserve
the existing constructor, destructor, constant bodies, secondary Get_Key and
unrelated animation declarations while correcting that slot order. Existing
legacy header consumers keep their current includes; no new search-path entry
or conditional fallback is added. The compressed view declares its already
rowed rva0018FB70 memory-query override at the actual inherited slot 22.

The sixth HAnim predicate, retaining its legacy neutral _bfme_hanim_v21 name,
is rowed at 0018D1B0 (5 bytes) against its native slot 20. Normal build.sh passes
63/63 rows, three strings, 15 floating references, two imports and four
renumbered funclets verified through their parent EH graphs. New headers are
explicit dependencies of this one producer; both must be tracked.

Private testing also verifies the compressed key, class-ID and visibility
predicate overrides against their native targets, preserving all 62 original
rows. Those bodies are banked separately after ordinary admission/builds.
The unchanged base Class_ID body still lacks ledger ownership at 0013B5E0;
that physical RVA is claimed by another contributor. No new pin is added.
The served two-table real-link pass test remains open until fresh evidence.
