# XML lexer CRT declaration cleanup

Inspected base: `93d6aea258`, 2026-10-29. Source:
`Code/GameEngine/Source/Common/BfmeLexEAN.cpp`.

The unit already includes `<string.h>` and selects `/MD`. Remove its redundant
local imported `strncpy` declaration and use the toolchain header declaration.
No function body, identity, source path, pin or shared header changes.

Before and after `./build.sh` verify all eight function rows, one data row,
one string literal and three named imports. The frozen-file checks pass.
`link_check.py --prepare-current` verifies the same scope with strict reusable
receipts. `ms_header_audit.py show` reports clean; its scoped `refresh_queue`
API removes exactly this source's one-definition queue entry, preserving other
rows. `check_csv.py` and `git diff --check` pass.

Ordinary `link_check.py` retains LINKS, 648 -> 648 authored bytes, against
index `85f6b7f40c` (2026-10-29 15:08). The staged-tree batch audit is
INCONCLUSIVE: the index predates the inspected base and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and this provider into the next scheduled census.
No census gain or full consumer closure is claimed.

Selection review: the default picker offered narrow istream's known LINK-058
wrapper-identity mismatch; its prerequisite remains unchanged and no source
trial was repeated. The Microsoft-header picker then offered Debug.h's
function-like diagnostic MESSAGE macro as a Routprot.h name; this unrelated
macro was left intact. FprintfAppendLine.cpp also remains unchanged: its game
`fprintf` identity conflicts with a direct stdio-header substitution. These
claims were released before this bounded cleanup.
