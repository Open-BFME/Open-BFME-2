# StdioStreambufBase unchanged merge dry run (2026-11-04)

The allocated 35-row plan has 4 donors. Dry run accepted none: the narrow
defaults donor redeclares `_STL::char_traits`/`fpos`; the `uflow` and `xsputnc`
donors report `_STL::locale` redefinition and missing `facet` errors. LinkGuard
confirms all four census units remain linked. Reconcile the STLport views in
another lane before retrying.
