### Inferred-name landings pushed with an INCONCLUSIVE link audit (2026-11-03)

Three `name_lane.py apply` batches landed this session (20, 18, 1 and 16 names across
`4959e5493e`..`f7f2258fa0`). Every one byte-verified at commit (`PRE-COMMIT OK`, sources
byte-verified), but each pre-push `link_batch_audit` returned INCONCLUSIVE — the local census
index sat at `70f7a5ae2a` while the outgoing bases had moved, so up to 19 source objects
"lack current receipts" and the hook reported `linking UNVERIFIED`. Renames change symbol
names, so link effects are not self-evidently nil: treat these units' link state as
**unmeasured, not clean**, and let the next census measure them. No census credit is claimed
for any of them.

Remedy applied: `python3 tools/link_check.py --fetch-index` pulled the current index
(984a4cdc4d, 2026-11-02 08:35, 14,831 objects into the object store), so a subsequent push
from this clone can produce a conclusive audit. No per-unit obstacle is recorded here, because
none was identified — the gap was measurement, not a prerequisite.

**Later pushes the same day, with a current index, were still INCONCLUSIVE (2026-11-03):**
The remedy above is necessary but not sufficient. With the index refreshed to
`8661f15284` (2026-11-03 20:03, 18,233 objects into the object store), two further pushes
from this clone still reported `linking UNVERIFIED`:

- `43744991a7`, the `tu_skeleton --split` carve of row `0x0004C6C6` into
  `W3DGameClient.cpp`: "1 source object(s) lack current receipts; first:
  Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DGameClient.cpp", base
  `e92c82cbb24`. Carried in [LINK-179](link-179-w3dgameclient-donor-slot-and-product-identities-contradict.md).
- `f6db41e10d`, the canonical GameWindowManager adoption in
  `Code/GameEngine/Source/GameClient/GUI/GUICallbacks/ControlBarVisibility.cpp`: the same
  finding against that unit, base `03c2f6340d7`.

Both changes are byte-exact and the adoption passed `header_adopt_lane accept`'s own link
guard, so the gap is again measurement and not a prerequisite: a published index carries
receipts for the objects as they were when the census ran, so the first push that *changes*
an object necessarily lacks a current receipt for it and the batch audit cannot close.
Refetching the index does not help for the object you just edited. Carry both units into
the next scheduled census. No linking, debt or census gain is claimed for either.
