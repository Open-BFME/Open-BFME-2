### LINK-150: STLport 4.6 moves left two body-less allocate specializations without a provider (2026-10-29)

Status: repaired, pending census confirmation. After the 85f6b7f40c census,
5c9a418aa4 and d2717d0481 moved VectorObjectIDFillInsert.cpp (578 B) and
stlport_deque_int.cpp (965 B) onto STLport 4.6. Both units declare
`allocator<T>::allocate(size_t, const void *)` without a body, so their calls
bind to retail's shared four-byte allocator at 0x00068E15 instead of inlining
it. Under 4.6 the member is non-const, and the declarations now name the QAE
twins `?allocate@?$allocator@W4ObjectID@@@_STL@@QAEPAW4ObjectID@@IPBX@Z` and
`?allocate@?$allocator@H@_STL@@QAEPAHIPBX@Z`. No object defines either name.
`link_check.py` over the two units and every source changed since the census
found both unresolved (578 -> 0, 965 -> 0 B). In VectorObjectIDFillInsert.cpp
the `_Vector_base(size_t, const allocator &)` and `_M_insert_overflow` copies
also fall to "retail: unproven": their allocate relocation has no row or pin.
Target fact: both pinned retail helpers (0x004F62A4 and 0x00148D00) call
0x00068E15, where `?allocate@?$allocator@H@_STL@@QBEPAHIPBX@Z` is rowed
(AptTimeLineStats.cpp).
Trials refuted:
- A QAE twin pin at 0x00068E15 is refused by `pin_admission.py --add`. The
  address carries a real name, and the fold-proof source must define the
  pinned symbol, which no object does.
- Dropping the bodies of the two growth helpers changes the code generation
  of the rowed `_M_fill_insert` and `insert` (2/9 FAIL).
- Dropping the allocate specialization would inline allocate into the rows.
Repair: both files are back on STLport 4.5.3 (their pre-move source). Their
rows are exact (9/9, 23/23) and repointed without `migrated=stlport-4.6`.
`link_check.py` on both units, the 1,407 index consumers of their names and
every source changed since the census predicts LINKS for both (578 B and
965 B again). The objects equal their census-time objects, so no consumer
changes. re_attempts.log records both files blocked for the 4.6 lane.
Prerequisite for moving them again: a provider of the QAE twin bodies whose
bytes equal 0x00068E15, usable as fold-proof, or a supported path that gives
the twins the address.

**2026-10-30 provider repair, base 84887c9bc04:**
[Complete bodies and native call evidence](../../reverse/attempt_support/allocator46-link-20261030/readme.md)
now supply both missing QAE allocator names in VectorObjectIDFillInsert.cpp.
The two 28-byte specializations and every relocation equal the existing
00068E15 owner; both call the existing GameMemory byte allocator directly.
Explicit instantiation retains the integer provider for the deque's caller.
Both consumers now use STLport4.6 and pass34/34 rows together; four-unit
preview with the old allocator owner and GameMemory retains4/4 LINKS against
85f6b7f40c. New unique bytes and claimed census gain are0. The old rollback
history above is retained. The missing-provider prerequisite for these two
files is repaired; full consumer confirmation and census verification remain.

Publication follow-up: source repair7d15ffa2bd52 passed its normal34-row push
gate. The broader audit is INCONCLUSIVE against outgoing base7f540888a6c3:
index85f6b7f40c is older, and1151 source objects lack current receipts, first
Common/AIGameTeam.cpp. Full consumer selection/loss verification is unproven.
Carry the migrated sources, new allocator providers and affected consumers to
the next scheduled census; the four-source preview is only the bounded proof.
[Published audit boundary](../../reverse/attempt_support/allocator46-link-20261030/readme.md#publication-and-full-consumer-boundary).

RankInfo follow-up (2026-10-30, base182dfeedd1e2): the newly rowed QAE integer
allocator lets RankInfoCtor.cpp adopt STLport4.6. All four raw row bodies
remain identical; the single changed external/row relocation still reaches
native00068E15. Two obsolete unreferenced proxy helpers leave the object;
every retained external definition stays byte/relocation-identical. All four
rows and strict preparation pass, and the paired15-row provider build passes.
Both sources preview LINKS against85f6b7f40c; RankInfo retains236 bytes.
Consumer-wide selection/loss verification and census confirmation remain open;
no unique-byte or census gain is claimed.
[Native edge and object comparison](../../reverse/attempt_support/rankinfo-allocator46-link-20261030/readme.md).

RankInfo audit follow-up: the initial15 missing direct-source receipts are
prepared through the supported tool, passing357/357 functions across15 sources
with strict reusable receipts. The repeated audit gets past that stage and
remains INCONCLUSIVE on an affected consumer lacking a current receipt,
Common/0CreateAHeroManager21FE49.cpp; its older-index baseline remains
provisional. Full consumer selection/loss verification is still unproven.
[Exact scope and terminal results](../../reverse/attempt_support/rankinfo-allocator46-link-20261030/readme.md#direct-consumer-receipt-repair-and-remaining-audit-boundary).

Word-vector follow-up (2026-10-30, base `32a7f941eb`):
`stlport_vector_word_o1.cpp` adopts STLport 4.6 with a complete non-const
word allocator supplied by `stlport_wide_num_put.cpp`. Its 29-byte body and
relocation equal the existing const owner at `00017710`; both native vector
growth calls reach that address. All 18 changed-source rows match, and all
32 previous num-put COMDATs remain identical. Strict preparation passes
43/43 rows and seven data rows across the pair, old owner and GameMemory;
the four-source preview retains LINKS against `85f6b7f40c`. All seven vector
rows are readmitted and the file leaves the migration queue. New unique
coverage and claimed census gain are zero.

The staged audit initially lacks four direct-source receipts; supported
preparation passes their 113/113 rows. The repeated audit reaches affected
consumers and remains INCONCLUSIVE on the older baseline and missing current
`Common/0CreateAHeroManager21FE49.cpp` receipt. Full consumer selection/loss
verification and census confirmation remain open; carry this provider and
consumer scope into the next scheduled census.
[Native proof, object changes and audit boundary](../../reverse/attempt_support/word-vector-stlport46-20261030-codex3/readme.md).

2026-11-12, timeline consolidation preparation: the existing integer
allocator provider and its seed stay unchanged. Rva005BEA22Dtor now uses
the same existing C++ game-free declaration as AptTimeLineStats instead of
redeclaring CRT free under a temporary macro. Both native donor rows verify
under both compiler profiles; normal build and strict preparation pass,
and both own link previews retain 4,179 bytes. This prepares the approved
TU merge without adding a pin or alias. The unrelated STLport4.6 and full
consumer/census scopes above remain unchanged.
[Native EH boundary and preparation](../../reverse/attempt_support/apt-timeline-merge-20261112.md).

Timeline follow-through (2026-11-12): tu_skeleton absorbs the prepared
Rva005BEA22Dtor.cpp into its approved AptTimeLineStats.cpp. All 78 rows and
six EH records pass; all 81 input COMDATs are preserved unchanged. The
combined link preview keeps 4,179 bytes, the donor's two ledger source
fields and map bookkeeping follow the parent, and one source file is
removed. The complete outgoing tooling/path audit needs no additional
consumer edits; three existing seed header debts remain. No STLport4.6,
census or game-run clearance is added.
[Merge and audit scope](../../reverse/attempt_support/apt-timeline-merge-20261112.md#applied-merge-and-outgoing-audit).

Timeline cleanup preparation (2026-11-12): native parent 5BEA22's exact EH
graph identifies its receiver+4 cleanup and the complete 14-byte buffer
destructor at the existing 7FAB3 ICF owner. Ordinary add_match --icf-owner
admits the already-emitted neutral buffer view without a pin or alias mask.
All 79 rows and strict preparation pass; own link preview reads LINKS.
The added shared-body row is zero unique bytes. The generated cleanup
replacement, three existing header debts and wider census scope remain open.
[Lifetime proof and audit boundary](../../reverse/attempt_support/apt-timeline-cleanup-20261112.md).
