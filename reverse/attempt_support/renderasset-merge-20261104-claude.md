# RenderAsset.cpp consolidation (first batch)

Approved TU: `Code/Libraries/Source/WWVegas/WW3D2/RenderAsset.cpp`. The ledger
already spells the seed `renderasset.cpp`, and the merge keeps that spelling. The
TU name remains provisional, and no donor path is claimed as retail's.

The seed fix (`b2ba42fdbc`) moves `ModifiedRenderFactory::PostLoad` out of the
`namespace RenderAsset {}` block. Compose treats that block as a single
declaration chunk and hoisted it above `renderAbs` and `g_Va00DB6218`, so the seed
was rejected (C2065). After the fix, `tu_skeleton.py --merge` accepted the seed,
`Create_Render_Obj.cpp`, `Rva00136642HintInsert.cpp` and
`Rva001364ACCreateNode.cpp`, for 10 rows in retail order. It repointed 9
functions.csv and 8 tu_map.csv source cells. It also moved one
`present_unmatched` hatch line (`Rva001364F7Iter` ctor) from HintInsert to the
seed through `hatch_counters --update`, keeping the total. No TU assignment was
regenerated.

Verification:

- `./build.sh .../renderasset.cpp`: 10/10 exact. 3 funclet labels were
  renumbered and verified against the parent EH data. 2 empty-string refs and
  2 float literals were verified.
- `eh_verify.py`: EXACT 1. `check_csv.py`, `class_gate.py --staged` and
  `data_check.py --staged` are clean. Frozen-source check: all matched.
- `link_check.py` preview (census 2026-11-04 17:56 at `8c757ea0db`): LINKS,
  249 -> 803 bytes. This is a preview, not a census gain.

Audit:

- Path consumers of the three deleted donors are only the census's
  `link_status.csv` and one functions.csv notes mention. No tool, include or
  workflow consumer is affected.
- The donors have no code-identity, data, header or MS-header keys; the only
  carried key is the hatch line above.

Still separate:

- `Rva001363A1Get.cpp`, `Rva001364F7Insert.cpp` and `Rva0013657FFinish.cpp`:
  C2011/C2953. Their private `_STL::_Rb_tree_node_base` / `_Rb_global` views
  clash with the seed's real STLport tree.
- `Rva0013676DClear.cpp`: `allocator<char>` is specialized twice because of the
  bfmealloc shim.
- Refused because the rows are not approved for this TU: HouseColorTexture,
  SwitchTexturesBFME2, Rva00136794 ctor/dtor, Rva00136A21MapSubscript.
