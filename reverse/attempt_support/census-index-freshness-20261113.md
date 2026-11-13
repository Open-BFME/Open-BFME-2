# Census measurement freshness after a local index refresh

The AITNGuard States composition passes its C++ and byte tests but remains
unjudgeable against the local census ordering evidence. Updating local
definitions to `de93b75bdc` rereads 855 objects and drops 25; it preserves the
original census at 2026-11-12 16:28 / `4ba87ee6df`.

The published index already carries the newer 21:59 / `27e4b01ed7` census,
rolled forward to `c40bbd895a` at 23:35. The local definition refresh happened
at 2026-11-13 00:18. Fetch compared these update timestamps, kept the older
measurement and printed that result. The accompanying JSON preserves both
actual metadata records. No source move or failed guard was bypassed.

The separate verifier change compares `census_date`, falling back to `date`
for a direct census or older format. Equal measurements retain the local
cache. The downloaded index's update commit and underlying census commit
must both be ancestors of the checkout before replacement. This also prevents
a rolled-forward cache from hiding a census commit the checkout lacks.

Six regression cases cover the reproduced stale-measurement selection, the
inverse downgrade, equal measurements, old-format compatibility and unknown
census ancestry. Before the fix, five fail. Afterwards the fetch-index suite
and unchanged exploit suite report 118 passed and one existing skipped case.
The temporary Git repositories in these tests run without the enclosing
checkout's process-level absolute hook override; actual repository commits
and pushes retain their normal hooks. No baseline, admission mode, source
ledger, merge-order test or byte test changes.
