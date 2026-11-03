### LINK-181 Real-link blockers in GameClient and GameEngineDevice (2026-11-03)

Seat halilkkaya-zs-o2. The real link was measured at `96cfeda7ba`; `reverse/exit_link_blockers.tsv`
lists the sources.

**Repaired.** Each unit's unrowed Zero Hour bodies were dropped. Rows, data rows and every name a
census unit takes were kept, and `link_check` over the consumers shows no loss.

| Unit | Real-link error rows | Linked bytes |
|---|---|---|
| SkirmishGameOptionsMenu | 46 | 0 → 98 B |
| LanGameOptionsMenu | 28 | 0 → 65 B |
| WOLGameSetupMenu | 11 | 0 → 23 B |
| WOLBuddyOverlay | 12 | does not link (see below) |
| W3DTerrainLogic | 7 | 0 → 145 B |

- **Menus** (`3670a49f64`): the three units together give 85 error rows, and 51 unique names lose
  their last reference.
- **WOLBuddyOverlay** (`75b05dbceb`): its 17 rows stay exact through address anchors. It still has
  two BuddyInfo-tree COMDAT variants that predate this change, so it does not link yet.
- **W3DTerrainLogic**: drops `loadMap`, `getExtent`, `getMaximumPathfindExtent`,
  `getExtentIncludingBorder` and `crc`.

**Blocked: needs class work rather than body drops.**
- **W3DTankTruckDraw (33) and HeightMap (32).** The kept ZH ctor emits the vtable. The rows
  `TreadObjectInfo` and `Material_Override` need a ctor emitter, and `TreadObjectInfo` is protected.
- **W3DGameClient (10).** Dropping the ZH ctor and dtor needs anchors for `firstDrawable` and
  `getDrawableList` (GameClientDrawableTOC takes them), and for the protected `createGameDisplay` row.
- **Rva0008EF3FProductCtor_Unresolved (35).** The canonical `InGameUI.h` slot names (slot52,
  slot10_xx, crc, ...) have no definers. Retail table 0x00BC7A88 points those slots at ICF-shared
  bodies rowed under other names. The fix is either fold rows (`add_match --icf-owner`) or slot
  renames in the shared header.
- **EvaMessageVectorAssign.** `??1EvaMessageInfo` is retail 0x003F60C8, rowed as
  `??1BfmeStringRecord00111ACF`. The fix is a placeholder-class rename.
- **W3DShaderManagerScreenBWFilterInit and Rva000FDCD7Get.** Both need the unowned screen-filter
  data globals at 0x009B5B54 and 0x009B5BD4 defined.
- **HelicopterSlowDeathUpdate (16, GameLogic).** The 16 names come from its unrowed ZH code calling
  three ZH-only SlowDeathBehavior bodies: `??1`, `crc` and `loadPostProcess`.
  - In retail the dtor is 0x0045D39E, rowed as `??1Rva0045D39E@@UAE@XZ`, so Rva0045D39E is
    SlowDeathBehavior.
  - `loadPostProcess` is the ICF-shared 0x00497805.
  - `crc` has no BFME 2 slot.
  - Fix in the consumer: drop its ZH bodies and keep the `isDieApplicable` row 0x0045D49E emitted.

**SlowDeathBehavior TU merge (2026-11-02).**
- The native seed (`0f8974c269`) drops the ZH chain, and the seed now links (28 B).
- A merge of 5 donors verifies: 18/18 rows exact, the TU goes 0 → 1,372 B, and there is no loss over
  3,316 units.
- `class_gate` refuses the merge. Its `scoped_move_spans` gives no move credit to a composed TU that
  contains a template class head, so the verbatim private UpdateModule/INIException views read as new
  copies.
- The false reject is logged in `reverse/re_attempts.log`. A tooling fix that credits non-template
  spans is needed.

**PlayerList.cpp merge.** It waits on `file:PlayerList.cpp`, held by ancalgonn-ops-srv1 for a
`// cl:` cleanup.
