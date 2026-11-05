### LINK-451: LivingWorldCampaignManager private header views
Status: Cleared for the five queued class consumers. Updated: 2026-11-05; inspected revision: 4b347686ad.
Evidence / affected units: [adoption and verification](../../reverse/attempt_support/livingworldcampaignmanager-header-adoption-20261105.md); getter, lookup, both filters and LivingWorldCampaignManager.cpp.
Completed: replaced five private class definitions with the existing canonical header; header_adopt_lane.py accept retired all five class queue rows.
Remaining / next check: the separate LivingWorldRegionManager adoption in LivingWorldCampaignManager.cpp remains outside this scope.
Clearance: all five final units byte-match and pass the owning adoption checks; link_check preserves 1,173/1,173 census-linked bytes.
Census confirmation: preview only against the 2026-11-05 05:17 census at c95fcfcfcd; no new census claimed.
