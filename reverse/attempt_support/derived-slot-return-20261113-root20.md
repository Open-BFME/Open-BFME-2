# LINK-625 exact return candidate: verifier false rejection

RVA 0x0056B613 is a 43-byte predicate, formerly rowed as a void member of
Rva0056B613. Its gate call at 0x56B626 leaves zero in AL on rejection; the
branch at 0x56B62D reaches the shared pop/ret epilogue without materializing
another zero. The other path returns the base predicate's AL result. Native
callers test AL. These facts establish a one-byte predicate result, while the
existing unsigned-char base contract supplies the coherent C++ return type;
they do not distinguish the original spelling from bool.

The proposed unsigned-char result variable preserves that shared epilogue and
exactly reproduces the existing 43 bytes and relocation targets. The 62-byte
base body also remains exact. Both independent native proposal workers chose
`isVisibleForPlayer`; agreement nl-87cec91d5d58 records this as an inferred
identifier, not a recovered original name. Both the ordinary rename tool and
the documented prepared naming-lane batch verify the complete transaction.
Neither source change was committed. No pin is added.

Both candidate workflows pass all three changed-source function rows and the
existing four-byte table row. Strict candidate preparation passes all four
sources with 24 rows and one data row. The restored original cohort also passes
all 24 rows and the data row.

## Commit refusal

`class_gate.vote_sources_change_problems` (tools/class_gate.py:158) compares
each newly added original-vote fingerprint directly with the final staged
source. The two genuine votes fingerprint the original source (a8919a8a),
whereas the verified prepared source is cc93cd5d. The guard does not recognize
the legitimate prepared operation or its staged landed outcome. The normal
`name_lane.py apply` reports landed 1, blocked 0, yet the commit is refused.
`carry_verified_votes` intentionally carries only other keys across pure
identifier renames; this scalar-return/body transformation is not one.

This is recorded as a false reject, not bypassed. The original Code files,
function row, tombstone ledger and name-basis ledger are restored. The original
two votes remain bound to their unchanged source, with a blocked naming outcome.
The prior unbanked solved verdict is voided through re_log.py. The exact
[candidate sources and approval/hash evidence](derived-slot-return-20261113-root20/reproduction.json)
are retained beside this handoff; they are evidence, not progress.

Tooling follow-up: exercise the staged and push-range fingerprint gate after
the normal prepared-batch application in test_name_lane_respell_batch.py and
test_vote_sources_push.py. Keep stale/forged fingerprints and every existing
test_gate_exploits case refused. Do not fabricate replacement fingerprints,
new voters or a receipt-only workaround commit.

This prerequisite does not repair the derived compiler vtable by itself:
Rva003FA118 still inherits the base predicate until supported slot ownership
recovery succeeds. The native copy constructor installs the derived table at
+0 and copies +0x58/+0x5C..0x5E; two independent allocation sites request 0x60.
The runtime icon object, which owns a template pointer at +0xAC, is distinct
from this template. Neither original class name is claimed here.

The base predicate's WorldBuilder name lead is not canonical proof: the paired
217-byte body asserts its name, but the default grader reports score 1 < 4.
No evidence threshold, name lead, canonical tier or verifier is changed.
No current whole-image or measured bridge-retirement result is claimed.
