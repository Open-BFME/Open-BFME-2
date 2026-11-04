# Preserved batch recovery, 2026-11-04 (codex3)

Preparation backup: `refs/runner/preparation/1793755157392811320`,
head `2110880e95773898ec0f2746fd4fb2326c244e15`.
The preparation record has no stash or resyncStash. The synchronized checkout
has nine outgoing commits, no active rebase, no unmerged index entries and no
staged, unstaged or untracked saved changes to restore. The backup remains.

Two gate failures reproduced against origin/master `dd7845d3fa`:

- LINK-187 was also assigned upstream to W3DSnow. Give this batch's new
  AptScriptFunction entry LINK-189; retain its text and evidence unchanged.
- The Player queue row retired before the UpgradeDie merge referred to a
  donor that is absent from the outgoing tip. The range checker requires
  disappearing-source accounting despite that earlier acceptance. Transfer
  the original queue row to UpgradeDie.cpp and leave it queued. Its RVA and
  canonical header remain unchanged; this recovery claims no Player debt
  retirement. The earlier consolidation audit describes historical acceptance,
  not the recovered tip's queue state.

The other six removed header rows passed the outgoing acceptance check;
the only reported rejection was the vanished UpgradeDieOnDie source.
`check_csv.py` passed (99,433 function rows); UpgradeDie.cpp's
`find_declared_unmatched.py` check reports all definitions already matched.

No game source, alias, pin, ledger placement, byte extent or verifier changes.
Existing consolidation audits retain the byte, link and path-consumer evidence
for LANGameInfo, AIStructureStats and UpgradeDie; recovery adds only the debt
transfer and the obstacle entry's control-path correction. The publication
hook will judge the complete outgoing batch against synchronized upstream.

Batch path audit repeated before publication: the three absorbed source paths
(Rva00447B0EDtor.cpp, Rva005965A5Ctor.cpp, UpgradeDieOnDie.cpp) and the old
AptScriptFunction obstacle filename have no active tooling, hook, workflow,
include or configuration consumers. Remaining matches are donor-origin/layout
comments, historical link status, historical obstacle notes and naming rejection
messages. No current functions, TU-map or debt-register entry still names an
absorbed source. The old obstacle filename has no incoming tracked links.
