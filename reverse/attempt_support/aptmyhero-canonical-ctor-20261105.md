# AptMyHero canonical constructor adoption (2026-11-05)

Seat `yasinschroeder-codexb`, model `gpt-6.1-sol`, base `c756ff3c6b`.
Supersedes the constructor prerequisite in
`aptmyhero-header-adoption-20261104.md`; the other two units remain queued.

## Change and evidence

The canonical header now carries the constructor's existing STLport vector
members at +0x15C and +0x174, and its two-float MyHeroViewRange at +0x168.
These are the existing matched constructor's type spellings, not newly
recovered donor names. The 0x190 extent check and CreateAHeroData base remain.
Scalar initialization of the two floats gives a different instruction order;
the original range constructor preserves retail's shared receiver and stores.

AptMyHeroCtor.cpp includes the canonical header and no longer declares a
private AptMyHero or private STLport implementation. Existing external vector
destructors remain declarations in this TU. Instantiating their definitions
instead introduced conflicting COMDAT bodies; using the STLport static-library
configuration also avoids a new imported node-allocator dependency. Neither
trial's link failure is retained. Both existing CreateAHeroData alternatenames
remain: no link-wide alias was removed.

The nine already-adopted consumers retain their layouts. Sources without an
STLport marker receive it for the canonical header's vector include. The
camera body accesses the range's two floats, and GetObjectInfo takes the
address of the now-typed vector while retaining its existing BfmePod8 view.
No function, data, pin or hatch row was added, and no source was moved.

## Verification

- `./build.sh` on the constructor and all nine direct consumers: 146/146
  matched rows, 64 string literals, two float literals and nine named imports.
  The final constructor-only rerun after destructor declarations/static-library
  flags passes 21/21 rows and 13 literals; EH parent evidence resolves its
  renumbered funclet labels without a ledger edit.
- `find_declared_unmatched.py` before and after: all ten sources pass.
- `link_check.py` with the same ten sources, index 2026-11-05 05:17 at
  `c95fcfcfcd`: ten of ten LINKS, 8,282 -> 8,282 census-linked bytes.
  This is a prediction preserving the census, not a new linking measurement.
- `header_adopt_lane.py accept --class AptMyHero` on AptMyHeroCtor.cpp:
  PASS; exactly one header-queue row retired by the acceptance tool.

## Remaining prerequisites

AptMyHero.cpp and AptMyHero_Unresolved.cpp retain their private base and
manager declarations and BfmePod8Vector views. Their CreateAHeroData and
CreateAHeroManager adoptions require separate claims and reconciliation;
see the earlier handoff for offset/token collisions. The canonical vector
layout is now available, but this change does not claim those units adopted.
LINK-177's repaired slot-3 identity and aliases are preserved.
