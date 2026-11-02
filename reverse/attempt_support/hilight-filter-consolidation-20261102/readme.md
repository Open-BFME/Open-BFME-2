# Highlight filter TU prerequisites (2026-11-02, halilkkaya-codex)

Base: 1291df600d4fba21e9a60ef84de93c18d033f5ea. Scope: device screen-filter TU.

Target facts: native shutdown FB8EB releases the consumed words at +04/+08,
clears the vector header at +18 and releases +2C/+24/+28/+30. Existing
postRender FAC37 consumes the same words through the seed's storage spelling.
This change shares that spelling with shutdown; it does not recover the
shader-word lifetime identity, introduce a constructor/table, or rename a row.
The existing int[3] kernel header is viewed as the existing vector only for
clear; COM words use the donor's existing Release slot interface.

Validation: ./build.sh passes 13/13 rows, string/float/import checks and
existing EH graphs. find_declared_unmatched passes both units. All 43
external COMDAT definitions (code and data) retain their normalized bytes
and relocation identities; shutdown-definitions.json records the comparison.
Paired link_check against 984a4cdc4d (2026-11-02 08:35) retains LINKS 3286 B.
Dry-run now accepts seed plus shutdown (13 rows); PreRender and Slot6 still
need declaration reconciliation. No header queue key is retired here.
