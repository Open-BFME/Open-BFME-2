# Player donor-body cleanup

The served Player.cpp owns 12 matched functions (112 bytes, all relocation-free)
and the native TheTeamFactory global at A028BC. The latter has 73 known address
references and stays in place. Player is canonical; no replacement private
class, header or ABI is introduced. Existing header-accessor and ScienceType
copy emissions must remain available throughout this pass.

## Science-points donor body

The unrowed addSciencePurchasePoints body introduces two unresolved invented
helper names. It has no runtime/data incoming relocation in the original object
and no outside incoming edge in published index86db074988. The old ILT comment
is a donor assertion, not BFME2 target evidence. Removing this unverified body
and that comment preserves all 12 native functions and the owned global.

The original-source control has 410 external code definitions, the corrected
object 409. The only removed definition is addSciencePurchasePoints; every
retained complete body and symbolic relocation is identical, and nothing is
added. Normal/frozen verification passes. The unit still does not link: its
other donor methods, two wrong-selected copies and additional STL imports
remain. This is cleanup, with no authored-byte or census gain claimed.

## Wrong selected upgrade-query copy

The unrowed pointer-overload hasUpgradeComplete body is removed separately.
Its code has no runtime/data incoming edge in this object or outside incoming
edge in the published index. The census certifies this copy as non-retail; the
current preview no longer selects it. The existing native provider and pins
are untouched. All 12 functions and the global still verify, and all 408
retained complete code definitions/relocations are identical to the preceding
409-definition control. Only the wrong copy disappears; nothing is added.

The owning hatch counter retires one of this source's two same-label
present-unmatched entries. It also synchronizes an already removed alias from
upstream ffdd9456a9 in FakePathfindPortalBehaviourDtor.cpp; that extra shrink is
upstream work, not credit for this pass. No baseline key is hand-added.

The code-identity hook reports existing shadow divergences in other retained
helpers. Whole-object controls show they are unchanged, and their register is
not edited. The remaining science-vector copy and donor imports still block
the unit; no complete link clearance is claimed.

The first two-removal batch passes strict preparation of all 12 function rows
and the one owned data row. Source paths, six admitted aliases and the canonical
class header are unchanged. Its strict receipt and output are retained.

## Relation-map donor CRC

The obsolete unrowed PlayerRelationMap::crc body is removed independently.
The native four-slot BFDD90 table has the deleting destructor, loadPostProcess,
name getter and xfer providers; no CRC slot is present. The old empty CRC also
has no incoming runtime/data edge locally or outside incoming edge in the
published index. The rowed loadPostProcess is retained.

All 12 functions and the global still verify. Only the CRC definition is lost:
407 complete code definitions/relocations remain identical to the preceding
408-definition control. The owning counter retires its one placeholder hatch.
The preview has no new unresolved CRC and retains the remaining blockers.
