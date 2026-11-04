# StdioStreambufBase consolidation probe (2026-11-04)

Allocated shard 1 TU `Code/GameEngine/Source/Common/StdioStreambufBase.cpp`
passed `consolidation_queue.py --check-tu`; the narrow Common consolidation
snapshot passed `name_lane.py consolidate --check`. The plan has 35 approved
rows, four donors, three mixed files and no statically refused rows.

`tu_skeleton.py --merge ... --dry-run` accepted no donors. The rejected
STLport donors duplicate `_STL::char_traits` / `_STL::fpos`, or `_STL::locale`
and lack `_STL::locale::facet`; LinkGuard marks the destination and three
provider units census-linked. The three mixed files were inspected with
`--split` and `--split ... --for StdioStreambufBase.cpp --dry-run`; all were
refused because the tool identifies them as vendored sources whose names are
upstream's. No split or merge was applied. The STLport composition and vendor
source ownership need work outside this mechanical lane.
