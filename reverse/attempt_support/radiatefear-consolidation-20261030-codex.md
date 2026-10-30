# RadiateFearUpdate: transfer-view prerequisite and consolidation

Inspected BFME 2 fbf8a43dea on 2026-10-30. The default picker claimed the
existing destination and four complete donors. The naming planner under
Code/GameEngine/Source/GameLogic/Object/Update supplied the path packets;
the supported TU mapper independently approves the transfer row at
0x0049C195 (61 bytes) for RadiateFearUpdate.cpp, provisionally. This proves
the approved grouping, not an original retail filename.

## Prerequisite

The initial supported merge accepted no donor. The destination's getter-only
RadiateFearUpdate declaration conflicted with the transfer's ObjectModule /
UpdateModule view. Reuse that existing transfer view in the destination and
declare getModuleNameKey in both views. Module's registered header supplies
slot 4; the rowed transfer calls UpdateModule::xfer and the UpgradeMux member
at +0x20. No constructor, table store or generated funclet is rewritten.
This bounded view reconciliation does not settle the other donors' layouts.

Verification before the separate prerequisite commit:

- `./build.sh` verifies all eight rows in the destination and transfer donor;
  find_declared_unmatched reports no unrowed definition in either.
- `eh_verify.py` reports two EXACT graphs, zero nonexact.
- Compared with copies of the original byte-verified objects, external
  COMDAT bodies and external symbol records are identical: seven COMDATs
  in the destination and two in the transfer donor, no added/removed body.
- `link_check.py --prepare-current` accepts two strict provider receipts.
  The preview reports LINKS for both, preserving 208 + 61 = 269 bytes
  against the 2026-10-30 10:11 census index at 12b9e7a7c0.
- ObjectModule header acceptance passes both sources. Module's separate
  acceptance probe requires a direct Module.h include; these sources inherit
  it through ObjectModule.h and no Module queue item is retired.
- No identity/data baseline, hatch, flag override or header-queue key belongs
  to the transfer donor. The two getter statics remain owned by the destination
  in data_ledger.csv.
- A new normal merge dry run accepts exactly the transfer donor (eight rows
  together). Constructor and update donors still fail composition; the
  module-data destructor donor changes bytes and remains separate. Mixed
  files and Code/gen_small/uw_gen_011.cpp remain outside the merge.

The global BFME 1 freshness check found official upstream at
219f8937e21d3f8c6f089ad4d14ee6e1de5c7d06. Another worker holds
file:reference/open-bfme-1. Keep the clean, already verified committed
reference 1d5131d3f193cdf01a99da66ccd6828639585650 and do not advance the
local freshness stamp or claim to have completed that worker's update.

The staged provider/consumer batch audit is INCONCLUSIVE: the index predates
HEAD, and affected consumer
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry that consumer and the RadiateFear providers into the next
scheduled census; the per-file LINKS preview does not close this limitation.
The scoped Microsoft-header scan finds zero local Microsoft declarations.

No new matched bytes, measured linking gain or image-ownership reduction is
claimed by this prerequisite. Follow with the supported merge, current
provider/consumer audit, header-queue refresh and full path-consumer review.
