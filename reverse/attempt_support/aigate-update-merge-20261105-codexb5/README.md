# AIGateUpdate approved-TU merge and compatibility audit

2026-11-05, codexb5; prerequisite parent a75b7e6903d5e2f323578f4d673c7108179afe5f.

`tu_skeleton.py --merge` absorbed AIGateUpdateCtor.cpp and AIGateUpdateDtor.cpp
into Code/GameEngine/Source/GameLogic/Object/Update/AIGateUpdate.cpp. The
supported consolidation planner was regenerated after publication/rebase;
its current queue marks all three as whole-file candidates. Current approved
TU assignments were used, including the parent-bound EH rows. The tool
preserved 12 distinct row addresses (13 ledger rows, including the existing
folded opener accessor), repointed five donor rows in functions.csv and only
their five source columns in tu_map.csv. Source-file count falls by two.

Verification: normal build 13/13 exact; two literal references exact; both EH
graphs EXACT, including compiler-renumbered funclets; declared-unmatched and
check_csv pass. Staged link admission with staged peers passes. Merge's
link guard preserves the census-linked seed and both absorbed donors. A
strict receipt was prepared for the merged destination via the supported
bounded link_check --prepare-current path, with normal byte gates again.
No census LINKED or image-ownership increase is claimed.

Compatibility audit covers this entire path-changing batch against its
parent a75b7e6903. Old constructor/destructor paths have no active tooling,
hook, workflow, source/header include, project/build/configuration or doxygen
consumer. Searches included their exact paths and basenames across tools/,
.githooks/, .github/, Code/, docs/ and active reverse/ registers. Remaining
mentions are historical source-origin comments, earlier obstacle history,
ledger notes, attempt logs and the census's link_status.csv (not rewritten
outside its owner). Active functions, TU-map source columns, body/data
owners, header/ms-header queues, flag overrides, identity/data registers
and hatch records do not point at the deleted donors.

The merge tool transfers all three constructor /alternatename keys through
hatch_counters --update, keeping every directive byte-for-byte and its total.
No alias is removed as dead. There are no donor data/code-identity keys to
retire; the earlier owning header-accept commit already retired the three
stale UpdateModule rows. Destination's two existing data-ledger owners stay
in place. No shared header changes, pin changes or new symbol identities.

Broader batch audit is INCONCLUSIVE, not clean: the available index is from
c95fcfcfcd (2026-11-05 05:17), older than the outgoing parent, and affected
consumer Common/0CreateAHeroManager21FE49.cpp lacks a current strict receipt.
The first audit lacked a destination strict receipt; the supported preparation
resolved that prerequisite. Its recheck reaches the unrelated consumer
receipt limitation. Carry these cases into the next census; no broad
unclaimed consumer rebuild or nightly job was started.

Remaining merge prerequisites: trigger's +4 module-data view conflicts with
the inherited layout and its ModuleData class-key/field spelling differs.
Its PolygonTrigger header queue remains pending. AIGateUpdateXfer.cpp and
ModuleDataBuildFieldParse.cpp are mixed donors; no split was attempted.
