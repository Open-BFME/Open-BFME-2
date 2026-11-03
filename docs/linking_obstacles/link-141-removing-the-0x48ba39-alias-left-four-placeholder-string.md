### LINK-141: removing the 0x48BA39 alias left four placeholder string destructors unresolved (2026-10-29, seat yasinschroeder-claudeb2)

Status: three units repaired, pending census confirmation; UnitRevivalTracker.cpp
open. Commit 7eca2a1774 removed ObjectTypesRemoveObjectType.cpp's
`/alternatename:??1Rva0048BA39StringElement@@QAE@XZ=??1AsciiString@@QAE@XZ`.
The alias had also served four other units, which declared that body-less
placeholder destructor for the 5-byte `??1AsciiString` (0x0048BA39, `jmp
releaseBuffer`). The 2026-10-29 census lists each of them linked=no with one
unresolved name: TeamTemplateInfoDtor.cpp, TeamTemplateInfoDeleter.cpp,
StlSweepW5Rva0002CD53.cpp and UnitRevivalTracker.cpp.
Repair: both TeamTemplateInfo units now declare their +0x118 array as
`AsciiString m_items118[32]`. With the default inline destructor, the
compiler-generated array destructor calls the `??1AsciiString` COMDAT
(15/15 rows exact). StlSweepW5Rva0002CD53.cpp builds with
`/DBFME_ASCII_DTOR_DECL` and destroys through `AsciiString::~AsciiString`
(1/1 exact). Preview: all three LINK (294 B).
Open, UnitRevivalTracker.cpp: retail's two static atexit thunks (0x7B7D77,
0x7B7D81) jump to 0x48BA39, while the unit's temporaries inline releaseBuffer.
A scratch compile shows that `BFME_ASCII_IMPLICIT_DTOR` gives exactly that
split. The whole unit under that switch, even with a `__forceinline`
`AsciiString(const char *)`, still misses three rows: UnitRevivalEntry's two
constructors (scheduling) and calcButtonImage (it grows past its 476-byte extent).
`BFME_ASCII_DTOR_DECL` would turn the temporaries into calls.
Prerequisite: an AsciiString form that keeps this unit's constructor and
temporary shapes while the static thunks still call the out-of-line destructor.
Alternatively, find the retail source construct (for example, statics of a
type whose implicit destructor wraps AsciiString). Pass test: the census shows
UnitRevivalTracker.cpp linked=yes.
Repair (2026-10-29, seat b1): `AsciiStringElementDtorTwins.cpp` now defines
`Rva0048BA39StringElement` as a class holding one `AsciiString` with an empty
out-of-line destructor; it compiles to the 5-byte `jmp releaseBuffer` and is
rowed as an ICF twin of `??1?$StringBase@D@@AAE@XZ` (`add_match --icf-owner`,
`fold-proof=` that unit). UnitRevivalTracker.cpp is unchanged, so its rows stay
exact. Preview: UnitRevivalTracker.cpp 0 -> 3,033 B and the twins unit LINKS.
Pending census confirmation.

2026-10-30, base `734530a648`: current TeamTemplateInfoDtor.cpp verification
confirms LINK-141's existing repair (14/14 rows, one EXACT EH graph, strict
provider preparation, ordinary preview LINKS for 236 authored bytes against
`85f6b7f40c`). Its stale destructor present-unmatched exemption and one hatch
register key are removed. The outgoing audit is INCONCLUSIVE on the older index
and missing current CreateAHeroManager consumer receipt. Carry that consumer
and the destructor provider into the scheduled census; no new linking gain or
full consumer closure is claimed.
[Exemption retirement and checks](../../reverse/attempt_support/team-template-marker-cleanup-20261030-codexb4.md).
