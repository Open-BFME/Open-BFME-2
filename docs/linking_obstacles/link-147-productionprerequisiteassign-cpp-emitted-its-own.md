### LINK-147: ProductionPrerequisiteAssign.cpp emitted its own BfmeStringRecord002CF5B1 assignment (2026-10-29, seat b1)

Status: repaired, pending census confirmation. The 85f6b7f40c census lists
ProductionPrerequisiteAssign.cpp linked=no, its implicit
`??4BfmeStringRecord002CF5B1@@QAEAAU0@ABU0@@Z` being the only (non-retail)
copy. Target fact: its byte-matched `__copy` (0x00564CD4) calls 0x00564B1A,
rowed as the placeholder `Rva00564B1A::rva00564B1A` (two StringBase sets at
+4/+8; symbols.csv already pins the ??4 name there). Repair: the unit declares
the operator out of line; Rva00564B1AAssign.cpp defines it on its own view as
an ICF-twin row (`add_match --icf-owner`, fold-proof that unit). Preview: all
15 units naming either class link (9,141 -> 9,265 B). Open identity question:
the consumer's view spells +4 as a word (its copy constructor 0x002CF5B1 is
rowed on that view) while retail's assignment treats +4 as a string; re_log
0x002D0C44 records the same conflict.
