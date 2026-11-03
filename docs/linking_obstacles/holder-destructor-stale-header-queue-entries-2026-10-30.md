### Holder destructor stale header queue entries (2026-10-30)

At base `94154fcaa4`, the owning Microsoft-header scan removes three stale
`free` declaration records for Rva0033BD50Free.cpp, Rva0033BD88Free.cpp and
Rva0033BDC0Free.cpp. Their real CRT headers were adopted in `5230801e84`;
no game source or provider changes here. Strict preparation passes 3/3 rows,
EH is EXACT 3, and ordinary preview retains 3/3 LINKS and 168 authored bytes
against index `12b9e7a7c0`. This resolves these providers' current-receipt
prerequisite only. Earlier wider outgoing-batch consumer checks remain
unverified; carry them into the next scheduled census/current-receipt audit.
No census gain is claimed.
[Repair history and scoped checks](../../reverse/attempt_support/holder-stale-msheaders-20261030-codexb4.md).
