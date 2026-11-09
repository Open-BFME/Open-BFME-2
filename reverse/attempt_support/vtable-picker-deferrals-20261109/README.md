# Vtable deferrals across compiler spellings, 2026-11-09

The default picker served BaseHeightMap's 7C5DB0 table and the Camera-derived
7C6C58 table as fresh work. Both native addresses already carried the same
bounding-getter prerequisite under older base-qualified compiler spellings.
The picker printed that evidence, but its deferral ordering used only the
new exact name. The current provider recheck is recorded in
base-height-map-bounding-recheck-20261109.json and LINK-619.

For vtable-bridge tasks, a standing compiler-table deferral now follows its
exact native address across ??_7 spellings. Existing re_log semantics still
judge the verdict, including voids, resolutions and blocked-on prerequisites.
A file is deferred only when every table in its queue group has a standing
deferral. Any untried table keeps the whole file fresh. Strong stand-ins and
virtual-base tables retain exact-name deferrals, without sharing hypotheses
between their different names. A reused candidate loses an obsolete deferral
tag when its state becomes fresh.

All candidates remain queued. Function-name hypotheses and terminal-boundary
filtering are unchanged. This changes task ordering, not verification,
claims, ledger ownership or publication admission. No table or queue row is
deleted and no native source repair is credited to the picker change.

The live queue replay retains all 1,585 file candidates with zero dropped
before and after. Eleven files with known compiler-table aliases move behind
untried work; 36 mixed or unsupported-boundary groups become fresh, changing
the deferred count from 84 to 59. queue-replay.json records every changed
candidate against the existing 4,085-row measurement at dc49d835d7.

Thirteen focused cases cover aliases, distinct addresses, non-table function
hypotheses, grouped fresh tables, exact-name stand-ins, virtual-base tables,
void/resolved/unblocked verdicts, malformed boundaries and stale tag reuse.
Loading the pre-change drop_logged from c4eff5c26f gives six failures and
seven passes. The final implementation passes the complete picker,
re_log/verdict and blocked-on, repair_queue and gate_exploits selection:
428 passed, four existing skips. Three skips concern unavailable picker
input/distribution cases; the fourth is the catalogued open-escape case.
No test or verification control is weakened or added to a whitelist.

The first broad invocation inherited this clone's publication-only hook
override in temporary test repositories, causing missing-hook fixture errors.
The final test child removes GIT_CONFIG_* overrides so those repositories
use their own configuration. Publication uses the normal hooks unchanged.
Logs and the read-only old-function/live-queue runners are under
build/vtable-picker-deferrals-20261109*.
