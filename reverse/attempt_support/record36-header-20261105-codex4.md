# Rva0007BB16Record: three declaration-only header adoptions

Inspected source: b7ed32a5ae, 2026-11-05, owner yasinschroeder-codex4.
Census/index: f44cbcf5b0, 2026-11-05 15:19 UTC.

Replace private Rva0007BB16Record declarations with its registered WWLib header
in W3DShadowMapManagerUpdateShadowMap.cpp, MeshMatDescFXShaderConversion.cpp and
StlSweepW4Rva001524F9.cpp. In the mesh converter, access values through the
existing FXParameter::storage view instead of duplicating typed fields on the
canonical record. Its constructor, destructor adapter and record() stay present.
The canonical header and all provider definitions remain unchanged.

Verification:

- Normal scoped build: 27/27 matched functions, one data row, 17 funclet pins,
  61 string literals and two empty strings, six float literals verified.
- Declared-unmatched checks pass for all three changed sources; check_csv passes.
- Combined current-object link preview: three LINKS; 273 + 1,070 + 3,845 =
  5,188 census-linked bytes preserved. This is no new census measurement.
- One header_adopt_lane.py accept over the entire ten-file queued cohort:
  these three PASS and the tool retires exactly their three queue rows;
  the seven unchanged private-body sources remain queued.
- External-definition counts before/after: shadow manager 39/39, mesh converter
  92/92, fill-insert 14/14. Names agree after normalizing compiler-generated
  anonymous-namespace hashes. Only ShadowColorParameter ctor/dtor and FXParameter
  ctor/dtor/record hashes change. A scan of all 26,116 other compiled .obj files
  finds no undefined external reference to any of the five old spellings.
  No shared provider or alternatename is removed.

The seven remaining queued units contain inline constructor adapters to other
ledger owner spellings; removing them requires coordinated owner/provider work.
Their existing failures were not retried as new reconstruction attempts.
The broader LINK-002 record/helper identity reconcile remains open.
