### LINK-651: the link batch audit needs receipts the hooks do not write
Status: Open, no tool work assigned. Updated: 2026-11-09.

**Read `linking UNVERIFIED` as unverified, not failed and not clean.** For an ordinary push it usually means this gap, and it says nothing about the push's links.
The next census measures them.

Cause (`docs/strict_receipts_design.md`, measured there): `link_batch_audit.py` proves an object current only through `build.compile_is_current(strict=True)`: a version-2
receipt whose include inventory still matches, or a header-free version-1 receipt. `./build.sh` and the hooks' scoped gates write version 1, so a source the pre-push hook has
just byte-verified can fail it with "N source object(s) lack current receipts".

This clone's verdict log (`link_audit_verdicts.jsonl`: count, first day, last day, verdicts, inconclusive reasons): 208 2026-11-07 2026-11-09 {'inconclusive': 123, 'clean': 85} {'other': 8, 'missing-receipts': 98, 'no-index': 17}.

**No batch reached a verdict.** srv1's shared log on 2026-11-09 holds 233 real lines from 2026-11-08 08:37Z, test fixtures dropped; the PC clone's holds none, and clones on other machines were not read. 97 lines changed no source object, and those are all its `clean` lines. Of the 136 with something to judge, none was judged: 113 had an older index and missing receipts, 20 had no index, and 3 were at an exact base but stopped early (1 missing receipts, 2 other errors). A run the time cap kills writes no line, so those are not counted.

Receipts come first: they return before any judgment, so an exact base alone would not have changed those 114. Behind them, measured the same day:
- A batch reaches a median 4,529 consumers (111 logged batches, against the 2026-11-08 index), because `touched` holds every COMDAT a changed object defines. Each needs a strict receipt, and 80 of 300 sampled objects had one on each of two warm seats. Of 14 batches sampled, the names that really differ have a median of 13.5 (from 478), which leaves about 28 consumers.
- Only 21 of 1,785 master commits (1.2%), ignoring publication delay, were at an exact base: master changes a census input a median 9 minutes after a census commit, and audits saw a median gap of 133 minutes and 91 commits.
- Earlier records show it has refused: `docs/consolidation.md` describes refused merges, and `6d409fd607` (2026-11-05) records a false reject. Those predate the log.

`exact_base` means no census input or census tool differs between the index and the base, not commit equality. The `OMITTED` refusal does not depend on the base, and real-link losses cannot refuse (`REAL_LINK_LOSS_MODE` is `report`).

Log lines before `judged` exists give `exact_base: true` on every early return, so count them by their text. From then on `exact_base` is null on an early return and `judged` says whether the batch's objects were read through to a verdict.

Example: `3202ad2313` went out with "5 source object(s) lack current receipts"; the census at `7a9fd24d68` then showed all three of its previously contested units linking.

What would make it conclusive: the hook's own compile writing version-2 receipts, or `link_check.py --prepare-current` over the outgoing sources first. The design's steps 1 to 5
are an unscheduled proposal. LINK-008 and LINK-017 record earlier cases of the same message.
