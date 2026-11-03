### AptCIH cleanup donor composition (2026-10-28)

Status: bounded composition verified; external consumer selection and census
confirmation pending. At base `e354463d59`, the supported merge absorbs
`AptCIH_DestroyGCPointers.cpp` into its approved AptCIH TU, removing one source
file. All 26 rows match, the EH graph is EXACT, scoped data checking has no
findings, and the merge guard accepts both census-linked inputs. The composed
unit previews LINKS for 1,861 authored bytes against index `41c28839bf`;
this is not a census gain. Strict preparation verifies the new destination.

The moved path has no active references in tools, hooks, configuration or
source includes. Its `name_basis.csv` record and the destination provenance
comment are historical. Neither moved source has a code-identity, data, hatch
or header queue key; the destination's existing flag override remains. The
pre-commit identity shadow reported a `uw_007a90d0` destructor
binding for review. The remaining donors require class/declaration or flag
reconciliation; two mixed files remain separate. Carry the moved provider and
its consumers into the next census; external selection remains unverified.
