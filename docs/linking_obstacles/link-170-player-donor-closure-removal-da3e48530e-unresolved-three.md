### LINK-170: Player donor-closure removal (`da3e48530e`) unresolved three Player consumers (2026-11-01, seat halilkkaya-lk12)

Status: Open (partly repaired). Base `6b1a8fb85c`; census 12:39 (`39dfbbdb50`), index `86db074988`.
Found by a current-object `link_check --refresh` over all 18,636 census sources (14 census-linked
units fail; this entry covers three). `da3e48530e` removed Player.cpp's unverified Zero Hour donor
bodies and their 115 incidental helpers. Its audit checked outside callers of removed helper
families in the published index, but three census-linked consumers still bound names only those
donors defined:

| Unit | B | Missing name | Status |
|---|---:|---|---|
| Common/RTS/PlayerList.cpp | 292 | `?removeTeamRelationship@Player@@QAE_NPBVTeam@@@Z` | repaired (below) |
| Common/RTS/RelationMapXfer.cpp | 654 | `??A?$hash_map@IW4Relationship@@...` (`hash_map<unsigned,Relationship>::operator[]`) | repaired 2026-11-02 (lk15, below) |
| Object/SpecialPower/SpecialPowerModule.cpp | 36 | `?getOrStartSpecialPowerReadyFrame@Player@@...`, `?resetOrStartSpecialPowerReadyFrame@Player@@...` | repaired (below) |

PlayerList.cpp: the only caller was its own unrowed Zero Hour `PlayerList::teamAboutToBeDeleted`
(present-unmatched). Retail's body is the 30 B row 0x002A7AFE (`PlayerList::rva002A7AFE`,
PlayerListRva002A7AFE.cpp), which TeamFactory::teamAboutToBeDeleted (0x003A3048) calls and which
calls the rowed per-player 0x002AD19E. Nothing references `?teamAboutToBeDeleted@PlayerList@@`
(source grep; only playerlist.h declares it), so the donor body and its marker go. `./build.sh`
8/8 rows and the data row; `find_declared_unmatched` clean; `link_check --refresh` PlayerList.cpp
0 -> 292 B (current objects), PlayerListRva002A7AFE 30 and Team.cpp 7,862 B unchanged LINKS.

RelationMapXfer.cpp declares `template <> Relationship &hash_map<unsigned int, Relationship>::operator[](const unsigned int &);`
("Player.cpp supplies the same team-relation subscript provider"); Player.cpp's removed donors were
that provider's only emitter (index: one COMDAT, two touching objects). Next check (needs the file):
drop that declaration-only specialization so the unit emits its own subscript, then recheck the
helpers it instantiates against their declared-only suppressions.
Repair (2026-11-02, seat halilkkaya-lk15, base `1765dc430d`): dropping the specialization alone
is not enough: the emitted subscript then needs `resize` and `_M_new_node` for the unsigned-key
table, whose own declaration-only suppressions also had the removed Player donors as their only
provider (index: no object defines either). symbols.csv pins the subscript itself at 0x0041F4E5,
the ICF-shared find-or-insert rowed as `?findSlot@ObjectLookupMap@@QAEPAPAVObject@@PAH@Z`
(ObjectLookupMapFindSlot.cpp, retail-proven copy), the provider PlayerRelationMap::xfer and
rva002ADE71 in the same unit already call through that view. TeamRelationMap::xfer now does the
same and the dead specialization is gone. `./build.sh` 6/6 rows (same bytes, same 0x0041F4E5
callee); scoped DIR32 OK; `link_check` RelationMapXfer 0 -> 654 B. Census confirmation: pending.

SpecialPowerModule.cpp: three unrowed Zero Hour bodies (getPercentReady, startPowerRecharge,
getReadyFrame) called the two removed donor timers. Dropping them is not an option: the linked
CashHackSpecialPower (435 B), DefectorSpecialPower (66 B) and OCLSpecialPower (1,403 B) bind their
vtable slots to these names (index `touches`). Retail's timers are rowed under the receiver-prefix
view `Rva002AC6B1PlayerTimers` (getOrStart 0x002AC7A0, resetOrStart 0x002AC6E1; Zero Hour Player.cpp
semantic donor, WorldBuilder 0xC1DDD0 by callgraph), so the three bodies now call those rows through
that view. `./build.sh` 4/4 rows; `find_declared_unmatched` clean; `link_check --refresh`
SpecialPowerModule.cpp 0 -> 36 B, Rva002AC6B1PlayerTimers 309 B and the three slot consumers
(1,904 B) unchanged LINKS. A real-name rename of the two rows into Player remains identity work
(placeholder-into-existing-class, LINK-063's maintainer decision).
Census confirmation: awaiting.
