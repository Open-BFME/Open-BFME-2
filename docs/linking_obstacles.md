# Linking obstacle register

One entry per file in [`linking_obstacles/`](linking_obstacles/). Until 2026-11-03 all 620 entries lived in
this file: dozens of edits a day to one 1.7 MB file made it the most frequent rebase conflict, and it could
no longer be read whole. The split kept each entry's text; only its relative links gained one `../`.

- Find entries by unit, symbol or ID: `rg -l "LINK-017|FXList.cpp" docs/linking_obstacles/`.
- Open and blocked entries: `rg -l -i "^\W*status\b[^a-z]*(open|blocked)" docs/linking_obstacles/`
  (101 at the split; it also finds bold and lower-case status lines). Status lines are free text,
  and 384 of the 620 entries have none at all, mostly dated work notes: search those by
  unit, symbol or ID.
- Update an entry in its own file. Add a new entry as a new file named after its heading: lowercase, other
  characters as `-`, at most 72 characters, for example `linking_obstacles/link-172-short-cause.md`.
  Start the file with the heading as before.
- Next free ID: `rg -o --no-filename "LINK-[0-9]+" docs/linking_obstacles/ | sort -u -t- -k2,2n | tail -1`.
  Never reuse an ID. IDs that head more than one entry (at the split: LINK-089, LINK-096, LINK-115, LINK-131, LINK-132, LINK-135, LINK-145, LINK-150, LINK-155, LINK-157, LINK-161, LINK-170, LINK-171, LINK-172):

  ```sh
  rg -o --no-filename "^#+ LINK-[0-9]+" docs/linking_obstacles/ | sort | uniq -d
  ```
- A link to `linking_obstacles.md#<heading>` from before the split: the entry's file is named after the
  same heading.

## Read these first

The entries other entries cite most often (at the split); their causes cut across many units.

- [LINK-063: `Scripts.cpp` needs `OrCondition`'s destructor, which is rowed under the placeholder `Rva003B262E`](linking_obstacles/link-063-scripts-cpp-needs-orcondition-s-destructor-which-is-rowed.md), cited by 9 entries
- [LINK-133: ICF-twin rows moved objects ahead in link order, so their wrong COMDAT copies became the kept copy](linking_obstacles/link-133-icf-twin-rows-moved-objects-ahead-in-link-order-so-their-wrong.md), cited by 9 entries
- [LINK-008: include inventories prevent strict reusable graphics receipts](linking_obstacles/link-008-include-inventories-prevent-strict-reusable-graphics-receipts.md), cited by 8 entries
- [LINK-095: generated EH funclets whose parent TU emits an unpinned or wrong dtor callee](linking_obstacles/link-095-generated-eh-funclets-whose-parent-tu-emits-an-unpinned-or.md), cited by 8 entries
- [LINK-002: distinct container element identities and exception contracts](linking_obstacles/link-002-distinct-container-element-identities-and-exception-contracts.md), cited by 5 entries
- [LINK-060: one address rowed twice; the non-linking copy is an over-claim](linking_obstacles/link-060-one-address-rowed-twice-the-non-linking-copy-is-an-over-claim.md), cited by 5 entries

## Maintaining this register

- Update only the entries your evidence affects. Record the date, source revision,
  affected symbols/units, work completed, verification result, remaining blockers
  and next useful check. Link a repair commit or tracked attempt evidence. For
  previews, identify the index revision, current-input checks and measured scope;
  put detailed receipts in the repair's normal evidence location.
- Reuse an existing ID for the same cause; give a new cause the next unused
  `LINK-NNN` ID. If a broad entry is only partly repaired, keep it open and list
  the repaired subset or split off a narrower entry. Do not mark a whole family
  cleared because one consumer links.
- Use **Open** for an unresolved lead, **Blocked** with a named prerequisite,
  **Repair landed / awaiting verification** for an unconfirmed repair, and
  **Cleared** only with verification of the stated scope against current inputs.
  State separately whether a later census confirms it. A preview clearance does
  not change the headline; a source edit or provider's existence alone is not
  proof that its consumers now link.
- Keep cleared entries and their evidence. Reopen an entry with the new failing
  revision and evidence if it regresses. Preserve other agents' updates when
  rebasing. Do not repeat an unchanged failed trial without new evidence or a
  resolved prerequisite.

For a new entry, use this shape:

```text
### LINK-NNN: concrete cause and affected scope
Status: Open. Updated: YYYY-MM-DD; inspected revision: <SHA>.
Evidence / affected units: <symbols, files, tracked evidence, index revision>.
Completed: <repair or attempt, commit and measured result, or none yet>.
Remaining / next check: <specific dependency and how to verify it>.
Clearance: <scope, current-input verification and evidence, or pending>.
Census confirmation: <published measurement revision, or awaiting / not claimed>.
```

## Baseline for the initial entries

Seeded on **2026-10-25** from the investigation at `76efac458e`.
The historical census measured `d2636bb381` at **2026-10-25 09:42 UTC**;
its status was published by `b78c9ed16e`. It records **7,343,016 / 7,512,658
executable-game bytes (97.7419%)**, leaving 169,642 bytes and 385 blocked units.
Use the published status: the status file inside the measured commit itself
describes the preceding census.

The official provider index inspected had provider facts updated to `51fde01dff`
at **2026-10-25 13:53 UTC**, but retained the 09:42 census's blocker lists.
Index SHA-256:
`7225d4beb4d607e264bb010fef0dc8fdcb36d15b684d16fc7e654ee776a037ed`.
Thus the counts below are historical leads, not freshly measured failures on
master. Recheck current inputs before choosing work. The register's initial
entries claim no new census or current-master compile result.

Start by verifying landed repairs, then reconcile container identities and
shared headers/providers in coherent batches. Do not total overlapping units,
authored-byte previews or commit-title gains into a projected headline.
