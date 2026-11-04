### LINK-228: GSConfig donors have incompatible STL and slot views
Status: Blocked. Updated: 2026-11-04; inspected revision: `81d2d1f584`.
Evidence / affected units: `GSConfig.cpp`, `Rva0054E7C3Find.cpp`, `Rva0054F434Dtor.cpp`, `Rva0054F434Vslot1.cpp`; [trial and verification](../../reverse/attempt_support/gsconfig-tree-header-20261104-codex5.md).
Completed: canonical `Rva00072FE6` adoption in the destructor and vslot donors; two header-queue rows retired, 10/10 byte checks pass, both donor link previews preserved.
Remaining / next check: reconcile STLport 4.5/4.6 allocator declarations, the private `set<int>` specialization hiding `insert`, and conflicting slot-1 views; repeat the supported GSConfig merge dry-run after separately verified repairs. Mixed donors also remain.
Clearance: pending for consolidation; only the two header-adoption prerequisites are cleared.
Census confirmation: no new census claimed.
