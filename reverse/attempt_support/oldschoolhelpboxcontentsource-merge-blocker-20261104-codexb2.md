# OldSchoolHelpBoxContentSource unchanged merge dry run (2026-11-04)

The allocated 22-row plan has 3 donors. Dry run accepted none:
`Rva00405C04Show.cpp` has undeclared `m_2a4` and lacks `Rva000AD6F4::get` in
the destination view; `Rva00405B60Ctor.cpp` fails byte verification. LinkGuard
confirms the three census units remain linked. Reconcile class views and recover
the ctor donor in another lane before retrying.
