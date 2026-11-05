# W3DTornadoDraw transfer: canonical DrawModule adoption

Inspected base: `643786484edb7518b60802847884cdf3f7f5b790`.
Scope: `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTornadoDraw_xfer.cpp`.

## Evidence and change

Target facts recorded in the canonical `GameLogic/Module/DrawModule.h`
establish its constructor at RVA 0x000B19A1, 12-byte layout, and transfer
slot at RVA 0x004CBF58. The rowed transfer function at 0x000D1776 calls
that base transfer and walks the list at +0x0C. Replacing the private
one-slot DrawModule and padded Rva000B19A1 intermediate with the canonical
header preserves that layout and the complete body. This does not claim a
recovered list element type; the existing list<int> view is retained.
No new row, pin, alias, hatch or source-path move.

## Verification

- `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTornadoDraw_xfer.cpp`: 1/1 matched; string, float and import reference checks pass.
- `find_declared_unmatched.py` on all three initially claimed sources: all defined functions matched; changed source checked again after editing with the same result.
- `header_adopt_lane.py accept --class DrawModule` on the changed source: PASS, retired exactly its one header queue row through the owning tool.
- Explicit `link_check.py` on the changed source: LINKS, LINKED 68 -> 68 bytes; census 2026-11-05 05:17 at c95fcfcfcd, current cached object.
- `check_csv.py`: OK, 99,455 function rows, 9,324 symbol rows, 2,268 data rows.

These are scoped byte/adoption checks and a link preview, not a new census
or real-game link/smoke result.

## Consolidation prerequisites

The initial merge dry run accepted no donors: the seed lacks a declaration
for W3DTornadoDraw::xfer and its module-data destructor loses bytes in the
composite. `tu_views.py` found differing W3DTornadoDraw bases and differing
module-data novtable attributes, and accepted no donors. The transfer source
now derives directly from canonical DrawModule, resolving its opaque-base
prerequisite without changing the seed or other vtable emitters.

Next: reconcile the seed with canonical DrawModule (its current +8
m_ropeDrawable corresponds to the canonical DrawableModule drawable storage),
and reconcile all W3DTornadoDraw vtable emitters together before adding the
seed's virtual transfer declaration. Earlier attempt 98962 records the
second vtable definer in W3DTornadoDrawDtor.cpp. Separately reconcile the
module-data ctor/dtor lifetime and novtable models. Claim those additional
sources before editing. Re-run the guarded merge only with such new evidence.
No file-count reduction or linked-byte gain is claimed.
