# tcbspline vector emission cleanup

Inspected base: `108d7c58b9`. Published preview index: `85f6b7f40c`,
2026-10-29 15:08. Scope: `Code/Libraries/Source/WWVegas/WWMath/tcbspline.cpp`.
The default picker claimed its file scope and 0x000F0CF9.

## Ownership and change

The current ledger owns five vector methods here: 0x000F0CF9 (41 bytes),
0x000F0DC5 (91), 0x000F0E20 (27), 0x000F1C16 (100), and 0x000F1CA6 (81).
There are no TCBSpline3DClass spline-method or factory rows. This agrees with
the earlier LINK-004 dependency audit; this is existing donor cleanup, not
recovery of lost coverage. No row or source path moves.

Remove the nine unrowed donor methods, persistence factory, force-link helper,
and their unused includes. Instantiate DynamicVectorClass's unsigned-size
constructor instead. Its virtual tables emit the same five matched methods.
A derived type exposing the protected nested element is only a type-access
bridge, as already used by W3DVolumetricShadow.cpp; it emits no spline object.

The donor TCBClass spelling is retained solely for existing bindings. Neither
the original donor pathname nor the byte matches establish a BFME 2 spline TU
or prove that retail used a TCB element. The existing native Vector3 resize
provider and the element/owner identity still require reconciliation.

Directly instantiating the five methods was rejected: VC7.1 stopped inlining
the element equality operator in three rows. Constructor-driven emission
restores all five. No failed body remains in Code and no new marker, alias,
pin, private class layout, or register exception is added.

## Verification

- `find_declared_unmatched.py`: nine donor definitions before, clean after.
- `./build.sh tcbspline.cpp`: 5/5 rows (340 bytes), strings, floats and imports
  pass before and after. Explicit strict preparation of this source passes.
- COFF comparison: 83 COMDATs before, 19 after. All 16 common COMDAT
  fingerprints and sizes are unchanged, including all five owned bodies and
  the already-wrong base resize. The three newly emitted definitions are the
  dynamic-vector constructor, base-vector destructor, and placement new[].
- 68 external definitions disappear. In the published index, 50 had only this
  provider and no other source touches them. Of 18 shared definitions, 16
  already select another provider. Curve3DClass key-vector subscript and Count
  select this source first, but curve.cpp supplies identical fingerprints
  (`06fb30b052c2` and `0ebf5f24c0ac`). This is index-bounded evidence, not a
  current whole-tree consumer guarantee.
- The following six unchanged peers pass 35/35 function rows, two data rows,
  eight strings and five floating-point literals with `./build.sh`:
  `WWMath/curve.cpp`, `WWLib/vector_class_vector3_resize.cpp`,
  `Common/Rva000F1A32Ctor.cpp`, and the three Shadow sources
  `W3DVolumetricShadow.cpp`, `W3DShadowGeometryMesh.cpp`, and
  `W3DVolumetricShadowRenderDynamicMeshVolume.cpp`.
- Paired ordinary previews of those six peers plus tcbspline use current
  objects before and after: 5/7 LINKS and 4,773 authored bytes preserved.
  curve.cpp's existing blockers are unchanged. tcbspline loses all 15
  unresolved references and the surplus Vector3 scaling diagnostic, retaining
  only the existing resize COMDAT/selected-provider findings.

The seven-source strict-preparation attempt stopped at
W3DVolumetricShadow.cpp's existing unknown include roots. The normal byte gate
above passes, but that source has no strict reusable receipt. The scoped
tcbspline strict preparation succeeds independently.

The staged-tree outgoing batch audit is **INCONCLUSIVE**: the index predates
the base and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a
current receipt. Carry the changed provider and its affected consumers into
the next scheduled census. Do not interpret this audit as clean.

## Remaining work

`VectorClass<TCBSpline3DClass::TCBClass>::Resize` still emits the wrong body for
its existing pin at 0x000F0BF1; the current matched owner is
`VectorClass<Vector3>::Resize` in vector_class_vector3_resize.cpp. The donor's
trivial element allocation and block-copy assignment do not establish that
native contract. Reconcile the element and provider identities across the
shadow consumers, keeping all five rows, before further link repair. A cast
between the template instantiations is not that repair.

No identity debt is retired, no source-file count falls, and no census-linked
byte gain or full link closure is claimed. Scratch source/object snapshots,
removed-definition analysis, and paired previews are under
`build/tcb-link-20261029/`.
