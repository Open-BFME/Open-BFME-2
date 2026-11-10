# wsock32 ntohl/ntohs thunks 0x0065565E / 0x006556B8: Import-ref false reject

Target facts (baselines/bfme2/workshop-vanilla-1.06/files/game.dat):

- The import directory (RVA 0x00A72C00) lies in an unnamed appended section,
  and all 23 descriptors have OriginalFirstThunk = 0. VC7.1's linker always
  emits an import lookup table, so the table was rebuilt after link (DRM
  unwrap).
- wsock32 slots 0x00BBA998 and 0x00BBA9A4 both read (hint 8, "htonl");
  0x00BBA98C and 0x00BBA968 both read (hint 9, "htons"). avifil32 0x00BBA05C
  and 0x00BBA064 both read (hint 20, "AVIFileRelease"). A linker gives one
  import one slot; a rebuilder that resolves bound addresses picks the first
  export name at a shared address (htonl/ntohl, htons/ntohs and probably
  AVIFileRelease/AVIStreamRelease share bodies).

Call-site facts (retail E8 into each thunk, symbol read from the matched
consumer objects with the GameSpy macros `#define ntohl htonl` /
`#define ntohs htons` removed):

- 0x0065565E (slot 0x00BBA9A4) callers are the ntohl sites only: nonport.c
  IsPrivateIP, peerMangle.c x2, qr2.c natneg cookie, sb_serverlist.c
  lastSeen/changeTime. The one exception is peerSBGroupsListCallback.c, whose
  BFME 1 import already spells it htonl.
- 0x006556B8 (slot 0x00BBA968) callers are the ntohs sites only: qr2_create_socket
  baseport, SBServerGetPublic/PrivateQueryPort, SBServerParseQR2FullKeys and
  sb_serverlist.c (3), gpiSendLogin.
- 0x00655670 / 0x00655682 callers are the htonl / htons sites only (9 / 32 sites).

Result: `_ntohl@4` / `_ntohs@4` thunks through `__imp__ntohl@4` /
`__imp__ntohs@4` byte-match. build.sh's Import-ref verify refuses them
(`__imp__ntohl@4 0x00BBA9A4: wsock32.dll!htonl`) because it trusts the rebuilt
table's names. With them, the macros in qr2.c, gpiConnect.c, sb_server.c and
sb_serverlist.c and the two `/alternatename:_ntohl@4=?ji_0065565e` hatches
(nonport.c, peerMangle.c) can go.

Tooling fix suggested: let Import-ref accept the ntohl/ntohs (and
AVIStreamRelease) name for a slot whose rebuilt-table name is shared with
another slot of the same DLL and whose export shares the body.

Status 2026-11-10 (lk90): fixed in Import-ref (tools/build.py
`rebuilt_import_partner`) and in the census and real-link import model
(`link_census.retail_imports`, retail-truth-6), both through
`build.rebuilt_partner_names`; `_ntohl@4` / `_ntohs@4` rowed in
Wsock32ImportThunks.cpp; the macros, peerMangle.c's hatch,
peerSBGroupsListCallback.c's htonl spelling and the stale pins removed.
See docs/linking_obstacles/link-658-*.md.
