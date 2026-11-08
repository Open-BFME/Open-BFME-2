# AIBackAwayAndCowerState virtual name getter

tools/rename.py function --to-class moves the existing six-byte getter
at 0x0033F35E from Rva0033F35ENamed::name into the protected virtual
AIBackAwayAndCowerState::GetSnapshotName. Both native lifecycle rows
install table VA 0x00C10EE0, whose slot 2 contains that getter. Its full
literal at VA 0x00C10F24 is AIBackAwayAndCowerState. No new body or unique
byte is claimed; the tool writes the old-row tombstone.

The constructor and destructor declare the proper override. Their two
68-byte tables stay identical; only slot 2 changes from __purecall to
the verified getter. The getter unit emits no extra table. Every retained
executable COMDAT body, relocation position, flag and policy remains
equal after the getter-name normalization. Other data/bindings agree;
the emitters replace only their purecall reference with the getter.
No pin, alias, flag, header or source path changes.

Normal tool verification passes all 45 rows/42 complete literals in the
three changed sources, then 247 rows/nine data rows across 28 dependent
sources. Strict preparation again passes 45/45. The destructor EH graph
is exact, and frozen-source and paired new-variant checks pass. Preview
over six existing, strictly current objects conserves LINKS/4,918 bytes
against index c885072a48 (2026-11-08 19:18); supporting sources are read
without compilation or mutation.

All 17 source slots now have their proper C++ implementations. Fourteen
have positive ledger-name bindings, including the weak vector-deleting
name's same-class scalar default. The other three are State's existing
loadPostProcess, _bfme_state_slot7 and _bfme_state_slot16: complete C3
bodies with no relocations, matching native State table VA 0x00C605D8
slots 1/7/16 at the already covered RVA 0x000B3FD0. The latter two names
remain neutral placeholders, not recovered retail method names.

At inspection, 0x000B3FD0 and class:State are held by
Burachi-3D@Burak/85351563; AIStateHashCtors0033F2FD.cpp is blocked too.
Those scopes are not edited, compiled or claimed here. This is a missing
name-proof dependency, not an unrowed body or coverage regression. A
later ICF admission needs an actual owner and owner-source fold proof;
Region2D::~Region2D in region.cpp and Coord2D::~Coord2D in coord2d.cpp
are complete twins. There is no general header-inline TU exemption:
B3FD0 has no approved TU, and an AI-source alias reports shadow A1
against region.cpp. Review that identity/TU issue rather than treating
an alias or a placement as source recovery.

Shared-class consolidation, the stale Wind queue identity, inherited
name proof and next-image confirmation remain open. No complete bridge,
image, census or runtime clearance is claimed. The blocked table handoff
is recorded through re_log.py; a mistaken covered-body dependency token
was retracted through the same tool and replaced with the claim/name
dependency. No log is edited by hand.
