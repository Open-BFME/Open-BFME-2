# AI constructor: existing INI repair clears the selected-copy blocker

Inspected upstream: `d7fa8a31bf`. The default picker served the whole
`Code/GameEngine/Source/GameLogic/AI/Rva00598E85Ctor.cpp` unit: four matched
rows, 177 bytes, one historical `wrong_selected` blocker.

No production source, function row, pin or verifier was changed in this pass.
The earlier count-tree repair remains in place and its evidence was read.

## Current-provider evidence

The fetched published index measures `f995f30157` at 2026-10-25 21:36 UTC.
Its SHA-256 is
`d244cb544150b60422badb41e5f29e831e64b8caafc441375877536bfb51b038`.
For `__lower_bound<const unsigned int*, unsigned int, less<unsigned int>, int>`
at 0x00568D2F, it selects INI.cpp's wrong copy (digest `50a4e52dfead`).
The AI unit's own copy is already retail-correct (`7953ff7c6d9d`).

Existing commit `0c7ebc35a7` moves `_STLP_BFME_LOWER_BOUND_EXTERN` before
INI's hash-map include, removing that competing search copy. Its original
[repair evidence](ini-bucket-provider-link-20261025/readme.md) describes the
provider and separate ownership-overlay requirements.

Against the unchanged published index, the ordinary single-source preview
still refuses the AI unit. Passing current AI, INI and
`stlport_lower_bound_uint.cpp` objects together removes that AI blocker:
the AI unit previews LINKS for all 177 authored bytes. The lower-bound provider
also previews LINKS (108 bytes). This verifies an existing upstream repair;
none of those bytes is credited as a new repair from this pass.

The three-source command still exits 1 because INI's own preview retains
duplicate and selected-copy findings from the historical ownership inventory.
That is separate from the now-clean AI unit. No claim is made that the entire
cohort links, that global closure holds, or that a new census passed.

## Validation and next check

- The entire AI file was read; its frozen-file check passes.
- Normal `build.sh` passes 46/46 rows across AI, INI and the lower-bound
  provider, including 39 string literals, one empty-string reference and eight
  named imports.
- `eh_verify.py` reports all six EH graphs EXACT, with no missing objects.
- The ordinary paired source selection uses the same published index and
  current objects, without editing or republishing that index.

Await a later maintainer census for the AI unit. A future local preview must
include the current INI provider; the old index alone repeats this stale blocker.
