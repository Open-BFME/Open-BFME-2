# MaterialPass destructor adopts canonical RefCountClass

Inspected base: `1e9ce84d89123b557f98332482eb7d7e7296917e`.
Scope: `Code/Libraries/Source/WWVegas/WW3D2/MaterialPassClassDestructor.cpp`.

Replaced the private RefCountClass declaration with the registered
`../WWLib/RefCountData.h`. Retained the empty inline destructor under the
existing size optimization, preserving the rowed destructor's code generation.
No shared header, pin, alias, source path or ledger identity changed.

Verification:

- Before and after `./build.sh <source>`: 6/6 matched rows, including both
  destructor unwind funclets; string/float/import reference checks pass.
- `find_declared_unmatched.py <source>`: all defined functions already matched.
- `header_adopt_lane.py accept --class RefCountClass <source>`: PASS;
  the owning tool retired one header-queue row.
- Before and after `link_check.py <source>`: LINKS, 167 -> 167 census-linked
  bytes, using census index c95fcfcfcd (2026-11-05 05:17).
- No data/code-identity debt keys belong to this source; its two pre-existing
  optimization hatches are unchanged. No debt is retired outside its lane.

This fixes the duplicate RefCountClass declaration prerequisite in LINK-439
for this donor only. The private MaterialPassClass owning-stage layout and
matpass's mixed compiler flags still prevent the full merge. No fresh census
or real-link result is claimed.
