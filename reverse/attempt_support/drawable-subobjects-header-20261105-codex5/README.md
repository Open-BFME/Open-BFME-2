# Drawable header adoption: W3DModelDraw sub-object updates

Inspected revision: `1de59bcc5ebca76c5bd60d445e87d3ba7c7f240b`. Scope: claimed Drawable cohort of 18 W3D device consumers.

## Completed

`W3DModelDrawUpdateSubObjects.cpp` now includes the canonical Drawable header instead of defining a private Drawable. The private inline getTemplate accessor loaded the pointer at +4; the canonical Thing base stores the same pointer in m_template. Its three diagnostic paths now access that field directly, preserving the existing inline loads rather than introducing an outlined Thing::getTemplate call. No shared header or ledger identity changed.

- Declared-unmatched check: all defined functions matched before and after.
- `./build.sh` verifies the complete 1,116-byte updateSubObjects body, its three literals, ten empty-string references and five named imports.
- `header_adopt_lane.py accept --class Drawable` passes and retires exactly this unit's queue row.
- Local link preview: LINKS, 1,116 -> 1,116 bytes against census c95fcfcfcd (2026-11-05 05:17). No new census or real-link result claimed.

## Cohort trial and remaining work

The automatic header-adoption trial restored every failing unit. Its 18 per-unit results are in cohort-adopt.log. The updateSubObjects mismatch was resolved as described above; the other 17 sources remain unchanged and their queue debt remains. Most require reconciling private fields with canonical layouts. W3DRopeDraw first needs its donor Coord3D/include identity reconciled. Parser refusals for the STLport config and the compiler C1001 are evidence only; no verifier was changed or bypassed.
