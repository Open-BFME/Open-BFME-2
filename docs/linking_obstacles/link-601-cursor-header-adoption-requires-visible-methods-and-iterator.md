### LINK-601: Cursor header adoption requires visible methods and iterator conversion
Status: Cleared for the eleven-consumer header cohort. Updated: 2026-11-05; inspected revision: bd3dc33fb4.
Evidence / affected units: [eleven-consumer adoption, byte verification and provider audit](../../reverse/attempt_support/cursor-header-adoption-20261105-codex.md).
Completed: Adopt Rva000411084.h in all eleven queued consumers, retaining native next/advance bodies outside the class where needed; PlayerXferStringMaps uses scoped typed-iterator field copies. The initial declaration-only and unscoped conversion trials changed code generation and were replaced.
Remaining / next check: None for this header cohort; original template identity remains unrecovered.
Clearance: 645/645 rows exact; cohort acceptance retired eleven queue rows with explicit no-loss link-preview verdicts. No real-link improvement claimed.
Census confirmation: Awaiting; no new census run.
