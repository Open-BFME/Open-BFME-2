# The merge lane's wall and LINK-619 are the same body, argued about twice

Measured at `c942591408f`, 2026-11-09, as a follow-up to
`merge-blocker-remedy-is-unreachable-20261109.md`.

## The claim

Two of the project's structural lanes have a dominant blocker, and they are the
same class of body: **a function no `.cpp` defines**, written in a header and
emitted by the compiler into whichever object uses it, with the linker keeping
one copy. Which object "has" it is a fact about emission and link order, not
about where source is written. Each lane then hits that fact from its own side:

- **Consolidation.** `tu_skeleton.merge()` refuses a TU whose file holds a row
  the map places elsewhere and says "split it first". For **14 of the 24** carves
  attempted today the row has no definition span in the file, so `identify()` has
  nothing to move and the remedy cannot be performed at any price.
- **Linking.** 73 rows of `reverse/vtable_bridge_queue.tsv` are `refused`, 33 of
  them `target-not-winning-provider`: a vtable slot points at a body whose
  *first* emitter is not the object owning the ledger row, so the bridge cannot
  be retired.

## The measurement

Taking the link lane's own data and asking the merge lane's question of it. The
33 `target-not-winning-provider` slots name 58 (slot, symbol) pairs over **16
distinct blocking symbols**. For each, `tu_skeleton.identify()` was run over the
definition spans of the source that owns the ledger row -- the strict predicate
the carve uses, not `spells_definition`:

| | symbols |
| --- | ---: |
| the owning source has **no definition span** for it | **15** of 16 |
| the owning source has one | 1 |
| the name is a template instance (`TEMPLATE_INSTANCE`) | 9 of 16 |
| a single ledger row at the address (not an ICF fold) | 16 of 16 |

The 15, with their owner and the object that emits first:

| symbol | ledger owner | first emitter |
| --- | --- | --- |
| `VectorClass<int>::??_G` | vector_class_resize.cpp | Render2DSentenceAllocateSurfaceBFME2 |
| `money_get<...>::do_get` (string) | stlport_narrow_money_get_string.cpp | ..._get |
| `money_get<...>::do_get` (long double) | stlport_narrow_money_get_long_double.cpp | ..._get |
| `basic_ios<char>::??_G` | stlport_narrow_ostream.cpp | Rva003A5DA0Write |
| `basic_filebuf<char>::seekoff` | stlport_narrow_ifstream.cpp | ..._filebuf |
| `basic_filebuf<char>::seekpos` | stlport_narrow_ifstream.cpp | FstreamDefaultProtectionNameCtors |
| `RenderObjClass::Get_Bounding_Sphere` | hlod.cpp | BaseHeightMapConstructor |
| `RenderObjClass::Get_Bounding_Box` | hlod.cpp | BaseHeightMapConstructor |
| `W3DShroudMaterialPassClass::??_G` | OpaqueScalarDeletingDtorsB08.cpp | W3DScene |
| `VectorClass<Vector3>::??_G` | vector_class_vector3_ctor.cpp | Rva007B7280Siblings |
| `VectorClass<Vector3>::Resize` | vector_class_vector3_resize.cpp | ..._ctor |
| `VectorClass<StringClass>::??_G` | dx8wrapper.cpp | INIStatsRecordTextures |
| `Bucket::??_G` | NameKeyGenerator.cpp | BucketDtor |
| `Rva005E3AE1::??_G` | SBServer.cpp | ..._dtor |
| `MeshGeometryClass::Get_Vertex_Array` | meshgeometry.cpp | W3DBridgeBuffer |

Three shapes, and every one of them is header-resident: an **inline member**
(`Get_Bounding_Sphere`, `Get_Vertex_Array`, `Resize`, `seekoff`, `seekpos`), a
**compiler-generated scalar deleting destructor** (`??_G`, eight of the fifteen),
or an **implicit template instantiation** (the `VectorClass<T>` and STLport
members). The one exception, `Rva0040DB52::??_G`, does have a definition span in
`Rva0040DB52Dtor.cpp` and is a different problem.

The sharpest way to put it: for these rows the ledger's `source` column names an
*emitter*, not an author. **Neither** the owning file nor the first emitter
contains the body. The merge lane is told to carve a body out of a file that
never held one; the link lane is told the wrong object emitted a body no object
was ever the home of.

## What this does not claim

- **Not that the 3,877 `bridged` rows are the same.** Only the 33
  `target-not-winning-provider` refusals were classified; `bridge-retirement`
  rows carry no provider blocking record and were not examined. The claim covers
  16 symbols, not the whole bridge population.
- **Not that this is ICF folding.** All 16 addresses carry exactly one ledger
  row. In the merge lane several blockers *are* ICF folds (0x002888D4 has 13
  ledger rows across as many files), so the shared property is "no source spells
  it", not "folded". An earlier guess of mine that the link cases would also be
  folds was wrong and is corrected here.
- **Not a proposed fix.** Both lanes have long, specific prior attempts recorded
  against these symbols (LINK-619 at `t=1..75` across several models). Nothing
  here says any of them was wrong; it says they are one problem counted twice.
- **Not a claim about cause in retail.** That retail's linker kept a given copy
  is an observation. Why BFME 2's build emits a copy in a particular object is a
  per-unit question the existing LINK-619 evidence packets address.

## Why it is worth recording

The two lanes are costed separately today -- consolidation by donor files
(1,513 behind the pre-compile blocker) and linking by bridge bytes -- so the same
underlying question is paid for twice and prioritised twice. It also explains a
pattern in the link queue that otherwise looks like coincidence: several of its
largest items say in their own recorded verdicts that they are waiting on TU
approval or a TU merge (`stlport_classic_locale.cpp`: "no legal row move. Waits
on `_STL.cpp` TU approval or STLport TU merge"; `BaseHeightMapConstructor.cpp`:
"neither address has an approved TU, so nothing in this file clears it"). Those
are not incidental cross-references. They are the link lane asking the
consolidation lane to decide who owns a header-resident body.

The tree already has a deliberate technique for steering this, which is worth
knowing before anyone designs a fix: `mesh.cpp` holds
`_bfmeVisTwoSidedInlineAnchor`, marked `absent-from-retail`, whose whole body is
two calls, present so the compiler emits those inline bodies into that object.
Emission placement is already something the project controls by hand in at least
one place.

## Method

- `reverse/vtable_bridge_queue.tsv` at the real link
  `a7a3c4d962bed43cfc66f94cfb06a699434801a2`; the `evidence` column is JSON
  carrying each blocked slot's providers, first object and ledger object.
- `tu_skeleton.identify()` and `def_spans()`/`span_scopes()` for the definition
  test, so both lanes are judged by the same predicate.
- Windows object paths in the queue were mapped back to tree paths before
  reading any file.
