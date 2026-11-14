# matrix4d.cpp: eight retail exports lost to the Coord3D adoption, 2026-11-14

Base `729b351200`; real link measured at `90f2c095cd`. No source, ledger or tool change is kept.

## What is wrong

`reverse/exit_link_blockers.tsv` lists `Code/Libraries/Source/WWVegas/WWMath/matrix4d.cpp` with 8 missing names.
23b22e04f4 ("Adopt canonical Coord3D in 1 more unit") replaced the unit's private `class Coord3D` with the canonical
`struct` and respelled these rows from `V` to `U`:

| RVA | retail export (V) |
|---|---|
| 0x00005BB8 | `??0Matrix4D@@QAE@ABVCoord3D@@@Z` |
| 0x00005BB8 | `?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@@Z` |
| 0x0009314A | `?GetTranslationVector@Matrix4D@@QBEAAVCoord3D@@AAV2@@Z` |
| 0x00004BBF | `?GetXVector@Matrix4D@@QBEAAVCoord3D@@AAV2@@Z` |
| 0x00004BD6 | `?GetYVector@Matrix4D@@QBEAAVCoord3D@@AAV2@@Z` |
| 0x00004BEE | `?GetZVector@Matrix4D@@QBEAAVCoord3D@@AAV2@@Z` |
| 0x00004753 | `?RotateCoord@Matrix4D@@QAEAAVCoord3D@@ABV2@AAV2@@Z` |
| 0x000046BD | `?TransformCoord@Matrix4D@@QAEAAVCoord3D@@ABV2@AAV2@@Z` |

`reverse/exports.csv` holds 10 `Matrix4D@@...VCoord3D` names and no `U` one. exit.exp references the export spelling,
and no object defines it any more. The adoption commit's own closure check ("no name newly undefined") reads link
objects and did not see the export file.

## What was tried

`git revert -n 23b22e04f4`, keeping the other units' refreshed queue rows and restoring only this unit's.

- `./build.sh Code/Libraries/Source/WWVegas/WWMath/matrix4d.cpp`: 24/24 matched.
- `tools/link_check.py` on the unit: LINKS, 4,707 -> 4,707 B (index 29dfc2e011).
- Consumers of the `U` names: none. `class Matrix4D` is declared only here and in Snapshot.cpp (axis-angle
  constructor and `Set` only); the census index's `referenced` set holds the eight `V` names and no `U` one.
- Pre-commit: `PRE-COMMIT FAILED: new private copy of a class with a shared header` (class gate). Not worked
  around; the tree was restored and the unit rebuilt 24/24 on master's source.

## Next step

One of, by the class owner or a maintainer:

1. The class-key flip (`header_adopt_lane.py rekey --class Coord3D --key class`), which makes these rows the exports.
2. Option B for these eight, as already done for the two axis-angle exports: `pin_admission.py --alias`, counted.
3. A gate-admitted `class` view for this unit until the flip.

Separately, for a tooling seat: `header_adopt_lane.ledger_renames` should refuse a rename whose old name is a retail
export at that row's address. Without it the lane repeats this on its next retry of any unit holding exported
Coord3D names (coord3d.cpp and region.cpp are queued).

Not measured: a real link with the revert applied.

## Status at handoff

This seat's operator chose route 2 (the eight `pin_admission.py --alias` twins). It was not applied: after the blocked
record the unit's claim was released, and nleigh@Nathans-PC drew `file:.../WWMath/matrix4d.cpp` and 0x0000401C from
the queue before it could be retaken. The aliases would be, for each row above, export (V) -> the row's current
`U` name at the same address; `?Set@Matrix4D@@QAEAAV1@ABUCoord3D@@@Z` is the ICF twin at 0x00005BB8.
