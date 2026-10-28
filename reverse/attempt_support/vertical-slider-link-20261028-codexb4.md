# Vertical slider renderer dependency cleanup

Inspected base: `66ae34555a`. Seat: yasinschroeder-codexb4. The default
picker claimed 0x0009DC22 and the W3DVerticalSlider.cpp file scope. The BFME 1
freshness receipt is dated 2026-10-26 and verifies donor revision
`de077dd5dd8339716a6abe453a1d81dfdf77e651`; no freshness refresh is due.
The current pinned reference is `0424131c818fba6641613ef826222ecf30845025`.
The current published preview index is `d92e7e6635`, 2026-10-28 15:58.

The existing source passes all 16 rows but fails ordinary preview only on
the selected `??_EPendingSurfaceStruct@Render2DSentenceClass@@QAEPAXI@Z`.
This repeats the horizontal slider's documented LINK-132 consumer cause.
The donor W3DGadget header includes W3DGameWindow, which imports the renderer.
These callbacks use GameWindow and the header's `(1.0f)` border-width macro;
neither callback uses the W3DGameWindow renderer. Include GameWindow directly
and retain that constant locally. No body, shared header, compiler option,
ledger, pin, name or source path changes.

The donor include graph and macro explain the dependency; the BFME 2 byte
checks establish preservation of the target bodies. This makes no additional
donor-name, layout or original-source claim.

Verification:

- `./build.sh` passes 16/16 function rows, with zero string, float and named
  import literals to verify. Frozen-file checks pass before and after.
- Strict current-receipt preparation passes for this explicit unit. EH
  verification reports no EH-bearing rows and no missing object. Scoped
  data checking reports zero findings.
- The object loses only the PendingSurfaceStruct vector deleting destructor
  and the compiler's vector-construction iterator. All 33 retained external
  COMDAT byte-and-symbolic-relocation fingerprints are unchanged. No external
  definition or dependency is added; four unused dependencies disappear.
  Both objects have no weak aliases. [Object comparison](vertical-slider-object-20261028-codexb4.json).
- Same-index ordinary preview changes from blocked to LINKS for 844 authored
  nonpadding bytes. This is a preview, not a census-linked gain or runtime
  result. LINK-132/LINK-133 global selection remains open.

Scratch source/object snapshots: `build/vertical-slider-link-20261028/`.
No source path moves or protected-register changes occur; the existing
folded-draw marker and hatch count are unchanged.

The outgoing audit of staged tree `0c475b9c75f6c5464f0df183329016a97d7089da` against `66ae34555a` is
INCONCLUSIVE: index `d92e7e6635` predates the outgoing base, and affected
consumer `Code/GameEngine/Source/Common/AIHarvestPrepareSiteState.cpp` lacks
a current receipt. No complete consumer clearance is established. Carry the
removed-helper scope and affected consumers into the next scheduled census.
Converged-data enforcement separately checks eleven addresses with no second
names or unjudged rows. No census, smoke or ownership measurement is run.
