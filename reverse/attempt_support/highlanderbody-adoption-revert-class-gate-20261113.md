# HighlanderBody.cpp real-link regression: exact revert refused by class_gate (2026-11-13)

Base 196c1cae97. Served by `next_work.py --claim` as the only source in
`reverse/exit_link_blockers.tsv` (real link at 10efe4859e: 35 missing names; the measures at
43fba69119 and e20d57868b list only the 2 unowned exports).

## Cause (measured)

922e561591 "Register canonical HighlanderBody, adopt it in 3 units" replaced HighlanderBody.cpp's
private `ActiveBody`/`HighlanderBody` views with `HighlanderBodyClass.h`, which includes
ActiveBody.h. The unit defines the constructor, so it emits the class's tables, now with every
ActiveBody.h virtual. `python3 tools/link_check.py Code/GameEngine/Source/GameLogic/Object/Body/HighlanderBody.cpp`
at HEAD: does not link, LINKED 241 -> 0, 35 unresolved `...@ActiveBody@@...` names.

Each of the 35 sits on a retail slot whose body already has a row under another name (tables read
from game.dat: primary 0x00C5B440/0x00C5B038, body interface 0x00C5B390/0x00C5B5B0, BodyModule's
0x00C5AC18). No new source is needed; the rows have to move into ActiveBody/BodyModule. That is
LINK-242 and the ActiveBody inventory in LINK-514, walled since 2026-11-04 by rename.py refusals.

## Repair tried: exact revert of 922e561591

    git revert --no-commit 922e561591
    # one conflict: reverse/canonical_classes.csv; keep HEAD's side minus the HighlanderBody row

Result on that tree:
- `./build.sh` on HighlanderBody.cpp, HighlanderBodyFriendNew.cpp, ModuleFactoryInit.cpp: 319/319 matched.
- `link_check.py` on the three: 3 of 3 link, HighlanderBody.cpp LINKED 241 -> 241.
- `check_csv.py`: OK. No other file references HighlanderBodyClass.h or the contract.

Refused at commit: `tools/class_gate.py --staged` reports HighlanderBody.cpp "declares its own
`ActiveBody`" (the view the unit had until 922e561591; the gate compares with HEAD only and has no
credit for the inverse of an adoption). Not committed; tree restored with `git revert --abort`.

## What clears it

Either of:
- the gate credits a staged unit whose private body equals the one an ancestor commit removed, when
  the same commit removes that adoption's registry row (tooling seat, `Verifier-Change:`); or
- the 35 rows move (LINK-242/LINK-514), after which the adoption links as is.

Not checked: the real link itself (maintainer-run); whether the restored short tables are what the
last crash-free image ran (they are what every image before 922e561591 linked).


## Isolated r22 revalidation at bc02ffea95e (2026-11-13)

Owner `codex-01a1071d-isolated-highlander-r22`; no source, contract or registry
edits. `git pull --rebase origin master`, `check_csv.py`, and official
`worktree_setup.py prepare` / `check` passed in the provided isolated worktree.
The Highlander implementation, factory-new unit, header and contract are
unchanged since 922e561591. ModuleFactoryInit and the registry have unrelated
later changes, which a future complete inverse must preserve.

Fresh claim dry-runs found `class:HighlanderBody` and
`file:Code/GameEngine/Source/GameLogic/Object/Body/HighlanderBody.cpp` held by
`ancalgonn-swarm-sweep-header`; the factory-new file also conflicts with that
class claim. No source scope was acquired or edited. Only evidence files were
claimed for this final records commit.

Current three-file `./build.sh` verification passed **319/319** rows, with
310 string literals and one float literal verified. Direct REL32 bindings in
Highlander's constructor, destructor and attemptDamage match retail targets
0x004BF6A1, 0x004BF951 and 0x004BFE07 and their existing ActiveBody ledger names.
Those valid direct calls do not supply the 35 missing virtual names.

`link_check.py` over the complete three-unit cohort still diagnoses the same
35 unresolved names in HighlanderBody.cpp; its own preview drops 241 -> 0
bytes, while the two other units read LINKS (cohort 17,299 -> 17,058).
**Limit:** the copied read-only ROOT index is 2026-11-13 00:44 at 3d7c5d8f25;
it warns of three added/deleted/renamed source paths. This is diagnostic
old-index evidence, not a current whole-ledger or authoritative real link.
No index update, whole-tree provider preparation or real-link runner was started.

The [35-name slot inventory](highlanderbody-provider-slots-20261113-r22.tsv)
reads the current emitted COFF relocations and native ActiveBody primary/body
VAs 0x00C5B038 / 0x00C5B5B0, alongside Highlander VAs 0x00C5B440 / 0x00C5B390.
All 35 native base-slot targets have existing matched rows, and none has a
matched row under the requested exact symbol. Occupancy and same-address rows
are evidence to investigate, **not approval of a new owner, method name, ABI,
ICF fold or alias**; the TSV caps example names at four and counts all rows.

An additional table-shape prerequisite is visible without any source trial:
HighlanderBody.cpp includes Module.h before BehaviorModule.h, so Snapshot is
already guarded before BehaviorModule can select BFME_SNAPSHOT_NAME_SLOT.
The current primary COFF table places ActiveBody::GetSnapshotName at slot 13,
not retail slot 2; subsequent new primary virtuals shift by one. For example,
vslot14 is emitted at 15 versus native 14. The native leaf slot 2 targets
0x004C07AB, whereas ActiveBody's slot 2 targets 0x004BF88D; leaf slot 1 also
differs (0x004C202F versus 0x004BF40F). Merely providing the 35 symbols would
therefore not prove a correct native Highlander table. Any provider repair
must reconcile the emitted order and leaf overrides as well as ownership.
No speculative repair was tried against the held class.

The previous rollback false reject remains reproducible **read-only**:
`class_gate.introduced` on the pre-922e561591 Highlander text with an in-memory
registry lacking only HighlanderBody returns `['ActiveBody']` at this HEAD.
The current gate hashes to SHA256
`8218c2eaee4b7ad1f63799ac8c818ac46657a3b58c5ec59e1ec05d824221c33c`.
No new rollback, staged-source experiment, naming trial or gate modification
was performed. This confirms the recorded enforcing prerequisite rather than
repeating the failed trial. The existing false-reject verdict above is retained.

Authoritative evidence remains run43414575861 at 10efe4859ee37651bd6b7fdcc15d915325c9b9fa,
2026-11-13 11:39 UTC: **37 unresolved, 0 duplicates, NO IMAGE**, 469 initializer
bridges, 3,331 vtable bridges / 50,310 slots. The two FX export guards remain
separate debt. Copied artifact SHA256s:

- errors.tsv: `621c19906cd033bdc82fa589178a1a66c2854559ad91b6e8b76044c3f4cdef6e`
- scoreboard.json: `4863a08b4a7fe55175bea8cd3d3875807c2d55e1940a84a6ab9a1353cf7b8529`

Next action is still the prerequisite in "What clears it": an independently
reviewed gate correction allowing the coherent rollback, or a supported
provider/identity repair with native table-order/override verification, once
the source owner releases or lands the scope. No repair or game reach is claimed.
