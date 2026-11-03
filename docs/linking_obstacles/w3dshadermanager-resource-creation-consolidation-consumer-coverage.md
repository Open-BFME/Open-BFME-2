### W3DShaderManager resource-creation consolidation: consumer coverage awaits census

Status: Verified composition; outgoing link audit inconclusive. Updated:
2026-10-28; inspected base `2a972506ca`; index `41c28839bf`.

Completed: the supported merge absorbs W3DShaderManagerCreateResources.cpp
into the approved W3DShaderManager.cpp, removing one source file and preserving
all 21 function rows and five data rows. All four EH graphs are EXACT. The
merged object preserves all 32 external definitions, the external dependency
set and all 18 distinct COMDAT byte-and-relocation digests. Data checks have no
findings and code identity has no new findings. LinkGuard accepts the two
census-linked inputs and composition; ordinary preview reports LINKS for the
merged object. [Scoped evidence, register/path audit and remaining donor
blockers](../../reverse/attempt_support/w3dshader-consolidation-20261028-codexb4.md).

Remaining / next check: strict receipts cover the destination and its init
caller Common/Rva00066A9ABody.cpp (two rows). The outgoing audit remains
INCONCLUSIVE because the index predates the base and affected consumer
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. Carry the moved
provider, init caller and affected consumers into the next scheduled census.
Nine whole-file donors need declaration/codegen reconciliation; two mixed
sources remain outside this merge. No rejected donor was edited.

Clearance: source consolidation and scoped byte/data/EH checks only. Full
selected-consumer coverage and census confirmation remain open; no measured
linked-byte or image-ownership gain is claimed.
