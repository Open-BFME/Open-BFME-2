# W3DSnow scoped local names after consolidation

Native child /root/snow_names proposed the complete ten-entry inventory for
rva00093B5B and target_00094652 in their final approved W3DSnow.cpp. The parent
read both complete functions, every mapping, retained-name rationale and preview
diff, and acknowledged the exact proposal and plan hashes through scoped review.
Three locals change: d to resolvedSettings, ft to fromSettings, and ov to
weatherSettings. Seven inventory entries are explicitly retained. Repeated
blend declarations are interpolation weights; repeated s declarations serve
both receiver phase and global weather state and retain their current spelling.
The inventory omits to in the multiple-declarator from/to declaration; inspected
and retained, not claimed as inventoried or renamed. No other unsupported
binding forms were found in these two complete functions.

name_lane.py scoped apply verified all three changes together: 23/23 exact
byte rows, seven float literals, empty-string and import checks pass. Frozen
source check clear. Name provenance is recorded by the tool in name_basis.csv.
The preceding vanished-source retirement accounting also passes both
repair_queue.py verify-missing and verify-removed --range origin/master HEAD;
the merge and accounting commits have been handed to the fleet publisher.
Local receipts: build/codex4-snow-naming-{next,preview,apply}.log and
build/codex4-snow-retirement-range.log; proposal/review snapshots remain under
build/name_lane/scoped/snow-merge-codex4-20261104.*.
