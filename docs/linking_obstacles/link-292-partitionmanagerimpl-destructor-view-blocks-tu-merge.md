### LINK-292: PartitionManagerImpl destructor view blocks its TU merge
Status: Blocked on manager ABI reconciliation; standalone destructor preview LINKS. Updated: 2026-11-04; inspected revision: 11dd6c6970.
Evidence / affected units: Common/PartitionManagerImpl.cpp and Libraries/Source/partitionmanager/PartitionManagerImpl.cpp; [prerequisite evidence](../../reverse/attempt_support/partition-impl-string-prerequisite-20261104-codexb.md).
Completed: replaced the destructor donor's private STLport string declaration with its real header and existing allocator configuration; 3/3 rows exact, preview LINKS 84 -> 84 bytes. Duplicate-template merge error removed.
Remaining / next check: seed lacks the destructor declaration (C2600); class reconciler refuses seed m_buckets at +0 beneath donor vfptr. Prove the retail manager ABI before unifying views; flag/result/byte prerequisites for other donors and the original source's two shadow destructor-adapter identity findings remain in the evidence.
Clearance: standalone linking preserved; no TU merge or filename approval claimed.
Census confirmation: no new measurement claimed.

2026-11-05: FlightDeck growth's environment prerequisite is repaired (34/34 paired rows exact, both previews LINKS); merge dry run now accepts that donor. Apply that merge next; the destructor ABI/result declarations and GetObjectsInRange override remain blocked. [Evidence](../../reverse/attempt_support/partition-flightdeck-environment-20261105-codexb.md).

2026-11-05: FlightDeck donor merged into the approved PartitionManager TU: one source removed, 34/34 rows exact, EXACT 2 EH records and preview LINKS at the preserved 3,719 bytes. Next: reconcile the destructor's specialization placement/manager ABI; result declarations and the range-query override remain blocked. [Merge audit](../../reverse/attempt_support/partition-flightdeck-merge-20261105-codexb.md).
