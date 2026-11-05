### LINK-549: PlayerHasScience's flattened vector prevents canonical-header adoption
Status: Cleared for this one-unit private-view prerequisite. Updated: 2026-11-05; inspected revision: 1ed7dd708e.
Evidence / affected unit: [Player::hasScience, RVA 0x002AB7D5, receipts and scope](../../reverse/attempt_support/player_has_science_header_20261105_codexb4.md).
Completed: replaced the private Player view with Player.h and its science vector; header_adopt_lane.py accept retired one queue row.
Clearance: the complete 40-byte body still matches; link_check previews LINKS at 40 bytes before and after against the 2026-11-05 05:17 census index (c95fcfcfcd).
Remaining / next check: reconcile the other Player donor views before retrying the broad Player.cpp merge; its interrupted dry-run produced no verdict.
Census confirmation: no new census or LINKED gain claimed; this unit was already linked.
