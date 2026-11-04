### LINK-201: SpawnArmy composition changes string COMDAT selection

Status: Blocked for the Equal and Notify donor merges; standalone units remain separate. Inspected `5001bb6e79`, 2026-11-04.
The merge guard rejects Rva004E20ABEqual.cpp's non-retail AsciiString::compare selection and Rva004E35D5Notify.cpp's StringBase operator< reference / less<AsciiString> selection. Reconcile their declaration and inline-overload bindings before retrying.
Evidence and the verified contains-helper merge: [2026-11-04 handoff](../../reverse/attempt_support/spawnarmy-consolidation-20261104.md).
Batch linking remains unverified: strict receipts for SpawnArmy.cpp and its Glo012F1024Item.cpp consumer are missing against the older index; carry both into the next scheduled census. No census gain claimed.
