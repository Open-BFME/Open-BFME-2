# Explicit current providers for header acceptance

At source HEAD 6c5724cf417, ordinary ControlBar adoption in Rva005DA6F3Ctor.cpp
passes all six rows and preserves all 27 COMDAT fingerprints. Acceptance refreshes
only that consumer against census index aa7acf764d. It reports 351 -> 0 linked
bytes because the index predates the separately committed native destructor name.
The same single-consumer failure is present in restored HEAD before adoption.
Refreshing the current constructor, destructor and scalar-deleting provider units
preserves 852 -> 852 bytes. This is scoped census preservation, not real-link proof.

The refused candidate was restored before changing the verifier. Its native proof
and logs remain under build/root-ai-upgrade-controlbar-*. The false reject is
recorded through re_log.py. The separate tooling change adds explicit mandatory
--provider context: bounded, tracked, owned C/C++ sources subject to the existing
link maintenance path/decoder/extent/selector checks. One resolved snapshot assigns
roles; all consumers and providers must byte-pass and have explicit link-preservation
verdicts. Failed, missing, duplicate or out-of-census provider evidence prevents all
retirement. Only consumers undergo structural adoption checks and queue retirement.
No-provider acceptance retains its original behavior. No baseline or exception changes.

Regression coverage includes provider failures, parser retries, dependency discovery,
structural rejection, protected paths and extents, untracked/unowned/outside sources,
ambiguous selectors, cohort bounds, role overlap and alias retargeting. Native retry
and final validation are recorded after the separate tooling commit.

## Normal commit gate remains blocked

The separate tooling commit 8b828f97d9b passed 566 tests with one skip. A genuine
retry passed explicit provider acceptance and retired one row locally; ./build.sh
passed 52/52 and all 27 COMDAT fingerprints remained identical. The normal source
commit nevertheless refused: repair_queue's HEAD-loaded single-consumer verdict
does not receive that explicit context and reports the same 351 -> 0 loss. No
source commit landed. Both the source adoption and its queue deletion were restored;
the refused candidate/proof remain in build/root-controlbar-final-refused.cpp.txt
and build/root-controlbar-refused-adoption.{md,json}. This provider option improves
the owning acceptance API but does not yet resolve the separate hook context issue.

A full --update-index would inspect/compile the whole current ledger (3,038 Code
paths changed since the index); no broad refresh or handwritten index update was
run. Future work must carry explicit, bounded, freshly verified provider context
through the normal debt gate, or use a supported safe current index. A provisional
acceptance result must never be treated as a passed commit gate.
