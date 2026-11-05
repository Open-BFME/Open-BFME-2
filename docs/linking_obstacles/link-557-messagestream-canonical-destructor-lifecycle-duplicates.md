### LINK-557: MessageStream canonical destructor adoption duplicates lifecycle methods
Status: Blocked. Updated: 2026-11-05; inspected revision: `46781e7090`.
Evidence / affected units: MessageStreamDtor.cpp and legacy MessageStream.cpp; [trial and consolidation boundary](../../reverse/attempt_support/messagestream-canonical-headers-20261105.md).
Completed: Propagation adopts canonical MessageStream/CommandList types; the destructor adoption was reverted after matching both rows but predicting LINKED 112 -> 0 from duplicate init/reset/update.
Remaining / next check: Reconcile the seed's out-of-line MessageStream lifecycle providers with the canonical inline definitions, then rerun destructor header acceptance and the TU merge dry run.
Clearance: Pending; destructor header debt remains.
Census confirmation: None claimed.
