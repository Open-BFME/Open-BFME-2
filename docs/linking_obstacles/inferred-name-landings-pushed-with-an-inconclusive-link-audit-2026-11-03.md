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

**The 38-donor Scripts.cpp merge, same shape at scale (2026-11-03, landed `e1ffb0b1df6`):**
`tu_skeleton --merge-all` absorbed 38 sources and 83 rows into
`Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp`. The push hook byte-verified
the result whole — functions 83/83 matched, EH EXACT on all 10 rows carrying EH data,
string/float/import refs OK, DIR32 consistent, `data_check` converged — and the batch
audit still reported `linking UNVERIFIED`: "38 source object(s) lack current receipts;
first: Code/GameEngine/Source/Common/EmbeddedMemberForwarders.cpp", index `984a4cdc4d`,
outgoing base `2be2d0e6d26`. This is the second half of the trap above at its limit: a
merge deletes the donor objects outright, so the count of missing receipts equals the
number of donors absorbed and no refetch can close it. Note also that the worker worktree
carried the 2026-11-02 index (`984a4cdc4d`) rather than the day's newer one — worth
refreshing per worktree, though it would not have changed this verdict. Carry this TU and
all 38 absorbed donors into the next scheduled census. No linking, debt or census gain is
claimed.

The view reconciliation that followed it (`5dd87dfdf6`, 12 sources, 10 shared class
spellings written into `Scripts.cpp` and its files) reported the same verdict for the same
reason: "11 source object(s) lack current receipts; first:
Code/GameEngine/Source/GameLogic/ScriptEngine/ParameterGetUiTextBody.cpp", index
`8661f15284`, outgoing base `14d304ffc61`. Changed declarations change objects, so these
11 join the carry list above. All 12 sources byte-verified (109/109 rows, EH EXACT 24).

The class-key unification (`120d078bdc`, two commits, 27 sources) reported the same
verdict a third time: "25 source object(s) lack current receipts; first:
Code/GameEngine/Source/Common/System/DataChunk.cpp", index `8661f15284`, outgoing base
`9f09ad90206`. The cause is the same and is worth stating plainly for this kind of change:
a class key is part of the mangled name of anything that takes the class as a type, so
unifying `struct` to `class` can rename an external symbol even when every byte of every
body is unchanged. That is a link-identity edit, not a cosmetic one, and an index built
before it cannot carry a receipt for it.

What is positive evidence here: `DIR32 consistency: OK (105 symbols; 0 whitelisted, 0
PE-verified duplicate imports, 0 new)` across the batch's 258 verified rows, and
`EH verify: 38 EXACT`. No row's bytes moved (233/233 plus 25/25). What is not evidence:
the audit itself, which stays INCONCLUSIVE and so counts as unverified. Carry all 25
objects into the next scheduled census alongside the earlier 38 and 11. No linking gain is
claimed.

The three classes the same pass pointed the wrong way were refused by the byte check
before any push, and two of them are recorded above as reverted
(`BfmeObject544`, `Rva00087A93`); the third, `Rva00587375`, is a name the ledger spells
both `U` and `V`, so it is two distinct types and no single spelling can serve the TU.

A fourth INCONCLUSIVE verdict, 2026-11-04, on the smallest possible version of this
change (`d92dd4c134`, two commits, 2 sources): "2 source object(s) lack current receipts;
first: Code/GameEngine/Source/GameLogic/Object/Contain/TransportContain.cpp", index
`8661f15284`, outgoing base `a7d6d877db6`. The edit gave
`TransportContain.cpp` and `TransportContainUpdateUpgradeCreationTriggers.cpp` one
spelling of `BfmeStringRecord00466E64`, a three-field private record. It is worth
recording because it is the case where a reader might expect the audit to come back
clean: the class name, its key (`struct`), its three member names and its layout are all
unchanged, so nothing here can rename an external symbol the way the class-key pass could.
`_STL::vector<BfmeStringRecord00466E64, ...>::push_back` keeps the mangled name it had.

The verdict is still INCONCLUSIVE, and the reason is the index, not the edit: an index
built at `8661f15284` holds no receipt for an object recompiled after it, whatever the
edit did. So this is not evidence that the change is risky; it is evidence that the audit
cannot distinguish a layout-neutral reformat from a link-identity edit once the receipts
are stale. Both carry. Positive evidence for this one: `DIR32 consistency: OK (17 symbols;
0 new)`, `EH verify: 7 EXACT`, and `Functions: OK 34/34`. Carry both objects into the next
scheduled census with the earlier 38, 11 and 25. No linking gain is claimed.

**Correction, same day.** The paragraph that stood here blamed a stale index and told
seats to run `python3 tools/link_check.py --fetch-index` before reading the verdict. That
was wrong, and the next push disproved it within the hour. The fetch did move this
worktree's index from `8661f15284` to `328bb2bbe4` (2026-11-04 12:49, 18,285 objects added
to the store). The very next push (`7c76d63c30`) then read INCONCLUSIVE again, against the
fresh index: "3 source object(s) lack current receipts".

The number is what gives it away. That push changed exactly three sources, and the audit
named exactly three objects; the push before it changed exactly two and the audit named
exactly two. The count is the batch's own changed sources, every time. That is structural,
not staleness: an object you just recompiled cannot have a receipt in an index built before
you compiled it, however new the index is. No fetch can ever cover the sources a push is
currently changing.

So an INCONCLUSIVE audit naming your own changed objects is the expected verdict for every
source-changing push, and it carries no information about the edit. Do not read merit into
it and do not chase it with a fetch. The fetch is still worth doing for its object store,
and a stale index does matter for the *other* objects in a batch - the absorbed donors and
consumers in the 38, 11 and 25 carry lists above, which are not the ones being recompiled.
The real signal for the changed sources stays where it always was: the DIR32, EH and byte
lines. Those objects carry into the next census regardless.
