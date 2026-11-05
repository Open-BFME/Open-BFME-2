### LINK-560: ObjectSMCHelper timer-list constructor uses the wrong allocator body
Status: Cleared for the constructor's code-identity key. Updated: 2026-11-05; inspected revision: `abe23372b65c`.
Evidence / completed: [retail call targets, allocator correction and checks](../../reverse/attempt_support/objectsmchelper-list-identity-20261105-codexb.md); the existing allocator shim restores the 41-byte list helper and the admission tool proves its allocation-proxy fold; one identity key retires through `repair_queue.py`.
Remaining / next check: include the changed template helpers in the normal outgoing audit and next census; LINK-333's destructor consolidation prerequisites remain separate.
Clearance: source byte check passes 1/1 rows; current-input preview remains LINKS at 81 bytes. Wider helper-consumer closure is subject to the outgoing audit.
Census confirmation: awaiting; no headline linking gain claimed.
