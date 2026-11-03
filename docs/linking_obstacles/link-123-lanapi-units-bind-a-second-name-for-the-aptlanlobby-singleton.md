### LINK-123: LANAPI units bind a second name for the AptLanLobby singleton at 0x00A03354

**Status: Open. Updated: 2026-10-27.**

- **Scope:** `Code/GameEngine/Source/GameNetwork/LANAPILobbyMenuForwarders.cpp` (105 B)
  and `Code/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp` (5,570 B). Each fails
  `tools/link_check.py` only on the unresolved
  `?g_Va00E03354@@3PAURva004469D1Receiver@@A`, a second binding of data 0x00A03354
  whose ledger symbol (`reverse/data_ledger.csv`) is `?g_Va00A03354@@3HA`, the
  spelling the linking units (LANAPIOnGameCreate.cpp, AptLanLobbyDestructor.cpp,
  Rva00444525Init.cpp) declare.
- **Verified trial (not landed):** declaring `extern int g_Va00A03354;` and casting
  at each use builds 54/54 rows byte-exact and link_check reports both units LINKS
  (0 -> 5,675 B). `tools/hatch_counters.py --staged` refuses it: address_global +9 and
  +7 for token `g_Va00A03354`, because a move must keep each token's total
  (rule 3a), not the hatch's. The patch is recorded in `reverse/re_attempts.log`
  (0x00248E2F, blocked).
- **Remaining / next check:** give 0x00A03354 a real name (the AptLanLobby
  singleton: its constructor stores `this` when unset, AptLanLobbyDestructor clears
  it) through `tools/rename.py global` with an agreed or canonical basis; the
  rename rewrites every consumer, and then the two LANAPI units can declare that
  name with no hatch growth.
- **Canonical name found (b1, 2026-10-28, inspected `2c1055bc13`):** WorldBuilder
  names the slot. Its `AptLanLobby::~AptLanLobby` (wb_va 0x140D710,
  `reverse/wb/wb_decomp.jsonl.xz`) asserts `"!(s_instance != this)"` exactly where
  retail's dtor (AptLanLobbyDestructor.cpp) compares `this` against 0x00E03354 and
  clears it. WB also has an `AptLanLobby::Instance` accessor. The sibling screens follow the
  same pattern; `reverse/data_ledger.csv` already names 0x00A048D4
  `?s_instance@AptCreateAHero@@0PAV1@A` (private static). The target name is
  therefore `?s_instance@AptLanLobby@@0PAV1@A` (basis `canonical:wb`).
  Prerequisites: `tools/rename.py global` refuses it today ("no
  reverse/data_rows.csv row names ?g_Va00A03354@@3HA"), and its `--new` changes the
  identifier only, while this rename changes the scope and type (int to
  `AptLanLobby *`). That means hand-retyping the 12 consumer files (`rg -l
  'g_Va00A03354|g_Va00E03354' Code`): add the private static plus a public inline
  `Instance()` to each AptLanLobby view, so the mangling stays `0PAV1@A`.
- **Repair (b1, 2026-10-28):** the hand rename does exactly that. All 12 consumers declare
  `AptLanLobby::s_instance` (the definer is Rva0050E9D3Enable.cpp, and the AptLanLobbyDestructor.cpp
  ctor/dtor use the member directly), and `reverse/data_ledger.csv`'s row is now
  owned under that single name. `./build.sh` passes 286/286 rows byte-exact. `link_check.py` reports
  LANAPICallbacks.cpp 0 -> 5,570 B and LANAPILobbyMenuForwarders.cpp 0 -> 105 B, and the
  other 9 consumers still LINK. Rva0050E9D3Enable.cpp's preview fails only on
  duplicates `?rva007B83E1@@YAXXZ`/`?rva007B8F26@@YAXXZ`: the census index still
  holds Rva007B6A00AtexitThunks.cpp's copies, which 9b744c61f4 moved after the census (the
  LINK-122 stale-object pattern), so that failure is expected until the next census. The address_global
  counts for both tokens fall to 0 in all 12 files. `hatch_counters.py --update` did not tighten
  `reverse/hatch_baseline.tsv` because of unrelated alternatename growth elsewhere.
  Awaiting census.
- **Clearance:** none.
- **Census confirmation:** not claimed.

**2026-10-27 follow-up, inspected `7db1ac5c68`, index 73061d9452:** link_check now drops a deleted unit's second copies (3d44b2bbcbe, Verifier-Change); ordinary previews of CrateSystem.cpp (447 B), boxrobj.cpp (5,522 B) and dx8wrapper.cpp (28,658 B) LINK, while BitFlagsClear.cpp's real wrong copy (LINK-030) is still reported. Merge previews are therefore conclusive again for units whose moved bodies have a surviving definer. A `tu_skeleton --merge --dry-run` sweep of all 22 queue TUs with no mixed/refused/held rows (registry, HeaderTemplate, quat, AptMpChat, NetCommandList, AIUnitUpgrader, Win32DIKeyboard, thread, RayEffect, AptValueVector, INIMultiplayer, AptValueGCAllocator, frustum, LivingWorldAIInformation, W3DDisplayStringManager, Transport, motchan, udp, UserPreferences, RadiusDecal, TerrainRoads, matpass) accepted no donor: every one needs private-view or flag reconciliation first (seed views lacking donor members, redefined STL/StringBase templates, sweep vs platformsdk headers, carried flag overrides). thread.cpp tolerates the `platformsdk` marker byte-exact, but its donor ThreadClassLifecycle.cpp is claimed by another seat. No merge pushed.
**2026-10-27 merge follow-up:** BitChannelLoadW3D.cpp merged into motchan.cpp (4f9f55f9cd5 donor reconcile: the view's `Free_Inline` became `Free`; d346ae3d08c merge, 19/19 byte-exact, link_check LINKS 984 -> 1,219 B). In the merged TU the out-of-line `BitChannelClass::Free` is auto-inlined into `Load_W3D` as retail does, so a private view's renamed inline copy is only needed while the body stands alone. Still blocked in motchan: AdaptiveDeltaMotionChannelFinish.cpp (view field `DataByteCount` has no counterpart in the seed's 0x24-byte header view; needs a layout reconcile) and AdaptiveDeltaLoadW3D.cpp (includes `<new>`, colliding with the seed's placement new). udp donors reference `rvaXXXXXXXX` placeholder members of their private `UDP` view; matpass donors lose rows under the seed's flag override or have no baseline match.
