### Selection lookup native fold prerequisite (2026-11-03)

The supported two-donor merge's normal hook correctly refused its carried pin:
the old witness emitted60B against native47B. Restore the merge, then expose two
ordinary vector accessor bodies. The63B parent remains exact and _M_find now
matches all47 native bytes with zero relocations. Other552-provider facts remain
except two added accessors: size9B loses to an earlier native25B copy; const[]12B
equals the earlier kept copy (native placement unknown). Guard and normal preview
pass63->63B. Re-run the supported merge and actual admission after this fix.
[Native witness and bounded selection proof](../../reverse/attempt_support/selection-native-fold-witness-20261103/README.md).
