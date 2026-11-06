# Making matched code link

AGENTS.md states the rules; this is the measurement, the tools and the BFME 1
linking pass, moved from AGENTS.md ("Make matched code link") in 2026-10.

A matched row whose unit cannot link is half done.

While inspecting a link repair, clarify unclear locals/parameters using the code
context you already loaded. The default picker's selected-work JSON and text,
`repair_queue.py link`, and `link_rank.py --file SOURCE` include a scoped naming
handoff for that source. After the repair edits, use the same worker/claim owner
and `name_lane.py scoped next --files SOURCE --functions 'Class::method'` for the
complete functions inspected, followed by native-child proposals, parent review
and combined application (`docs/naming.md`). Update the scope if the repair changed
the function's name. Keep clear names and unknown roles; do not fill a quota from
unrelated files. Naming does not clear a link blocker, replace link verification
or delay publishing the primary fix.

## Shared obstacle register

Search the [obstacle register](linking_obstacles.md) (one file per entry in
`linking_obstacles/`) before selecting linking work, including a link task served by
the default picker. Check its evidence and
prerequisites against current source and providers before repeating an attempt:
the ranking can still contain repairs that landed after the last census.

Read the [linking target checklist](linking_targets.md) alongside the register.
It preserves 50 named census leads, their byte counts and follow-up status.
Update affected rows with the repair or attempt evidence and remaining blockers.

Update the entries you worked on in the same commit as a repair or substantive
attempt handoff, and before ending the pass. Record what was completed, new
obstacles, remaining dependencies and the next useful check. Add a new stable ID
for a distinct cause. Keep cleared entries with their proof; reopen them when new
evidence contradicts the clearance. Follow the register's status and update
format. It supplements claims, attempt evidence and debt registers; it does not
replace their required updates or retire debt.

After pulling or rebasing, reconcile other agents' updates before publishing.
A current-object preview can clear its stated repair scope, but only a new census
can change the headline. Record those outcomes separately; do not add overlapping
preview gains or treat an old blocker list as a current link result. Existing
restrictions on maintainer-only measurement runners still apply.

## The census is not the build

The census says whether each file links under `/FORCE`. The real link says whether the game
builds. Read [automation.md](automation.md) for its result. A linker-invisible gap (an initializer,
a vtable, a data table) passes both, so neither alone means the game runs.

Exit-link omission needs each omitted `uw_gen` funclet emitted by an EXACT kept parent. Take a
funclet's parent from retail's FuncInfo table, never adjacency. A `.text$x` difference of one or two
bytes in a parent is usually a member's real offset (`add ecx,K`); its body can match either way,
because the view's padding hides where the member starts.

`reverse/exit_link_blockers.tsv` lists the sources the last real link stopped on, and the link tier
serves them first. Most missing names come from a function the ledger does not know: a donor body
retail never had. Row it, or remove it if retail lacks it (`find_declared_unmatched.py`, "Frozen
files"). A virtual one also needs its vtable slot resolved: the slot's retail function may already
have a row under a placeholder name, in which case the fix is a rename.

## How the census decides

`reverse/link_status.csv` and `tools/link_census.py` measure linking under
Open-BFME-1's rules:

- A COMDAT copy loses when retail's bytes prove it wrong. Since `retail-truth-3`
  it does not lose when another object supplies the retail-proven copy, which the
  link keeps and runs. Since `retail-truth-4` an unproven copy does not lose
  either when the copy the link keeps (the first in link order) is retail's.
- Otherwise a copy loses when it differs from the first copy in link order; never
  by majority, STLport included. Since `retail-truth-2` it does not lose when the
  name has no retail address and nothing the link keeps references it.
- A file fails when a name it touches resolves to a kept definition proven not
  retail's (`wrong_selected`).
- Link order is retail's layout: an object goes by the lowest retail RVA of its
  own rows (`link_census.code_places`; `link_check.link_rank`, tu_skeleton's
  merge guard and `allowed_symbols` reuse it). Since `retail-truth-5` a row
  whose address another object's row also claims (an ICF fold or over-claim,
  marked `fold-proof=` or not) does not place its object, unless every row of
  the object is one (LINK-133). Before then a folded row at a low address could
  move a unit megabytes ahead and make its non-retail COMDAT copies the kept ones.

The census counts only objects proven current by census receipts and records
nothing if objects, inputs or tools move during the run. Each
`reverse/link_census_history.csv` row names its `rules`; a rule change is recorded
once, by `tools/census_rebaseline.py`, never by hand.

## The census index

The index is `build/link_census/link_index.pkl`. Download the last published one
with `python3 tools/link_check.py --fetch-index` rather than running a census for
it. It also brings the published tree's compiled objects, which builds reuse when
source and headers match, so run it after pulling instead of recompiling what
others changed. A census or a follower of master (`--update-index`) publishes with
`python3 tools/link_check.py --publish-index` after its commit is on master.

## Tools

- `python3 tools/link_rank.py` ranks blockers by the matched bytes they hold out
  (`--file SOURCE` for one unit, `--near` for units close to linking). Prefer work
  that unblocks the most bytes.
- `python3 tools/link_check.py SOURCE...` (or `--staged`) predicts, without
  link.exe, whether units link after your change; `--refresh` first recompiles
  objects other commits made stale.
- `python3 tools/name_globals.py` replaces hard-coded global addresses (the
  largest blocker class) with the ledger's globals, keeping rewrites that still
  byte-match.
- `python3 tools/rehome_rows.py [--apply]` moves rows from split-out units back to
  the home unit that already compiles an exact copy (rows move only into the
  approved unit: AGENTS.md hard rules).
- `python3 tools/repair_queue.py link` serves rows the last link cycle did not
  place or wire.

## Reconcile classes, not just bodies

For unused private declarations left behind by file splitting, use
`python3 tools/class_views.py --unused --under Code/GameEngine/Source/Common --top 20`.
This ranks textual class heads without a full class-layout survey, then runs the
existing conservative `tu_skeleton.prune_unused_classes` check. By default it
inspects 350 ranked matched authored sources; `--scan-limit N` changes that
scope (`0` inspects all), and `--files SOURCE...` selects explicit sources.
Positive and negative results are content-keyed by source, current reachable
macro tokens and parser/pruner version. Header/macro changes invalidate the
relevant result; cached proposals never approve an edit.

Add `--apply` to claim and verify a bounded batch (at most 25 files), skipping
held or already-modified sources. The command checks declared-unmatched bodies,
byte-verifies originals and results through the normal scoped builder, and
compares all non-debug object contents, relocation targets, external definitions,
COMDAT policies and weak bindings. A bijective renumbering of named sections is
permitted; changed contents or bindings are refused. Failed units are restored
and rebuilt; passing units remain for normal review, commit and push. The command
never commits or pushes. Release its file claims after publishing. `--json PATH`
saves candidates, refusals, cache counts and timings for subsequent runs.

Private per-unit views of one class cause most COMDAT and unresolved blockers.
`python3 tools/class_views.py` ranks classes by private views (`--blockers`: by
what the census holds against them; `--class X` and `--shims X` list the views and
competing shim headers). A class with a shared header is registered in
`reverse/canonical_classes.csv`, and `tools/class_gate.py` refuses new private
copies of it. To give a class a canonical header, follow
`python3 tools/header_adopt_lane.py order`: `tools/class_contract.py` decides its
ABI from evidence (bytes, retail access, retail vftables, ZH, majority), and
`header_adopt_lane.py run --generate --apply` generates the header, gates each
unit and queues the rest in `reverse/header_queue.tsv`. The swap renames a unit's
private field names to the header's (one offset and size is one field). For a
class whose merge donors still mostly carry private views, adopt unit by unit
without registering: `header_adopt_lane.py adopt --class X --header PATH FILE...`
(`--apply` writes the units that byte-match). Trials share one scoped byte-verifier
process per cohort/header variant, splitting a failed cohort to retain individual
diagnostics. `accept --class X FILE...` also shares the byte setup and previews all
byte-passing objects together; only individually passing rows leave the queue.
The header tier serves bounded class batches (up to 25 files and about 6,000 path
characters), with every chunk of a larger class available. Its `sources` field
and start/accept commands name the whole batch; `source` remains its anchor for
older consumers. Adoption claims the class, the frozen header and this cohort's
source files. A peer-held private-view-only consumer in another cohort does not
block this one. The class claim still protects the shared definition and its member
providers; establishing or changing a header keeps its broader dependent scope.
`class_views.py`, contract discovery and bulk adoption share a content-keyed
private-declaration inventory: every query reads current contents, but unchanged
contents reuse their parsed declarations. A first single-class query prefilters
class heads instead of building the whole inventory. Compiled layout, byte and
link checks remain required.

Commit and push hooks also batch retired header-queue rows through the trusted
base's adoption checks: one byte gate per bounded cohort, individual structural
verdicts and combined link previews of byte-passing consumers. Byte failures are
isolated by the lane's normal bisection; missing link results still refuse
retirement. Staged/outgoing input checks run before and after judgment. The
hooks also record successful header-debt verdicts in this clone's receipt store.
A retry can reuse them only when the tracked verification inputs, trusted and
working verifiers, ordinary compiler/dependency currency, exact objects and
dependency receipts, retail image, census index and environment still match.
Structural/include checks and staged/outgoing tree binding always run afresh.
Documentation and raw naming-vote changes alone do not invalidate them.
Missing proof runs the normal
checks; changed inputs during reuse refuse retirement. Other push audits still run.

Before probing a class-key change (`struct`/`class`), the lane predicts its row-name
changes and uses `name_dependents` to discover code and data consumers in one shared
scan. A missing caller produces a `symbol dependencies` diagnostic listing the
units to reconcile; no candidate source/ledger write or byte trial occurs. The
lane never edits or claims outside callers automatically. Connected provider/caller
groups must pass together: a byte failure, held unit or link refusal cannot leave
only half the group applied. Survivors are reverified if a failed rename changes
the temporary resolver. `accept` checks already-applied row changes against HEAD
before retiring debt, so manual adoptions get the same early guard. Discovery
errors refuse approval; symbol-preserving work skips this scan. Normal commit and
push hooks still provide the final checks over affected callers.

Class-key row planning resolves MSVC's name and argument-type backreferences;
it changes only U/V type-key characters whose resolved qualified type is the
requested class. Template name tables stay local; nested function signatures
share the argument-type table. Unrelated types, reference digits and all other
characters are preserved. Unsupported grammar, invalid references and mixed
keys for the same type refuse the whole unit. The lane also refuses a rename
whose old name occurs in active metadata, pins, data or debt registers, or whose
target already exists or is tombstoned: its narrow ledger writer cannot migrate
those families. This guard runs before trial source writes. A canonical-header
key change still needs an explicit complete consumer and metadata migration;
already-adopted header users are not automatically selected by the private-view
adoption lane.

The header tier serves
classes by the queued TU-merge donors their header unblocks:
`header_adopt_lane.py order --merges [N]` lists them (private views in one
approved TU that tu_views cannot reconcile, or private copies of a registered
class; textual, `--refresh` recomputes), never ranking a prerequisite (a base,
an earlier DEPENDENCY_ORDER stage) below what needs it. The ranking lives in the
shared picker cache (`<git common dir>/bfme-picker-cache/merge_blockers/`).
The picker never computes it: on a miss it ranks by DEPENDENCY_ORDER and starts
one locked background refresh (never in CI or under pytest). Classes without a
header there are served as `class-header-establish` items. These claim the
class, its header destination (from BFME 1 or ZH, `header_adopt_lane.py dest
--class NAME`; an ambiguous one is left for the seat to choose) and its merge
donors. `run --apply` claims the other units it rewrites just before writing
them, refuses if another worker holds one, and `header_adopt_lane.py release
--class NAME` gives them back after the push. Items go to `run --generate`
first; only a contract with undecided virtual slots sends the seat to write the
header by hand. Claim scope-wide work:
`python3 tools/claims.py claim class:NAME` or `file:PATH`.

Bulk mode: `header_adopt_lane.py run --all` walks the establish classes in
`order --merges` rank, a class never before a ranked base it names. For each
class it claims `class:X` (a held class or unit is skipped and recorded), runs
the contract, `--generate` with every variant (`includes` among them) and a
trial apply. It then drops each adopted unit whose `link_check` prediction loses
census-linked bytes or gives no verdict, and commits the class on its own. What
it cannot decide goes to `reverse/header_decisions.jsonl`, one record per class,
ranked by merge donors unblocked: an undecided contract attribute with its
competing candidates, a slot no view can declare, a base without a header, no
destination, no adopting unit, a link regression, a refused commit or a held
claim. The header tier serves these as `class-header-decide` items in place of
establish items. `--resume` skips classes a pass adopted or queued,
`--budget-min` stops starting classes, `--jobs N` runs classes that share no
unit side by side, `--only CLASS...` retries a decision, and `--dry-run` only
reports. Push the class commits, then `header_adopt_lane.py release --class X`
and `claims.py release class:X`.

## A dedicated linking pass: BFME 1 repairs first

In a dedicated linking pass, sweep BFME 1's linking repairs before rediscovering
shared fixes: compare BFME 2's ranked blockers with `reference/open-bfme-1`'s
linking repairs, canonical headers and dependency reconciliations and their
verification evidence, prioritizing shared library and engine families. Routine
linking and small dependency repairs proceed directly.

- Track the donor revision reviewed and whether each repair is inherited,
  applicable, blocked or inapplicable; revisit blocked ones when their
  dependencies or donor evidence change; do not repeat an unchanged donor scan.
- Try a donor repair directly where BFME 2 evidence supports it, then adapt it.
  Preserve BFME 2 layouts, addresses, ABI and behavior, verify affected bodies and
  check providers and consumers together: a BFME 1 linking result is a lead, not
  BFME 2 proof.
- After a repair succeeds, sweep BFME 2 units with the same supported cause, batch
  the compatible fixes and refresh the blockers; continue with independent
  candidates when a repair needs unrelated investigation.
- Accumulate verified linking repairs and push them in batches rather than
  pushing each repair individually (AGENTS.md, publication).
