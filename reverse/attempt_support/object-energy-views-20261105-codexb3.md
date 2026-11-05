# Object's private Energy declarations

Inspected revision: `2b840363c8`. Scope: `Object.cpp` and
`ObjectRva0028B8A6DisablePower.cpp` under
`Code/GameEngine/Source/GameLogic/Object/`.

The sources declared disjoint method sets for `Energy`. The supported
`tu_views.py Object.cpp --class Energy --no-merge-check` reconciles both to
the union of their existing declarations. No fields, bases, virtual methods,
method bodies or names are inferred. The extra `Object` forward declaration
lets the second source declare the two influence methods before object.h.

The consolidation planner's source packet identifies Object.cpp as the sole
destination alternative for the disable-power rows, but labels the committed
map stale. The view tool rebuilds routing in memory. No row or file is moved;
whole-TU merge trials are outside this two-source declaration cleanup.

Verification:

- `./build.sh` on both sources: 101/101 function rows, one data row, string,
  float and import references pass. Declared-unmatched checks pass.
- `tu_views.py`: Energy applied to both sources, with compiler-layout and
  external-symbol-set checks passing.
- Independently rebuilt the original and edited sources through `./build.sh`;
  `class_cleanup.snapshot` / `same_runtime` confirm equal non-debug COFF
  contents, relocations, provider definitions, weak bindings and COMDAT policies.
  Object.cpp has 187 sections and 162 external definitions; the disable-power
  source has 10 sections and four external definitions.
- Before and after `link_check.py`: both LINKS, unchanged 7,026 and 195 authored
  bytes, against the census index at `c95fcfcfcd` (2026-11-05 05:17).
- `data_check.py`: zero findings for both sources. Existing header queue and
  hatch entries remain intact; no register key is retired or transferred.

This unifies declarations only. It removes no source file, claims no census
gain, and does not resolve the unrelated Energy lifetime/vtable obstacles in
LINK-006 or LINK-175.
