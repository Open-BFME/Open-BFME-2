### LINK-651: the link batch audit needs receipts the hooks do not write
Status: Open, no tool work assigned. Updated: 2026-11-09.

**Read `linking UNVERIFIED` as unverified, not failed and not clean.** For an ordinary push it usually means this gap, and it says nothing about the push's links.
The next census measures them.

Cause (`docs/strict_receipts_design.md`, measured there): `link_batch_audit.py` proves an object current only through `build.compile_is_current(strict=True)`: a version-2
receipt whose include inventory still matches, or a header-free version-1 receipt. `./build.sh` and the hooks' scoped gates write version 1, so a source the pre-push hook has
just byte-verified can fail it with "N source object(s) lack current receipts".

This clone's verdict log (`link_audit_verdicts.jsonl`: count, first day, last day, verdicts, inconclusive reasons): 208 2026-11-07 2026-11-09 {'inconclusive': 123, 'clean': 85} {'other': 8, 'missing-receipts': 98, 'no-index': 17}.

Example: `3202ad2313` went out with "5 source object(s) lack current receipts"; the census at `7a9fd24d68` then showed all three of its previously contested units linking.

What would make it conclusive: the hook's own compile writing version-2 receipts, or `link_check.py --prepare-current` over the outgoing sources first. The design's steps 1 to 5
are an unscheduled proposal. LINK-008 and LINK-017 record earlier cases of the same message.
