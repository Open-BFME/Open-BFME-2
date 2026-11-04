### SidesList composition changes the POD-map pair destructor (2026-11-04)

Status: Open, rejected merge only. `WWLib/stlport_map_int_vector_pod128.cpp` links in census `a62ac1c10b`; the SidesList merge guard rejects its composed `pair<const int, vector<BfmePod128> >` destructor as non-retail. The donor remains unchanged. Reconcile the emitted destructor and vector/allocator context before retrying that donor; byte and affected-consumer checks are required. A smaller verified merge is separately blocked by live RVA claims.

[Scope, verification and claim handoff](../../reverse/attempt_support/sideslist-consolidation-20261104-codexb4.md).
