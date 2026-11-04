# gamebrowserdemangler unchanged merge dry run (2026-11-04)

The allocated 15-row plan has 2 donors. Dry run accepted none: `Rva00800920FeslCtor.cpp`
fails because `Rva00800920Owner::rva00800a40` is absent and `m_14` is
undeclared in the destination view. LinkGuard confirms both census units remain
linked. Reconcile those class views in another lane before retrying.
