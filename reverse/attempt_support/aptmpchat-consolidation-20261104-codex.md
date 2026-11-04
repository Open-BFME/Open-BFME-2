# AptMpChat constructor consolidation, 2026-11-04

Base: `aa6af9423d` (view reconciliation, initially `dc6b28713c` before the
runner publication rebase); preceding input `9057bc235e`.
Scope: absorb `Code/GameEngine/Source/Common/Rva0057FF3ECtor.cpp` into
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptMpChat.cpp`.

## Evidence and prerequisite repair

The initial source-layout planner found a stale committed map and reported its
placements as hints, with macro, include-resolution and path-register review
required. The merge engine rebuilt the map in memory: constructor 0x0057FF3E
is approved for AptMpChat; its compiler-generated EH rows follow their parent.
No placement or approval was added by hand. Only the three source cells of the
committed map change; its assignments were not regenerated.

The first dry run rejected the constructor with C2511 (missing declaration).
`tu_views` also identified differing +0x58 holder types. The constructor has
+0x58 refcount ownership, integer fields +0x5c/+0x60, a raw helper pointer +0x64
and byte +0x68. The destructor's previous +0x64 RAII member was replaced by its
same cleanup in the destructor body; using that RAII member in the constructor
would introduce additional exception cleanup. Both views now agree. This is
layout/code-generation reconciliation, without a claim about original names.

Reconciliation commit: `aa6af9423d`. Both files pass 18/18 byte checks and
`find_declared_unmatched.py`. `link_check.py` reports LINKS for both:
constructor 105 bytes, original TU 829 bytes. Four EH parents are EXACT.

## Applied merge and verification

`tu_skeleton.py --merge` accepts both files, with no rejected or mixed donor;
18/18 rows survive. Its census-linked guard covers both original units and
checks provider/consumer and selected-COMDAT compatibility before applying.
The tool repoints the constructor and its two EH rows in functions.csv and
the source cells of tu_map.csv. The donor is deleted: source files decrease by
one. The generated 0x0079C723 cleanup remains in gen_small; it was not claimed
or moved by this merge.

After composition:

- `./build.sh .../AptMpChat.cpp`: 18/18 rows matched; eight string literals
  verified; compiler literals and named imports pass.
- `find_declared_unmatched.py`: all defined functions already matched.
- `eh_verify.py`: four parents EXACT, no baseline exceptions or missing objects.
- `link_check.py`: LINKS, destination 829 -> 934 bytes. This retains the two
  original units' combined 934 bytes; it is a prediction, not a census gain.

## Debt, reports and tooling audit

The donor has no code-identity or data-check baseline keys. Its Rva005248D0
header-queue row is transferred to the destination by the merge engine,
including its acceptance command. Both existing destination adoption rows
remain. No header debt was retired, including duplicate-class obligations.
The old source name in that row's failure diagnostic remains historical.
The Microsoft-header queue is refreshed for the destination and removed donor.

No pins, aliases, globals, hatches, compiler options or shared headers are added
or removed. The merge tool's whole-tree hatch update also tightened unrelated
pre-existing counts and removed two old admission annotations. Those incidental
changes were restored to HEAD; this donor carries no hatch and this merge needs
no hatch-baseline change.

The compatibility audit covers the complete pending source-path change: this
one absorbed donor. Searching tools/, .githooks/, .github/, Code/, docs/ and
reverse/ for its full path and basename finds no active include, build/config
consumer or path-dependent tool. Remaining occurrences are source-origin
comments, historical link status, historical naming votes/basis/agreement
records, the transferred header failure diagnostic, and previous attempt
receipts. These retain their provenance. Active function/map ownership and
header acceptance paths point at the surviving TU. No data/provider register
names the removed source. The default outgoing batch link audit still runs
through the publication hook; no census or full-game result is claimed here.

The old LINK-123 sweep's AptMpChat merge prerequisite is resolved for this donor.
The singleton issue described by that entry and other TUs in its sweep are
outside this change. Remaining AptMpChat header adoption and generated cleanup
recovery are separate work.

Additional checks: staged TU ownership reports no findings; data_check reports
zero findings in both shadow and enforced-converged modes; the refreshed
Microsoft-header scan reports no copied definitions, adaptations or failures;
check_csv passes (99,438 function rows). The source-layout planner was regenerated
after composition, so the initial stale snapshot is not reused.

## Existing destination header key accounting

Pre-commit passes all checks, including 18/18 rows and four EXACT EH parents.
Commit-msg then requests accounting for the vanished constructor source's
Rva005248D0 key. `repair_queue._debt_transferred` subtracts sets of (class,
source) pairs, so it cannot detect the added transferred row when the same
class/source pair was already queued at the destination. Both destination
Rva005248D0 rows remain, including the donor's three RVAs. The same case was
previously recorded for LANGameInfo in re_attempts.log.

The failure is recorded through re_log.py. The permitted per-key Debt-Retired
trailer explains only the vanished source's key; it does not claim adoption
or remove any destination debt. No gate code or debt register is relaxed.
