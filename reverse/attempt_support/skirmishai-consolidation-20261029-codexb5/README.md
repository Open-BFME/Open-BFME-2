# SkirmishAI consolidation probe

Base: `1c16abe8f6` (2026-10-29). The default picker claimed the destination
`Code/GameEngine/Source/GameLogic/SkirmishAI/SkirmishAI.cpp` and six whole-file
donors. The scoped naming planner reported 24 groups and no missing inputs; its
snapshot is local build evidence, not TU approval. The picker reported 28 donor
rows and five mixed files that remain outside this merge.

`tu_views.py` applied byte-verified private-view reconciliations for PlayerList,
Rva002A8F24 and Rva002A8AB1Record, but its own merge dry run accepted zero
of six donors both before and after those changes. The trial changes were
restored. No rows or paths moved and no linking improvement is claimed.

The remaining compile boundaries in that probe were:

- `Rva002C6E4EDtor.cpp`: `_Rb_tree` explicit specialization after instantiation;
  the AIBuilder layouts also overlap incompatibly in the automatic view plan.
- `Rva002C6EA4Method.cpp`: duplicate `_Rb_tree_iterator` operator template.
- `SkirmishAI_isAPartialBrain.cpp`: the destination's SkirmishAI class lacks the
  `isAPartialBrain` declaration.
- `SkirmishAI_resetMaster.cpp` and `SkirmishAI_updatePhase.cpp`: their member
  spellings differ from the destination's fields at corresponding offsets.
- `Rva002A8AB1RecordGet.cpp`: the destination's Player view lacks the donor's
  `m_164` member spelling.

The automatic Player reconciliation failed to compile its donor because the
proposed base and a by-value member were undefined. Automatic SkirmishAI
reconciliation refused a token rename because `m_178` also names a member of
Rva002A8AB1Record. Next investigate those views with explicit type and field
ownership, then verify each donor and its object bindings before repeating the
supported merge probe. The earlier declaration-only trial is not evidence of a
successful composition or consumer-wide link closure.

## Phase donor composition follow-up

At base `11833cbfe1`, align the update-phase donor's four field spellings
with the destination and declare the manager lookup in the destination. The
prerequisites preserve 1/1 and 19/19 rows respectively; each previews LINKS
against index `85f6b7f40c` (258 and 1,207 authored bytes). The supported merger
then accepts the phase donor and its link guard accepts the census-linked
inputs. The applied destination verifies 20/20 rows, six float references,
two EXACT EH graphs and no newly unmatched definitions. Its ordinary preview
is LINKS for 1,465 bytes against that index; those 258 moved bytes are existing
coverage, not a census gain. The other five whole donors and five mixed files
remain, with the previous class and STL composition prerequisites.

The merger refreshed its header queues; the destination's Microsoft-header
show is clean. The staged ownership and data checks report no findings. Neither
source appears in the identity, data, hatch, flag or header queues/registers
searched. The supported merge repoints the function and TU-map source; no data
or body-owner rows were moved. The link guard checks selected bindings during
composition; broader consumer and census confirmation remain pending.

Path audit of the outgoing batch based on `origin/master` through this staged
move: this is its only deleted Code path. A repository-wide search for the old
basename finds only the historical name-basis entry, the census link-status
snapshot, the merge provenance comment and this handoff. No active tooling,
include, workflow or build consumer names it. The pre-push batch audit must
still judge affected consumers against current receipts; an older index or a
missing receipt is not a clearance.

The outgoing batch audit after the move is INCONCLUSIVE: index `85f6b7f40c`
predates the outgoing base, and three source objects lack current receipts,
first `GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchProcessGameSpyResponses.cpp`.
Carry the moved provider and those affected consumers into the next scheduled
census; the local preview does not resolve this boundary. The merge hook also
reported the donor's unused address-named float declaration in shadow mode;
a follow-up removes that declaration and preserves 20/20 rows.

## Partial-brain donor follow-up

The partial-brain donor's two SkirmishAI member spellings were aligned with
the destination; its 105-byte row remains exact. The destination gained the
existing PlayerList count layout and method declarations needed by the donor,
with its original 20 rows exact. The supported merger then accepted the donor
and its link guard accepted the census-linked inputs. The merged destination
has 21/21 exact rows, six verified float references, two EXACT EH graphs and
no newly unmatched definitions. Its local link preview is LINKS for 1,570 bytes
against index `85f6b7f40c`; this is moved existing coverage, not a census gain.

The staged ownership and data checks found no issues, and the Microsoft-header
audit reports the destination clean. Searches found neither source in the
identity, data, hatch, flag or header registers. The merge repointed its code
row and TU-map source; it moved no data or body-owner row. The full outgoing
path audit against `origin/master` covers this donor and the previously merged
phase donor: old-path references are historical name-basis and census entries,
source provenance comments and this handoff, with no active consumer found.
The prior batch audit's stale index and missing receipts still require census
confirmation of external consumers. Four whole donors and five mixed files
remain: resetMaster needs its member view aligned, RecordGet needs its Player
and record views reconciled, and the other two have STL composition conflicts.
The outgoing batch audit after this move remains INCONCLUSIVE: index
`85f6b7f40c` predates `origin/master` and four source objects lack current
receipts, first `Code/GameEngine/Source/Common/RTS/PlayerKillPlayer.cpp`.
Carry those consumers and both moved providers into the next scheduled census.
