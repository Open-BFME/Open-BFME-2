### LINK-658: GameSpy ntohl/ntohs bound to the htonl/htons thunks by a rebuilt import table

Status: repaired by the lk90 batch (2026-11-10, unpushed when written). Open after landing: the
`retail-truth-6` re-baseline row (`tools/census_rebaseline.py`, a maintainer run).

**Cause (target facts).** game.dat's import directory was rebuilt after link (appended section,
OriginalFirstThunk = 0 in all 23 descriptors). wsock32's table spells `htonl` on slots 0x00BBA998 and
0x00BBA9A4 and `htons` on 0x00BBA98C and 0x00BBA968, never `ntohl`/`ntohs`. Every retail caller of the
thunks 0x0065565E (slot 0x00BBA9A4) and 0x006556B8 (slot 0x00BBA968) is an ntohl / ntohs site,
including `piSBGroupsListCallback` (call at 0x006A5656 -> 0x0065565E). Evidence:
[`reverse/attempt_support/wsock32_ntohl_ntohs_import_slots.md`](../../reverse/attempt_support/wsock32_ntohl_ntohs_import_slots.md).
Our sources followed the rebuilt names (`#define ntohs htons` / `ntohl htonl` in qr2.c, gpiConnect.c,
sb_server.c, sb_serverlist.c; `htonl` in peerSBGroupsListCallback.c; an `/alternatename:_ntohl@4` in
peerMangle.c), so their bodies relocated to the htonl/htons thunks. Byte verification accepted the twin
import thunk; the census digested the bodies as not retail's. link_rank's top census blockers were the
result: `_SBServerGetPrivateQueryPort`, `_qr2_create_socket`, `_SBServerGetPublicQueryPort`,
`_SBSendPlayerSearchRequest`, `_SBServerParseQR2FullKeys`, `_piSBGroupsListCallback`. Our tools trusted
the same table: Import-ref refused `__imp__ntohl@4` / `__imp__ntohs@4`, and `link_census.retail_imports()`
(census excuses, the real link's import libraries, `link_batch_audit`) did not import them.

**Repaired (lk90 commits, in landing order):**

1. `tools/build.py` Import-ref admits a typed import of the shared-body partner at a rebuilt table's
   duplicate slot (`rebuilt_import_partner`; both twins taken as the partner are refused).
2. `retail-truth-6`: `link_census.retail_imports()` adds the partners the rebuilt table hides, through
   the same test (`build.rebuilt_partner_names`: wsock32 htonl/ntohl and htons/ntohs only; the name on
   exactly two slots of the DLL, the partner on none). On game.dat it adds exactly `ntohl` and `ntohs`
   (735 -> 737 names). `link_cycle.import_def_entries` reads it, so exit_link.py's import libraries now
   carry `ntohl@4` / `ntohs@4` (listing call on Wsock32ImportThunks.obj: nothing missing; the old model
   left both missing). `RULES` moved to `retail-truth-6`; `census_rebaseline.py` measures
   `retail-truth-5` with its own tool.
3. `_ntohl@4` 0x0065565E and `_ntohs@4` 0x006556B8 rowed in
   `Code/Libraries/Source/Win32/Wsock32ImportThunks.cpp`, replacing the `?ji_0065565e` / `?ji_006556b8`
   gen-import placeholders.
4. The four macro blocks removed; 5. peerMangle.c's `/alternatename:_ntohl@4` removed; 6.
   peerSBGroupsListCallback.c calls `ntohl` (the 2007 SDK text it follows reads `ntohl` too; donor fact,
   kept apart from the call-target evidence).
7. The stale pins `_htonl@4`@0x0065565E and `_htons@4`@0x006556B8 (second names on the new rows'
   addresses) and the redundant `_ntohl@4`@0x0065565E pin removed; no built object needed them (33
   referencing sources, 924/924 matched).

Measured with `link_check` against the census of 2026-11-10 17:31 (60189f9ced), the index's import
excuses recomputed by the working tree's `retail_imports()` (as the next census index stores them);
every changed body `./build.sh`-exact:

| unit | LINKED before -> after |
| --- | --- |
| serverbrowsing/sb_server.c | 0 -> 2,614 |
| qr2/qr2.c | 0 -> 7,510 |
| serverbrowsing/sb_serverlist.c | 0 -> 8,381 |
| serverbrowsing/sb_queryengine.c | 0 -> 1,703 |
| peer/peerOperationsListGroupRooms.c | 0 -> 3,670 |
| peer/peerMainBlockingOperations.c | 0 -> 9,114 |
| peer/peerSBAutoMatchRating.c | 0 -> 921 |
| peer/peerAutoMatchJoinRoom.c | 0 -> 167 |
| peer/peerSBGroupsListCallback.c | 0 -> 278 |
| peer/peerSBInit.c | 0 -> 322 |
| Win32/Wsock32ImportThunks.cpp | 144 -> 156 |
| gp/gpiConnect.c, nonport.c, peer/peerMangle.c | LINKS -> LINKS (4,252; 2,989; 801) |

Total 8,186 -> 42,878 over the 16 checked units; none goes from LINKS to "does not link". With the
published index's own excuses (`retail-truth-5`) Wsock32ImportThunks.cpp reads 144 -> 0 until the next
census index. `tools/link_batch_audit.py` over the batch is INCONCLUSIVE locally: 16 objects lack
current receipts (the GameSpy C units' shim includes are uncacheable, so `link_check --prepare-current`
cannot give them strict receipts; LINK-651).

**Open.**

- After landing, the maintainer runs `python3 tools/census_rebaseline.py --commit` on the frozen
  origin/master with census publishers paused; until that row exists `check_history_rules` refuses an
  ordinary census (the last row is `retail-truth-5`).
- `reverse/hatch_baseline.tsv` (claimed by ancalgonn-swarm-sweep-hatch on 2026-11-10) still reads
  peerMangle.c `_ntohl@4` alternatename 1 and pins 0x0065565E 2, 0x006556B8 1; the files now hold none,
  so `hatch_counters.py --update` lowers them.
- `Thread/PeerThread.cpp` (18,622 bytes) still waits on `?allocate@?$allocator@G@_STL@@QBEPAGIPBX@Z`
  (its own copy differs from the first in link order); its `_SBServerGetPrivateQueryPort` selection
  clears with this batch.
- C++ dllimport sites still spell the rebuilt names at the partner slots (`htonl` read from 0x00BBA9A4,
  `htons` from 0x00BBA968 in udp.cpp, FirewallHelper.cpp, Rva00447909Copy.cpp, Transport.cpp,
  IPEnumeration.cpp, NetworkUtilResolveIP.cpp, StagingRoomGameInfo.cpp, InitializeAssetManager.cpp,
  PeerThread.cpp); Import-ref keeps accepting them on the table name, so their spelling is a separate
  cleanup.
- avifil32's `AVIFileRelease` (0x00BBA05C, 0x00BBA064) and msvcr71's `_strcmpi`, `abs`, `fgetc`,
  `fputc` show the same duplicate-slot pattern; neither Import-ref nor the import model admits a
  partner for them without call-site proof.
