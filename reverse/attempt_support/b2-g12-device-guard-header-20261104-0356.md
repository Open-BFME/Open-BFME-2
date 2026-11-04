# Adopt canonical device guard in Rva0007E12F

After the separate canonical bool-unlock declaration prerequisite, replace one
private empty class with the registered existing BFMEDX8DeviceLock header.
The old constructor/destructor bodies already call the same lock/unlock pair
with the bool declaration; no method, call, lifetime or exception specification
is changed. Native CodeView proves this source's1-byte empty class, no fields,
bases/vptr or virtuals; this agrees with the actual existing header, not the
older inferred4-byte contract sample. No allocation/array extent is inferred.

Normal/frozen checks preserve 3 existing ledger rows. All
3 external code definitions/relocations and every non-debug
section (data/EH/directives included) remain identical. Only the canonical
header is added to resolved dependencies; every old physical path/native hash
is retained. Native header acceptance retires exactly the one owned queue key.
The earlier queue failure is rechecked against the separately published
bool-provider header prerequisite from the preceding run. That prerequisite
is reused as existing evidence and is not counted as a new task here. No new coverage, shared-header/flag/pin/alias edit or runtime gain.
