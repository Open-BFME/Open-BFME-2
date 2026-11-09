# The 29 destination TUs behind the merge lane, and which of provisional()'s three conditions each one fails

Measured at `490ff921b41`, 2026-11-09. Third note of the day; it turns
`merge-blocker-remedy-is-unreachable-20261109.md`'s "17 TUs / 615 donor files
are CARVABLE once approved" into a per-destination work list.

## Where this sits

The chain, each link measured earlier today:

1. 139 TUs are refused before any donor is weighed; 80 hold 2+ donors
   (1,513 donor files).
2. 47 of those 80 are blocked by a row whose destination the map only
   **proposes**, so AGENTS.md forbids the move.
3. Of those, **17 TUs (615 donor files) have a blocking row with a real body** --
   `identify()` finds exactly one definition span -- so approving the
   destination would make a split attemptable. The other 25 are
   header-resident COMDATs no approval can help.
4. Those 17 (plus 5 mixed) point at **29 destination TUs**, over 21 distinct
   blocked TUs. **None of the 29 has a file in the tree**, and all are
   unanchored, so each would have to come through `tu_map.provisional()`.

`provisional()` approves an unanchored TU, grouped by its rows' N/U hints alone,
when three things hold: it has at least `PROV_MIN` (2) approvable rows with
islands excluded; no row that could be approved for another root or candidate TU
sits inside its span (`SPAN_BREAKERS`); and its span overlaps no anchored TU's
reach.

## Which condition each destination fails

| destinations | blocked TUs | donor files | verdict |
| ---: | ---: | ---: | --- |
| 12 | 9 | 176 | **SPAN BROKEN** -- another TU's rows sit inside its span |
| 9 | 8 | 181 | **TOO FEW ROWS** -- 1 approvable row, needs 2 |
| 7 | 5 | 348 | **OVERLAPS AN ANCHORED TU** |
| 1 | 1 | 2 | already anchored (its blocker is proposed for another reason) |

Donor files are counted once per blocked TU, and a TU appearing under two
verdicts is counted under both, so the columns do not sum to 21 or to 615.

### TOO FEW ROWS -- the one mechanical subset (9 destinations, 181 donor files)

Each of these holds exactly **one** approvable (N/U) row and needs two. One more
row in the same address cluster, carrying a name whose `<dir>/<Class>.cpp` hint
names the same file, tips it over. That is naming work with a defined
consequence, not a judgement about layout.

| donors | destination | unblocks |
| ---: | --- | --- |
| 83 | `attackorders.cpp` | LivingWorldLogic.cpp |
| 27 | `siegeenginecontain.cpp` | HordeSiegeEngineContain.cpp |
| 27 | `dualindexeddispatchthunk.cpp` | PeerThread.cpp |
| 27 | `bfmestagingcreationcrcs.cpp` | PeerThread.cpp |
| 23 | `dx8wrapperstagehelper.cpp` | dx8wrapper.cpp |
| 9 | `overridable.cpp` | LargeGroupAudio.cpp |
| 8 | `manthewallsspecialpowerslotview.cpp` | ManTheWallsSpecialPower.cpp |
| 2 | `die.cpp` | SpecialPowerCompletionDie.cpp |
| 2 | `made002cc8a4.cpp` | MetaImpactNugget.cpp |

`siegeenginecontain.cpp` is the best-evidenced of them: it already has **4
WorldBuilder leads** (`SiegeEngineContain::createPayload` 0x0047BBA7,
`SiegeEngineContain::addToContainList` 0x0047C07F and two more).
`livingworldregionmanager.cpp` has 18 leads but fails on SPAN BROKEN instead.
WorldBuilder paths are donor facts and anchor nothing on their own; they are a
place to look for a real name, not a reason to approve.

### OVERLAPS AN ANCHORED TU -- the biggest, and not naming work (5 TUs, 348 donor files)

This group holds the two largest prizes in the lane, and for both the obstacle is
a layout question, not a missing name:

- `objectrecoveryhelper.cpp`, which blocks **`Object.cpp` (208 donor files)** --
  an anchored span reaches into `0x0028CA4D..0x0028CA92`.
- `aiattackpositionaimattargetstate.cpp`, `aiattackmeleeengagestate.cpp` and
  `aifollowpathasteamstate.cpp`, which block **`AIStates.cpp` (109)** -- anchored
  spans reach into `0x0034A570..0x0034A871`, `0x003497E6..0x00349D26` and
  `0x0034E307..0x0034E5B5`.

An anchored TU's span covering these addresses means the map currently believes a
file with hard (F/Z/S/L/W) evidence owns that range. Either that anchor's extent
is wrong, or these classes really do share the anchored file -- which is the `U`
signal's question, and `contested()` in `tu_map` already documents how badly a
wrong answer propagates (one row at 0x004A0E47 "merged the whole class into
SupplyCenterDockUpdate.cpp, whose span then covered RepairDockUpdate"). Resolving
one of these is worth more than everything else in this note put together, and it
needs the `--tier tu-evidence` treatment, not a name.

### SPAN BROKEN (12 destinations, 9 TUs, 176 donor files)

Another candidate TU's approvable rows are interleaved with this one's. Three of
them are mutual -- `livingworldregionmanager.cpp` and
`livingworldregionbonusrule.cpp` break each other's spans, as do two
`eastringc.cpp` spans against `eastring.cpp` -- which is the signature of two
classes sharing one retail file rather than of a wrong extent. `playerposition.cpp`
is the cheapest: only **3** `maputil.cpp` rows sit inside
`0x003023B8..0x003039E8`, against 99 for `gamespyinfo.cpp`.

## What this does not claim

- **Not that approving a destination lands a merge.** It makes the split
  *attemptable*. Of today's 24 attempted carves 23 refused, several after a clean
  carve, so attemptable is a long way from landed.
- **Not that any of these TUs should be approved.** The three conditions are
  `provisional()`'s, and whether a given span or anchor is right is exactly the
  evidence question the tu-evidence lane exists for. Nothing here asserts a TU.
- **Not a measurement of the whole tu-approval queue.** That queue holds 1,373
  TUs with 7,160 proposed rows. These 29 are only the destinations that would
  unblock a merge; approving others still raises TU-APPROVED.
- **Not reachable by renaming anything by hand.** A `TOO FEW ROWS` destination
  needs a second row whose real name genuinely places it there. Inventing a name
  to reach `PROV_MIN` would be fabricating evidence.

## Method

`tu_map.provisional()` was wrapped to capture the real `assigned` (35,134 rows),
`roots` (723 anchored TUs) and `lo_hi` (2,289 spans) that `tu_map.build()`
derives, and its own three conditions were then re-run per destination as a
report. `current_rows()` serves rebuilds from the shared picker cache, so
`build()` had to be called directly -- it is documented as a pure function of the
inputs and is exactly what that cache stores. Nothing was reimplemented except
the explanation, which is the habit this lane has had to learn twice: a
hand-rolled stand-in for a tool predicate over-reported by 38% earlier today, and
a plausible-looking extra wall of my own hid the day's only landing.

One figure in the first run of this diagnosis was wrong and is corrected here: a
per-verdict donor total summed a blocked TU once per destination, so TUs with
several destinations (AIStates.cpp has three) were counted repeatedly, and the
line was labelled "up to" while holding a sum.
