### LINK-140: STLport 4.6 migration removed the only provider of the 4.5.3 proxy<char> allocate (2026-10-29, seat yasinschroeder-claudeb2)

**2026-10-30 two-argument fstream constructors (base `8ca3c9be51`):** select
4.6 and remove two obsolete proxy allocation declarations, addressing the
recorded C2244 prerequisite without repeating the marker-only failure. All
5 rows and both EH graphs remain exact; strict preparation passes. All 134
retained external code bodies/relocations and undefined references are
identical. Six old default-construction helpers and 538 header constants
disappear; no definition is added. File preview retains LINKS/528 authored
bytes at `ccafe54d1d`. Carry removed helper/constant providers and affected
consumers into the scheduled audit/census; full consumer selection/loss
verification remains open. No LINK-140 family clearance, debt retirement or
census gain is claimed. [Evidence](../../reverse/attempt_support/fstream-stlport46-qwen-20261030.md).

**2026-10-30 particle template writer (base `724f3a7ffc`):** the claimed
ParticleSystemTemplateWriteINI.cpp now selects 4.6 and removes its obsolete
proxy allocate/deallocate specializations. All 8 rows and the EH graph remain
exact; strict verification with the existing native narrow allocator owner
passes 42 rows. The writer retains 1,067 authored LINKS bytes; the pair retains
2/2 LINKS and 1,917 bytes against `ccafe54d1d`. All 26 retained external code
definitions are identical. One unreferenced 22-byte non-retail allocator
deallocate copy is newly emitted; bounded selection retains the existing
20-byte native owner. Carry that copy and affected consumers into the next
scheduled census/audit. Full consumer selection/loss verification remains
open; no census gain, identity retirement or LINK-140 family clearance is
claimed. [Evidence and rejected helper advice](../../reverse/attempt_support/particle-writer-stlport46-qwen-20261030.md).

**2026-10-30 narrow-string migration (base `40e30bd124`, codexb4):**
`stlport_narrow_string.cpp` now selects 4.6 and removes its obsolete proxy
allocate/deallocate specializations, which are inherited allocator operations
under that release. All eight rows remain exact; all 30 retained external
COMDAT fingerprints and external references stay identical. Only the emitted
`string::npos` constant disappears. The owning migration queue no longer
serves the file. Strict six-source preparation passes 51/51 rows and both
EH graphs are EXACT; joint preview retains 6/6 LINKS and 4,529 authored bytes
against index `12b9e7a7c0` (2026-10-30 10:11). This file did not provide the
old proxy helper, so its migration leaves that wider prerequisite unchanged.

The full outgoing staged audit against `6e3f45976c` is INCONCLUSIVE on the
older index and 48 objects without current receipts, first
`Common/BfmeConv1456.cpp`. Carry this provider, its removed constant and
affected consumers into the next scheduled census/current-receipt audit;
full consumer selection/loss verification remains open. No census gain or
debt retirement is claimed.
[Changes, object comparison and verification](../../reverse/attempt_support/narrow-string-stlport46-20261030-codexb4.md).

**2026-10-30 Buddy constructor follow-up (base `89295774ff`):** declaring its
existing native narrow-string constructor (0x00007850) suppresses 11 local
copies, including the competing allocator proxy. All 17 retained Buddy copies
remain identical. Ordinary strict four-source verification passes 23 rows and
four EXACT EH graphs; the paired preview improves 3/4 to 4/4 LINKS, 540 to
770 bytes (Buddy: 0 -> 230). The existing constructor, proxy provider and caller
stay linked. The staged audit is INCONCLUSIVE on the older index and affected
consumer Common/0CreateAHeroManager21FE49.cpp without a strict receipt; carry
the changed instantiation and affected consumers into the next scheduled census.
No census gain or wider migration clearance is claimed.
[Evidence](../../reverse/attempt_support/buddy-native-string-ctor-20261030/readme.md).

Status: partially repaired, pending census confirmation; the provider-retirement
follow-up below remains open. The 2026-10-29 17:26 census
(85f6b7f40c) drops ten units from linked to not linked, each with exactly one
unresolved name, `?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z`:
NarrowStringRecordCopyBFME2.cpp, PeerThread.cpp,
PeerThreadStats_PackStatKey.cpp, registry.cpp, urlBuilder.cpp,
Rva001F9524Concat.cpp, stlport_narrow_ios_imbue.cpp,
stlport_narrow_ostringstream_dtor.cpp, stlport_narrow_stringbuf_overflow_setbuf.cpp
and stlport_wide_ios_imbue.cpp. Their unrowed 4.5.3 COMDATs (for example the
/Od `append<const char*>` copy) call the proxy allocate, which each of them
declares as a body-less specialization. Index 840db2d676 shows the only
copies came from stlport_float_format.cpp and stlport_narrow_money_put_string.cpp
(digest fbdef5e80d3e, no retail address). Once those units were on 4.6 they
called `allocator<char>::allocate` directly and stopped emitting it. Retail has
no body for this name, because its rowed callers (for example `append` at
0x1B3E0) inline it. Repair: stlport_narrow_stringbuf_overflow_setbuf.cpp no
longer declares that specialization, so it emits the one copy (7/7 rows still
exact). There is a single provider, so no copy with a different digest can
lose a COMDAT selection. Preview with the current 4.6 objects of both former
providers: all ten units plus both former providers LINK (12/12, 29,668 B).
Caution for later migrations: about twenty 4.5.3 units still declare this
specialization. If this provider moves to 4.6, it must keep a copy, or its
consumers must stop declaring it.
Regressed again (2026-10-29, seat b1): 5cea349adb moved the provider onto
STLport 4.6, so the ten units were unresolved on the same name again.
Repair: stlport_narrow_ios_imbue.cpp (4.5.3) no longer declares the proxy
specialization, so it emits the copy, and it now declares
`__malloc_alloc<0>::allocate` body-less so the emitted proxy body does not
bring a non-retail `__malloc_alloc` copy first in link order (6/6 rows exact).
Preview: the ten consumers, both earlier providers and this unit LINK (12/12,
5,457 -> 29,668 B); all 48 other declaring units still link except
stlport_list_string_erase_00424363.cpp, whose list-helper COMDATs are unrelated
(LINK-143). Pending census confirmation.
Confirmed at 2a7e3dc198 (seat dd-11, 2026-10-29): the ten census-listed units
alone plus stlport_narrow_ios_imbue.cpp give 10/10 LINK, 4,437 -> 26,741 B, with
the published index 2026-10-29 15:08 at 85f6b7f40c. Only registry.cpp (WWLib)
was already linked at that census; the other nine are 0 -> 22,304 B. The
consumer-side body-less proxy declarations are therefore correct as they stand
and need no edit; the index predates c69c376bb6, which is why the picker still
serves PeerThreadStats_PackStatKey.cpp as a 344 B link repair. Nothing to
repair here: the next census confirms. If the provider ever moves to STLport
4.6 it must keep the copy (this entry's warning above).

2026-10-29 follow-up (codexb4, inspected `addc18930a`): 5cea349adb migrated
the overflow/setbuf provider to 4.6 after the repair above. Its current object
no longer supplies the proxy helper. Preview of the narrow ostringstream
destructor with all three former providers replaced by current objects still
finds that one unresolved name. The consumer now also uses 4.6, removing its
obsolete proxy specialization; all six rows remain exact. The parent's exact
EH graph binds the renumbered cleanup to 0x0076B44E, with gen-funclet metadata
added through add_match. Strict current preparation passes; joint preview
is 4/4 LINKS (6,442 authored bytes, including 418 in the selected consumer).
This clears only that consumer's dependency, pending census confirmation.
The staged-tree batch audit is INCONCLUSIVE: index 85f6b7f40c predates base
86058c40c8 and 34 affected sources lack current receipts, first
Common/Rva003A5DA0Write.cpp. Carry that cohort into the next scheduled census;
broader consumer closure remains unverified.
The other historical consumers require current-object revalidation and
migration or a proven provider repair; the old helper has not been restored.
The migration retains one shadow allocator-definition finding: suppressing its
21-byte allocator<char>::allocate copy keeps all six rows exact and cleans the
identity scan, but makes the current overflow/setbuf unit lose COMDAT selection
(joint preview 3/4, down from 4/4). That isolated suppression is restored;
reconcile the allocator provider cohort before removing this copy. No identity
debt retirement is claimed.
[Checks and evidence](../../reverse/attempt_support/ostringstream-stlport46-link-20261029-codexb4.md).

2026-10-30 follow-up (codex5, base `1726d2b12a`): the selected
NarrowStringRecordCopyBFME2.cpp consumer now uses 4.6 and no longer requires
the obsolete proxy helper. All 34 rows (947 bytes) remain exact, including
the deallocate instantiation whose native signature changes from const to
non-const with identical bytes and relocation. All ten parent EH graphs are
EXACT. Removing only the 4.5.3 proxy suppression failed COMDAT selection.
An initial 4.6 trial retaining allocator<char>::allocate suppression linked
this consumer but broke overflow/setbuf's allocator selection (4/5 preview).
The final source retains that allocator helper, as required by the existing
provider-cohort caution above. Joint preview with all four current former
helper providers and the narrow ostringstream repair is 6/6 LINKS
(5,457 -> 7,567 authored bytes, including 850 in this consumer).
This is bounded prediction, pending census confirmation; the other historical
consumers and broader provider selection remain open. The new 35-byte malloc
allocator helper is an unreferenced majority-copy difference in preview;
the staged identity gate reports one new shadow definition finding, which
is not retired. Do not suppress it in isolation. The staged-tree batch audit
is INCONCLUSIVE (exit 2): the older index lacks current receipts for 27 affected
sources, first Common/NarrowStringRecord00427F75Helpers.cpp. Carry this unit
and that cohort into the next scheduled census; their broader closure is
unverified.
[Repair evidence and remaining scope](../../reverse/attempt_support/narrow-record-stlport46-20261030.md).
Repair (2026-10-29, seat dd-15), NarrowStringRecordCopyBFME2.cpp: that unit's
one unresolved reference did not need the proxy copy at all. Its only reference
came from a local `basic_string<char>` default-constructor COMDAT; retail emits
no such copy in this TU, because its rowed record default constructor
(0x0041A1CF) calls retail's out-of-line default constructor at 0x00007850 twice.
The unit now declares that constructor body-less beside its copy constructor and
`assign`, so it links against the rowed 0x7850 body instead of emitting a copy
and an allocator reference. Build 34/34 rows exact; link_check 0 -> 850 B.
Pending census confirmation.
