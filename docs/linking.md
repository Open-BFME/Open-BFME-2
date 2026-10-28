# Making matched code link

AGENTS.md states the rules; this is the measurement, the tools and the BFME 1
linking pass, moved from AGENTS.md ("Make matched code link") in 2026-10.

A matched row whose unit cannot link is half done.

## Shared obstacle register

Read [linking_obstacles.md](linking_obstacles.md) before selecting linking work,
including a link task served by the default picker. Check its evidence and
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

Private per-unit views of one class cause most COMDAT and unresolved blockers.
`python3 tools/class_views.py` ranks classes by private views (`--blockers`: by
what the census holds against them; `--class X` and `--shims X` list the views and
competing shim headers). A class with a shared header is registered in
`reverse/canonical_classes.csv`, and `tools/class_gate.py` refuses new private
copies of it. To give a class a canonical header, follow
`python3 tools/header_adopt_lane.py order`: `tools/class_contract.py` decides its
ABI from evidence (bytes, retail access, retail vftables, ZH, majority), and
`header_adopt_lane.py run --generate --apply` generates the header, gates each
unit and queues the rest in `reverse/header_queue.tsv`. The header tier serves
classes by the queued TU-merge donors their header unblocks:
`header_adopt_lane.py order --merges [N]` lists them (private views in one
approved TU that tu_views cannot reconcile, or private copies of a registered
class; textual, `--refresh` recomputes), never ranking a prerequisite (a base,
an earlier DEPENDENCY_ORDER stage) below what needs it. The ranking lives in the
shared picker cache (`<git common dir>/bfme-picker-cache/merge_blockers/`).
The picker never computes it: on a miss it ranks by DEPENDENCY_ORDER and starts
one locked background refresh (never in CI or under pytest). Classes without a
header there are served as `class-header-establish` items. These claim every
unit `run --apply` may rewrite and name the header destination from BFME 1 or
ZH (`header_adopt_lane.py dest --class NAME`); an ambiguous destination is
left for the seat to choose. Claim scope-wide work:
`python3 tools/claims.py claim class:NAME` or `file:PATH`.

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
