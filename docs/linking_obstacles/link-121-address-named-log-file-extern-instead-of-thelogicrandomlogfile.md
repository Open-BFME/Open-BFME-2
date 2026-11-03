### LINK-121: address-named log-file extern instead of `theLogicRandomLogFile`

Status: two consumers repaired; alternate-name hatches remain. Updated: 2026-10-27; preview index: 73061d9452.

Evidence: `tools/link_rank.py` listed `?g_00DFEFF0@@3PAXA` as the sole blocker of
GameLogicInit.cpp (28,160 B) and ThingFactory_newObject.cpp (344 B). Both declared
`extern void *g_00DFEFF0;`, a second, C++-mangled name for the global at VA
0x00DFEFF0, while every linking consumer declares `extern "C" void
*theLogicRandomLogFile;` (the `_theLogicRandomLogFile` name `reverse/data_ledger.csv`
records for 0x009FEFF0).

Completed (claude2): both units now declare and use `theLogicRandomLogFile`.
GameLogicInit.cpp builds 195/195 and ThingFactory_newObject.cpp 2/2 matched with
string, float and import refs verified. `link_check.py` against the 73061d9452
index: 2 of 2 LINKS, LINKED 0 -> 28,504 B (prediction only; census confirmation
pending).

Remaining: the `?g_00DFEFF0@@3PAXA` pin (`reverse/symbols.csv`) and the two
`/alternatename:_theLogicRandomLogFile=?g_00DFEFF0@@3PAXA` hatches in
Rva00395F57CanUnpack.cpp and Rva0054467AFinish.cpp (held by another seat at the
time) still bind the address name. Once no source references it, remove those
hatches through the hatch path and rename the pin to the real name.

Also completed (claude2, same pass): Rva007B6880Thunks.cpp (909 rows, 9,050 B)
had the sole blocker `?ScreenCurrentShader@@3IA`, a stray name for VA 0x00DEE5D8,
which `reverse/data_ledger.csv` and dx8wrapper.cpp define as
`DX8Wrapper::render_state` (protected static). Thunk 0x007B6FD0, the global's
destructor thunk, now names it through a minimal DX8Wrapper view that befriends
the thunk. Builds 909/909 matched; `link_check.py` predicts LINKS 0 -> 9,050 B
(census confirmation pending).

Blocked (claude2, same pass): LANAPICallbacks.cpp (5,570 B) and
LANAPILobbyMenuForwarders.cpp (105 B) have the sole blocker
`?g_Va00E03354@@3PAURva004469D1Receiver@@A`, a second, typed name for the LAN
menu pointer at VA 0x00E03354. Every other consumer binds the ledger owner
`extern int g_Va00A03354;` (Rva0050E9D3Enable.cpp). Rebinding both units to it
and casting to their views built 50/50 and 4/4 matched, and `link_check.py`
predicted 2/2 LINKS, 0 -> 5,675 B. `hatch_counters` refused the commit:
moving 9 + 7 address_global occurrences from key g_Va00E03354 to key
g_Va00A03354 counts as growth, and `--update` cannot move them across keys.
Reverted and recorded as a false reject in `reverse/re_attempts.log`. Next: a
tooling seat lets `--update` move a same-address rename between keys, or the
global's real name is recovered (no BFME 1 or WorldBuilder name found; BFME 1
also uses an address name).

Also completed (claude2, same pass): Rva0073F895Fade.cpp (2,027 B) had the
sole blocker `?g_mapperProjectionUpload_009EDBF0@@3VMatrix4@@A`, a stray name for
VA 0x00DEDBF0, which the ledger and dx8wrapper.cpp define as
`DX8Wrapper::DeviceProjectionMatrix` (protected static). The TU's shim
dx8wrapper.h omits that member, so the unit now binds the mangled name the way
TextureMapperApply.cpp does, with no shared-shim edit. Builds 6/6 matched;
`link_check.py` predicts LINKS 0 -> 2,027 B (census confirmation pending).

Open leads (claude2, same pass; not edited):

- DynamicDecalFXNuggetDoFXPos.cpp binds `g_00DEC2D4` for VA 0x00DEC2D4. Retail
  `8b0dd4c2de00` (mov ecx,[0x00DEC2D4]) at doFXPos 0x001E0E43+238 and at
  TerrainResourceClaimFeedback 0x004E7FCA+313 shows the address is
  `TheProjectedShadowManager`, defined in W3DProjectedShadowUpdate.cpp (links);
  TerrainResourceClaimFeedback.cpp already links through it. The ledger's owner
  names it `g_00DEC2D4` in Rva0029E159Audio.cpp. Next: rename the ledger owner
  to `TheProjectedShadowManager` and rebind both consumers (the file was held by
  another seat during this pass).
  **2026-10-28 follow-up (codex):** removed that duplicate unrowed definition;
  all nine affected sources now bind the existing
  `ProjectedShadowManager *TheProjectedShadowManager` owner in
  W3DProjectedShadowUpdate.cpp, casting to existing private views where needed.
  An explicit verified data row supersedes the heuristic owner at RVA
  0x009EC2D4, and data_converged.csv protects the single name. Bounded singleton
  binding cleanup verified: 74/74 function rows, 2/2 data rows, 13/13 EH rows,
  zero data/convergence findings, and ten available ordinary link previews
  pass against index 73061d9452. The decal unit already linked before this
  cleanup; no new census gain is claimed. Merged W3DShadow.cpp is absent from
  that index, so its current link closure and census confirmation remain open.
  Evidence and donor/target separation:
  reverse/attempt_support/20261028-projected-shadow-singleton.md.
- Rva00415704Ctor.cpp (90 B) fails on unresolved
  `??1Rva0022A809Subsystem@@UAE@XZ`, whose provider Rva00415CABDtor.cpp (272 B)
  itself fails: comdat `??_7Rva0022A809Subsystem@@6B@` differs from the first
  copy in link order. SubsystemInterface.cpp:274 declares the class as an empty
  `SubsystemInterface` subclass with an implicit destructor (its slot vtable
  emits a different `??_7`), while Rva00415CABDtor.cpp, Rva00415704Ctor.cpp and
  OpaqueScalarDeletingDtorsB10.cpp declare a user virtual destructor.
  Prerequisite: one class declaration for `TheCrowdResponseStore`'s type (a
  shared header with the real destructor) used by all five units.
  **2026-10-28 current-input recheck (codex, `bd82c0156d2e`):** this historical
  constructor lead is superseded by LINK-112's landed repair. All four ctor
  rows pass the normal build; a joint ordinary preview with
  Rva00415CABDtor.cpp and OpaqueScalarDeletingDtorsB10.cpp reports 3/3 LINKS
  (90, 272 and 544 authored bytes, index `73061d9452`). No source edit was
  needed. [Receipt](../../reverse/attempt_support/update-e038-guard-data-index-20261028-codex.md).
  Census confirmation remains pending.

**2026-10-27 follow-up (lk1, inspected `d16a31e4dc`, index 73061d9452), same cause, a table this time:**
`BfmeThreeHundredThirtyFour.cpp` (22 B) failed only on `_bfmeVftSF`, a stray name for
the 0x00816778 table. `reverse/data_ledger.csv` names that table `??_7Rva00360243@@6B@`
and lists `_bfmeVftSF` as an alias. Rva00360474Ctor.cpp defines that name, and its
rowed ctor 0x00360243 stores the same 0x00C16778. 4e4c99282a binds the defined name;
`tools/dir32.py` resolves both stores to 0x00C16778. 1/1 rows exact; link_check 3/3
LINKS with Rva00360474Ctor.cpp and Rva0035FF76FamilyInitDraw.cpp (0 -> 22 B,
prediction only). A sweep of every current unresolved name against the ledger's
alias lists found no other alias with a defined owner, apart from LINK-123's
`g_Va00E03354`. The class still has three spellings (BfmeThingSF, Rva00360243,
Rva003601C5; re_attempts 80298), which needs a class reconciliation.
